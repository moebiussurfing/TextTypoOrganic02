#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Deploy

	#ifdef OFWORKS_DEMO_APP_DEPLOY
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetLogLevel("SurfingPresetsLite", OF_LOG_SILENT);
	#endif
	
	ofLogNotice("ofApp") << "setup()";

	//--

	// Window

#if 0
	resetWindowCustom();
#else
	// Move window to my FHD left monitor
	int h_ = 40;
	ofSetWindowPosition(-1920, h_);
	int w_ = 1800;
	ofSetWindowShape(w_, w_ * (9.f / 16.f));
	#endif
	
	e_vResetWindow = vResetWindow.newListener([this](void) { resetWindowCustom(); });

	float fps = 60.f;
	ofSetFrameRate(fps);

	//--
	
	// Parameters

	bBgGradient.set("Background Gradient", false);
	bMouseBrowsing.set("Mouse Browsing", true);
	bTweeningMode.set("Mode Tweening", true);

	//--

	// Organic Text

	ot.setup(fps);
	ot.gui.setPosition(ofGetWidth() - ot.gui.getWidth() - 5, 5);

	//--

	// Presets Manager

	pm.setup(ot.paramsPreset);
	pm.gui.add(ot.bGui);

	paramsScene.setName("Scene");
	paramsScene.add(bBgGradient);
	paramsScene.add(bTweeningMode);
	
	pm.gui.add(paramsScene);
	pm.gui.add(vResetWindow);

	ot.refreshGuiPanel(pm.guiParams);

	//--

	setupTweensCallbacks();
}

//--------------------------------------------------------------
void ofApp::update() {
	// Performance
	fps = ofGetFrameRate();
	frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);

	// Window title
	std::string s = "";
	std::string s1 = "";
	static std::string s2 = "";
	if (ot.bDebug) {
		s1 = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
		if (pm.isChangedIndex()) {
			s2 = "PRESET " + ofToString(pm.getPresetIndex());
		}
		s = "\t\t" + s1 + "\t\t" + s2;
	}
	string wt = ofToString(SURFING_APP_TITLE) + s;
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Background
	if (bBgGradient){
		ofxDrawBgGradient(0, 40, OF_GRADIENT_CIRCULAR); // center too black
		// ofxDrawBgGradient(40, 10, OF_GRADIENT_CIRCULAR); // +
		// ofxDrawBgGradient(40, 0, OF_GRADIENT_CIRCULAR); // +
	} else {
		ofClear(20);
	}

	// Organic Text
	ot.draw();

	// Presets Manager
	pm.drawGui();
	if (pm.bGui) ot.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	const auto k = eventArgs.key;
	ofLogNotice("ofApp") << "keyPressed(): " << char(k);

	ot.keyPressed(eventArgs);

	//--

	// Debug mode
	if (k == 'd') {
		if (!ot.bKeys) ot.bDebug = !ot.bDebug;
		return;
	}

	//--

	// User workflow: window shape and edit/advanced mode

	if (k == 'w') {
		resetWindowCustom();
		if (pm.bGui) pm.bGui = false;
		return;
	}
	if (k == OF_KEY_SPACE) {
		bWindowFullScreen = !bWindowFullScreen;
		if (pm.bGui) pm.bGui = false;
		if (bWindowFullScreen) {
			resetWindowFullScreen();
		} else {
			resetWindowCustom();
		}
		return;
	}
	if (k == 'e') {
		resetWindowFullScreen();
		if (!pm.bGui) pm.bGui = true;
		return;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofLogNotice("ofApp") << "mousePressed(): " << x << "," << y << " " << button;

	// Get browse direction from mouse click x position
	// (left/reight half = previous/next)
	if (bMouseBrowsing) {
		if (ot.isTweening()) return; // Skip mouse clicks until running tweening ends.
		if (x < ofGetWidth() / 2) {
			if (button == 0)
				browseDirection = BROWSE_PREVIOUS;
			else
				browseDirection = BROWSE_NEXT;
		} else {
			if (button == 2)
				browseDirection = BROWSE_PREVIOUS;
			else
				browseDirection = BROWSE_NEXT;
		}
		nextScene();
		return;
	}
}

//--

//--------------------------------------------------------------
void ofApp::resetWindowCustom() { // Set window size and centered
	ofLogNotice("ofApp") << "resetWindowCustom()";

	const int w = OFWORKS_DEMO_APP_WIDTH; // from organicText.h
	const int h = OFWORKS_DEMO_APP_HEIGHT;

	// BUG: For Windows: 2 steps: do twice to fix bug multi monitor un centered well
	for (int i = 0; i < 2; i++) {
		ofSetWindowShape(w, h);
		ofSetWindowPosition(ofGetScreenWidth() * 0.5f - w * 0.5f, ofGetScreenHeight() * 0.5f - h * 0.5f);
	}
}

//--------------------------------------------------------------
void ofApp::resetWindowFullScreen() { // Set window full screen
	ofLogNotice("ofApp") << "resetWindowFullScreen()";

	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);
}

//--

//--------------------------------------------------------------
void ofApp::exit() {
	ofLogNotice("ofApp") << "exit()";
	ot.exit();
}

//----

//--------------------------------------------------------------
void ofApp::setupTweensCallbacks() {
	ofLogNotice("ofApp") << "setupTweensCallbacks()";

	// Setup tween callbacks to be called when completed
	// Custom workflow for combine with/as preset transitions

	// writeIn tween completed
	// Empty space: not drawing nothing on complete
	// In=1, Out=1
	ot.setOnCompleteWriteIn([this]() {
		ofLogNotice("ofApp") << "writeIn completed. (Empty space: no draw)";
		if (browseDirection == BROWSE_NEXT)
			pm.doLoadNext(); // Load next preset
		else
			pm.doLoadPrevious(); // Load previous preset
		ot.writeOut(); // Animate draw tween
	});

	// writeOut tween completed
	ot.setOnCompleteWriteOut([this]() {
		ofLogNotice("ofApp") << "writeOut completed. (Full range draw)";
	});
}

//--------------------------------------------------------------
void ofApp::nextScene() {
	ofLogNotice("ofApp") << "nextScene()";
	if (bTweeningMode)
		ot.writeIn();
	else {
		if (browseDirection == BROWSE_NEXT) {
			pm.doLoadNext();
		} else {
			pm.doLoadPrevious();
		}
	}
}
