#pragma once

#define USE_OFX_POSTPROCESSING_MANAGER

#include <ofMain.h>

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
  // Organic Text
  OrganicText ot;

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
  ofParameter<ofColor> bgColor1;
  ofParameter<ofColor> bgColor2;
  ofParameter<bool> bBgGradient;

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

  // Helpers
  inline void ofxDrawBgGradient(const ofColor & c1 = ofColor { 10 },
                               const ofColor & c2 = ofColor { 40 },
                               ofGradientMode g = OF_GRADIENT_CIRCULAR) {
    ofBackgroundGradient(c1, c2, g);
  }

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
