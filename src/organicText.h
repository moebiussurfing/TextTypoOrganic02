#pragma once

#include "ofMain.h"
#include "ofxGui.h"
using namespace glm;

constexpr const char * ORGANICTEXT = "OF TEXT";
constexpr float MAX_RADIUS = 50.0f;
constexpr float MIN_RADIUS = 0.0f;
constexpr float ZOOM_MAX_X = 10.0f;

// ============================================================================
// DRAWING & ANIMATION CONSTANTS
// ============================================================================

// Density Constants
constexpr float DENSITY_SPACING_MIN = 1.0f;
constexpr float DENSITY_SPACING_MAX = 25.0f;
constexpr float DENSITY_MIN_SPACING_MIN = 0.5f;
constexpr float DENSITY_MIN_SPACING_MAX = 15.0f;

// Animation Displacement Constants
constexpr float ANIM_NOISE_MAX = 35.0f;
constexpr float ANIM_WAVE_MAX = 60.0f;
constexpr float ANIM_SPIRAL_MAX = 45.0f;
constexpr float ANIM_PULSE_MAX = 50.0f;

// Animation Frequency Constants
constexpr float ANIM_WAVE_FREQ_MIN = 0.001f;
constexpr float ANIM_WAVE_FREQ_MAX = 0.08f;
constexpr float ANIM_SPIRAL_TIGHT_MIN = 0.002f;
constexpr float ANIM_SPIRAL_TIGHT_MAX = 0.025f;

// Time System
constexpr float BASE_TIME_STEP = 0.008f;

// Color Constants
constexpr float COLOR_DISTANCE_MAX = 250.0f;
constexpr float COLOR_DISTANCE_INNER = 0.4f;
constexpr float COLOR_DISTANCE_MIDDLE = 0.7f;
constexpr float COLOR_ALPHA_CENTER = 255.0f;
constexpr float COLOR_ALPHA_EDGE = 80.0f;

// Connection Constants
constexpr int CONNECTIONS_SEARCH_NEAR = 50;
constexpr int CONNECTIONS_SEARCH_FAR = 100;
constexpr int CONNECTIONS_MAX_PER_POINT_NEAR = 3;
constexpr int CONNECTIONS_MAX_PER_POINT_FAR = 8;

// Trail Constants
constexpr float TRAIL_MAX_ALPHA = 180.0f;

// Shape Constants
constexpr float SHAPE_ROTATION_SPEED = 0.2f;
constexpr float SHAPE_SIZE_NOISE_SCALE = 0.5f;
constexpr float SHAPE_SIZE_INDEX_SCALE = 0.01f;

// Outline Constants
constexpr float OUTLINE_WIDTH_BASE = 0.5f;

// ============================================================================

enum ShapeType {
	SHAPE_CIRCLE = 0,
	SHAPE_RECTANGLE = 1,
	SHAPE_TRIANGLE = 2,
	SHAPE_STAR = 3,
	SHAPE_CROSS = 4,
	SHAPE_POINT = 5
};

enum ColorMode {
	COLOR_GLOBAL_1 = 0,
	COLOR_GLOBAL_2 = 1,
	COLOR_GLOBAL_3 = 2,
	COLOR_GLOBAL_MIX = 3,
	COLOR_DISTANCE = 4
};

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
private:
	void setupGui();
	void setupParams();
	void setupCallbacks();
public:
	void draw();
	void keyPressed(ofKeyEventArgs & eventArgs);
	void exit();

	// Configuration before setup()
	void setTargetFPS(float fps) { targetFPS = fps; }

private:
	void update();
	void update(ofEventArgs & args);

private:
	string pathSettings = "OrganicText.json";
	float targetFPS = 120.0f;

