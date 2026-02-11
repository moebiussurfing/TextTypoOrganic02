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
	// float fps = 120.f;
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
		// Workflow ui to improve user experience
		if (bDistMode.get()) {
			ot.bKeys = false;
		} else {
			ot.bGui.set(true);
		}
	});

	// Window Full Screen / default size
	bFullScreen.set("Full Screen", false);
	e_bFullScreen = bFullScreen.newListener([this](bool & v) {
		ofLogNotice("ofApp") << "bFullScreen: " << v;
		if (bFullScreen.get()) {
			//fullScreenWindow();
			ofSetFullscreen(true);
		} else {
			resetWindow();
			ofSetFullscreen(false);
		}
	});

	//--

	// Organic Text Session

	ot.setup(fps);
	// ot.gui.setPosition(ofGetWidth() - ot.gui.getWidth() - 5, 5);//top right

	//--

	// Presets Manager

	pm.setup(ot.paramsPreset);
	pm.gui.add(ot.bGui);
	ot.refreshGuiPanel(pm.guiParams);

	//--

	// Gui Scene Slideshow
	paramsScene.setName("Scene");

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	paramsOfApp.add(bGui_Fx);
#endif

	paramsScene.add(bBgGradient);
	paramsScene.add(bFullScreen);
	paramsScene.add(bTweeningMode);
	paramsScene.add(bMouseBrowsing);

	guiScene.setup("Scene Slideshow");

	guiScene.add(paramsScene);

	// Refresh
	slideshow.setup(&ot, [this]() { nextScene(); });
	slideshow.setMouseIdleChecker([this]() { return isMouseIdle(); });
	guiScene.add(slideshow.getParameters());

	// Collapse scene group
	guiScene.getGroup(paramsScene.getName()).minimize();
	guiScene.getGroup(paramsScene.getName()).minimizeAll();

	// Collapse slideshow groups using their declared names
	auto & slideshowGroup = guiScene.getGroup(slideshow.getParameters().getName());
	slideshowGroup.minimize();
	slideshowGroup.minimizeAll();
	auto & feedbackGroup = slideshowGroup.getGroup(slideshow.getFeedbackParameters().getName());
	feedbackGroup.minimize();
	feedbackGroup.minimizeAll();

	//--

	setupTweensCallbacks();

	//--

	// App session settings
	paramsOfApp.setName("ofApp");
	//paramsOfApp.add(bDistMode);
	//paramsOfApp.add(bFullScreen);
	//paramsOfApp.add(bMouseBrowsing);
	//paramsOfApp.add(bFullScreen);
	paramsOfApp.add(paramsScene);
	paramsOfApp.add(slideshow.getParameters());

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	setupFx();
	paramsOfApp.add(bGui_Fx);
#endif

	ofxSurfing::loadGroup(paramsOfApp);
}

#ifdef USE_OFX_POSTPROCESSING_MANAGER
//--------------------------------------------------------------
void ofApp::setupFx() {

	//setup manager
	manager.setup(ofGetWidth(), ofGetHeight(), "fonts\\VCR_OSD_MONO_1.001.ttf", 8);

	bGui_Fx.set("UI FX", true);

	// Load Settings
	manager.loadSettings();
}
#endif

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	ofLogNotice("ofApp") << "windowResized " << w << "," << h;

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.windowResized(w, h);
#endif
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

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	updateFx();
#endif

	slideshow.update(ofGetLastFrameTime());
}

#ifdef USE_OFX_POSTPROCESSING_MANAGER
//--------------------------------------------------------------
void ofApp::updateFx() {
	// update manager
	manager.updateValues();
}
#endif

