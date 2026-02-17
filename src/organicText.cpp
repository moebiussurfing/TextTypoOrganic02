#include <algorithm>

#include "organicText.h"

#include "organicTextResetsRandoms.h"
//#include "ofxSurfingOfxGui.h" // ofxGui theme styling

//--------------------------------------------------------------
OrganicText::OrganicText() {
	ofLogVerbose("OrganicText") << "OrganicText()";

	// Initialize data storage
	data = std::make_unique<OrganicTextData>();

	ofAddListener(ofEvents().update, this, &OrganicText::update);
	ofAddListener(ofEvents().windowResized, this, &OrganicText::windowResized);

	//ofxSurfing::setOfxGuiTheme(true); // ofxGui theme styling
}

//--------------------------------------------------------------
OrganicText::~OrganicText() {
	ofLogVerbose("OrganicText") << "~OrganicText()";

	ofRemoveListener(ofEvents().update, this, &OrganicText::update);
	ofRemoveListener(ofEvents().windowResized, this, &OrganicText::windowResized);
}

//--------------------------------------------------------------
void OrganicText::setTargetFPS(float fps) {
	ofLogNotice("OrganicText") << "setTargetFPS() fps:" << fps;

	targetFPS = fps;
}

//--------------------------------------------------------------
void OrganicText::setup(float fps) {
	ofLogNotice("OrganicText") << "setup() fps:" << fps;

	targetFPS = fps;
	setup();
}

//--------------------------------------------------------------
void OrganicText::setup() {
	ofLogNotice("OrganicText") << "setup()";

	setupScene();
	renderer_.setup(this);
	setupParams();
	setupTweens();
	setupCallbacks();
	setupGui();
	startup();

	ofLogNotice("OrganicText") << "Setup complete - Target FPS: " << targetFPS;
}

//--------------------------------------------------------------
void OrganicText::startup() {
	ofLogNotice("OrganicText") << "startup()";

	// // Load font
	// loadFont();
	// refreshFont();

	// Set defaults settings on these methods instead of into setupParams() init params!
	organicTextResetsRandoms::resetAll(this);

	// Load saved settings
	loadSettings();

	refreshWindowResized();
}

//--------------------------------------------------------------
void OrganicText::setupScene() {
	ofLogNotice("OrganicText") << "setupScene()";

	ofSetCircleResolution(100);

	// Initialize
	t = 0.0;
	mouseLocalPos = vec2(0, 0);
	lineLocalPos = vec2(0, 0);
	bMouseInBounds = false;

	// Initialize mode names
	int dummy = 0;
	updateShapeTypeName(dummy);
	updateColorModeName(dummy);
	updateAnimationModeName(dummy);

	colorDebug = ofColor::yellow;

	//--

	// Initialize modifiers will be done in startup()
}

//--

//--------------------------------------------------------------
void OrganicText::setupTweens() {
	ofLogNotice("OrganicText") << "setupTweensCallbacks()";

	// Disable internal JSON settings handling to avoid conflicts
	tweenInPoint.setDisableInternalJsonSettings(true);
	tweenOutPoint.setDisableInternalJsonSettings(true);

	// Tween drawing controls - will be populated in setupTweens()
	paramsTweens.setName("Tweens Drawing");
	paramsTweens.add(inPoint);
	paramsTweens.add(outPoint);

	tweenInPoint.setup(inPoint);
	// Internal callback (always runs for system state)
	tweenInPoint.onCompleteCallback([this]() {
		ofLogNotice("OrganicText") << "tweenInPoint completed";
	});

	tweenOutPoint.setup(outPoint);
	// Internal callback (always runs for system state)
	tweenOutPoint.onCompleteCallback([this]() {
		ofLogNotice("OrganicText") << "tweenOutPoint completed";
	});

	// Set default ease modes
	tweenInPoint.setEase(OF_EASE_CUBIC_IN);
	tweenOutPoint.setEase(OF_EASE_CUBIC_IN);

	// Add tween parameters to paramsTweens group
	paramsTweens.add(tweenInPoint.getParameters());
	paramsTweens.add(tweenOutPoint.getParameters());

	//TODO: Center/Width control In/Out for special fx gradual left-to-right drawing
	// //Two extra params for more drawing variations to experiment
	// paramsTweens.add(centerPoint);
	// paramsTweens.add(widthPoint);
	// // Center/Width control In/Out
	// e_centerPoint = centerPoint.newListener([this](float & v) {
	// 	inPoint = ofClamp(centerPoint - widthPoint, 0.0f, 1.0f);
	// 	outPoint = ofClamp(centerPoint + widthPoint, 0.0f, 1.0f);
	// });
	// e_widthPoint = widthPoint.newListener([this](float & v) {
	// 	inPoint = ofClamp(centerPoint - widthPoint, 0.0f, 1.0f);
	// 	outPoint = ofClamp(centerPoint + widthPoint, 0.0f, 1.0f);
	// });

	// Fix start resseted in out draw range that could be saved unfinished (in settings)
	writeFull();
}

//--

