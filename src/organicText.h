#pragma once

//TODO: Comment to use internal params handling (instead of using an external preset manager)
#define SURFING_USE_EXTERNAL_PRESET_MANAGER

//--

#include "ofMain.h"

#include "ofxTweenLiteHelper.h"
#include "organicTextConstants.h"

//----------------------------------------------------------------------------

#include "ofxGui.h"

using namespace glm;

//----

class OrganicText {
public:
	OrganicText();
	~OrganicText();

	//--

public:
	//TODO: WIP: mouse interaction over shapes points
	ofParameter<float> radiusMouse { "radiusMouse", 0.1, 0, 1 };
	mutable glm::vec2 mousePos;
	ofParameter<bool> bMouseTweaks;

	// Mouse tweaks parameters
	ofParameter<bool> bMouseControlOrigin;
	ofParameter<bool> bMouseHighlightPoints;
	ofParameter<ofColor> colorMouseHighlight;
	ofParameter<float> mouseInfluenceStrength;
	ofParameter<bool> bMouseDisplacePoints;
	ofParameter<float> mouseDisplacePower;
	ofParameter<bool> bMouseScaleShapes;
	ofParameter<float> mouseScalePower;

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
	ofParameterGroup paramsMouseTweaks;

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
	ofParameter<float> colorInner;
	ofParameter<float> colorDistMiddle;
	ofParameter<float> colorAlphaRange;

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
	ofParameter<float> animOriginX;

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
	ofParameter<void> vRandomPreset;
	ofParameter<void> vResetMouseTweaks;
	ofParameter<void> vRandomMouseTweaks;

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
	ofEventListener e_DensitySpacing, e_sText;
	ofEventListener e_vResetDensity, e_vResetShape, e_vResetColor;
	ofEventListener e_vResetGlobalColor, e_vResetAnimation, e_vResetConnection, e_vResetAll, e_vResetPreset;
	ofEventListener e_vRandomDensity, e_vRandomShape, e_vRandomColor, e_vRandomGlobalColor, e_vRandomPreset;
	ofEventListener e_vRandomAnimation, e_vRandomConnection;
	ofEventListener e_vLoadSettigs, e_vSaveSettigs;
	ofEventListener e_trailLength;
	ofEventListener e_vResetMouseTweaks, e_vRandomMouseTweaks;

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

	/// @brief Calculate mouse influence factor for a given position (0-1)
	float getMouseInfluence(vec2 position) const;

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

private:
	std::string ORGANIC_TEXT_FONT_DEFAULT;
	ofTrueTypeFont font;
	vec2 textCenter;
	float textWidth;
	float textHeight;

	// Data
	vector<vec2> pointsString;
	vector<vector<vec2>> pointTrails;
	mutable vector<vec2> pointsAnimatedCache; // Cache animated positions for reuse
	
	mutable vec2 mouseLocalPos;
	mutable bool bMouseInBounds;

public:
	float t; // Time accumulator

private:
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

	//----

	//TODO: WIP
	// Tween controls for drawing ranges and writing animation
public:
	ofParameterGroup paramsTweens { "Tweens" };
	ofParameter<float> inPoint { "In", 0, 0, 1 };
	ofParameter<float> outPoint { "Out", 1, 0, 1 };

private:
	ofEventListener e_inPoint, e_outPoint;
	//TODO:
	// Two extra params for more drawing variations to experiment
	// ofParameter<float> centerPoint{"Center",0.5,0,1};
	// ofParameter<float> widthPoint{"Width",0.15,0,1};
	// ofEventListener e_centerPoint,e_widthPoint;

private:
	ofxTweenLiteHelper<float> tweenInPoint;
	ofxTweenLiteHelper<float> tweenOutPoint;

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