//--------------------------------------------------------------
void ofApp::draw() {

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.begin();
#endif

	// Background
	if (bBgGradient) {
		ofxDrawBgGradient();
	} else {
		ofBackground(20);
	}

	// beginBloom();
	// // Organic Text
	ot.draw();
	// endBloom();
	// bloom.draw();

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.end();
#endif

	//--

	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui() {
	if (!bDistMode.get()) {
		// Presets Manager
		pm.drawGui();
		if (pm.bGui) ot.drawGui();
	} else {
		// Draw Help Dist
		if (bHelpDist) drawHelpDist();
	}

	if (ot.bGui && !bDistMode) {
		int p = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
		int y = ofGetHeight() - p - guiScene.getHeight();
		guiScene.setPosition(p, y);
		guiScene.draw();

		// fx
#ifdef USE_OFX_POSTPROCESSING_MANAGER
		if (bGui_Fx) {
			manager.drawGui(ofGetWidth() - manager.getGUIWidth(), 0);
		} else {
			// There is a kind of buggy issue on MAC.
			// Drawing the GUI out of the window.
			// Otherwise FPS draws continously
			manager.hideGui();
		}
#endif
	}

	// session
	ot.gui.setPosition(SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS + ot.gui.getWidth() + SURFING__OFXGUI__PAD_BETWEEN_PANELS, ofGetHeight() - ot.gui.getHeight() - SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS); //bottom left 2nd column
}

//--------------------------------------------------------------
void ofApp::drawHelpDist() {
	// Help Dist info
	std::string s = "";
	s += "ORGANIC TEXT";
	s += "\n\n";
	s += "H              Help";
	s += "\n\n";
	s += "SPACE          Next";
	s += "\n";
	if (bMouseBrowsing) {
		s += "MOUSE CLICK    Prev / Next";
		s += "\n";
		if (ofGetMouseX() < ofGetWidth() / 2)
			s += "*Left/Right    Half Screen";
		else
			s += " Left/Right*   Half Screen";
		s += "\n\n";
	}
	s += "ENTER          Advanced";
	s += "\n\n";
	s += "WINDOW";
	s += "\n";
	s += " F             " + ofToString(bFullScreen ? "Reset" : "Full Screen");
	s += "\n";
	s += " C             Center";
	s += "\n\n";
	s += " L             Trig Line Tweaks";
	s += "\n";
	string sp = ofToString(slideshow.bEnabled_.get() ? "Slideshow Pause" : "Slideshow Play");
	s += " P             " + sp;
	s += "\n\n";
	s += "KIT            " + ofToString(pm.getKitName());
	s += "\n";
	s += "PRESET         " + ofToString(pm.getPresetIndex()) + " / " + ofToString(pm.getPresetIndexLast());
	s += "\n";
	s += "               " + pm.getPresetFileName();
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

	// Dist Mode / advanced mode
	if (k == OF_KEY_RETURN) {
		bDistMode.set(!bDistMode.get());
		//workflow
		// if(bDistMode &&!ot.bGui) ot.bGui=true;
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
	if (k == 'l' || k == 'L') {
		ot.vTrigLineTweaks.trigger();
		return;
	}
	if (k == 'p' || k == 'P') {
		slideshow.toggle();
		return;
	}

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	else if (k == OF_KEY_F1)
		manager.loadSettings("scene1.json");

	else if (k == OF_KEY_F2)
		manager.loadSettings("scene2.json");

	else if (k == OF_KEY_F3)
		manager.loadSettings("scene3.json");
#endif

	else {
		ot.keyPressed(eventArgs);

		//--

		// Debug mode
		if (k == 'd' || k == 'D') {
			//workflow
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

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	lastMouseMove = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
bool ofApp::isMouseIdle() const {
	return (ofGetElapsedTimeMillis() - lastMouseMove) > mouseWait;
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
		slideshow.applyTextFromFileNow();
		if (!slideshow.isPresetLocked()) {
			if (browseDirection == BROWSE_NEXT)
				pm.doLoadNext(); // Load next preset
			else
				pm.doLoadPrevious(); // Load previous preset
		}
		ot.writeOut(); // Animate draw tween
	});

	// writeOut tween completed
	ot.setOnCompleteWriteOut([this]() {
		ofLogNotice("ofApp") << "writeOut completed. (Full range draw)";
		if (pendingLineTweaks && ot.bLineTweaks.get()) {
			ot.vTrigLineTweaks.trigger();
		}
		pendingLineTweaks = false;
	});
}

//--------------------------------------------------------------
void ofApp::nextScene(browseDirection_ bd) {
	ofLogNotice("ofApp") << "nextScene() browseDirection:" << bd;

	slideshow.onSceneAdvanced();

	browseDirection = bd;
	pendingLineTweaks = false;
	const bool wantLineTweaks = ot.bLineTweaks.get();

	if (bTweeningMode) {
		pendingLineTweaks = wantLineTweaks;
		ot.writeIn();
	} else {
		slideshow.applyTextFromFileNow();
		if (!slideshow.isPresetLocked()) {
			if (browseDirection == BROWSE_NEXT) {
				pm.doLoadNext();
			} else {
				pm.doLoadPrevious();
			}
		}
		if (wantLineTweaks) {
			ot.vTrigLineTweaks.trigger();
		}
	}
}

//--

//--------------------------------------------------------------
void ofApp::exit() {
	ofLogNotice("ofApp") << "exit()";

	ot.exit();

	ofxSurfing::saveGroup(paramsOfApp);
}
