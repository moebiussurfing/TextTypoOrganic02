#include "organicTextScene.h"

//--------------------------------------------------------------
void OrganicTextScene::setup(float fpsTarget) {

// Deployment app distribution version
#ifdef OFWORKS_DEMO_APP_DISTRIBUTION
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetLogLevel("OrganicText", OF_LOG_SILENT);
	ofSetLogLevel("SurfingPresetsLite", OF_LOG_SILENT);
#endif

	ofLogNotice("OrganicTextScene") << "setup()";

	//--

	// Window

	centerWindow();

	//--

	// Parameters

	bMouseBrowsing.set("Mouse Browsing", false);
	bTweeningMode.set("Mode Tweening", true);

	//--

	// Distribution Mode

	bHelpDistribution.set("Help Distribution", true);

	// False: Advanced Mode. True: Distribution (User) Mode
	bDistributionMode.set("Distribution mode", true);
	e_bDistributionMode = bDistributionMode.newListener([this](bool & v) {
		ofLogNotice("OrganicTextScene") << "bDistributionMode: " << v;
		// Workflow ui to improve user experience
		if (bDistributionMode.get()) {
			ot.bKeys = false;
		} else {
			ot.bGui.set(true);
		}
	});

	// Window Full Screen / default size
	bFullScreen.set("Full Screen", false);
	e_bFullScreen = bFullScreen.newListener([this](bool & v) {
		ofLogNotice("OrganicTextScene") << "bFullScreen: " << v;
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
	ot.setup(fpsTarget);

	//--

	// Presets Manager

	pm.setup(ot.paramsPreset);
	pm.gui.add(ot.bGui);
	ot.refreshGuiPanel(pm.guiParams);

	//--

	// Gui Scene Slideshow
	paramsScene.setName("Scene");
	paramsScene.add(bFullScreen);
	paramsScene.add(bTweeningMode);
	paramsScene.add(bMouseBrowsing);

	// Gui
	guiScene.setup("Manager");
	guiScene.add(slideshow.bEnabled_);
	guiScene.add(slideshow.progressFeedback_);
	guiScene.add(slideshow.slideIndex_);
#ifdef USE_OFX_POSTPROCESSING_MANAGER
	setupFx();
	paramsScene.add(bGui_Fx);
#endif
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
	paramsOfApp.add(paramsScene);
	paramsOfApp.add(slideshow.getParameters());

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	paramsOfApp.add(bGui_Fx);
#endif

	ofxSurfing::loadGroup(paramsOfApp);
}

#ifdef USE_OFX_POSTPROCESSING_MANAGER
//--------------------------------------------------------------
void OrganicTextScene::setupFx() {

	// Setup manager
	manager.setup(ofGetWidth(), ofGetHeight(), ofToDataPath("fonts/VCR_OSD_MONO_1.001.ttf"), 8);

	bGui_Fx.set("UI FX", true);

	// Load Settings
	manager.loadSettings();
	manager.loadSessionState();
}
#endif

//--------------------------------------------------------------
void OrganicTextScene::windowResized(int w, int h) {
	ofLogNotice("OrganicTextScene") << "windowResized " << w << "," << h;

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.windowResized(w, h);
#endif
}

//--------------------------------------------------------------
void OrganicTextScene::update() {

	// Performance
	fps = ofGetFrameRate();
	frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);

	// Window title
	std::string s = "";
	std::string s1 = "";
	static std::string s2 = "";
	std::string s3 = "";
	// Debug info
	s1 = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
	if (ot.bDebug) {
		if (pm.isChangedIndex()) {
			s2 = "PRESET " + ofToString(pm.getPresetIndex());
		}
		s3 = ofToString(ofGetWindowWidth()) + "x" + ofToString(ofGetWindowHeight());
		s = "     " + s1 + "     " + s3 + "     " + s2;
	} else {
		s = "     " + s1;
	}
	std::string wt = ofToString(OFWORKS_DEMO_APP_TITLE) + s;
	ofSetWindowTitle(wt);

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	updateFx();
#endif

	slideshow.update(ofGetLastFrameTime());
}

#ifdef USE_OFX_POSTPROCESSING_MANAGER
//--------------------------------------------------------------
void OrganicTextScene::updateFx() {
	// update manager
	manager.updateValues();
}
#endif

//--------------------------------------------------------------
void OrganicTextScene::draw() {

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.begin();
#endif

	ot.draw();

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.end();
#endif

	//--

	if ((bHelpDistribution && bDistributionMode) || ot.bGui && !bDistributionMode) {
	std:
		string s = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
		ofxSurfing::ofDrawBitmapStringBox(s, ofxSurfing::SURFING_LAYOUT_TOP_CENTER);
	}
}

//--------------------------------------------------------------
void OrganicTextScene::drawGui() {
	ot.drawDebugOverlay();

	if (!bDistributionMode.get()) {
		// Presets Manager
		pm.drawGui();
		if (pm.bGui) ot.drawGui();
	} else {
		// Draw Help Distribution
		if (bHelpDistribution) drawHelpDistribution();
	}

	if (ot.bGui && pm.bGui && !bDistributionMode) {
		int p = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
		int y = ofGetHeight() - p - guiScene.getHeight();
		guiScene.setPosition(p, y);
		guiScene.draw();

// Fx
#ifdef USE_OFX_POSTPROCESSING_MANAGER
		if (bGui_Fx && pm.bGui) {
			manager.drawGui(ofGetWidth() - manager.getGUIWidth(), 0);
		} else {
			// There is a kind of buggy issue on MAC.
			// Drawing the GUI out of the window.
			// Otherwise FPS draws continously
			manager.hideGui();
		}
#endif
	}

	// Session
	ot.gui.setPosition(SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS + ot.gui.getWidth() + SURFING__OFXGUI__PAD_BETWEEN_PANELS,
		ofGetHeight() - ot.gui.getHeight() - SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS); //bottom left 2nd column
}

//--------------------------------------------------------------
void OrganicTextScene::drawHelpDistribution() {
	// Help Dist info
	std::string s = "";
	s += "ORGANIC TEXT";
	s += "\n\n";
	s += "H              Help";
	s += "\n\n";
	s += "ENTER          Advanced Mode";
	s += "\n\n";
	s += "SPACE          Next Slide";
	s += "\n";
	if (bMouseBrowsing) {
		s += "MOUSE CLICK    Prev / Next";
		s += "\n";
		if (ofGetMouseX() < ofGetWidth() / 2)
			s += "*Left/Right    (Half Screen)";
		else
			s += " Left/Right*   (Half Screen)";
		s += "\n\n";
	}
	s += "< >            Browse Presets";
	s += "\n";
	std::string sp = ofToString(slideshow.bEnabled_.get() ? "Slideshow Pause" : "Slideshow Play");
	s += "P              " + sp;
	s += "\n";
	s += "L              Trig Line Tweaks";
	s += "\n";
	s += "O/I            Clear/Write Text";
	s += "\n\n";
	s += "WINDOW";
	s += "\n";
	s += " F             " + ofToString(bFullScreen ? "Reset" : "Full Screen");
	// s += "\n";
	// s += " C             Center";
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
void OrganicTextScene::keyPressed(ofKeyEventArgs & eventArgs) {
	const auto k = eventArgs.key;
	ofLogNotice("OrganicTextScene") << "keyPressed(): " << char(k);

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
		bDistributionMode.set(!bDistributionMode.get());
		//workflow
		// if(bDistributionMode &&!ot.bGui) ot.bGui=true;
		return;
	}

	// Next preset
	if (k == OF_KEY_SPACE) {
		nextScene();
		return;
	}

	if (bDistributionMode.get()) {
		// Help Dist
		if (k == 'h' || k == 'H') {
			bHelpDistribution.set(!bHelpDistribution.get());
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

	else if (k == 'I' || k == 'i') {
		ot.writeOut();
		return;
	}

	else if (k == 'O' || k == 'o') {
		ot.writeClear();
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
void OrganicTextScene::mousePressed(int x, int y, int button) {
	ofLogNotice("OrganicTextScene") << "mousePressed(): " << x << "," << y << " " << button;

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
void OrganicTextScene::mouseMoved(int x, int y) {
	lastMouseMove = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
bool OrganicTextScene::isMouseIdle() const {
	return (ofGetElapsedTimeMillis() - lastMouseMove) > mouseWait;
}

//--

// Window management

//--------------------------------------------------------------
void OrganicTextScene::centerWindow() {
	ofLogNotice("OrganicTextScene") << "centerWindow()";

	int w = ofGetWindowWidth();
	int h = ofGetWindowHeight();
	ofSetWindowPosition(ofGetScreenWidth() * 0.5f - w * 0.5f,
		ofGetScreenHeight() * 0.5f - h * 0.5f);
}

//--------------------------------------------------------------
void OrganicTextScene::fullScreenWindow() { // Set window full screen
	ofLogNotice("OrganicTextScene") << "resetWindowFullScreen()";

	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void OrganicTextScene::resetWindow() { // Set window reset
	ofLogNotice("OrganicTextScene") << "resetWindow()";

	int w = OFWORKS_DEMO_APP_WIDTH;
	int h = OFWORKS_DEMO_APP_HEIGHT;

	ofSetWindowShape(w, h);
	ofSetWindowPosition(ofGetScreenWidth() / 2 - w / 2,
		ofGetScreenHeight() / 2 - h / 2);
}

//----

// Scenes tweener

//--------------------------------------------------------------
void OrganicTextScene::setupTweensCallbacks() {
	ofLogNotice("OrganicTextScene") << "setupTweensCallbacks()";

	// Setup tween callbacks to be called when completed
	// Custom workflow for combine with/as preset transitions

	// writeIn tween completed
	// Empty space: not drawing nothing on complete
	// In = 1, Out = 1
	ot.setOnCompleteWriteIn([this]() {
		ofLogNotice("OrganicTextScene") << "writeIn completed. (Empty space: no draw)";
		if (slideshow.consumeSkipWriteInCompletion()) {
			return;
		}
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
		ofLogNotice("OrganicTextScene") << "writeOut completed. (Full range draw)";
		if (pendingLineTweaks && ot.bLineTweaks.get()) {
			ot.vTrigLineTweaks.trigger();
		}
		pendingLineTweaks = false;
	});
}

//--------------------------------------------------------------
void OrganicTextScene::nextScene(BrowseDirection bd) {
	ofLogNotice("OrganicTextScene") << "nextScene() browseDirection:" << bd;

	slideshow.onSceneAdvanced();

	browseDirection = bd;
	pendingLineTweaks = false;
	const bool wantLineTweaks = ot.bLineTweaks.get();

	if (bTweeningMode && slideshow.consumeStartFromClear()) {
		pendingLineTweaks = wantLineTweaks;
		slideshow.applyTextFromFileNow();
		if (!slideshow.isPresetLocked()) {
			if (browseDirection == BROWSE_NEXT) {
				pm.doLoadNext();
			} else {
				pm.doLoadPrevious();
			}
		}
		ot.writeOut();
		return;
	}

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
void OrganicTextScene::exit() {
	ofLogNotice("OrganicTextScene") << "exit()";

	ot.exit();

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	manager.saveSessionState();
#endif

	ofxSurfing::saveGroup(paramsOfApp);
}
