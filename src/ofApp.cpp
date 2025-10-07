#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(24);

	#if 1
	int w = 1920;
	int h = 1080;
	int p = 25;
	ofSetWindowShape(w, h-p);
	ofSetWindowPosition(-w,p);
	#endif

	float fps = 60;
	ofSetFrameRate(fps);
	
	t.setTargetFPS(fps);
	t.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	t.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & eventArgs){
	t.keyPressed(eventArgs);
}

//--------------------------------------------------------------
void ofApp::exit(){
	t.exit();
}
