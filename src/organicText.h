#pragma once

#include "ofMain.h"
#include "ofxGui.h"
using namespace glm;

constexpr const char* ORGANICTEXT = "ARB";
constexpr float MAX_RADIUS = 50.0f;
constexpr float MIN_RADIUS = 1.0f;

// Shape types for drawing points
enum ShapeType {
	SHAPE_CIRCLE = 0,
	SHAPE_RECTANGLE = 1,
	SHAPE_TRIANGLE = 2,
	SHAPE_STAR = 3,
	SHAPE_CROSS = 4
};

// Color modes
enum ColorMode {
	COLOR_PLAIN = 0,
	COLOR_RAINBOW = 1,
	COLOR_GRADIENT = 2,
	COLOR_NOISE = 3,
	COLOR_DISTANCE = 4,
	COLOR_GLOBAL_1 = 5,
	COLOR_GLOBAL_2 = 6,
	COLOR_GLOBAL_3 = 7,
	COLOR_GLOBAL_MIX = 8
};

// Animation modes
enum AnimMode {
	ANIM_NOISE = 0,
	ANIM_WAVE = 1,
	ANIM_SPIRAL = 2,
	ANIM_PULSE = 3,
	ANIM_ORBIT = 4
};

class OrganicText {
public:
	//OrganicText();
	//~OrganicText();

	void setup();
	void update();
	void draw();
	void exit(); // New: exit function for auto-save
	//void update(ofEventArgs & args);
	void keyPressed(ofKeyEventArgs & eventArgs);
	//void exit();

	string pathSettings = "OrganicText.json";

	ofParameterGroup parameters;
	ofParameterGroup shapeGroup;
	ofParameterGroup densityGroup;
	ofParameterGroup colorGroup; // Color controls
	ofParameterGroup globalColorGroup; // New: Global color controls
	ofParameterGroup animGroup; // Animation controls
	ofParameterGroup connectionGroup; // Connection controls

	// Basic parameters
	ofParameter<bool> bKeys;
	ofParameter<bool> bDebug;
	ofParameter<bool> bFill;
	ofParameter<bool> bPlain;
	ofParameter<bool> bDrawShapes; // New: Toggle to disable shape drawing
	ofParameter<bool> bEnableAnimation; // New: Toggle to disable animation
	ofParameter<float> noiseSize;
	ofParameter<string> sText;

	// Density parameters with enable/reset
	ofParameter<bool> bEnableDensity; // New: Enable density group
	ofParameter<void> resetDensity; // New: Reset density group
	ofParameter<void> randomDensity; // New: Randomize density group
	ofParameter<float> pointsSpacing;
	ofParameter<float> pointDensity;
	ofParameter<float> minSpacing;
	ofParameter<float> contourSampling; // New: Better contour sampling control

	// Shape parameters with enable/reset
	ofParameter<bool> bEnableShape; // New: Enable shape group
	ofParameter<void> resetShape; // New: Reset shape group
	ofParameter<void> randomShape; // New: Randomize shape group
	ofParameter<int> shapeType;
	ofParameter<float> pointRadius;
	ofParameter<float> pointsRadiusMin;
	ofParameter<float> triangleRatio;
	ofParameter<bool> bShowOutline;
	ofParameter<float> shapeRotation;

	// Color parameters with enable/reset
	ofParameter<bool> bEnableColor; // New: Enable color group
	ofParameter<void> resetColor; // New: Reset color group
	ofParameter<void> randomColor; // New: Randomize color group
	ofParameter<int> colorMode;
	ofParameter<float> colorSpeed;
	ofParameter<float> hueShift;
	ofParameter<float> saturation;
	ofParameter<float> brightness;
	ofParameter<bool> bColorByDistance;

	// Global color parameters with enable/reset
	ofParameter<bool> bEnableGlobalColor; // New: Enable global color group
	ofParameter<void> resetGlobalColor; // New: Reset global color group
	ofParameter<void> randomGlobalColor; // New: Randomize global color group
	ofParameter<ofColor> globalColor1;
	ofParameter<ofColor> globalColor2;
	ofParameter<ofColor> globalColor3;
	ofParameter<float> globalColorMix;

	// Animation parameters with enable/reset
	ofParameter<bool> bEnableAnimationGroup; // New: Enable animation group
	ofParameter<void> resetAnimation; // New: Reset animation group
	ofParameter<void> randomAnimation; // New: Randomize animation group
	ofParameter<int> animationMode;
	ofParameter<float> animSpeed;
	ofParameter<float> waveFrequency;
	ofParameter<float> waveAmplitude;
	ofParameter<float> spiralTightness;
	ofParameter<float> pulseIntensity;

	// Connection parameters with enable/reset
	ofParameter<bool> bEnableConnection; // New: Enable connection group
	ofParameter<void> resetConnection; // New: Reset connection group
	ofParameter<void> randomConnection; // New: Randomize connection group
	ofParameter<bool> bDrawConnections;
	ofParameter<float> connectionDistance;
	ofParameter<float> connectionAlpha;
	ofParameter<bool> bOnlyNearConnections;

	// Trail parameters
	ofParameter<bool> bDrawTrails;
	ofParameter<int> trailLength;
	ofParameter<float> trailFade;

	// Global controls
	ofParameter<void> resetAll; // New: Reset everything to defaults

	// Event listeners
	ofEventListener e_PointsRadius;
	ofEventListener e_PointsSize;
	ofEventListener e_sText;
	ofEventListener e_PointDensity;
	ofEventListener e_ShapeType;
	ofEventListener e_ColorMode;
	ofEventListener e_AnimMode;
	ofEventListener e_WindowClosed;

	// Functions
	vector<vec2> sampleStringPoints(const string& s, float ds) const;
	void drawShape(vec2 position, float size, ShapeType shape, float rotation = 0) const;
	void drawConnections() const;
	void updateTrails();
	ofColor getPointColor(int index, vec2 position, float phase) const;
	vec2 getAnimatedOffset(int index, float phase) const;
	void saveSettings();
	void loadSettings();
	
	// Reset functions
	void resetDensityParams();
	void resetShapeParams();
	void resetColorParams();
	void resetGlobalColorParams();
	void resetAnimationParams();
	void resetConnectionParams();
	void resetAllParams();
	
	// Randomize functions
	void randomizeDensityParams();
	void randomizeShapeParams();
	void randomizeColorParams();
	void randomizeGlobalColorParams();
	void randomizeAnimationParams();
	void randomizeConnectionParams();

	// Data
	vector<vec2> pointsString;
	vector<vector<vec2>> pointTrails; // For trail effect
	ofTrueTypeFont font;
	float t;
	vec2 textCenter; // Center of text for distance calculations

	ofxPanel gui;
	void refreshPointsString();

};
