/*

	TODO

	- gradient bg
	- smooth transients ?
		new smooth class
	- player next presets timed
		browse presets ?

	- fix tweak ranges
		check not normalized 0-1 all params ?
	- mouse interact/dist ?
		radius distort. debug affected points
	- zoom lines ratio ?
		related to fullscreen/screen size?
		ofCamera ?
		fbo overscaled?
	- undo history
	- add define remove preset addon
		hardcode json files to one .h file. replace workflow
	- ofxSurfingPresetsLiteOfxGui
		copy presets to next or other
			but copy to mem + move without load + save
 
 */

#pragma once

#include "ofMain.h"

//---

// Window title
const std::string SURFING_APP_TITLE = "DEMO - ofWorks";

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
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

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

	ofParameter<bool> bMouseInteract;
};
