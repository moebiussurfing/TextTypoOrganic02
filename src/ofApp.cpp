#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(24);

	resetWindowCustom();
	e_vResetWindow = vResetWindow.newListener([this](void) { resetWindowCustom(); });

	float fps = 60;
	ofSetFrameRate(fps);

	// Organic text
	t.setup(fps);
	t.gui.setPosition(ofGetWidth() - t.gui.getWidth() - 5, 5);

	// Presets manger
	p.setup(t.paramsPreset);
	p.gui.add(t.bGui);
	p.gui.add(vResetWindow);

	//TODO
	t.refreshGuiPanel(p.guiParams);
}

//--------------------------------------------------------------
void ofApp::update() {
	fps = ofGetFrameRate();
	frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);

	// Window title
	std::string s1 = "";
	if (t.bDebugDraw || !p.bGui) s1 = ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
	static std::string s2 = "";
	if (p.isChangedIndex()) {
		s2 = "PRESET " + ofToString(p.getPresetIndex());
	}
	string wt = ofToString(SURFING_APP_TITLE) + "\t\t" + s1 + "\t\t" + s2;
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	t.draw();

	p.drawGui();
	if (p.bGui) t.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	t.keyPressed(eventArgs);

	if (eventArgs.key == 'w') resetWindowCustom();
	if (eventArgs.key == 'W') resetWindowFullScreen();
}

//--------------------------------------------------------------
void ofApp::resetWindowCustom() { // Set window size and centered
	const int w = OFWORKS_APP_WIDTH;
	const int h = OFWORKS_APP_HEIGHT;

	// 2 steps: do twice to fix bug multi monitor un centered well
	for (int i = 0; i < 2; i++) {
		ofSetWindowShape(w, h);
		ofSetWindowPosition(ofGetScreenWidth() * 0.5f - w * 0.5f, ofGetScreenHeight() * 0.5f - h * 0.5f);
	}
}

//--------------------------------------------------------------
void ofApp::resetWindowFullScreen() { // Set window full screen
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit() {
	t.exit();
}
