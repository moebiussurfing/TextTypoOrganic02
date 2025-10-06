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
	t.setTargetFPS(fps);
	ofSetFrameRate(fps);
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
void ofApp::keyPressed(int key){
	ofKeyEventArgs args;
	args.key = key;
	args.keycode = key;
	args.scancode = 0;
	args.codepoint = 0;
	t.keyPressed(args);
}

//--------------------------------------------------------------
void ofApp::exit(){
	t.exit();
}
