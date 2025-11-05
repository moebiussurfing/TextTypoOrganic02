/*

	TODO

	- smooth transients ?
		- smooth points only ?
		- debug: draw smooth points & shapes 
	- mouse interact/dist ?
			radius distort. debug affected points

	- player next presets timed
	- fix switch windoResise glitch. call update
	- fix tweak ranges
		- tweak shape size param range
		check not normalized 0-1 all params ?. anim speed, mix
	- color modes mix/speed. adjust. add spread param
	- zoom lines ratio ?
		related to fullscreen/screen size? ofCamera ? fbo overscaled?

	- Deployment: add define remove preset addon
		hardcode json files to one .h file. replace workflow

	- ofxSurfingPresetsLiteOfxGui
		copy presets (button) to next or other
			slider target index. button To and From
			but copy to mem + move without load + save
		set kit path dialog
		add 9-0 key coommands

	- separate write tweenign methods to new class
		static pointers? Forward declaration?

	- make parent class ofApp -> OrganicTextType
 
 */

#pragma once

#include "ofMain.h"

//#define OFWORKS_DEMO_APP_DEPLOY // uncomment for the deployment release version

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
	OrganicText ot;

	// Presets Manager
	SurfingPresetsLiteOfxGui pm;

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
	enum browseDirection_ {
		BROWSE_NEXT = 0,
		BROWSE_PREVIOUS
	};
	browseDirection_ browseDirection = BROWSE_NEXT;

	ofParameterGroup paramsScene;

	// Scene drawing management
	void setupTweensCallbacks();
	void nextScene();

	//--

	// Helpers

	inline void ofxDrawBgGradient(ofColor c1 = ofColor { 70 }, ofColor c2 = ofColor { 10 }, ofGradientMode g = OF_GRADIENT_CIRCULAR) {
		ofBackgroundGradient(c1, c2, g);
	};
};