//--------------------------------------------------------------
void OrganicText::setupParams() {
	ofLogNotice("OrganicText") << "setupParams()";

	// Basic parameters
	bGui.set("OrganicText", true);
	bKeys.set("Keys", true);
	bDebug.set("Debug", false);
	bHelp.set("Help", false);

	bDrawFill.set("Draw Fill", true);
	bDrawShapes.set("Draw Shapes", true);
	bRender3D.set("3D Mode", true);
	bEnableAnimation.set("Animate", true);
	const float zoomDefault = (1.0f - ZOOM_GLOBAL_SCALE_MIN) / (ZOOM_GLOBAL_SCALE_MAX - ZOOM_GLOBAL_SCALE_MIN);
	zoomGlobal.set("Zoom", ofClamp(zoomDefault, 0.0f, 1.0f), 0.0f, 1.0f);
	bAutoZoomGlobal.set("Auto Zoom", false);
	sText.set("Text", ORGANIC_TEXT_DEFAULT_STRING);

	// Font parameters
	fontPath.set("Font Path", ofToDataPath(ofToString(ORGANIC_TEXT_FONT_DEFAULT)));
	//fontPath.setSerializable(false);
	fontSize.set("Size", 150, 50, 500);
	letterSpacing.set("Spacing", 0, -1, 1);
	vResetFont.set("Reset");

	//--

	// Density group
	vResetDensity.set("Reset");
	vRandomDensity.set("Random");
	densitySpacing.set("Spacing", 0.2f, 0.05f, 1.f);

	// Shape group
	vResetShape.set("Reset");
	vRandomShape.set("Random");
	shapeType.set("Type", 0, 0, 5);
	shapeTypeName.set("Name", "Circle");
	shapeTypeName.setSerializable(false);
	bShapeBack.set("Back", false);
	bShapesAsObjects3D.set("3D Objects", true);
	bDrawWire.set("Draw Wire", false);
	shapeSize.set("Size", 0.5, 0, 1);
	shapeSizeMin.set("Min Size", 0.3, 0, 1);
	shapeRatio.set("Ratio", .5, 0, 1.0f);
	shapeRotation.set("Rotation", 0, 0, 1.0f);

	// Color group
	vResetColor.set("Reset");
	vRandomColor.set("Random");
	colorMode.set("Mode", 3, 0, 4);
	colorModeName.set("Mode Name", "Mix");
	colorModeName.setSerializable(false);
	colorSpeed.set("Speed", 1.0, 0.1, 5.0);
	colorMixFactor.set("Mix", 0.5, 0.0, 1.0);
	bColorByDistance.set("By Dist", false);
	colorInner.set("Inner", 0.4, 0.0, 1.0);
	colorDistMiddle.set("Dist Middle", 0.7, 0.0, 1.0);
	colorAlphaRange.set("Alpha Range", 0.7, 0.0, 1.0);

	// Colors group
	vResetGlobalColors.set("Reset");
	vRandomGlobalColors.set("Random");
	color1.set("Color 1", ofColor::cyan);
	color2.set("Color 2", ofColor::magenta);
	color3.set("Color 3", ofColor::yellow);
	colorOutline.set("Color Outline", ofColor::black);
	colorConnection.set("Color Connections", ofColor::white);
	colorTrails.set("Color Trails", ofColor::black);

	// Animation group
	vResetAnimation.set("Reset");
	vRandomAnimation.set("Random");
	animationMode.set("Mode", 0, 0, 4);
	animationModeName.set("Name", "Noise");
	animationModeName.setSerializable(false);
	animSpeed.set("Speed", 0.2f, 0.0f, 1.0f);
	animPower.set("Power", 0.1, 0.0, 1.0);
	animWaveFreq.set("Wave Freq", 0.3, 0.0, 1.0);
	animIntensity.set("Intensity", 0.2, 0.0, 1.0);
	animSpiral.set("Spiral", 0.2, 0.0, 1.0);
	animPulseIntensity.set("Pulse", 0.2, 0.0, 1.0);
	animOriginX.set("Origin X", 0.5, 0.0, 1.0);
	animDepthAmount.set("Depth Z (0-1)", 0.35f, 0.0f, 1.0f);
	animDepthFreq.set("Depth Freq", 0.5f, 0.0f, 1.0f);

	// Connection group
	vResetConnection.set("Reset");
	vRandomConnection.set("Random");
	bDrawConnections.set("Draw Connections", false);
	connectDistance.set("Distance", 30, 5, 100);
	connectLineWidth.set("Line Width", 1.0f, 0.1f, CONNECTIONS_MAX_LINE_WIDTH);
	connectAlpha.set("Alpha", 0.5, 0, 1);
	bConnectNearOnly.set("Near Only", true);
	connectQuality.set("Quality", 1.0, 0.1, 1.0);

	// Trail
	bDrawTrails.set("Draw Trails", false);
	trailLength.set("Length", 0.5f, 0, 1.f);
	trailLineWidth.set("Line Width", 1.0f, 0.1f, TRAILS_LINE_WIDTH_MAX);
	trailFade.set("Fade", 0.5f, 0, 1.f);

	// Mouse Tweaks
	bMouseTweaks.set("Mouse Tweaks Enabler", false);
	bMouseControlOrigin.set("x Origin", false);
	bMouseHighlightPoints.set("Highlight", false);
	colorMouseHighlight.set("Color", ofColor(0, 150, 255));
	mouseInfluenceStrength.set("Influence", 0.5, 0.0, 1.0);
	bMouseDisplacePoints.set("Displace", false);
	mouseDisplacePower.set("D Power", 0.5, 0.0, 1.0);
	bMouseScaleShapes.set("Scale", false);
	mouseScalePower.set("S Power", 0.5, 0.0, 1.0);

	// Line tweaks
	bLineTweaks.set("Line Tweaks Enabler", true);
	radiusLineMouse.set("Radius Line Mouse", 1.0f, 0.0f, 1.0f);
	vTrigLineTweaks.set("Trig Line Tweaks");
	vLineFrom.set("From", glm::vec2(-1.0, 0.0), glm::vec2(-1.0, -1.0), glm::vec2(1.0, 1.0));
	vLineTo.set("To", glm::vec2(1.0, 0.0), glm::vec2(-1.0, -1.0), glm::vec2(1.0, 1.0));
	lineTweaksDuration.set("Duration", 5.0f, 0.1f, 10.0f);
	vResetLineTweaks.set("Reset");

	// Background
	vResetBg.set("Reset");
	bBgGradient.set("Background Gradient", false);
	bgColor1.set("Bg Color 1", ofColor(10));
	bgColor2.set("Bg Color 2", ofColor(40));

	//--

	// Settings group
	bAutosave.set("Autosave", true);
	vSaveSettigs.set("Save");
	vLoadSettigs.set("Load");

	// Global reset
	vResetAll.set("Reset All");
	vResetPreset.set("Reset Preset");
	vRandomPreset.set("Random Preset");
	vResetMouseTweaks.set("Reset");
	vRandomMouseTweaks.set("Random");

	//--

	// Fonts groups
	paramsFont.setName("Font");
	paramsFont.add(fontPath);
	paramsFont.add(fontSize);
	paramsFont.add(letterSpacing);
	paramsFont.add(vResetFont);

	//--

	paramsShape.setName("Shape");
	paramsShape.add(bDrawFill);
	paramsShape.add(bDrawWire);
	paramsShape.add(bShapeBack);
	paramsShape.add(shapeType);
	paramsShape.add(shapeTypeName);

	params3dZ.setName("3d Z");
	params3dZ.add(bShapesAsObjects3D);
	params3dZ.add(animDepthAmount);
	params3dZ.add(animDepthFreq);
	paramsShape.add(params3dZ);

	paramsShape.add(shapeSize);
	paramsShape.add(shapeSizeMin);
	paramsShape.add(shapeRatio);
	paramsShape.add(shapeRotation);
	paramsShape.add(vRandomShape);
	paramsShape.add(vResetShape);

	paramsDensity.setName("Density");
	paramsDensity.add(densitySpacing);
	paramsDensity.add(vRandomDensity);
	paramsDensity.add(vResetDensity);

	paramsColors.setName("Colors");
	paramsColors.add(color1);
	paramsColors.add(color2);
	paramsColors.add(color3);
	paramsColors.add(colorConnection);
	paramsColors.add(colorTrails);
	paramsColors.add(vRandomGlobalColors);
	paramsColors.add(vResetGlobalColors);

	paramsColorModes.setName("Color Modes");
	paramsColorModes.add(colorMode);
	paramsColorModes.add(colorModeName);
	paramsColorModes.add(colorSpeed);
	paramsColorModes.add(colorMixFactor);
	paramsColorModes.add(bColorByDistance);
	paramsColorModes.add(colorInner);
	paramsColorModes.add(colorDistMiddle);
	paramsColorModes.add(colorAlphaRange);
	paramsColorModes.add(vRandomColor);
	paramsColorModes.add(vResetColor);

	paramsAnim.setName("Animation");
	paramsAnim.add(bEnableAnimation);
	paramsAnim.add(animationMode);
	paramsAnim.add(animationModeName);
	paramsAnim.add(animSpeed);
	paramsAnim.add(animPower);
	paramsAnim.add(animWaveFreq);
	paramsAnim.add(animIntensity);
	paramsAnim.add(animSpiral);
	paramsAnim.add(animPulseIntensity);
	paramsAnim.add(animOriginX);
	paramsAnim.add(vRandomAnimation);
	paramsAnim.add(vResetAnimation);

	paramsConnections.setName("Connections");
	paramsConnections.add(bDrawConnections);
	paramsConnections.add(connectDistance);
	paramsConnections.add(connectLineWidth);
	paramsConnections.add(connectAlpha);
	paramsConnections.add(connectQuality);
	paramsConnections.add(bConnectNearOnly);

	paramsTrails.setName("Trails");
	paramsTrails.add(bDrawTrails);
	paramsTrails.add(trailLineWidth);
	paramsTrails.add(trailLength);
	paramsTrails.add(trailFade);
	paramsTrails.add(vResetConnection);
	paramsTrails.add(vRandomConnection);

	paramsMouseTweaks.setName("Mouse Tweaks");
	paramsMouseTweaks.add(bMouseTweaks);
	paramsMouseTweaks.add(bMouseControlOrigin);
	paramsMouseTweaks.add(radiusMouse);
	paramsMouseTweaks.add(bMouseHighlightPoints);
	paramsMouseTweaks.add(colorMouseHighlight);
	paramsMouseTweaks.add(mouseInfluenceStrength);
	paramsMouseTweaks.add(bMouseDisplacePoints);
	paramsMouseTweaks.add(mouseDisplacePower);
	paramsMouseTweaks.add(bMouseScaleShapes);
	paramsMouseTweaks.add(mouseScalePower);
	paramsMouseTweaks.add(vResetMouseTweaks);
	paramsMouseTweaks.add(vRandomMouseTweaks);

	paramsLineTweaks.setName("Line Tweaks");
	paramsLineTweaks.add(bLineTweaks);
	paramsLineTweaks.add(radiusLineMouse);
	paramsLineTweaks.add(vTrigLineTweaks);
	paramsLineTweaks.add(vLineFrom);
	paramsLineTweaks.add(vLineTo);
	paramsLineTweaks.add(lineTweaksDuration);
	paramsLineTweaks.add(vResetLineTweaks);

	//Background
	paramsBg.setName("Background");
	paramsBg.add(bgColor1);
	paramsBg.add(bgColor2);
	paramsBg.add(bBgGradient);
	paramsBg.add(vResetBg);

	//--

	// Presets parameters
	// Group all relevant params for presets management
	paramsPreset.setName("OrganicText");
	paramsPreset.add(bDrawShapes);
	paramsPreset.add(bDrawFill);
	paramsPreset.add(bDrawConnections);
	paramsPreset.add(bDrawTrails);
	paramsPreset.add(bEnableAnimation);
	paramsPreset.add(paramsShape);
	paramsPreset.add(paramsDensity);
	paramsPreset.add(paramsColors);
	paramsPreset.add(paramsColorModes);
	paramsPreset.add(paramsAnim);
	paramsPreset.add(paramsConnections);
	paramsPreset.add(paramsTrails);
	paramsPreset.add(paramsMouseTweaks);
	paramsPreset.add(paramsLineTweaks);
	paramsPreset.add(paramsBg);
	paramsPreset.add(vRandomPreset);
	paramsPreset.add(vResetPreset);

	//--

	// Session settings
	paramsSessionSettings.setName("Session Settings");
	paramsSessionSettings.add(vLoadSettigs);
	paramsSessionSettings.add(vSaveSettigs);
	paramsSessionSettings.add(bAutosave);

	paramsInternal.setName("Internal");
	paramsInternal.add(bGui);
	paramsInternal.add(vRandomPreset);
	paramsInternal.add(vResetPreset);
	paramsInternal.add(vResetAll);

	//--

	// Gui parameters
	parameters.setName("OrganicText");
	parameters.add(bRender3D);
	parameters.add(sText);
	parameters.add(paramsFont);
	parameters.add(bAutoZoomGlobal);
	parameters.add(zoomGlobal);
	parameters.add(colorOutline);
	parameters.add(bDebug);
	parameters.add(bHelp);
	parameters.add(bKeys);
	parameters.add(paramsSessionSettings);
	parameters.add(paramsInternal);
	parameters.add(paramsTweens);

#ifndef SURFING_USE_EXTERNAL_PRESET_MANAGER
	// exclude these settings from settings
	// as will be handled by presets manager externally
	parameters.add(paramsPreset);
#endif
}

