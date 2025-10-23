/*
 
 TODO
 
 - mouse interact/dist
 - same help box styles black
 - fix gui groups collappse. collapse fonts 
 - lock ui right + help left
 - fix save debug (auto save ok)
 - set ofxgui style mini
 - refresh trails callback
 - add define remove preset 
 - add W key full screen
 - play next presets timed
 - browse presets ?
 - smooth transients ?
 
 */

#pragma once

#include "ofMain.h"

// Window title
const std::string SURFING_APP_TITLE = "DEMO -- ofWorks";

// Window size
constexpr float OFWORKS_APP_WIDTH = 1200;
constexpr float OFWORKS_APP_HEIGHT = 550;

#include "ofxSurfingPresetsLiteOfxGui.h"
#include "organicText.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(ofKeyEventArgs & eventArgs);

	OrganicText t;

	SurfingPresetsLiteOfxGui p;

	ofParameter<void> vResetWindow { "Reset Window" };
	ofEventListener e_vResetWindow;
	void resetWindow();
	void resetWindowFullScreen();

	float fps;
	float frameTime;
};
