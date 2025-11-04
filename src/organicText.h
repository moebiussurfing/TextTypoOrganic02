#pragma once

#include "ofMain.h"
#include "ofxTweenLiteHelper.h"

//----------------------------------------------------------------------------

// OFAPP

// Window size
constexpr int OFWORKS_DEMO_APP_WIDTH = 1200;
constexpr int OFWORKS_DEMO_APP_HEIGHT = 550;

// Default text
constexpr const char * ORGANIC_TEXT_DEFAULT_STRING = "ofWorks";

//----------------------------------------------------------------------------

//TODO: Comment to use internal preset params handling (instead of using an external preset manager)
#define SURFING_USE_EXTERNAL_PRESET_MANAGER

#include "ofxGui.h"
using namespace glm;

// ============================================================================
// DRAWING & ANIMATION CONSTANTS
// ============================================================================

//TODO: when not using glm lib...
#ifndef TWO_PI
constexpr double TWO_PI = 6.283185307179586476925286766559; // 2 * π
#endif

constexpr float ZOOM_GLOBAL_MAX = 1.1f;

// Density Constants
constexpr float DENSITY_SPACING_MIN = 1.0f;
constexpr float DENSITY_SPACING_MAX = 25.0f;
constexpr float DENSITY_MIN_SPACING_MIN = 0.5f;
constexpr float DENSITY_MIN_SPACING_MAX = 15.0f;

// Animation Displacement Constants
constexpr float ANIM_NOISE_MAX = 35.0f;
constexpr float ANIM_WAVE_MAX = 60.0f;
constexpr float ANIM_SPIRAL_MAX = 45.0f;
constexpr float ANIM_PULSE_MAX = 20.0f;

// Animation Frequency Constants
constexpr float ANIM_WAVE_FREQ_MIN = 0.001f;
constexpr float ANIM_WAVE_FREQ_MAX = 0.04f;
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
constexpr float CONNECTIONS_MAX_LINE_WIDTH = 3.f;

// Trails Constants
constexpr float TRAILS_ALPHA_MAX = 255.0f; // Full alpha range
constexpr float TRAILS_LINE_WIDTH_MAX = 5.f;
constexpr float TRAILS_LENGTH_MIN = 3.f; // amount trails per group
constexpr float TRAILS_LENGTH_MAX = 100.f; // amount trails per group - longer trails
constexpr float TRAILS_FADE_MIN = 0.5f; // More transparent at minimum
constexpr float TRAILS_FADE_MAX = 1.0f; // Fully opaque at maximum

// Shape Constants
constexpr float SHAPE_MAX_RADIUS = 50.0f;
constexpr float SHAPE_MIN_RADIUS = 0.0f;
constexpr float SHAPE_ROTATION_SPEED = 0.2f;
constexpr float SHAPE_SIZE_NOISE_SCALE = 0.5f;
constexpr float SHAPE_SIZE_INDEX_SCALE = 0.01f;

constexpr int DEBUG_ALPHA_MAX = 120;
constexpr int DEBUG_ALPHA_MIN_OFFSET = 0;
constexpr float DEBUG_SPEED = 2.0f;

// Outline Constants
constexpr float OUTLINE_WIDTH_BASE = 0.5f;

constexpr float MOUSE_RADIUS_INTERACT_MAX = 100.0f;
constexpr float MOUSE_RADIUS_INTERACT_MIN = 10.0f;

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

	//--

	//TODO: WIP
	// Tween controls for drawing ranges and writing animation
public:
	ofParameterGroup paramsTweens { "Tweens" };
	ofParameter<float> inPoint { "In", 0, 0, 1 };
	ofParameter<float> outPoint { "Out", 1, 0, 1 };

private:
	ofEventListener e_inPoint, e_outPoint;
	// Two extra params for more drawing variations to experiment
	// ofParameter<float> centerPoint{"Center",0.5,0,1};
	// ofParameter<float> widthPoint{"Width",0.15,0,1};
	// ofEventListener e_centerPoint,e_widthPoint;

private:
	ofxTweenLiteHelper<float> tweenInPoint;
	ofxTweenLiteHelper<float> tweenOutPoint;

	//--

public:
	//TODO: WIP: mouse interaction over shapes points
	ofParameter<float> radiusMouse { "radiusMouse", 0.1, 0, 1 };
	mutable glm::vec2 mousePos;

	//--