//--------------------------------------------------------------
void OrganicText::setupCallbacks() {
	ofLogNotice("OrganicText") << "setupCallbacks()";

	// Settings listeners
	e_vLoadSettigs = vLoadSettigs.newListener([this](void) { loadSettings(); });
	e_vSaveSettigs = vSaveSettigs.newListener([this](void) { saveSettings(); });

	// Font listeners
	e_FontPath = fontPath.newListener([this](std::string & s) { loadFont(); });
	e_vFontSize = fontSize.newListener([this](float & f) { loadFont(); });
	e_letterSpacing = letterSpacing.newListener([this](float & f) { flagRefreshFont(); });
	e_vResetFont = vResetFont.newListener([this](void) { organicTextResetsRandoms::resetFonts(this); });

	// Density listeners
	e_DensitySpacing = densitySpacing.newListener([this](float & v) { renderer_.refreshPointsString(); });
	e_sText = sText.newListener([this](std::string & s) { renderer_.refreshPointsString(); });

	// Mode name listeners
	shapeType.addListener(this, &OrganicText::updateShapeTypeName);
	colorMode.addListener(this, &OrganicText::updateColorModeName);
	animationMode.addListener(this, &OrganicText::updateAnimationModeName);

	e_trailLength = trailLength.newListener([this](float & v) {
		int tl = (int)ofMap(v, 0.f, 1.f, TRAILS_LENGTH_MIN, TRAILS_LENGTH_MAX, true);
		data->initTrails(tl);
	});

	//--

	// Reset listeners
	e_vResetDensity = vResetDensity.newListener([this](void) { organicTextResetsRandoms::resetDensityParams(this); });
	e_vResetShape = vResetShape.newListener([this](void) { organicTextResetsRandoms::resetShapeParams(this); });
	e_vResetColor = vResetColor.newListener([this](void) { organicTextResetsRandoms::resetColorModes(this); });
	e_vResetGlobalColor = vResetGlobalColors.newListener([this](void) { organicTextResetsRandoms::resetGlobalColorParams(this); });
	e_vResetAnimation = vResetAnimation.newListener([this](void) { organicTextResetsRandoms::resetAnimationParams(this); });
	e_vResetConnection = vResetConnection.newListener([this](void) { organicTextResetsRandoms::resetConnectionParams(this); });
	e_vRandomPreset = vRandomPreset.newListener([this](void) { organicTextResetsRandoms::randomPreset(this); });
	e_vResetPreset = vResetPreset.newListener([this](void) { organicTextResetsRandoms::resetPreset(this); });
	e_vResetAll = vResetAll.newListener([this](void) { organicTextResetsRandoms::resetAll(this); });

	// Random listeners
	e_vRandomDensity = vRandomDensity.newListener([this](void) { organicTextResetsRandoms::randomizeDensityParams(this); });
	e_vRandomShape = vRandomShape.newListener([this](void) { organicTextResetsRandoms::randomizeShapeParams(this); });
	e_vRandomColor = vRandomColor.newListener([this](void) { organicTextResetsRandoms::randomizeColorModes(this); });
	e_vRandomGlobalColor = vRandomGlobalColors.newListener([this](void) { organicTextResetsRandoms::randomizeGlobalColorParams(this); });
	e_vRandomAnimation = vRandomAnimation.newListener([this](void) { organicTextResetsRandoms::randomizeAnimationParams(this); });
	e_vRandomConnection = vRandomConnection.newListener([this](void) { organicTextResetsRandoms::randomizeConnectionParams(this); });
	e_vResetMouseTweaks = vResetMouseTweaks.newListener([this](void) { organicTextResetsRandoms::resetMouseTweaks(this); });
	e_vRandomMouseTweaks = vRandomMouseTweaks.newListener([this](void) { organicTextResetsRandoms::randomizeMouseTweaks(this); });
	e_vResetLineTweaks = vResetLineTweaks.newListener([this](void) { organicTextResetsRandoms::resetLineTweaks(this); });
	e_vResetBg = vResetBg.newListener([this](void) { organicTextResetsRandoms::resetBg(this); });

	//--

	e_bMouseTweaks = bMouseTweaks.newListener([this](bool & b) {
		ofLogNotice("OrganicText") << "bMouseTweaks: " << b;
	});

	e_mouseInfluenceStrength = mouseInfluenceStrength.newListener([this](float & v) {
		ofLogNotice("OrganicText") << "mouseInfluenceStrength: " << v;
	});

	e_bLineTweaks = bLineTweaks.newListener([this](bool & b) {
		ofLogNotice("OrganicText") << "bLineTweaks: " << b;
	});

	e_vTrigLineTweaks = vTrigLineTweaks.newListener([this](void) {
		ofLogNotice("OrganicText") << "vTrigLineTweaks triggered";

		// Configure start / end positions in text space (normalized -1..1)
		posStart = renderer_.lineTweakToTextSpace(vLineFrom.get());
		posEnd = renderer_.lineTweakToTextSpace(vLineTo.get());

		// Position tween: from left to right
		tweenPosition.setFrom(posStart)
			.setTo(posEnd)
			// .setDuration(10.0f)
			.setDuration(lineTweaksDuration)
			// .setEase(OF_EASE_BOUNCE_INOUT)
			// .setEase(OF_EASE_EXPO_INOUT)
			.setEase(OF_EASE_QUAD_INOUT)
			.setChainFromCurrentValue(false);
		tweenPosition.start();
	});

	e_bAutoZoomGlobal = bAutoZoomGlobal.newListener([this](bool & b) {
		ofLogNotice("OrganicText") << "bAutoZoomGlobal: " << b;
		refreshWindowResized();
	});
}

