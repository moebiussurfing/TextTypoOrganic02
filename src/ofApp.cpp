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
	paramsScene.add(bMouseBrowsing);
	pm.gui.add(paramsScene);

	ot.refreshGuiPanel(pm.guiParams);

	//--

	setupTweensCallbacks();

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
	std::string u = "    "; // Union spacing
	std::string s = "";
	s += "ORGANIC";
	s += "\n";
	s += "TEXT";
	s += "\n";
	s += "\n";
	s += "H         " + u + "Help";
	s += "\n";
	s += "\n";
	s += "SPACE     " + u + "Next";
	s += "\n";
	s += "\n";
	s += "MouseClick" + u + "Previous/Next";
	s += "\n";
	s += "   Left/Right Half Screen";
	s += "\n";
	s += "   Left/Right Mouse Button";
	s += "\n";
	s += "\n";
	s += "ENTER     " + u + "Advanced";
	s += "\n";
	s += "\n";
	s += "WINDOW    ";
	s += "\n";
	s += "F         " + u + "Full Screen";
	s += "\n";
	s += "C         " + u + "Center";
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
		fullScreenWindow();
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

//----

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
