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
	SHAPE_CROSS = 4,
	SHAPE_POINT = 5  // New: Just points for debug-like visualization
};

// Color modes (simplified - based only on global colors)
enum ColorMode {
	COLOR_GLOBAL_1 = 0,     // Use globalColor1
	COLOR_GLOBAL_2 = 1,     // Use globalColor2  
	COLOR_GLOBAL_3 = 2,     // Use globalColor3
	COLOR_GLOBAL_MIX = 3,   // Mix all 3 colors
	COLOR_DISTANCE = 4      // Mix based on distance from center
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
	ofParameter<bool> bDrawFill; // Fill shapes 
	ofParameter<bool> bEnablePlain;
	ofParameter<bool> bDrawShapes; // Enable shape drawing (renamed from bEnableShapes)
	ofParameter<bool> bEnableAnimation; // Enable animation
	ofParameter<bool> bDrawOutline; // Draw text outline
	ofParameter<float> sceneZoom; // Scene zoom factor (0-1, maps to 1x-5x)
	ofParameter<string> sText;

	// Density parameters with enable/reset
	ofParameter<bool> bEnableDensity; // Enable density group
	ofParameter<void> resetDensity; // Reset density group
	ofParameter<void> randomDensity; // Randomize density group
	ofParameter<float> pointsSpacing;
	ofParameter<float> pointDensity;
	ofParameter<float> minSpacing;
	ofParameter<float> contourSampling; // Better contour sampling control

	// Shape parameters with enable/reset
	ofParameter<bool> bEnableShape; // Enable shape group
	ofParameter<void> resetShape; // Reset shape group
	ofParameter<void> randomShape; // Randomize shape group
	ofParameter<int> shapeType;
	ofParameter<float> pointRadius;
	ofParameter<float> pointsRadiusMin;
	ofParameter<float> triangleRatio;
	ofParameter<float> shapeRotation;

	// Simplified color parameters (based on global colors only)
	ofParameter<bool> bEnableColor; // Enable color group
	ofParameter<void> resetColor; // Reset color group
	ofParameter<void> randomColor; // Randomize color group
	ofParameter<int> colorMode; // Simplified: 0=Color1, 1=Color2, 2=Color3, 3=Mix, 4=Distance
	ofParameter<float> colorSpeed;
	ofParameter<float> colorMixFactor; // How colors blend
	ofParameter<bool> bColorByDistance;

	// Global color parameters with enable/reset
	ofParameter<bool> bEnableGlobalColor; // Enable global color group
	ofParameter<void> resetGlobalColor; // Reset global color group
	ofParameter<void> randomGlobalColor; // Randomize global color group
	ofParameter<ofColor> globalColor1;
	ofParameter<ofColor> globalColor2;
	ofParameter<ofColor> globalColor3;

	// Animation parameters with enable/reset
	ofParameter<bool> bEnableAnimationGroup; // Enable animation group
	ofParameter<void> resetAnimation; // Reset animation group
	ofParameter<void> randomAnimation; // Randomize animation group
	ofParameter<int> animationMode;
	ofParameter<float> animSpeed;
	ofParameter<float> noiseSize; // Moved from basic parameters
	ofParameter<float> waveFrequency;
	ofParameter<float> waveAmplitude;
	ofParameter<float> spiralTightness;
	ofParameter<float> pulseIntensity;

	// Connection parameters with enable/reset
	ofParameter<bool> bEnableConnection; // Enable connection group
	ofParameter<void> resetConnection; // Reset connection group
	ofParameter<void> randomConnection; // Randomize connection group
	ofParameter<bool> bDrawConnections;
	ofParameter<float> connectionDistance;
	ofParameter<float> connectionAlpha;
	ofParameter<bool> bOnlyNearConnections;

	// Trail parameters
	ofParameter<bool> bDrawTrails;
	ofParameter<int> trailLength;
	ofParameter<float> trailFade;

	// Global controls
	ofParameter<void> resetAll; // Reset everything to defaults

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
	vector<vec2> sampleStringPoints(const string& s, float ds);
	void drawShape(vec2 position, float size, ShapeType shape, float rotation = 0) const;
	void drawConnections() const;
	void updateTrails();
	ofColor getPointColor(int index, vec2 position, float phase) const;
	vec2 getAnimatedOffset(int index, float phase) const;
	void saveSettings();
	void loadSettings();
	void drawDebugInfo() const; // New: Debug visualization
	
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
	
	// Preset functions (0-9 numerical keys)
	void loadPreset(int presetNumber);

	// Data
	vector<vec2> pointsString;
	vector<vector<vec2>> pointTrails; // For trail effect
	ofTrueTypeFont font;
	float t;
	vec2 textCenter; // Center of text for distance calculations

	ofxPanel gui;
	void refreshPointsString();

};