public:
	ofParameterGroup parameters;
	ofParameterGroup paramsFont;
	ofParameterGroup paramsShape;
	ofParameterGroup paramsDensity;
	ofParameterGroup paramsColorModes;
	ofParameterGroup paramsColors;
	ofParameterGroup paramsAnim;
	ofParameterGroup paramsConnections;
	ofParameterGroup paramsSettings;

	// Basic parameters
	ofParameter<bool> bDebugDraw;
	ofParameter<bool> bDebugDrawInfo;
	ofParameter<bool> bDrawShapesFill;
	ofParameter<bool> bDrawShapes;
	ofParameter<bool> bEnableAnimation;
	ofParameter<bool> bDrawOutline;
	ofParameter<float> zoomGlobal;
	ofParameter<string> sText;

	// Font parameters
	ofParameter<string> fontPath;
	ofParameter<float> fontSize;

	// Density parameters
	ofParameter<void> resetDensity;
	ofParameter<void> randomDensity;
	ofParameter<float> densitySpacing; // Renamed from densityPointsSpacing
	ofParameter<float> densityAmount; // Renamed from densityPoints
	ofParameter<float> densityMinGap; // Renamed from densityMinSpacing

	// Shape parameters
	ofParameter<void> resetShape;
	ofParameter<void> randomShape;
	ofParameter<int> shapeType;
	ofParameter<string> shapeTypeName;
	ofParameter<float> shapePointRadius; // Renamed from shapePointRadius
	ofParameter<float> shapePointsRadiusMin; // Renamed from shapePointsRadiusMin
	ofParameter<float> shapeTriangleRatio;
	ofParameter<float> shapeRotation;

	// Color parameters
	ofParameter<void> resetColor;
	ofParameter<void> randomColor;
	ofParameter<int> colorMode;
	ofParameter<string> colorModeName;
	ofParameter<float> colorSpeed;
	ofParameter<float> colorMixFactor; // Renamed from colorMixFactor
	ofParameter<bool> bColorByDistance;

	// Colors parameters
	ofParameter<void> resetGlobalColors;
	ofParameter<void> randomGlobalColors;
	ofParameter<ofColor> color1;
	ofParameter<ofColor> color2;
	ofParameter<ofColor> color3;
	ofParameter<ofColor> colorOutline;
	ofParameter<ofColor> colorConnection;
	ofParameter<ofColor> colorTrails;

	// Animation parameters
	ofParameter<void> resetAnimation;
	ofParameter<void> randomAnimation;
	ofParameter<int> animationMode;
	ofParameter<string> animationModeName;
	ofParameter<float> animSpeed;
	ofParameter<float> animPower;
	ofParameter<float> animWaveFreq; // Renamed from animWaveFrequency
	ofParameter<float> animIntensity;
	ofParameter<float> animSpiral;
	ofParameter<float> animPulseIntensity; // Renamed from animPulseIntensity

	// Connection parameters
	ofParameter<void> resetConnection;
	ofParameter<void> randomConnection;
	ofParameter<bool> bDrawConnections;
	ofParameter<float> connectDistance; // Renamed from connectionsDistance
	ofParameter<float> connectAlpha; // Renamed from connectionsAlpha
	ofParameter<bool> bConnectNearOnly; // Renamed from bConnectionOnlyNear
	ofParameter<float> connectQuality; // Renamed from connectionQuality

	// Trail parameters
	ofParameter<bool> bDrawTrails;
	ofParameter<int> trailLength;
	ofParameter<float> trailFade;

	// Global controls
	ofParameter<void> resetAll;
	
	// Settings
	ofParameter<bool> bAutosave;
	ofParameter<void> vLoadSettigs;
	ofParameter<void> vSaveSettigs;

private:
	// Event listeners
	ofEventListener e_FontPath, e_FontSize;
	ofEventListener e_DensitySpacing, e_DensityAmount, e_sText;
	ofEventListener e_ResetDensity, e_ResetShape, e_ResetColor, e_ResetGlobalColor, e_ResetAnimation, e_ResetConnection, e_ResetAll;
	ofEventListener e_RandomDensity, e_RandomShape, e_RandomColor, e_RandomGlobalColor, e_RandomAnimation, e_RandomConnection;
	ofEventListener e_vLoadSettigs, e_vSaveSettigs;
	
	// Functions
	vector<vec2> sampleStringPoints(const string & s, float ds);
	void drawShape(vec2 position, float size, ShapeType shape, float rotation = 0) const;
	void drawConnections() const;
	void updateTrails();
	ofColor getPointColor(int index, vec2 position, float phase) const;
	vec2 getAnimatedOffset(int index, float phase) const;
	void drawDebug() const;
	void drawDebugInfo() const;

	// Font management
	void reloadFont();

public:
	void saveSettings();
	void loadSettings();

private:
	void updateShapeTypeName(int &);
	void updateColorModeName(int &);
	void updateAnimationModeName(int &);

public:
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
	vector<vector<vec2>> pointTrails;
	ofTrueTypeFont font;
	float t;
	vec2 textCenter;

	void refreshPointsString();

	// Fps
	float fps;
	float frameTime;

	// Cached connection count for debug display
	mutable int cachedConnectionCount = 0;

public:
	ofxPanel gui;

	void loadPreset(int presetNumber);
};