//--------------------------------------------------------------
void OrganicText::setupGui() {
	ofLogNotice("OrganicText") << "setupGui()";

	gui.setup(parameters);

#ifndef SURFING_USE_EXTERNAL_PRESET_MANAGER
	refreshGuiPanel(gui);
#endif

	// Collapse gui folders
	refreshGuiSession();
}

//--------------------------------------------------------------
void OrganicText::refreshGuiSession() {
	ofLogNotice("OrganicText") << "refreshGuiSession()";

	// Font
	gui.getGroup(paramsFont.getName()).minimize();
	// Internal
	gui.getGroup(paramsInternal.getName()).minimize();
	// Session
	auto & g = gui.getGroup(paramsSessionSettings.getName());
	g.minimize();

	// Tweens
	auto & gt = gui.getGroup(paramsTweens.getName());
	gt.minimize();
	tweenInPoint.refreshGui(gt);
	tweenOutPoint.refreshGui(gt);
	auto & gt1 = gt.getGroup(tweenInPoint.params_.getName());
	auto & gt2 = gt.getGroup(tweenOutPoint.params_.getName());
	gt1.minimize();
	gt2.minimize();
}

//--------------------------------------------------------------
void OrganicText::windowResized(ofResizeEventArgs & resize) {
	ofLogNotice("OrganicText") << "windowResized()";

	refreshWindowResized();
}

