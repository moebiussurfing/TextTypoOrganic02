#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	#if 0
	ofSetWindowShape(512, 512);
	int p = 50;
	ofSetWindowPosition(-ofGetWidth()-p, +p);
	#endif

	t.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	t.update();
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
