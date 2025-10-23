/*

	BUG
	- startup loading fails some trail.
		connections amount..
	- min gap does nothing ?
 
	TODO

	- gradient bg
	- player next presets timed
		browse presets ?
	- smooth transients ?
		new smooth class

	- fix tweak ranges
		check not normalized 0-1 all params ?
	- mouse interact/dist ?
		radius distort
		next prev preset
	- zoom lines ratio ?
		related to fullscreen/screen size?
		ofCamera ?
		fbo overscaled?
	- undo history
	- add define remove preset addon
		hardcode json files to one .h file. replace workflow
	- ofxSurfingPresetsLiteOfxGui
		copy presets to next or other
 
 */

#pragma once

#include "ofMain.h"

//---

// Window title
const std::string SURFING_APP_TITLE = "DEMO - ofWorks";

// Window size
constexpr float OFWORKS_APP_WIDTH = 1200;
constexpr float OFWORKS_APP_HEIGHT = 550;

//---

#include "ofxSurfingPresetsLiteOfxGui.h"
#include "organicText.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(ofKeyEventArgs & eventArgs);

	// Organic Text
	OrganicText t;

	// Presets Manager
	SurfingPresetsLiteOfxGui p;

	// Reset app window custom shape
	ofParameter<void> vResetWindow { "Reset Window" };
	ofEventListener e_vResetWindow;
	void resetWindowCustom();
	void resetWindowFullScreen();

	float fps;
	float frameTime;
};