//--------------------------------------------------------------
void OrganicText::refreshWindowResized() {
	ofLogNotice("OrganicText") << "refreshWindowResized()";

	// Move the gui panel to right border
	auto pad = 5;
	auto w = gui.getWidth();
	gui.setPosition(ofGetWidth() - w - pad, pad);

	// Auto Zoom
	if (bAutoZoomGlobal) {
		const float textWidth = data->getTextWidth();
		const float textHeight = data->getTextHeight();
		const float pad = ZOOM_GLOBAL_AUTO_PADDING;
		const float availW = ofClamp(ofGetWidth() - pad * 2.0f, 1.0f, 100000.0f);
		const float availH = ofClamp(ofGetHeight() - pad * 2.0f, 1.0f, 100000.0f);
		if (textWidth > 0.0f && textHeight > 0.0f) {
			const float scaleX = availW / textWidth;
			const float scaleY = availH / textHeight;
			const float targetScale = ofClamp(std::min(scaleX, scaleY), ZOOM_GLOBAL_SCALE_MIN, ZOOM_GLOBAL_SCALE_MAX);
			const float range = ZOOM_GLOBAL_SCALE_MAX - ZOOM_GLOBAL_SCALE_MIN;
			const float normalized = (range > 0.0f) ? ((targetScale - ZOOM_GLOBAL_SCALE_MIN) / range) : 0.0f;
			zoomGlobal = ofClamp(normalized, 0.0f, 1.0f);
		}
	}
}

