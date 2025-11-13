/*
	BUGS
	- window handlig requires some fixes/workarounds
		to work well in multi-monitors (and WIN32)  setup 

	TODO
	- fix update anims when not drawing shapes!
	- improve draw glitches.
		calculate pointsAnimatedCache on update() instead of draw(),
		that is sensible to draw order, tween drawing etc
	- fix ratio and mouse tweaks for cross shape
	- ofxSurfingPresetsLite
		fix empty/first startup
		fix path_kit single place store and persistence
		copy presets (button) to next or other
			slider target index. button To and From
			but copy to mem + move without load + save
			set kit path dialog
			
	IDEAS
	- finish implement deployment define OFWORKS_DEMO_APP_DEPLOY ?
	- player next presets timed
	- zoom lines ratio ? related to fullscreen/screen size ?
	- separate write tweening methods to new class files
	- make parent class ofApp -> OrganicTextScene
 */

// (WIP) demo particle modifier
#define USE_PARTICLE_MODIFIER 
#define NUM_PARTICLES 4

#pragma once

#include "ofMain.h"

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
	void centerWindow();
	void fullScreenWindow();
	void resetWindow();

	// Performance
	float fps;
	float frameTime;

	//--

	// Scene parameters
	ofParameterGroup paramsScene;
	ofParameter<bool> bBgGradient;

	// Interaction
	ofParameter<bool> bTweeningMode;
	ofParameter<bool> bMouseBrowsing;
	// Direction enum/flag
	enum browseDirection_ {
		BROWSE_NEXT = 0,
		BROWSE_PREVIOUS
	};
	browseDirection_ browseDirection = BROWSE_NEXT;

	// Scene drawing management
	void setupTweensCallbacks();
	void nextScene(browseDirection_ bd = BROWSE_NEXT);

	//--

	// Helpers
	inline void ofxDrawBgGradient(ofColor c1 = ofColor { 10 }, ofColor c2 = ofColor { 40 }, ofGradientMode g = OF_GRADIENT_CIRCULAR) {
		ofBackgroundGradient(c1, c2, g);
	};

	//--

	// Distribution Mode
	ofParameter<bool> bDistMode; // False: Advanced Mode. True: Distribution (User) Mode
	ofParameter<bool> bHelpDist;
	ofEventListener e_bDistMode;
	void drawHelpDist();
	ofParameter<bool> bFullScreen;
	ofEventListener e_bFullScreen;
	
	//TODO: WIP
#ifdef USE_PARTICLE_MODIFIER
	struct RefractiveRect {
	  ofRectangle bounds;
	  glm::vec2 velocity;
	  float angle;
	  float angularVelocity;
	};
	vector<RefractiveRect> rectangles;
	void drawRefractionRectangle(const ofRectangle& bounds, float angle);
#endif
};
