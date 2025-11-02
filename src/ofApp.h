/*

	TODO

	- smooth transients ?
		- smooth points only ?
		- debug: draw smooth points & shapes 
	- mouse interact/dist ?
			radius distort. debug affected points
	- player next presets timed
		browse presets ?
	- fix switch windoResise glitch. call update

	- fix tweak ranges
		check not normalized 0-1 all params ?
			anim speed, mix
	- zoom lines ratio ?
		related to fullscreen/screen size?
		ofCamera ?
		fbo overscaled?
	- Deploy: add define remove preset addon
		hardcode json files to one .h file. replace workflow

	- ofxSurfingPresetsLiteOfxGui
		copy presets (button) to next or other
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
	void mousePressed(int x, int y, int button);

	// Organic Text
	OrganicText t;

	// Presets Manager
	SurfingPresetsLiteOfxGui p;

	// Reset app window custom shape
	ofParameter<void> vResetWindow { "Reset Window" };
	ofEventListener e_vResetWindow;
	void resetWindowCustom();
	void resetWindowFullScreen();
	bool bWindowFullScreen = false;

	float fps;
	float frameTime;

	//--

	// Interaction
	ofParameter<bool> bMouseBrowsing;
	ofParameter<bool> bTweeningMode;
	ofParameterGroup paramsScene;

	// Scene drawing management
	void setupTweens();
	void nextScene();

	//--

	// Helpers

	inline void ofxDrawBgGradient(ofColor c1 = ofColor { 70 }, ofColor c2 = ofColor { 10 }, ofGradientMode g = OF_GRADIENT_CIRCULAR) {
		ofBackgroundGradient(c1, c2, g);
	};
};