//--

//--------------------------------------------------------------
void OrganicText::flagRefreshFont() {
	ofLogNotice("OrganicText") << "flagRefreshFont()";

	bFlagRefreshFont = true;
}

//--------------------------------------------------------------
void OrganicText::loadFont() {
	ofLogNotice("OrganicText") << "loadFont()";

	bool success = font.load(fontPath.get(), fontSize.get(), false, false, true);

	if (success) {
		ofLogNotice("OrganicText") << "Font loaded: " << fontPath.get() << " @ " << fontSize.get() << "px";
		baseSpaceSize = font.getSpaceSize();
	} else {
		ofLogError("OrganicText") << "Failed to load font: " << fontPath.get();

		success = font.load(fontPath.get(), fontSize.get(), false, false, true);
		if (success) {
			ofLogNotice("OrganicText") << "Forced font loaded: " << fontPath.get() << " @ " << fontSize.get() << "px";
			baseSpaceSize = font.getSpaceSize();
		} else {
			ofLogError("OrganicText") << "Failed to load font: " << fontPath.get();
			ofLogFatalError("OrganicText") << "Failed last try to load OF_TTF font.";
			return;
		}
	}
}

//--------------------------------------------------------------
void OrganicText::refreshFont() {
	ofLogNotice("OrganicText") << "refreshFont(): " << fontPath.get();

	const float spMin = 0.2f;
	const float spMax = 4.f;
	float sp = 1.f;
	if (letterSpacing < 0)
		sp = ofMap(letterSpacing, 0, -1, 1, spMin, true);
	else if (letterSpacing > 0)
		sp = ofMap(letterSpacing, 0, 1, 1, spMax, true);
	if (baseSpaceSize <= 0.0f) {
		baseSpaceSize = font.getSpaceSize();
	}
	font.setSpaceSize(baseSpaceSize * sp);
	font.setLetterSpacing(sp);

	renderer_.refreshPointsString();
}

//--

//--------------------------------------------------------------
void OrganicText::update(ofEventArgs & args) {
	update();
}

//--------------------------------------------------------------
void OrganicText::update() {
	renderer_.update();
}

bool OrganicText::isLineTweaksRunning() const {
	return bLineTweaks.get() && tweenPosition.isRunning();
}

//--

void OrganicText::draw() {

	// Background
	if (bBgGradient) {
		ofxDrawBgGradient(bgColor1, bgColor2);
	} else {
		ofBackground(bgColor1);
	}

	renderer_.draw();
}

//--------------------------------------------------------------
void OrganicText::drawDebugOverlay() {
	if (!bDebug) return;

	// Layer: Debug (drawn before panels and outside postprocessing)
	renderer_.drawDebug();

	if (bDebugLowFPS) {
		ofPushStyle();
		ofNoFill();
		ofSetLineWidth(2);
		ofSetColor(colorDebug);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofPopStyle();

		// Low FPS warning
		std::string s = "LOW FPS";
		auto bf = ofBitmapFont();
		ofDrawBitmapStringHighlight(
			s,
			ofGetWidth() / 2 - bf.getBoundingBox(s, 0, 0).getWidth() / 2,
			bf.getBoundingBox(s, 0, 0).getHeight(),
			ofColor::yellow,
			ofColor::black);
	}
}

//--------------------------------------------------------------
void OrganicText::drawGui() {
	if (!bGui) return;

	gui.draw();

	if (bHelp) {
		drawHelp();
	}
}

//--

