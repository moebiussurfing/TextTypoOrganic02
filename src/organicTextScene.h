#pragma once

#define USE_OFX_POSTPROCESSING_MANAGER

#include <ofMain.h>

#include "ofxGui.h"
#include "ofxSurfingPresetsLiteOfxGui.h"
#include "organicText.h"
#include "presetSlideshow.h"

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	#include "ofxPostProcessingManager.h"
#endif

class OrganicTextScene {
public:
	void setup(float fpsTarget);
	void update();
	void draw();
	void drawGui();
	void exit();
	void windowResized(int w, int h);
	void keyPressed(ofKeyEventArgs & eventArgs);
	void mousePressed(int x, int y, int button);
	void mouseMoved(int x, int y);
	bool isMouseIdle() const;

#ifdef USE_OFX_POSTPROCESSING_MANAGER
	void setupFx();
	void updateFx();
	ofxPostProcessingManager manager;
	ofParameter<bool> bGui_Fx;
#endif

private:
	void setup3DScene();
	void update3DScene();
	void refresh3DCamera();

	// Organic Text
	OrganicText ot;

	// 3D scene
	ofEasyCam cam_;
	ofLight keyLight_;
	ofLight fillLight_;
	ofxPanel gui3D_;
	ofParameterGroup params3D_;
	ofParameterGroup paramsCamera_;
	ofParameterGroup paramsLights_;
	ofParameter<float> camDistance_;
	ofParameter<float> camOffsetX_;
	ofParameter<float> camOffsetY_;
	ofParameter<float> camOffsetZ_;
	ofParameter<float> camTargetOffsetX_;
	ofParameter<float> camTargetOffsetY_;
	ofParameter<float> camTargetOffsetZ_;
	ofParameter<bool> bDisableCamera_;
	ofParameter<bool> bCamMouseInput_;
	ofParameter<void> vResetCamera_;
	ofParameter<float> ambientLight_;
	ofParameter<float> keyLightIntensity_;
	ofParameter<float> keyLightOffsetX_;
	ofParameter<float> keyLightOffsetY_;
	ofParameter<float> keyLightOffsetZ_;
	ofParameter<void> vResetKeyLight_;
	ofParameter<float> fillLightIntensity_;
	ofParameter<float> fillLightOffsetX_;
	ofParameter<float> fillLightOffsetY_;
	ofParameter<float> fillLightOffsetZ_;
	ofParameter<void> vResetFillLight_;
	ofParameter<void> vResetLights_;
	ofEventListener eCamMouseInput_;
	ofEventListener eDisableCamera_;
	ofEventListener eResetCamera_;
	ofEventListener eResetKeyLight_;
	ofEventListener eResetFillLight_;
	ofEventListener eResetLights_;

	// Presets Manager
	SurfingPresetsLiteOfxGui pm;
	PresetSlideshow slideshow;

	// Reset app window custom shape
	void centerWindow();
	void fullScreenWindow();
	void resetWindow();

	// Performance
	float fps = 0.0f;
	float frameTime = 0.0f;

	// Scene parameters
	ofParameterGroup paramsScene;

	// Interaction
	ofParameter<bool> bTweeningMode;
	ofParameter<bool> bMouseBrowsing;

	// Direction enum/flag
	enum BrowseDirection {
		BROWSE_NEXT = 0,
		BROWSE_PREVIOUS
	};
	BrowseDirection browseDirection = BROWSE_NEXT;

	// Scene drawing management
	void setupTweensCallbacks();
	void nextScene(BrowseDirection bd = BROWSE_NEXT);

	// Delay line tweaks until tween-out finishes to avoid distorting the reveal
	bool pendingLineTweaks = false;
	bool skipSceneAdvanceOnWriteIn_ = false;

	// Distribution Mode
	ofParameter<bool> bDistributionMode;
	ofParameter<bool> bHelpDistribution;
	ofEventListener e_bDistributionMode;
	void drawHelpDistribution();
	ofParameter<bool> bFullScreen;
	ofEventListener e_bFullScreen;

	ofParameterGroup paramsOfApp;
	ofxPanel guiScene;

	int lastMouseMove = 0;
	int mouseWait = 1000; // ms
};
