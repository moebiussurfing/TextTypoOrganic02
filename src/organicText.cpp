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
		bKeys.set("Keys", false);
		bDebug.set("Debug", false);
		bHelp.set("Help", false);
		
		bDrawFill.set("Draw Fill", true);
		bDrawShapes.set("Draw Shapes", true);
		bEnableAnimation.set("Animate", true);
		bDrawOutline.set("Draw Outline", false);
		outlineThickness.set("Thickness", 0.15f, 0.0f, 1.0f);
		zoomGlobal.set("Zoom", 0.0f, 0.0f, 1.0f);
		bAutoZoomGlobal.set("Auto Zoom", true);
		sText.set("Text", ORGANIC_TEXT_DEFAULT_STRING);
		bMouseTweaks.set("Mouse Tweaks Enabled", true);
		
		// Font parameters
		fontPath.set("Font Path", ofToString(ORGANIC_TEXT_FONT_DEFAULT));
		fontPath.setSerializable(false);
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
		bDrawOutline.set("Draw Outline", false);
		bShapeBack.set("Back", false);
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
		bMouseControlOrigin.set("x Origin", false);
		bMouseHighlightPoints.set("Highlight", false);
		colorMouseHighlight.set("Color", ofColor(0, 150, 255));
		mouseInfluenceStrength.set("Influence", 0.5, 0.0, 1.0);
		bMouseDisplacePoints.set("Displace", false);
		mouseDisplacePower.set("D Power", 0.5, 0.0, 1.0);
		bMouseScaleShapes.set("Scale", false);
		mouseScalePower.set("S Power", 0.5, 0.0, 1.0);
		
		//--
		
		// Settings group
		bAutosave.set("Autosave", false);
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
		paramsShape.add(bShapeBack);
		paramsShape.add(shapeType);
		paramsShape.add(shapeTypeName);
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
		paramsMouseTweaks.add(bMouseControlOrigin);
		paramsMouseTweaks.add(radiusMouse);
		paramsMouseTweaks.add(bMouseHighlightPoints);
		paramsMouseTweaks.add(colorMouseHighlight);
		paramsMouseTweaks.add(bMouseTweaks);
		paramsMouseTweaks.add(mouseInfluenceStrength);
		paramsMouseTweaks.add(bMouseDisplacePoints);
		paramsMouseTweaks.add(mouseDisplacePower);
		paramsMouseTweaks.add(bMouseScaleShapes);
		paramsMouseTweaks.add(mouseScalePower);
		paramsMouseTweaks.add(vResetMouseTweaks);
		paramsMouseTweaks.add(vRandomMouseTweaks);
		
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
		parameters.add(sText);
		parameters.add(paramsFont);
		parameters.add(bAutoZoomGlobal);
		parameters.add(zoomGlobal);
		parameters.add(bDrawOutline);
		parameters.add(outlineThickness);
		parameters.add(colorOutline);
		parameters.add(bDebug);
		parameters.add(bHelp);
		parameters.add(bKeys);
		parameters.add(paramsSessionSettings);
		parameters.add(paramsInternal);
		parameters.add(paramsTweens);
		parameters.add(bMouseTweaks);
		
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
		e_DensitySpacing = densitySpacing.newListener([this](float & v) { refreshPointsString(); });
		e_sText = sText.newListener([this](std::string & s) { refreshPointsString(); });
		
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
	
		//--
		
		e_bMouseTweaks = bMouseTweaks.newListener([this](bool & b) {
			ofLogNotice("OrganicText") << "bMouseTweaks: " << b;
		});
		
		e_mouseInfluenceStrength = mouseInfluenceStrength.newListener([this](float & v) {
			ofLogNotice("OrganicText") << "mouseInfluenceStrength: " << v;
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
			auto ww = 2560; // callibarted for QHD / 2K screen but will work ok for others
			zoomGlobal = ofMap(ofGetWidth(), 1200, ww, 0.f, 1.0f, false);
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
		} else {
			ofLogError("OrganicText") << "Failed to load font: " << fontPath.get();
			
			success = font.load(fontPath.get(), fontSize.get(), false, false, true);
			if (success) {
				ofLogNotice("OrganicText") << "Forced font loaded: " << fontPath.get() << " @ " << fontSize.get() << "px";
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
		
		font.setSpaceSize(font.getSpaceSize() * letterSpacing);
		
		const float spMin = 0.2f;
		const float spMax = 4.f;
		float sp = 1.f;
		if (letterSpacing < 0)
		sp = ofMap(letterSpacing, 0, -1, 1, spMin, true);
		else if (letterSpacing > 0)
		sp = ofMap(letterSpacing, 0, 1, 1, spMax, true);
		font.setLetterSpacing(sp);
		
		refreshPointsString();
	}
	
	//--
	
	//--------------------------------------------------------------
	void OrganicText::update(ofEventArgs & args) {
		update();
	}
	
	//--------------------------------------------------------------
	void OrganicText::update() {
		if (bEnableAnimation.get()) {
			float dt = ofGetLastFrameTime();
			float normalizedDt = dt / (1.0f / targetFPS);
			t += BASE_TIME_STEP * animSpeed.get() * ANIM_SPEED_MAX * normalizedDt;
		}
		
		fps = ofGetFrameRate();
		frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);
		
		bDebugLowFPS = (fps < (targetFPS * 0.75f));
		
		//TODO: improve this flag and avoid re calling system
		if (bFlagRefreshFont) {
			refreshFont();
			bFlagRefreshFont = false;
		}
		
		//--
		
		// Mouse coordinate transformation
		// Convert window coordinates to local text coordinates
		mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
		
		// Apply inverse transformations (same as in draw())
		float zoomFactor = 1.0f + (zoomGlobal.get() * ZOOM_GLOBAL_MAX);
		float centerX = ofGetWidth() * 0.5f;
		float centerY = ofGetHeight() * 0.5f;
		
		// Step 1: Translate from window to center
		vec2 translated = mousePos - vec2(centerX, centerY);
		
		// Step 2: Inverse scale (divide by zoom)
		vec2 scaled = translated / zoomFactor;
		
		// Step 3: Translate to text origin (inverse of text centering)
		float textOffsetX = -data->getTextWidth() * 0.5f;
		float textOffsetY = data->getTextHeight() * 0.5f;
		mouseLocalPos = scaled - vec2(textOffsetX, textOffsetY);
		
		// Check if mouse is within text bounds
		bMouseInBounds = (mouseLocalPos.x >= 0 && mouseLocalPos.x <= data->getTextWidth() && mouseLocalPos.y >= -data->getTextHeight() && mouseLocalPos.y <= 0);
		
		if (bDebug) {
			// Smooth alpha blinking using sine wave
			float t = ofGetElapsedTimef(); // Elapsed time in seconds
			float speed = DEBUG_SPEED; // Blink speed (cycles per second)
			float alpha = (sin(glm::two_pi<float>() * speed * t) * 0.5f + 0.5f) * DEBUG_ALPHA_MAX + DEBUG_ALPHA_MIN_OFFSET;
			// sin oscillates -1..1 → remap to 0..1 → scale to 0..255
			
			colorDebugBlink = ofColor(colorDebug.r, colorDebug.g, colorDebug.b, static_cast<int>(alpha));
		}
		
		//--
		
		// Update tweens
		tweenInPoint.update();
		tweenOutPoint.update();
		
		//--
		
	}
	
	//--
	
	// @brief Samples points along the outlines of the given string at intervals of ds.
	//--------------------------------------------------------------
	vector<vec2> OrganicText::sampleStringPoints(const std::string & s, float ds) {
		ofLogNotice("OrganicText") << "sampleStringPoints() s:" << s << ", ds:" << ds;
		
		vector<vec2> points;
		if (s.empty()) return points;
		
		vector<ofPath> paths = font.getStringAsPoints(s, true, false);
		
		for (auto & path : paths) {
			vector<ofPolyline> polylines = path.getOutline();
			
			for (auto & polyline : polylines) {
				if (polyline.size() == 0) continue;
				
				float totalLength = polyline.getPerimeter();
				int numSamples = static_cast<int>(totalLength / ds);
				numSamples = ofClamp(numSamples, 3, 100000);
				
				for (int i = 0; i < numSamples; i++) {
					float position = static_cast<float>(i) / static_cast<float>(numSamples - 1);
					vec2 point = polyline.getPointAtPercent(position);
					points.push_back(point);
				}
			}
		}
		
		return points;
	}
	
	//--------------------------------------------------------------
	void OrganicText::refreshPointsString() {
		ofLogNotice("OrganicText") << "refreshPointsString()";
		
		// Map spacing (0-1 normalized)
		float finalSpacing = ofMap(densitySpacing.get(), 0, 1, DENSITY_SPACING_MIN, DENSITY_SPACING_MAX, true);
		
		// Sample and set base points
		std::vector<vec2> sampledPoints = sampleStringPoints(sText, finalSpacing);
		data->setBasePoints(sampledPoints);
		
		// Initialize trails
		int tl = (int)ofMap(trailLength.get(), 0.f, 1.f, TRAILS_LENGTH_MIN, TRAILS_LENGTH_MAX, true);
		data->initTrails(tl);
		
		// Calculate center
		const auto& points = data->getBasePoints();
		if (points.size() > 0) {
			vec2 sum(0, 0);
			for (const auto & p : points) {
				sum += p;
			}
			vec2 center = sum / static_cast<float>(points.size());
			
			// Store text metrics
			float width = font.stringWidth(sText);
			float height = font.stringHeight(sText);
			data->setTextMetrics(width, height, center);
		}
	}
	
	//--------------------------------------------------------------
	vec2 OrganicText::getAnimatedOffset(int index, float phase) const {
		vec2 offset(0, 0);
		
		const auto& pointsString = data->getBasePoints();
		if (!bEnableAnimation.get() || pointsString.empty()) {
			return offset;
		}
		
		float fontScale = fontSize.get() / 150.0f;
		
		// Calculate custom animation origin based on animOriginX (0=left, 0.5=center, 1=right)
		float customOriginX = data->getTextWidth() * animOriginX.get();
		float customOriginY = data->getTextCenter().y;
		
		// Override with mouse position if mouse control is active
		// Now works across entire canvas, deforming the constellation
		// exclude ANIM_WAVE because no good results seen with it
		if (bMouseTweaks.get() && bMouseControlOrigin.get() && (AnimMode)animationMode.get() != ANIM_WAVE) {
			customOriginX = mouseLocalPos.x;
			customOriginY = mouseLocalPos.y;
		}
		
		vec2 customOrigin = vec2(customOriginX, customOriginY);
		
		switch ((AnimMode)animationMode.get()) {
			case ANIM_NOISE: {
				float maxDisp = ofMap(animPower.get(), 0, 1, 0, ANIM_NOISE_MAX * fontScale, true);
				
				// If mouse control is active, reduce noise displacement near mouse position
				if (bMouseTweaks.get() && bMouseControlOrigin.get()) {
					float mouseInfluence = getMouseInfluence(pointsString[index]);
					maxDisp *= (1.0f - mouseInfluence * 2.f); // Reduce up to % near mouse
				}
				
				offset = vec2(ofSignedNoise(phase, 0.0f), ofSignedNoise(phase, 233.0f)) * maxDisp;
				break;
			}
			
			case ANIM_WAVE: {
				float freq = ofMap(animWaveFreq.get(), 0, 1, ANIM_WAVE_FREQ_MIN, ANIM_WAVE_FREQ_MAX, true);
				float amp = ofMap(animIntensity.get(), 0, 1, 0, ANIM_WAVE_MAX * fontScale, true);
				
				// Use distance from custom origin instead of absolute x position
				float distFromOrigin = pointsString[index].x - customOriginX;
				float wave = sin(distFromOrigin * freq + t * glm::two_pi<float>()) * amp;
				offset = vec2(0, wave);
				break;
			}
			
			case ANIM_SPIRAL: {
				if (pointsString.size() < 2) break;
				
				// Use custom origin for spiral center
				float angle = atan2(pointsString[index].y - customOrigin.y, pointsString[index].x - customOrigin.x);
				float distance = glm::distance(pointsString[index], customOrigin);
				float tightness = ofMap(animSpiral.get(), 0, 1, ANIM_SPIRAL_TIGHT_MIN, ANIM_SPIRAL_TIGHT_MAX, true);
				float maxDisp = ofMap(animPower.get(), 0, 1, 0, ANIM_SPIRAL_MAX * fontScale, true);
				
				float spiralPhase = distance * tightness + t * glm::two_pi<float>();
				float spiralOffset = sin(spiralPhase) * maxDisp;
				
				offset = vec2(cos(angle) * spiralOffset, sin(angle) * spiralOffset);
				break;
			}
			
			case ANIM_PULSE: {
				if (pointsString.size() < 2) break;
				
				// Use custom origin for pulse center
				float distance = glm::distance(pointsString[index], customOrigin);
				float maxPulse = ofMap(animPulseIntensity.get(), 0, 1, 0, ANIM_PULSE_MAX * fontScale, true);
				float pulsePhase = sin(t * glm::two_pi<float>() * 0.5f) * maxPulse;
				
				if (distance > 0.5f) {
					vec2 direction = normalize(pointsString[index] - customOrigin);
					offset = direction * pulsePhase;
				}
				break;
			}
			
			case ANIM_ORBIT: {
				if (pointsString.size() < 2) break;
				
				// Use custom origin as pivot point for orbit
				float angle = atan2(pointsString[index].y - customOrigin.y, pointsString[index].x - customOrigin.x);
				angle += t * glm::two_pi<float>() * 0.3f;
				
				float distance = glm::distance(pointsString[index], customOrigin);
				vec2 newPos = customOrigin + vec2(cos(angle), sin(angle)) * distance;
				offset = newPos - pointsString[index];
				break;
			}
		}
		
		return offset;
	}
	
	//--------------------------------------------------------------
	float OrganicText::getMouseInfluence(vec2 position) const {
		float radiusPixels = ofMap(radiusMouse.get(), 0.f, 1.f, MOUSE_RADIUS_INTERACT_MIN, MOUSE_RADIUS_INTERACT_MAX, true);
		float distToMouse = glm::distance(position, mouseLocalPos);
		
		if (distToMouse >= radiusPixels) {
			return 0.0f; // Outside radius
		}
		
		// Calculate normalized influence (1.0 at center, 0.0 at edge)
		float influence = ofMap(distToMouse, 0, radiusPixels, 1.0f, 0.0f, true);
		
		// Apply mouseInfluenceStrength BEFORE power curve to maintain control range
		influence *= mouseInfluenceStrength.get();
		
		// Apply power curve for gradient shape
		// Power of 0.7 creates a softer, wider gradient
		float power = 0.7f;
		influence = std::pow(influence, power);
		
		return influence;
	}
	
	//--------------------------------------------------------------
	ofColor OrganicText::getPointColor(int index, vec2 position, float phase) const {
		ofColor color = ofColor(ofColor::white, 255);
		
		const auto& pointsString = data->getBasePoints();
		if (pointsString.empty()) return color;
		
		switch ((ColorMode)colorMode.get()) {
			case COLOR_GLOBAL_1:
			color = color1.get();
			break;
			
			case COLOR_GLOBAL_2:
			color = color2.get();
			break;
			
			case COLOR_GLOBAL_3:
			color = color3.get();
			break;
			
			case COLOR_GLOBAL_MIX: {
				float indexFactor = static_cast<float>(index) / ofClamp(static_cast<float>(pointsString.size()), 1.0f, 100000.0f);
				float timeFactor = (sin(t * colorSpeed.get() * glm::two_pi<float>()) + 1.0f) * 0.5f;
				
				ofColor c1 = color1.get();
				ofColor c2 = color2.get();
				ofColor c3 = color3.get();
				
				// Use dynamic transition points
				float innerPoint = colorInner.get();
				if (indexFactor < innerPoint) {
					color = c1.lerp(c2, indexFactor / innerPoint);
				} else {
					color = c2.lerp(c3, (indexFactor - innerPoint) / (1.0f - innerPoint));
				}
				
				color = color.lerp(c3, timeFactor * colorMixFactor.get() * 0.4f);
				
				// Apply alpha fade based on index position (left to right)
				if (colorAlphaRange.get() > 0.01f) {
					float alphaMin = ofMap(colorAlphaRange.get(), 0, 1, 255, 50, true);
					float alpha = ofMap(indexFactor, 0, 1, 255, alphaMin, true);
					color.a = alpha;
				}
				break;
			}
			
			case COLOR_DISTANCE: {
				float distance = glm::distance(position, data->getTextCenter());
				float distFactor = ofMap(distance, 0, COLOR_DISTANCE_MAX, 0, 1, true);
				
				ofColor c1 = color1.get();
				ofColor c2 = color2.get();
				ofColor c3 = color3.get();
				
				// Use dynamic transition points
				float innerPoint = colorInner.get();
				float middlePoint = colorDistMiddle.get();
				
				if (distFactor < innerPoint) {
					color = c1.lerp(c2, distFactor / innerPoint);
				} else if (distFactor < middlePoint) {
					float localT = (distFactor - innerPoint) / (middlePoint - innerPoint);
					color = c2.lerp(c3, localT);
				} else {
					color = c3;
				}
				
				// Apply alpha fade based on distance from center
				if (colorAlphaRange.get() > 0.01f) {
					float alphaCenter = 255.0f;
					float alphaEdge = ofMap(colorAlphaRange.get(), 0, 1, 255, 50, true);
					float alpha = ofMap(distance, 0, COLOR_DISTANCE_MAX, alphaCenter, alphaEdge, true);
					color.a = alpha;
				}
				break;
			}
		}
		
		if (bColorByDistance) {
			float distance = glm::distance(position, data->getTextCenter());
			// Map alpha range dynamically: 255 (center) to edge based on colorAlphaRange
			float alphaEdge = ofMap(colorAlphaRange.get(), 0, 1, 255, 0, true);
			float alpha = ofMap(distance, 0, COLOR_DISTANCE_MAX, 255, alphaEdge, true);
			color.a = alpha;
		}
		
		// Mouse highlight: override color for points within mouse radius
		if (bMouseTweaks.get() && bMouseHighlightPoints.get()) {
			float influence = getMouseInfluence(position);
			if (influence > 0.0f) {
				color = color.lerp(colorMouseHighlight.get(), influence);
			}
		}
		
		return color;
	}
	
	//--------------------------------------------------------------
	void OrganicText::drawShape(vec2 position, float size, ShapeType shape, float rotation) const {
		ofPushMatrix();
		ofTranslate(position);
		ofRotateDeg(rotation);
		float h = size * ofMap(shapeRatio.get(), 0.f, 1.f, 1.f, 10.f, true);
		
		switch (shape) {
			case SHAPE_CIRCLE:
			ofDrawCircle(0, 0, size);
			break;
			
			case SHAPE_RECTANGLE:
			ofDrawRectangle(-size * 0.5f, -size * 0.5f, size, h);
			break;
			
			case SHAPE_TRIANGLE: {
				ofDrawTriangle(0, -h * 0.5f, -size * 0.5f, h * 0.5f, size * 0.5f, h * 0.5f);
				break;
			}
			
			case SHAPE_STAR: {
				ofPolyline star;
				int points = 5;
				for (int i = 0; i < points * 2; i++) {
					float angle = (static_cast<float>(i) * glm::two_pi<float>()) / (static_cast<float>(points) * 2.0f);
					float radius = (i % 2 == 0) ? size : size * 0.4f;
					star.addVertex(cos(angle) * radius, sin(angle) * radius);
				}
				star.close();
				
				// Convert polyline to path for fill support
				ofPath starPath;
				starPath.setFilled(bDrawFill.get()); // enable or disable fill
				starPath.setFillColor(ofGetStyle().color); // use current drawing color
				starPath.setStrokeColor(ofGetStyle().color); // outline uses same color
				starPath.setStrokeWidth(1.0f);
				
				starPath.moveTo(star[0]);
				for (std::size_t i = 1; i < star.size(); ++i) {
					starPath.lineTo(star[i]);
				}
				starPath.close();
				
				starPath.draw(); // draw filled or not depending on flag
				break;
			}
			
			case SHAPE_CROSS: {
				float thickness = size * 0.2f;
				ofDrawRectangle(-thickness * 0.5f, -size * 0.5f, thickness, size);
				ofDrawRectangle(-size * 0.5f, -thickness * 0.5f, size, thickness);
				break;
			}
			
			case SHAPE_POINT: {
				ofDrawCircle(0, 0, size * 0.05f);
				break;
			}
		}
		
		ofPopMatrix();
	}
	
	//--------------------------------------------------------------
	void OrganicText::updateTrails() {
		const auto& pointsString = data->getBasePoints();
		const auto& pointsAnimatedCache = data->getAnimatedCache();
		
		for (std::size_t i = 0; i < pointsString.size(); i++) {
			// Use cached animated position if available, otherwise calculate
			vec2 currentPos;
			if (i < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
				currentPos = pointsAnimatedCache[i];
			} else {
				float phase = t + 0.123f * static_cast<float>(i);
				vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
				currentPos = pointsString[i] + offset;
			}
			
			data->updateTrailPoint(i, currentPos);
		}
	}
	
	//--------------------------------------------------------------
	void OrganicText::drawConnections() const {
		const auto& pointsString = data->getBasePoints();
		if (!bDrawConnections.get() || pointsString.size() < 2) return;
		
		float maxDist = connectDistance.get();
		float quality = ofClamp(connectQuality.get(), 0.1f, 1.0f);
		int skipFactor = ofClamp(static_cast<int>(1.0f / quality), 1, 100);
		
		int maxConPerPoint = bConnectNearOnly ? CONNECTIONS_MAX_PER_POINT_NEAR : CONNECTIONS_MAX_PER_POINT_FAR;
		
		// Reset cached count
		cachedConnectionCount = 0;
		ofPushStyle();
		ofSetLineWidth(connectLineWidth);
		
		// Use ofMesh for maximum performance - batch all connection lines into single draw call
		ofMesh connectionMesh;
		connectionMesh.setMode(OF_PRIMITIVE_LINES);
		
		const auto& pointsAnimatedCache = data->getAnimatedCache();
		
		// Collect all connection segments into a single mesh
		for (std::size_t i = pointsString.size() * inPoint.get(); i < pointsString.size() && i < pointsString.size() * outPoint.get(); i += skipFactor) {
			// Use cached animated position if available, otherwise calculate
			vec2 pos1;
			if (i < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
				pos1 = pointsAnimatedCache[i];
			} else {
				float phase1 = t + 0.123f * static_cast<float>(i);
				vec2 offset1 = getAnimatedOffset(static_cast<int>(i), phase1);
				pos1 = pointsString[i] + offset1;
			}
			
			int connectionsDrawn = 0;
			int searchLimit = bConnectNearOnly ? ofClamp(CONNECTIONS_SEARCH_NEAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i)) : ofClamp(CONNECTIONS_SEARCH_FAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i));
			
			for (int offset = 1; offset < searchLimit && connectionsDrawn < maxConPerPoint; offset += skipFactor) {
				std::size_t j = i + offset;
				if (j >= pointsString.size()) break;
				
				// Use cached animated position if available, otherwise calculate
				vec2 pos2;
				if (j < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
					pos2 = pointsAnimatedCache[j];
				} else {
					float phase2 = t + 0.123f * static_cast<float>(j);
					vec2 offset2 = getAnimatedOffset(static_cast<int>(j), phase2);
					pos2 = pointsString[j] + offset2;
				}
				
				float dist = glm::distance(pos1, pos2);
				
				if (dist < maxDist) {
					float alpha = ofMap(dist, 0, maxDist, 255, 0, true);
					float acolor = ofMap(colorConnection.get().a, 0, 255, 0.f, 1.f, true);
					float o = 2.f; //power
					alpha = ofMap(alpha * (acolor * o * connectAlpha.get()), 0, 255, 0, 255, true);
					
					ofColor connectionColor = colorConnection.get();
					connectionColor.a = alpha;
					
					// Add line segment vertices
					glm::vec3 p1(pos1.x, pos1.y, 0.0f);
					glm::vec3 p2(pos2.x, pos2.y, 0.0f);
					
					connectionMesh.addVertex(p1);
					connectionMesh.addColor(connectionColor);
					connectionMesh.addVertex(p2);
					connectionMesh.addColor(connectionColor);
					
					connectionsDrawn++;
					cachedConnectionCount++;
				}
			}
		}
		
		// Single draw call for all connections - MUCH faster than individual lines
		if (connectionMesh.getNumVertices() > 0) {
			connectionMesh.draw();
		}
		
		ofPopStyle();
	}
	
	//--------------------------------------------------------------
	void OrganicText::drawTrails() {
		#ifdef FIX_ORGANIC_TEXT_TWEEN_TRAILS_PROBLEMS
		if (this->isTweening()) return; // Skip drawing trails while tweening in/out
		#endif
		
		const auto& pointsString = data->getBasePoints();
		const auto& pointTrails = data->getTrails();
		
		ofPushStyle();
		ofSetLineWidth(trailLineWidth);
		float tf = ofMap(trailFade, 0.f, 1.f, TRAILS_FADE_MIN, TRAILS_FADE_MAX, true);
		
		// Use ofMesh for maximum performance - batch all trail lines into single draw call
		ofMesh trailMesh;
		trailMesh.setMode(OF_PRIMITIVE_LINES);
		
		// Collect all trail segments into a single mesh
		for (std::size_t i = pointsString.size() * inPoint.get(); i < pointTrails.size() && i < pointsString.size() * outPoint.get(); i++) {
			if (pointTrails[i].size() < 2) continue; // Skip if not enough points
			
			// Add line segments for this trail
			for (std::size_t j = 1; j < pointTrails[i].size(); j++) {
				float fadeAmount = pow(tf, static_cast<float>(j));
				float alpha = fadeAmount * TRAILS_ALPHA_MAX;
				
				ofColor segmentColor = colorTrails.get();
				segmentColor.a = alpha;
				
				// Add line segment vertices
				glm::vec3 p1(pointTrails[i][j - 1].x, pointTrails[i][j - 1].y, 0.0f);
				glm::vec3 p2(pointTrails[i][j].x, pointTrails[i][j].y, 0.0f);
				
				trailMesh.addVertex(p1);
				trailMesh.addColor(segmentColor);
				trailMesh.addVertex(p2);
				trailMesh.addColor(segmentColor);
			}
		}
		
		// Single draw call for all trails - MUCH faster than individual lines
		if (trailMesh.getNumVertices() > 0) {
			trailMesh.draw();
		}
		
		ofPopStyle();
	}
	
	//--
	
	//--------------------------------------------------------------
	void OrganicText::drawDebug() const {
		ofPushStyle();
		
		ofSetColor(colorDebugBlink);
		
		ofNoFill();
		ofSetLineWidth(1.2f);
		
		// Text center crosshair
		float crossSize = 7;
		vec2 textCenter = data->getTextCenter();
		ofDrawLine(textCenter - vec2(crossSize, 0), textCenter + vec2(crossSize, 0));
		ofDrawLine(textCenter - vec2(0, crossSize), textCenter + vec2(0, crossSize));
		ofDrawCircle(textCenter, crossSize * 0.7);
		
		ofSetColor(colorDebugBlink);
		
		//// Text bounding box
		//ofNoFill();
		//ofDrawRectangle(0, -textHeight, textWidth, textHeight);
		
		// All sample points
		if(bDrawOutline){
			ofFill();
			const auto& pointsString = data->getBasePoints();
			for (const auto & point : pointsString) {
				ofDrawCircle(point, 1.f);
			}
		}		
		ofPopStyle();
	}
	
	//--
	
	//--------------------------------------------------------------
	void OrganicText::drawShapes() {
		const auto& pointsString = data->getBasePoints();
		
		// Resize cache if needed
		if (data->getAnimatedCache().size() != pointsString.size()) {
			data->resizeCache(pointsString.size());
		}
		
		for (std::size_t i = pointsString.size() * inPoint.get(); i < pointsString.size() && i < pointsString.size() * outPoint.get(); i++) {
			ofPushStyle();
			
			float phase = t + 0.123f * static_cast<float>(i);
			vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
			vec2 finalPos = pointsString[i] + offset;
			
			// Calculate influence from mouse tweaks only
			float mouseInfluence = 0.0f;
			vec2 influenceSourcePos = mouseLocalPos;
			
			if (bMouseTweaks.get()) {
				mouseInfluence = getMouseInfluence(finalPos);
			}
			
			float totalInfluence = mouseInfluence;
			
			// Apply displacement effect (bidirectional)
			// < 0.5 = attract, 0.5 = neutral, > 0.5 = repel
			if (bMouseDisplacePoints.get() && totalInfluence > 0.0f) {
				vec2 direction = glm::normalize(finalPos - influenceSourcePos);
				
				// Map mouseDisplacePower: 0.5 = no effect, < 0.5 = attract, > 0.5 = repel
				float powerCentered = (mouseDisplacePower.get() - 0.5f) * 2.0f; // Maps [0,1] to [-1,1]
				
				float maxDisplacement = 50.0f; // Maximum displacement in pixels
				float displacement = totalInfluence * powerCentered * maxDisplacement;
				
				// If powerCentered is negative (attract), direction is inverted
				finalPos += direction * displacement;
			}
			
			// Cache the final animated position for reuse in connections and trails
			data->setCachedAnimatedPoint(i, finalPos);
			
			ofColor color = getPointColor(static_cast<int>(i), finalPos, phase);
			
			ofSetColor(color);
			
			if (bDrawFill.get())
			ofFill();
			else
			ofNoFill();
			
			float maxSize = ofMap(shapeSize.get(), 0, 1, SHAPE_MIN_RADIUS, SHAPE_MAX_RADIUS, true);
			float minSize = ofMap(shapeSizeMin.get(), 0, 1, 0, maxSize, true);
			
			float sizeNoise = ofNoise(phase * SHAPE_SIZE_NOISE_SCALE, static_cast<float>(i) * SHAPE_SIZE_INDEX_SCALE);
			float pointSize = ofLerp(minSize, maxSize, sizeNoise);
			
			// Apply scale effect (bidirectional)
			// < 0.5 = shrink, 0.5 = neutral, > 0.5 = grow
			if (bMouseScaleShapes.get() && totalInfluence > 0.0f) {
				// Map mouseScalePower: 0.5 = no effect, < 0.5 = shrink, > 0.5 = grow
				float powerCentered = (mouseScalePower.get() - 0.5f) * 2.0f; // Maps [0,1] to [-1,1]
				
				// Calculate scale multiplier
				// Positive: grows up to MAX_SCALE_POWER times
				// Negative: shrinks down to near 0
				float scaleMultiplier = 1.0f + (totalInfluence * powerCentered * MAX_SCALE_POWER);
				pointSize *= scaleMultiplier;
			}
			
			float rotation = ofMap(shapeRotation.get(), 0, 1, 0, 360, true);
			
			drawShape(finalPos, pointSize, (ShapeType)shapeType.get(), rotation);
			
			if (bDebug) {
				ofSetColor(colorDebug);
				ofDrawCircle(finalPos, 2.f);
			}
			
			ofPopStyle();
		}
	}
	
	//--------------------------------------------------------------
	void OrganicText::draw() {
		auto td = ofGetElapsedTimeMicros(); //benchmark measure performance
		
		float zoomFactor = 1.0f + (zoomGlobal.get() * ZOOM_GLOBAL_MAX);
		
		ofPushMatrix();
		{
			float centerX = ofGetWidth() * 0.5f;
			float centerY = ofGetHeight() * 0.5f;
			ofTranslate(centerX, centerY);
			ofScale(zoomFactor, zoomFactor);
			
			ofTranslate(-font.stringWidth(sText) * 0.5f, font.stringHeight(sText) * 0.5f);
			
			//--
			
			// Layer 0: Shapes
			if (bDrawShapes && bShapeBack) {
				drawShapes();
			}
			
			// Layer 1: Connections
			if (bDrawConnections) {
				drawConnections();
			}
			
			// Layer 2: Trails
			if (bDrawTrails) {
				updateTrails();
				
				drawTrails();
			}
			
			// Layer 3: Shapes
			if (bDrawShapes && !bShapeBack) {
				drawShapes();
			}
			
			//--
			
			// Layer 4: Outline
			if (bDebug) {
				ofPushStyle();
				ofNoFill();
				ofSetColor(colorDebugBlink);
				ofSetLineWidth(1.f);
				font.drawStringAsShapes(sText, 0, 0);
				ofPopStyle();
			} else if (bDrawOutline) {
				ofPushStyle();
				ofNoFill();
				ofSetColor(colorOutline.get());
				float thickness = ofMap(outlineThickness.get(), 0.f, 1.f, OUTLINE_WIDTH_BASE, OUTLINE_THICKNESS_MAX);
				ofSetLineWidth(thickness * zoomFactor);
				font.drawStringAsShapes(sText, 0, 0);
				ofPopStyle();
			}
			
			//--
			
			// Layer 5: Debug (always on top)
			if (bDebug) {
				drawDebug();
			}
		}
		ofPopMatrix();
		
		//--
		
		// Mouse interact debug visualization
		if (bDebug) {
			ofPushStyle();
			ofFill();
			ofSetColor(ofColor(colorDebug, DEBUG_ALPHA_MAX * 0.5f));
			float r = ofMap(radiusMouse.get(), 0.f, 1.f, MOUSE_RADIUS_INTERACT_MIN, MOUSE_RADIUS_INTERACT_MAX, true);
			ofDrawCircle(mousePos, r);
			ofPopStyle();
			
			//--
			
			// Mouse debug visualization only
		}
		
		// Debug bench measuring drawing performance
		timeDrawBenchmark = ofGetElapsedTimeMicros() - td;
	}
	
	//--------------------------------------------------------------
	void OrganicText::drawGui() {
		if (!bGui) return;
		
		if (bDebug && bDebugLowFPS) {
			ofPushStyle();
			ofNoFill();
			ofSetLineWidth(2);
			ofSetColor(colorDebug);
			ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
			ofPopStyle();
			
			// Low FPS warning
			std::string s = "LOW FPS";
			//ofxSurfing::ofDrawBitmapStringBox(s, ofxSurfing::SURFING_LAYOUT_TOP_CENTER);
			auto bf = ofBitmapFont();
			//bf.getBoundingBox(s,0,0);
			ofDrawBitmapStringHighlight(s, ofGetWidth() / 2 - bf.getBoundingBox(s, 0, 0).getWidth() / 2, bf.getBoundingBox(s, 0, 0).getHeight(), ofColor::yellow, ofColor::black);
		}
		
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
		const auto& pointTrails = data->getTrails();
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
			boxX = gui.getPosition().x - boxWidth - 5;
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
	
	