#include "ofApp.h"
// //--------------------------------------------------------------
// void ofApp::setupBloom() {
// 	//Src fbo's texcoord has to be normalized(0 - 1)
// 	ofDisableArbTex();
// 	fbo.allocate(ofGetWidth(), ofGetHeight());
// 	ofEnableArbTex();

// 	bloom.setup(ofGetWidth(), ofGetHeight(), fbo);

// 	gui.setup();
// 	gui.add(scale.setup("Scale", 2.3f, 0.1f, 16.f));
// 	gui.add(brightness.setup("Brightness", 5.0f, 0.f, 30.f));
// 	gui.add(thresh.setup("Threshold", 0.f, 0.1f, 2.f));
// }

// //--------------------------------------------------------------
// void ofApp::beginBloom() {
// 	time = ofGetElapsedTimef();

// 	fbo.begin();
// 	ofClear(20);

// }

// //--------------------------------------------------------------
// void ofApp::endBloom() {
	
// 	fbo.end();

// 	bloom.setBrightness(brightness);
// 	bloom.setScale(scale);
// 	bloom.setThreshold(thresh);
// 	bloom.process();
// }

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

	slideshow.setup(&ot, [this]() { nextScene(); });
	slideshow.setMouseIdleChecker([this]() { return isMouseIdle(); });
	pm.gui.add(slideshow.getParameters());
	
	ot.refreshGuiPanel(pm.guiParams);
	
	//--
	
	setupTweensCallbacks();
	
	//--
	
	// App session settings
	paramsOfApp.setName("ofApp");
	paramsOfApp.add(bDistMode);
	paramsOfApp.add(bFullScreen);
	paramsOfApp.add(bMouseBrowsing);
	paramsOfApp.add(bFullScreen);
	ofxSurfing::loadGroup(paramsOfApp);

	// setupBloom();
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

	slideshow.update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw() {
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

	if (!bDistMode.get()) {
		// Presets Manager
		pm.drawGui();
		if (pm.bGui) ot.drawGui();
	} else {
		// Draw Help Dist
		if (bHelpDist) drawHelpDist();
	}

	// gui.draw();
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
	string sp=ofToString(slideshow.bEnabled_.get() ? "Slideshow Pause" : "Slideshow Play");
	s += " P             "+ sp;
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
	if (k == 'l'|| k == 'L') {
		ot.vTrigLineTweaks.trigger();
	}
	if (k == 'p'|| k == 'P') {
		slideshow.toggle();
		return;
	}
	
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
		if (browseDirection == BROWSE_NEXT)
		pm.doLoadNext(); // Load next preset
		else
		pm.doLoadPrevious(); // Load previous preset
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
		if (browseDirection == BROWSE_NEXT) {
			pm.doLoadNext();
		} else {
			pm.doLoadPrevious();
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