//--------------------------------------------------------------
void OrganicText::drawHelp() const {
	ofPushMatrix();
	ofPushStyle();

	int totalPoints = data->getPointCount();

	int totalTrailPoints = 0;
	const auto & pointTrails = data->getTrails();
	for (const auto & trail : pointTrails) {
		totalTrailPoints += trail.size();
	}

	// Use cached connection count from last draw
	int activeConnections = cachedConnectionCount;

	std::string perfStatus = (fps >= (targetFPS * 0.9f)) ? "GOOD" : ((fps <= (targetFPS * 0.5f)) ? "OK" : "POOR");
	ofColor perfColor = (fps >= (targetFPS * 0.9f)) ? ofColor(100, 255, 100) : ((fps >= (targetFPS * 0.5f) ? ofColor(255, 255, 100) : ofColor(255, 100, 100)));

	// Map spacing (0-1 normalized)
	float finalSpacing = ofMap(densitySpacing.get(), 0, 1, DENSITY_SPACING_MIN, DENSITY_SPACING_MAX, true);

	std::vector<std::string> s;
	s.push_back("ORGANIC");
	s.push_back("TEXT");
	s.push_back("");
	s.push_back("PERFORMANCE");
	s.push_back("FPS      " + ofToString(fps, 0) + " (" + ofToString(targetFPS, 0) + ") " + perfStatus);
	s.push_back("Frame t  " + ofToString(frameTime, 0) + " ms");
	s.push_back("Draw()   " + ofToString(timeDrawBenchmark / 1000) + " ms");
	s.push_back("         " + ofToString(timeDrawBenchmark % 1000) + " mics");
	s.push_back("");
	s.push_back("GEOMETRY");
	s.push_back("Points   " + ofToString(totalPoints));
	s.push_back("Shapes   " + ofToString(bDrawShapes.get() ? totalPoints : 0));
	s.push_back("Connects " + ofToString(bDrawConnections.get() ? activeConnections : 0));
	s.push_back("Trails   " + ofToString(bDrawTrails.get() ? totalTrailPoints : 0));
	s.push_back("");
	s.push_back("CONFIG");
	s.push_back("FSpacing " + ofToString(finalSpacing, 2));
	s.push_back("Animate  " + std::string(bEnableAnimation.get() ? "On" : "Off"));
	s.push_back("   Mode  " + animationModeName.get());
	s.push_back("Shape    " + shapeTypeName.get());
	s.push_back("Color    " + colorModeName.get());
	if (bKeys) {
		s.push_back("");
		s.push_back("------------------------");
		s.push_back("");
		s.push_back("KEYS");
		s.push_back("");
		s.push_back("D        Debug");
		s.push_back("H        Help");
		s.push_back("< >      Zoom");
		s.push_back("- +      Density");
		s.push_back("Up Down  Speed");
		s.push_back("");
		s.push_back("MODES");
		s.push_back("A        Animation");
		s.push_back("a          " + std::string(!bEnableAnimation.get() ? "On" : "Off"));
		s.push_back("C        Color");
		s.push_back("");
		s.push_back("DRAW");
		s.push_back("S        Shapes");
		s.push_back("F          Fill");
		s.push_back("C        Connections");
		s.push_back("T        Trails");
		s.push_back("");
		s.push_back("BACKSP   Reset all");
	}

	float boxWidth = 218;
	float lineHeight = 16;
	float padding = 10;
	float boxHeight = s.size() * lineHeight + padding * 2;

	float boxX;
	float boxY;

	if (bGui) {
		// linked to gui anchor
		//// left of the panel
		//boxX = gui.getPosition().x - boxWidth - 5;
		//boxY = gui.getPosition().y - 1;
		// right of the panel
		boxX = gui.getPosition().x + gui.getWidth() + 5;
		boxY = gui.getPosition().y - 1;
	} else {
		// screen border
		boxX = ofGetWidth() - boxWidth - 15;
		boxY = 15;
	}

	// Background rectangle
	ofSetColor(0, 0, 0, 220);
	ofFill();
	ofDrawRectRounded(boxX, boxY, boxWidth, boxHeight, 4);

	// Text
	for (size_t i = 0; i < s.size(); i++) {
		float textX = boxX + padding;
		float textY = boxY + padding + (i + 1) * lineHeight - 2;

		if (s[i].find("FPS") != std::string::npos) {
			ofSetColor(perfColor);
		} else if (s[i].find("Points") != std::string::npos || s[i].find("Connects") != std::string::npos) {
			if (totalPoints > 1500 || activeConnections > 5000) {
				ofSetColor(255, 150, 0);
			} else {
				ofSetColor(255);
			}
		} else {
			ofSetColor(255); //white
		}

		ofDrawBitmapString(s[i], textX, textY);
	}

	ofPopStyle();
	ofPopMatrix();
}

//--

//--------------------------------------------------------------
void OrganicText::saveSettings() {
	ofLogNotice("OrganicText") << "saveSettings()";

	ofJson settings;
	ofSerialize(settings, parameters);
	bool b = ofSavePrettyJson(pathSettings, settings);
	if (b)
		ofLogNotice("OrganicText") << "Settings saved";
	else
		ofLogError("OrganicText") << "Unable to save settings!";
}

