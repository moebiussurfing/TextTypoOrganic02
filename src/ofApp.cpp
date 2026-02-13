#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofLogNotice("ofApp") << "setup()";
	const float fpsTarget = ORGANIC_TEXT_FPS;
	ofSetFrameRate(fpsTarget);

	scene_.setup(fpsTarget);

#if 1
	ofSetWindowPosition(-2560+6, 40);
#endif
}

//--------------------------------------------------------------
void ofApp::update() {
	scene_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	scene_.draw();
	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui() {
	scene_.drawGui();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	scene_.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs) {
	scene_.keyPressed(eventArgs);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	scene_.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	scene_.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::exit() {
	scene_.exit();
}
