/*

	BUG
	- startup loading fails some trail.
		connections amount..
	- min gap does nothing ?
	- normalize 0-1 all params ?
 
	TODO

	- fix tweak ranges
	- gradient bg
	- mouse interact/dist ?
	- zoom lines ratio ?
		related to fullscreen/screen size?
		ofCamera ?
		fbo overscaled?
	- player next presets timed
		browse presets ?
	- smooth transients ?
		new smooth class
	- add define remove preset 
	- unde history
 
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
