/*
 
 TODO
 
 - mouse interact/dist
 - same help box styles black
 - fix gui groups collappse. collapse fonts 
 - lock ui right
 - fix save debug
 - set ofxgui style
 
 */



#pragma once

#include "ofMain.h"

const std::string SURFING_APP_TITLE = "DEMO ofWorks";

constexpr float OFWORKS_APP_WIDTH = 1200;
constexpr float OFWORKS_APP_HEIGHT = 550;

#include "organicText.h"
#include "ofxSurfingPresetsLiteOfxGui.h"

class ofApp : public ofBaseApp {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(ofKeyEventArgs & eventArgs);
	
	OrganicText t;
	
	SurfingPresetsLiteOfxGui p;
	
	ofParameter<void> vResetWindow{"Reset Window"};
	ofEventListener e_vResetWindow;
	void resetWindow();
	
	float fps;
	float frameTime;
	
	bool bGui=true;
};