public:
	// Must set before setup()
	void setTargetFPS(float fps);

	void setup();
	void setup(float fps);

private:
	void setupParams();
	void setupCallbacks();
	void setupTweens();
	void setupGui();
	void setupScene();
	void startup();

public:
	void draw();
	void drawGui();

	void keyPressed(ofKeyEventArgs & eventArgs);
	void exit();

private:
	void update();
	void update(ofEventArgs & args);

public:
	ofParameterGroup parameters; // For gui usage
	// Will include preset settings only when not using an external preset manager

	ofParameterGroup paramsFont;
	ofParameterGroup paramsPreset;
	ofParameterGroup paramsShape;
	ofParameterGroup paramsDensity;
	ofParameterGroup paramsColorModes;
	ofParameterGroup paramsColors;
	ofParameterGroup paramsAnim;
	ofParameterGroup paramsConnections;
	ofParameterGroup paramsTrails;

	ofParameterGroup paramsSessionSettings; // For session status, not preset
	ofParameterGroup paramsInternal; // Some internal settings

	// Basic parameters
	ofParameter<bool> bHelp;
	ofParameter<bool> bDebug;
	ofParameter<bool> bDrawOutline;
	ofParameter<bool> bDrawFill;
	ofParameter<bool> bDrawShapes;
	ofParameter<bool> bEnableAnimation;
	ofParameter<float> zoomGlobal;
	ofParameter<bool> bAutoZoomGlobal;
	ofParameter<std::string> sText;

	// Font parameters
	ofParameter<std::string> fontPath;
	ofParameter<float> fontSize;
	ofParameter<float> letterSpacing;
	ofParameter<void> vResetFont;

	// Density parameters
	ofParameter<void> vResetDensity;
	ofParameter<void> vRandomDensity;
	ofParameter<float> densitySpacing;
	ofParameter<float> densityAmount;

	// Shape parameters
	ofParameter<void> vResetShape;
	ofParameter<void> vRandomShape;
	ofParameter<int> shapeType;
	ofParameter<std::string> shapeTypeName;
	ofParameter<bool> bShapeBack;
	ofParameter<float> shapeSize;
	ofParameter<float> shapeSizeMin;
	ofParameter<float> shapeRatio;
	ofParameter<float> shapeRotation;

	// Color parameters
	ofParameter<void> vResetColor;
	ofParameter<void> vRandomColor;
	ofParameter<int> colorMode;
	ofParameter<std::string> colorModeName;
	ofParameter<float> colorSpeed;
	ofParameter<float> colorMixFactor;
	ofParameter<bool> bColorByDistance;

	// Colors parameters
	ofParameter<void> vResetGlobalColors;
	ofParameter<void> vRandomGlobalColors;
	ofParameter<ofColor> color1;
	ofParameter<ofColor> color2;
	ofParameter<ofColor> color3;
	ofParameter<ofColor> colorOutline;
	ofParameter<ofColor> colorConnection;
	ofParameter<ofColor> colorTrails;

	// Animation parameters
	ofParameter<void> vResetAnimation;
	ofParameter<void> vRandomAnimation;
	ofParameter<int> animationMode;
	ofParameter<std::string> animationModeName;
	ofParameter<float> animSpeed;
	ofParameter<float> animPower;
	ofParameter<float> animWaveFreq;
	ofParameter<float> animIntensity;
	ofParameter<float> animSpiral;
	ofParameter<float> animPulseIntensity;

	// Connection parameters
	ofParameter<void> vResetConnection;
	ofParameter<void> vRandomConnection;
	ofParameter<bool> bDrawConnections;
	ofParameter<float> connectDistance;
	ofParameter<float> connectLineWidth;
	ofParameter<float> connectAlpha;
	ofParameter<bool> bConnectNearOnly;
	ofParameter<float> connectQuality;

	// Trail parameters
	ofParameter<bool> bDrawTrails;
	ofParameter<float> trailLength;
	ofParameter<float> trailLineWidth;
	ofParameter<float> trailFade;

	// Global controls
	ofParameter<void> vResetPreset;
	ofParameter<void> vResetAll;
	ofParameter<void> vRandomAll;

	// Settings
	ofParameter<bool> bAutosave;
	ofParameter<void> vLoadSettigs;
	ofParameter<void> vSaveSettigs;

	// Internal
	ofParameter<bool> bGui;
	ofParameter<bool> bKeys;

