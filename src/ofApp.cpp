#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(24);

	#if 1
//	int w = 1920;
//	int h = 1080;
//	int p = 25;
//	ofSetWindowShape(w, h-p);
//	ofSetWindowPosition(-w,p);
	int w = 1200;
	int h = 550;
	ofSetWindowShape(w, h);
	ofSetWindowPosition(ofGetWidth()*0.5-w*0.5,ofGetHeight()*0.5-h*0.5);
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
