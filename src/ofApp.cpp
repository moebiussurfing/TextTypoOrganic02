#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetLogLevel("SurfingPresetsLite", OF_LOG_SILENT);

	ofLogNotice("ofApp") << "setup()";

	float fps = 60.f;
	ofSetFrameRate(fps);

	bMouseBrowsing.set("Mouse Browsing", true);
	bTweeningMode.set("Mode Tweening", true);

	// Window
#if 0
	resetWindowCustom();
#else
	// move window to left monitor
	int h_ = 28;
	ofSetWindowShape(1920, 1080 - h_);
	ofSetWindowPosition(-1920, h_);
#endif

	e_vResetWindow = vResetWindow.newListener([this](void) { resetWindowCustom(); });

	//--

	// Organic Text
	t.setup(fps);
	t.gui.setPosition(ofGetWidth() - t.gui.getWidth() - 5, 5);

	//--

	// Presets Manager
	p.setup(t.paramsPreset);
	p.gui.add(t.bGui);

	paramsScene.setName("Scene");
	paramsScene.add(bMouseBrowsing);
	paramsScene.add(bTweeningMode);
	p.gui.add(paramsScene);

	p.gui.add(vResetWindow);

	t.refreshGuiPanel(p.guiParams);

	//--

	setupTweensCallbacks();
}

//--------------------------------------------------------------
void ofApp::setupTweensCallbacks() {
	ofLogNotice("ofApp") << "setupTweensCallbacks()";

	// Setup tween callbacks to be called when completed
	// Custom workflow for combine with/as preset transitions

	// writeIn tween completed
	// Empty space: not drawing nothing on complete
	//  In=1, Out=1
	t.setOnCompleteWriteIn([this]() {
		ofLogNotice("ofApp") << "writeIn completed. (Empty space: no draw)";
		if (browseDirection == BROWSE_NEXT)
			p.doLoadNext(); // Load next preset
		else
			p.doLoadPrevious(); // Load previous preset
		t.writeOut(); // Animate draw tween
	});

	// writeOut tween completed
	t.setOnCompleteWriteOut([this]() {
		ofLogNotice("ofApp") << "writeOut completed. (Full range draw)";
	});
}

//--------------------------------------------------------------
void ofApp::update() {
	fps = ofGetFrameRate();
	frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);

	// Window title
	std::string s = "";
	std::string s1 = "";
	std::string s2 = "";
	if (t.bDebug) {
		s1 = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
		if (p.isChangedIndex()) {
			s2 = "PRESET " + ofToString(p.getPresetIndex());
		}
		s = "\t\t" + s1 + "\t\t" + s2;
	}
	string wt = ofToString(SURFING_APP_TITLE) + s;
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Background
	//ofxDrawBgGradient();//70,10
	//ofxDrawBgGradient(70, 10, OF_GRADIENT_CIRCULAR);
	//ofxDrawBgGradient(10, 70, OF_GRADIENT_CIRCULAR);
	//ofxDrawBgGradient(40, 10, OF_GRADIENT_CIRCULAR);//++
	//ofxDrawBgGradient(0, 40, OF_GRADIENT_CIRCULAR);//center too black
	//ofxDrawBgGradient(40, 0, OF_GRADIENT_CIRCULAR);//+++
	//ofClear(30);
	ofClear(20);

	// Organic Text
	t.draw();

	// Presets Manager
	p.drawGui();
	if (p.bGui) t.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	const auto k = eventArgs.key;
	ofLogNotice("ofApp") << "keyPressed(): " << char(k);

	t.keyPressed(eventArgs);

	//--

	// Debug mode
	if (k == 'd') {
		if (!t.bKeys) t.bDebug = !t.bDebug;
		return;
	}

	//--

	// User workflow: window and edit/advanced mode
	if (k == 'w') {
		resetWindowCustom();
		if (p.bGui) p.bGui = false;
		return;
	}
	if (k == OF_KEY_SPACE) {
		bWindowFullScreen = !bWindowFullScreen;
		if (p.bGui) p.bGui = false;
		if (bWindowFullScreen) {
			resetWindowFullScreen();
		} else {
			resetWindowCustom();
		}
		return;
	}
	if (k == 'e') {
		resetWindowFullScreen();
		if (!p.bGui) p.bGui = true;
		return;
	}
}

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

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofLogNotice("ofApp") << "mousePressed(): " << x << "," << y << " " << button;

	// Get browse direction from mouse click x position (left/reight half = previous/next)
	if (button == 0 && bMouseBrowsing) {
		if (x < ofGetWidth() / 2) {
			browseDirection = BROWSE_PREVIOUS;
		} else {
			browseDirection = BROWSE_NEXT;
		}
		nextScene();
		return;
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofLogNotice("ofApp") << "exit()";
	t.exit();
}

//--

//--------------------------------------------------------------
void ofApp::nextScene() {
	ofLogNotice("ofApp") << "nextScene()";
	if (bTweeningMode)
		t.writeIn();
	else {
		if (browseDirection == BROWSE_NEXT) {
			p.doLoadNext();
		} else {
			p.doLoadPrevious();
		}
	}
}