private:
	// Event listeners
	ofEventListener e_FontPath, e_vFontSize, e_letterSpacing, e_vResetFont;
	ofEventListener e_DensitySpacing, e_DensityAmount, e_sText;
	ofEventListener e_vResetDensity, e_vResetShape, e_vResetColor;
	ofEventListener e_vResetGlobalColor, e_vResetAnimation, e_vResetConnection, e_vResetAll, e_vResetPreset;
	ofEventListener e_vRandomDensity, e_vRandomShape, e_vRandomColor, e_vRandomGlobalColor, e_vRandomAll;
	ofEventListener e_vRandomAnimation, e_vRandomConnection;
	ofEventListener e_vLoadSettigs, e_vSaveSettigs;
	ofEventListener e_trailLength;

	// Functions
	vector<vec2> sampleStringPoints(const std::string & s, float ds);
	void drawShape(vec2 position, float size, ShapeType shape, float rotation = 0) const;
	void drawShapes();

	void drawConnections() const;

	void initTrails();
	void updateTrails();
	void drawTrails();

	ofColor getPointColor(int index, vec2 position, float phase) const;
	vec2 getAnimatedOffset(int index, float phase) const;

	// Font management
	void loadFont();
	void refreshFont();
	bool bFlagRefreshFont = false; // Avoids multiple calls in a single frame
	void flagRefreshFont();

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
	void resetColorModes();
	void resetGlobalColorParams();
	void resetAnimationParams();
	void resetConnectionParams();
	void resetFonts();
	void resetAll();
	void resetPreset();
	void randomAll();

	// Randomize functions
	void randomizeDensityParams();
	void randomizeShapeParams();
	void randomizeColorModes();
	void randomizeGlobalColorParams();
	void randomizeAnimationParams();
	void randomizeConnectionParams();

private:
	// Data
	vector<vec2> pointsString;
	vector<vector<vec2>> pointTrails;
	ofTrueTypeFont font;
	std::string FONT_DEFAULT;
	float t;
	vec2 textCenter;

	void refreshPointsString();

	//--

	// Fps
	float frameTime;
	float fps;
	float targetFPS = 120.0f;
	bool bDebugLowFPS = false;

	// Settings
	std::string pathSettings = "OrganicText.json";

	// Cached connection count for debug display
	mutable int cachedConnectionCount = 0;

public:
	ofxPanel gui;

	// Collapse groups for preset settings (if included when not using external preset manager)
	void refreshGuiPanel(ofxPanel & ui);
	void refreshGuiGroup(ofxGuiGroup & g);
	void refreshGuiSession();

private:
	std::string sHelp;

	void drawHelp() const;

	void drawDebug() const;
	ofColor colorDebug;
	ofColor colorDebugBlink;

	void windowResized(ofResizeEventArgs & resize); // Auto call when window resized
	void refreshWindowResized();

	// Bench measure time elapsed on draw() in microseconds
	uint64_t timeDrawBenchmark = 0;

	//--

	// Writing Tweening
	// outPoint: limites the end (to the right) of the text that is being drawn.
	// inPoint: limites the starting (from left) of the text that is being drawn.
	// To draw the full text complete (from left to right):
	// outPoint = 1
	// inPoint = 0

public:
	void writeIn() {
		ofLogNotice("OrganicText") << "writeIn()";
		// Animate inPoint from 0 to 1
		inPoint.set(0.0f);
		outPoint.set(1.0f);
		tweenInPoint.start();
	}
	void writeOut() {
		ofLogNotice("OrganicText") << "writeOut()";
		// Animate outPoint from 0 to 1
		inPoint.set(0.0f);
		outPoint.set(0.0f);
		tweenOutPoint.start();
	}
	//void writeFull() {
	//	ofLogNotice("OrganicText") << "writeFull()";
	//	// Full range visible left to right
	//	inPoint.set(0.0f);
	//	outPoint.set(1.0f);
	//}

	bool isTweening() {
		bool b = tweenOutPoint.isRunning() || tweenInPoint.isRunning();
		return b;
	}

	/// @brief Set custom callback for when writeOut tween completes
	void setOnCompleteWriteOut(std::function<void()> callback) {
		tweenOutPoint.onUserCompleteCallback(callback);
	}
	/// @brief Set custom callback for when writeIn tween completes
	void setOnCompleteWriteIn(std::function<void()> callback) {
		tweenInPoint.onUserCompleteCallback(callback);
	}
};
