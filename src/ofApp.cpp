#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// Deployment app version
#ifdef OFWORKS_DEMO_APP_DEPLOY
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetLogLevel("SurfingPresetsLite", OF_LOG_SILENT);
#endif

	ofLogNotice("ofApp") << "setup()";

	//--

	// Window

	centerWindow();

	//--

	// Frame rate

	float fps = 60.f;
	ofSetFrameRate(fps);

	//--

	// Parameters

	bBgGradient.set("Background Gradient", false);
	bMouseBrowsing.set("Mouse Browsing", true);
	bTweeningMode.set("Mode Tweening", true);

	//--

	// Dist Mode

	bHelpDist.set("Help Dist", true);

	// False: Advanced Mode. True: Distribution (User) Mode
	bDistMode.set("Dist mode", true);
	e_bDistMode = bDistMode.newListener([this](bool & v) {
		ofLogNotice("ofApp") << "bDistMode: " << v;
		// Workflow ui
		if (bDistMode.get()) {
			ot.bKeys = false;
		} else {
		}
	});

	// Window Full Screen / default size
	bFullScreen.set("Full Screen", false);
	e_bFullScreen = bFullScreen.newListener([this](bool & v) {
		ofLogNotice("ofApp") << "bFullScreen: " << v;
		if (bFullScreen.get()) {
			fullScreenWindow();
		} else {
			resetWindow();
		}
	});

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
	paramsScene.add(bFullScreen);
	paramsScene.add(bTweeningMode);
	paramsScene.add(bMouseBrowsing);

	pm.gui.add(paramsScene);

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
	std::string s3 = "";
	// Debug info
	if (ot.bDebug) {
		s1 = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
		if (pm.isChangedIndex()) {
			s2 = "PRESET " + ofToString(pm.getPresetIndex());
		}
		s3 = ofToString(ofGetWindowWidth()) + "x" + ofToString(ofGetWindowHeight());
		s = "     " + s1 + "     " + s3 + "     " + s2;
	}
	string wt = ofToString(OFWORKS_DEMO_APP_TITLE) + s;
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Background
	if (bBgGradient) {
		ofxDrawBgGradient();
	} else {
		ofClear(20, 255);
	}

	// Organic Text
	ot.draw();

	if (!bDistMode.get()) {
		// Presets Manager
		pm.drawGui();
		if (pm.bGui) ot.drawGui();
	} else {
		// Draw Help Dist
		if (bHelpDist) drawHelpDist();
	}
}

//--------------------------------------------------------------
void ofApp::drawHelpDist() {
	// Help Dist info
	std::string s = "";
	s += "ORGANIC";
	s += "\n";
	s += "TEXT";
	s += "\n\n";
	s += "H              Help";
	s += "\n\n";
	s += "KIT            " + ofToString(pm.getKitName());
	s += "\n\n";
	s += "PRESET         " + ofToString(pm.getPresetIndex()) + " / " + ofToString(pm.getPresetIndexLast());
	s += "\n";
	s += "               " + pm.getPresetFileName();
	s += "\n\n";
	s += "SPACE          Next";
	s += "\n\n";
	if (bMouseBrowsing) {
		s += "MOUSE CLICK    Prev/Next";
		s += "\n";
		if (ofGetMouseX() < ofGetWidth() / 2)
			s += " *Left/Right   Half Screen";
		else
			s += "  Left/Right*  Half Screen";
		s += "\n";
		s += "  Left/Right   Mouse Button";
	}
	s += "\n\n";
	s += "ENTER          Advanced";
	s += "\n\n";
	s += "WINDOW";
	s += "\n";
	s += "F              " + ofToString(bFullScreen ? "Reset" : "Full Screen");
	s += "\n";
	s += "C              Center";
	s += "\n";
	ofxSurfing::ofDrawBitmapStringBox(s, ofxSurfing::SURFING_LAYOUT_BOTTOM_CENTER);
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	const auto k = eventArgs.key;
	ofLogNotice("ofApp") << "keyPressed(): " << char(k);

	//--

	// Full screen window
	if (k == 'f' || k == 'F') {
		bFullScreen.set(!bFullScreen.get());
		return;
	}
	// Center window
	if (k == 'c' || k == 'C') {
		centerWindow();
		return;
	}

	//--

	// Dist Mode
	if (k == OF_KEY_RETURN) {
		bDistMode.set(!bDistMode.get());
		return;
	}

	// Next preset
	if (k == OF_KEY_SPACE) {
		nextScene();
		return;
	}

	if (bDistMode.get()) {
		// Help Dist
		if (k == 'h' || k == 'H') {
			bHelpDist.set(!bHelpDist.get());
			return;
		}
	}

	else {
		ot.keyPressed(eventArgs);

		//--

		// Debug mode
		if (k == 'd' || k == 'D') {
			if (!ot.bKeys) ot.bDebug = !ot.bDebug;
			return;
		}
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
		nextScene(browseDirection);
		return;
	}
}

//--

// Window management

//--------------------------------------------------------------
void ofApp::centerWindow() {
	ofLogNotice("ofApp") << "centerWindow()";

	int w = ofGetWindowWidth();
	int h = ofGetWindowHeight();
	ofSetWindowPosition(ofGetScreenWidth() * 0.5f - w * 0.5f, ofGetScreenHeight() * 0.5f - h * 0.5f);
}

//--------------------------------------------------------------
void ofApp::fullScreenWindow() { // Set window full screen
	ofLogNotice("ofApp") << "resetWindowFullScreen()";

	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void ofApp::resetWindow() { // Set window reset
	ofLogNotice("ofApp") << "resetWindow()";

	int w = OFWORKS_DEMO_APP_WIDTH;
	int h = OFWORKS_DEMO_APP_HEIGHT;

	ofSetWindowShape(w, h);
	ofSetWindowPosition(ofGetScreenWidth() / 2 - w / 2, ofGetScreenHeight() / 2 - h / 2);
}

//----

// Scenes tweener

//--------------------------------------------------------------
void ofApp::setupTweensCallbacks() {
	ofLogNotice("ofApp") << "setupTweensCallbacks()";

	// Setup tween callbacks to be called when completed
	// Custom workflow for combine with/as preset transitions

	// writeIn tween completed
	// Empty space: not drawing nothing on complete
	// In = 1, Out = 1
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
void ofApp::nextScene(browseDirection_ bd) {
	ofLogNotice("ofApp") << "nextScene() browseDirection:" << bd;

	browseDirection = bd;
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

//--

//--------------------------------------------------------------
void ofApp::exit() {
	ofLogNotice("ofApp") << "exit()";

	ot.exit();
}
