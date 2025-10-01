#pragma once

#include "ofMain.h"
#include "ofxGui.h"
using namespace glm;

constexpr const char* ORGANICTEXT = "ARB";
constexpr float MAX_RADIUS = 50.0f;
constexpr float MIN_RADIUS = 1.0f;
constexpr float ZOOM_MAX_X = 10.0f;

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
	OrganicText();
	~OrganicText();

	void setup();
	void draw();
	void keyPressed(ofKeyEventArgs & eventArgs);
	void exit();

private:
	void update();
	void update(ofEventArgs & args);

public:
	string pathSettings = "OrganicText.json";

	ofParameterGroup parameters;
	ofParameterGroup shapeGroup;
	ofParameterGroup densityGroup;
	ofParameterGroup colorGroup; // Color controls
	ofParameterGroup globalColorGroup; // New: Global color controls
	ofParameterGroup animGroup; // Animation controls
	ofParameterGroup connectionGroup; // Connection controls

	// Basic parameters - Simplified
	ofParameter<bool> bDebugDraw;
	ofParameter<bool> bDebugDrawInfo;
	ofParameter<bool> bDrawFill; 
	ofParameter<bool> bDrawShapes; 
	ofParameter<bool> bEnableAnimation; 
	ofParameter<bool> bDrawOutline; 
	ofParameter<float> sceneZoom; 
	ofParameter<string> sText;

	// Density parameters - Removed unused bEnableDensity
	ofParameter<void> resetDensity; 
	ofParameter<void> randomDensity; 
	ofParameter<float> pointsSpacing;
	ofParameter<float> pointDensity;
	ofParameter<float> minSpacing;
	ofParameter<float> contourSampling; 

	// Shape parameters - Removed unused bEnableShape
	ofParameter<void> resetShape; 
	ofParameter<void> randomShape; 
	ofParameter<int> shapeType;
	ofParameter<string> shapeTypeName; // NEW: Display current shape name
	ofParameter<float> pointRadius;
	ofParameter<float> pointsRadiusMin;
	ofParameter<float> triangleRatio;
	ofParameter<float> shapeRotation;

	// Color parameters - Removed unused bEnableColor
	ofParameter<void> resetColor; 
	ofParameter<void> randomColor; 
	ofParameter<int> colorMode; 
	ofParameter<string> colorModeName; // NEW: Display current color mode name
	ofParameter<float> colorSpeed;
	ofParameter<float> colorMixFactor; 
	ofParameter<bool> bColorByDistance;

	// Colors parameters - Simplified, removed unused bEnableGlobalColor
	ofParameter<void> resetGlobalColor; 
	ofParameter<void> randomGlobalColor; 
	ofParameter<ofColor> globalColor1;
	ofParameter<ofColor> globalColor2;
	ofParameter<ofColor> globalColor3;
	
	// NEW: Outline and connection colors
	ofParameter<ofColor> outlineColor;
	ofParameter<ofColor> connectionColor;

	// Animation parameters - Removed redundant bEnableAnimationGroup (use bEnableAnimation)
	ofParameter<void> resetAnimation; 
	ofParameter<void> randomAnimation; 
	ofParameter<int> animationMode;
	ofParameter<string> animationModeName; // NEW: Display current animation mode name
	ofParameter<float> animSpeed;
	ofParameter<float> noiseSize; 
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

private:
	// Event listeners
	ofEventListener e_PointsSize, e_PointsRadius, e_sText, e_PointDensity, e_ContourSampling;
	ofEventListener e_ResetDensity, e_ResetShape, e_ResetColor, e_ResetGlobalColor, e_ResetAnimation, e_ResetConnection, e_ResetAll;
	ofEventListener e_RandomDensity, e_RandomShape, e_RandomColor, e_RandomGlobalColor, e_RandomAnimation, e_RandomConnection;

	// Functions
	vector<vec2> sampleStringPoints(const string& s, float ds);
	void drawShape(vec2 position, float size, ShapeType shape, float rotation = 0) const;
	void drawConnections() const;
	void updateTrails();
	ofColor getPointColor(int index, vec2 position, float phase) const;
	vec2 getAnimatedOffset(int index, float phase) const;
	void drawDebug() const; // Debug visualization
	void drawDebugInfo() const; // Performance information box

public:
	void saveSettings();
	void loadSettings();
	
	// Update mode name strings
	void updateShapeTypeName(int &);
	void updateColorModeName(int &);
	void updateAnimationModeName(int &);

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

private:
	// Data
	vector<vec2> pointsString;
	vector<vector<vec2>> pointTrails; // For trail effect
	ofTrueTypeFont font;
	float t;
	vec2 textCenter; // Center of text for distance calculations

	void refreshPointsString();

	float fps;
	float frameTime;

public:
	ofxPanel gui;

	// Preset functions (0-9 numerical keys)
	void loadPreset(int presetNumber);

};