//--------------------------------------------------------------
void OrganicText::loadSettings() {
	ofLogNotice("OrganicText") << "loadSettings()";

	ofFile file(pathSettings);
	if (file.exists()) {
		ofJson settings = ofLoadJson(pathSettings);
		ofDeserialize(settings, parameters);
		ofLogNotice("OrganicText") << "Settings loaded";
	} else
		ofLogWarning("OrganicText") << "Unable to load settings file or not found!";
}

//--------------------------------------------------------------
// MODE NAME UPDATES
//--------------------------------------------------------------

void OrganicText::updateShapeTypeName(int &) {
	const char * names[] = { "Circle", "Rectangle", "Triangle", "Star", "Cross", "Point" };
	shapeTypeName.set(names[(int)ofClamp(shapeType.get(), 0, 5)]);
}

void OrganicText::updateColorModeName(int &) {
	const char * names[] = { "Color 1", "Color 2", "Color 3", "Mix", "Distance" };
	colorModeName.set(names[(int)ofClamp(colorMode.get(), 0, 4)]);
}

void OrganicText::updateAnimationModeName(int &) {
	const char * names[] = { "Noise", "Wave", "Spiral", "Pulse", "Orbit" };
	animationModeName.set(names[(int)ofClamp(animationMode.get(), 0, 4)]);
}

//--------------------------------------------------------------
void OrganicText::refreshGuiPanel(ofxPanel & ui) {
	ofLogNotice("OrganicText") << "refreshGuiPanel() " << ui.getName();

	ui.getGroup(paramsDensity.getName()).minimizeAll();
	ui.getGroup(paramsShape.getName()).minimizeAll();
	ui.getGroup(paramsColorModes.getName()).minimizeAll();
	ui.getGroup(paramsColors.getName()).minimizeAll();
	ui.getGroup(paramsAnim.getName()).minimizeAll();
	ui.getGroup(paramsConnections.getName()).minimizeAll();
	ui.getGroup(paramsMouseTweaks.getName()).minimizeAll();
	ui.getGroup(paramsLineTweaks.getName()).minimizeAll();
	ui.minimizeAll();
}

//--------------------------------------------------------------
void OrganicText::refreshGuiGroup(ofxGuiGroup & g) {
	ofLogNotice("OrganicText") << "refreshGuiGroup() " << g.getName();

	g.getGroup(paramsDensity.getName()).minimizeAll();
	g.getGroup(paramsShape.getName()).minimizeAll();
	g.getGroup(paramsColorModes.getName()).minimizeAll();
	g.getGroup(paramsColors.getName()).minimizeAll();
	g.getGroup(paramsAnim.getName()).minimizeAll();
	g.getGroup(paramsConnections.getName()).minimizeAll();
	g.getGroup(paramsMouseTweaks.getName()).minimizeAll();
	g.getGroup(paramsLineTweaks.getName()).minimizeAll();
	g.minimizeAll();
}

//--

//--------------------------------------------------------------
void OrganicText::keyPressed(ofKeyEventArgs & eventArgs) {
	if (!bKeys) return;

	const int key = eventArgs.key;
	ofLogNotice("OrganicText") << "keyPressed() " << char(key);

	//--

	if (key == 'd') {
		bDebug.set(!bDebug.get());
	} else if (key == 'h') {
		bHelp.set(!bHelp.get());
	}

	else if (key == OF_KEY_LEFT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() - 0.01f, 0.0f, 1.0f));
	} else if (key == OF_KEY_RIGHT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() + 0.01f, 0.0f, 1.0f));
	}

	else if (key == OF_KEY_UP) {
		animSpeed.set(ofClamp(animSpeed.get() + 0.01f, animSpeed.getMin(), animSpeed.getMax()));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(ofClamp(animSpeed.get() - 0.01f, animSpeed.getMin(), animSpeed.getMax()));
	}

	else if (key == 'C') {
		colorMode.set((colorMode.get() + 1) % 5);
	} else if (key == 'A') {
		animationMode.set((animationMode.get() + 1) % 5);
	}

	else if (key == '+' || key == '=') {
		densitySpacing.set(ofClamp(densitySpacing.get() + 0.05f, densitySpacing.getMin(), densitySpacing.getMax()));
	} else if (key == '-') {
		densitySpacing.set(ofClamp(densitySpacing.get() - 0.05f, densitySpacing.getMin(), densitySpacing.getMax()));
	}

	else if (key == 'S') {
		bDrawShapes.set(!bDrawShapes.get());
	}

	else if (key == 'F') {
		bDrawFill.set(!bDrawFill.get());
	}

	else if (key == 'C') {
		bDrawConnections.set(!bDrawConnections.get());
	}

	else if (key == 'T') {
		bDrawTrails.set(!bDrawTrails.get());
	}

	else if (key == 'a') {
		bEnableAnimation.set(!bEnableAnimation.get());
	}

	else if (key == OF_KEY_BACKSPACE) {
		organicTextResetsRandoms::resetAll(this);
	}
}

//--

//--------------------------------------------------------------
void OrganicText::exit() {
	ofLogNotice("OrganicText") << "exit()";

	// Save tween settings
	tweenInPoint.exit();
	tweenOutPoint.exit();

	if (bAutosave) saveSettings();
}

//--
