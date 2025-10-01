#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofBackground(0); // Changed to black for better color effects
	//ofSetFrameRate(60);

	#if 0
	ofSetWindowShape(512, 512);
	int p = 50;
	ofSetWindowPosition(-ofGetWidth()-p, +p);
	#endif

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
