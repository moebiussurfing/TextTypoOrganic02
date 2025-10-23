#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(24);

	resetWindow();
	e_vResetWindow = vResetWindow.newListener([this](void) { resetWindow(); });

	float fps = 60;
	ofSetFrameRate(fps);

	// organic text
	t.setup(fps);
	t.gui.setPosition(ofGetWidth() - t.gui.getWidth() - 5, 5);

	// presets manger
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
	string sp = "";
	if (t.bDebugDraw) sp = "\t\t\t\t" + ofToString(fps, 0) + " Fps / " + ofToString(frameTime, 0) + " ms";
	string wt = ofToString(SURFING_APP_TITLE) + sp;
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	t.draw();

	// if(!bGui) return;
	t.drawGui();
	p.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	t.keyPressed(eventArgs);

	if (eventArgs.key == 'g') bGui = !bGui;
	if (eventArgs.key == 'w') resetWindow();
	if (eventArgs.key == 'W') resetWindowFullScreen();
}

//--------------------------------------------------------------
void ofApp::resetWindow() { // set window size and centered
	const int w = OFWORKS_APP_WIDTH;
	const int h = OFWORKS_APP_HEIGHT;
	// 2 steps: do twice to fix bug multi monitor un centered well
	for (int i = 0; i < 2; i++) {
		ofSetWindowShape(w, h);
		ofSetWindowPosition(ofGetScreenWidth() * 0.5f - w * 0.5f, ofGetScreenHeight() * 0.5f - h * 0.5f);
	}
}

//--------------------------------------------------------------
void ofApp::resetWindowFullScreen() { // set window full screen
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit() {
	t.exit();
}
