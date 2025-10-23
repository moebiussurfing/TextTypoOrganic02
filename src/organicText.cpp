#include "organicText.h"

#include <algorithm>
#include <cmath>

//--------------------------------------------------------------
OrganicText::OrganicText() {
	ofLogNotice("OrganicText") << "OrganicText()";

	ofAddListener(ofEvents().update, this, &OrganicText::update);
	ofAddListener(ofEvents().windowResized, this, &OrganicText::windowResized);
}

//--------------------------------------------------------------
OrganicText::~OrganicText() {
	ofLogNotice("OrganicText") << "~OrganicText()";

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
	setupCallbacks();
	setupGui();
	startup();

	ofLogNotice("OrganicText") << "Setup complete - Target FPS: " << targetFPS;
}

//--------------------------------------------------------------
void OrganicText::startup() {
	ofLogNotice("OrganicText") << "startup()";

	//// Load font
	//refreshFont();

	// Set defaults settings on these methods instead of into setupParams() init params!
	resetAll();

	// Load saved settings
	loadSettings();
}

//--------------------------------------------------------------
void OrganicText::setupScene() {
	ofLogNotice("OrganicText") << "setupScene()";

	// Initialize
	t = 0.0;
	textCenter = vec2(0, 0);

	// Initialize mode names
	int dummy = 0;
	updateShapeTypeName(dummy);
	updateColorModeName(dummy);
	updateAnimationModeName(dummy);

	colorDebug = ofColor::yellow;
}

//--------------------------------------------------------------
void OrganicText::setupParams() {
	ofLogNotice("OrganicText") << "setupParams()";

	// Basic parameters
	bDebugDraw.set("Debug", false);
	bHelp.set("Help", false);
	bDrawFill.set("Draw Fill", true);
	bDrawShapes.set("Draw Shapes", true);
	bEnableAnimation.set("Animate", true);
	bDrawOutline.set("Draw Outline", false);
	zoomGlobal.set("Zoom", 0.0f, 0.0f, 1.0f);
	sText.set("Text", ORGANICTEXT);

	// Font parameters
	fontPath.set("Font Path", "NotoSansMono-Regular.ttf"); // File not required! Currently using OF bundled OF_TTF
	fontSize.set("Size", 150, 50, 500);
	letterSpacing.set("Spacing", 0, -1, 1);
	vResetFont.set("Reset");

	// Density group
	vResetDensity.set("Reset");
	vRandomDensity.set("Random");
	densitySpacing.set("Spacing", 0.2, 0.05, 1);
	densityAmount.set("Amount", 1.0, 0.1, 5.0);
	densityMinGap.set("Min Gap", 0.1, 0.0, 1.0);

	// Shape group
	vResetShape.set("Reset");
	vRandomShape.set("Random");
	shapeType.set("Type", 0, 0, 5);
	shapeTypeName.set("Name", "Circle");
	shapeTypeName.setSerializable(false);
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
	animSpeed.set("Speed", 1.0, 0.1, 3.0);
	animPower.set("Power", 0.1, 0.0, 1.0);
	animWaveFreq.set("Wave Freq", 0.5, 0.0, 1.0);
	animIntensity.set("Intensity", 0.2, 0.0, 1.0);
	animSpiral.set("Spiral", 0.2, 0.0, 1.0);
	animPulseIntensity.set("Pulse", 0.2, 0.0, 1.0);

	// Connection group
	vResetConnection.set("Reset");
	vRandomConnection.set("Random");
	bDrawConnections.set("Draw Connections", false);
	connectDistance.set("Distance", 30, 5, 100);
	connectLineWidth.set("Line Width", 1.0f, 0.1f, CONNECTIONS_MAX_LINE_WIDTH);
	connectAlpha.set("Alpha", 100, 0, 255);
	bConnectNearOnly.set("Near Only", true);
	connectQuality.set("Quality", 1.0, 0.1, 1.0);

	// Trail
	bDrawTrails.set("Draw Trails", false);
	trailLength.set("Length", 0.5f, 0, 1.f);
	trailLineWidth.set("Line Width", 1.0f, 0.1f, TRAILS_LINE_WIDTH_MAX);
	trailFade.set("Fade", 0.5f, 0, 1.f);

	// Settings group
	bAutosave.set("Autosave", false);
	vSaveSettigs.set("Save");
	vLoadSettigs.set("Load");

	// Global reset
	vResetAll.set("Reset All");
	vResetPreset.set("Reset Preset");
	vRandomAll.set("Random All");

	//--

	// Organize groups
	paramsFont.setName("Font");
	paramsFont.add(fontPath);
	paramsFont.add(fontSize);
	paramsFont.add(letterSpacing);
	paramsFont.add(vResetFont);

	paramsDensity.setName("Density");
	paramsDensity.add(densitySpacing);
	paramsDensity.add(densityAmount);
	paramsDensity.add(densityMinGap);
	paramsDensity.add(vRandomDensity);
	paramsDensity.add(vResetDensity);

	paramsShape.setName("Shape");
	paramsShape.add(bDrawFill);
	paramsShape.add(shapeType);
	paramsShape.add(shapeTypeName);
	paramsShape.add(shapeSize);
	paramsShape.add(shapeSizeMin);
	paramsShape.add(shapeRatio);
	paramsShape.add(shapeRotation);
	paramsShape.add(vRandomShape);
	paramsShape.add(vResetShape);

	paramsColorModes.setName("Color Modes");
	paramsColorModes.add(colorMode);
	paramsColorModes.add(colorModeName);
	paramsColorModes.add(colorSpeed);
	paramsColorModes.add(colorMixFactor);
	paramsColorModes.add(bColorByDistance);
	paramsColorModes.add(vRandomColor);
	paramsColorModes.add(vResetColor);

	paramsColors.setName("Colors");
	paramsColors.add(color1);
	paramsColors.add(color2);
	paramsColors.add(color3);
	paramsColors.add(colorOutline);
	paramsColors.add(colorConnection);
	paramsColors.add(colorTrails);
	paramsColors.add(vRandomGlobalColors);
	paramsColors.add(vResetGlobalColors);

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

	paramsSessionSettings.setName("Session Settings");
	paramsSessionSettings.add(bAutosave);
	paramsSessionSettings.add(vLoadSettigs);
	paramsSessionSettings.add(vSaveSettigs);

	paramsInternal.setName("Internal");
	paramsInternal.add(bGui);

	// Preset
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
	paramsPreset.add(vResetPreset);

	// gui
	parameters.setName("OrganicText");
	parameters.add(sText);
	parameters.add(paramsFont);
	parameters.add(zoomGlobal);
	parameters.add(bDrawOutline);
	parameters.add(bDebugDraw);
	parameters.add(bHelp);
	parameters.add(bKeys);
	parameters.add(paramsSessionSettings);
	parameters.add(paramsInternal);

#ifndef SURFING_USE_EXTERNAL_PRESET_MANAGER
	// exclude these settings from settings
	// as will be handled by presets manager externally
	parameters.add(paramsPreset);
#endif

	//parameters.add(vRandomAll); // not useful
	parameters.add(vResetPreset);
	parameters.add(vResetAll);
}

//--------------------------------------------------------------
void OrganicText::setupCallbacks() {
	ofLogNotice("OrganicText") << "setupCallbacks()";

	// Font listeners
	e_FontPath = fontPath.newListener([this](string & s) { loadFont(); });
	e_vFontSize = fontSize.newListener([this](float & f) { loadFont(); });
	e_letterSpacing = letterSpacing.newListener([this](float & f) { flagRefreshFont(); });
	e_vResetFont = vResetFont.newListener([this](void) { resetFonts(); });

	// Density listeners
	e_DensitySpacing = densitySpacing.newListener([this](float & v) { refreshPointsString(); });
	e_DensityAmount = densityAmount.newListener([this](float & v) { refreshPointsString(); });
	e_sText = sText.newListener([this](string & s) { refreshPointsString(); });

	// Settings listeners
	e_vLoadSettigs = vLoadSettigs.newListener([this](void) { loadSettings(); });
	e_vSaveSettigs = vSaveSettigs.newListener([this](void) { saveSettings(); });

	// Mode name listeners
	shapeType.addListener(this, &OrganicText::updateShapeTypeName);
	colorMode.addListener(this, &OrganicText::updateColorModeName);
	animationMode.addListener(this, &OrganicText::updateAnimationModeName);

	e_trailLength = trailLength.newListener([this](float & v) { initTrails(); });

	//--

	// Reset listeners
	e_vResetDensity = vResetDensity.newListener([this](void) { resetDensityParams(); });
	e_vResetShape = vResetShape.newListener([this](void) { resetShapeParams(); });
	e_vResetColor = vResetColor.newListener([this](void) { resetColorModes(); });
	e_vResetGlobalColor = vResetGlobalColors.newListener([this](void) { resetGlobalColorParams(); });
	e_vResetAnimation = vResetAnimation.newListener([this](void) { resetAnimationParams(); });
	e_vResetConnection = vResetConnection.newListener([this](void) { resetConnectionParams(); });
	e_vRandomAll = vRandomAll.newListener([this](void) { randomAll(); });
	e_vResetAll = vResetAll.newListener([this](void) { resetAll(); });
	e_vResetPreset = vResetPreset.newListener([this](void) { resetPreset(); });

	// Random listeners
	e_vRandomDensity = vRandomDensity.newListener([this](void) { randomizeDensityParams(); });
	e_vRandomShape = vRandomShape.newListener([this](void) { randomizeShapeParams(); });
	e_vRandomColor = vRandomColor.newListener([this](void) { randomizeColorModes(); });
	e_vRandomGlobalColor = vRandomGlobalColors.newListener([this](void) { randomizeGlobalColorParams(); });
	e_vRandomAnimation = vRandomAnimation.newListener([this](void) { randomizeAnimationParams(); });
	e_vRandomConnection = vRandomConnection.newListener([this](void) { randomizeConnectionParams(); });
}

//--------------------------------------------------------------
void OrganicText::setupGui() {
	ofLogNotice("OrganicText") << "setupGui()";

	gui.setup(parameters);

#ifndef SURFING_USE_EXTERNAL_PRESET_MANAGER
	refreshGuiPanel(gui);
#endif

	// collapse folders
	refreshGuiSession();
}

//--------------------------------------------------------------
void OrganicText::refreshGuiSession() {
	ofLogNotice("OrganicText") << "refreshGuiSession()";

	gui.getGroup(paramsFont.getName()).minimize();
	gui.getGroup(paramsInternal.getName()).minimize();
	auto & g = gui.getGroup(paramsSessionSettings.getName());
	g.minimize();
}

//--------------------------------------------------------------
void OrganicText::windowResized(ofResizeEventArgs & resize) {
	ofLogNotice("OrganicText") << "windowResized()";

	// Move the gui panel
	auto pad = 5;
	auto w = gui.getWidth();
	gui.setPosition(ofGetWidth() - w - pad, pad);
}

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
		fontPath.set(OF_TTF_SANS);
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
		sp = ofMap(letterSpacing, 0, -1, 1, spMin);
	else if (letterSpacing > 0)
		sp = ofMap(letterSpacing, 0, 1, 1, spMax);
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
		t += BASE_TIME_STEP * animSpeed.get() * normalizedDt;
	}

	fps = ofGetFrameRate();
	frameTime = 1000.0f / ofClamp(fps, 0.1f, 10000.0f);

	if (bFlagRefreshFont) {
		refreshFont();
		bFlagRefreshFont = false;
	}
}

//--

//--------------------------------------------------------------
vector<vec2> OrganicText::sampleStringPoints(const string & s, float ds) {
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
	// Map spacing (0-1 normalized)
	float baseSpacing = ofMap(densitySpacing.get(), 0, 1, DENSITY_SPACING_MIN, DENSITY_SPACING_MAX, true);
	float finalSpacing = baseSpacing / densityAmount.get();

	// Map min gap (0-1 normalized) with font scaling
	float fontScale = fontSize.get() / 150.0f;
	float minGap = ofMap(densityMinGap.get(), 0, 1, DENSITY_MIN_SPACING_MIN, DENSITY_MIN_SPACING_MAX, true);
	minGap *= fontScale;

	finalSpacing = ofClamp(finalSpacing, minGap, 1000.0f);

	pointsString = sampleStringPoints(sText, finalSpacing);

	// Initialize trails
	initTrails();

	// Calculate center
	if (pointsString.size() > 0) {
		vec2 sum(0, 0);
		for (const auto & p : pointsString) {
			sum += p;
		}
		textCenter = sum / static_cast<float>(pointsString.size());
	}
}

//--------------------------------------------------------------
vec2 OrganicText::getAnimatedOffset(int index, float phase) const {
	vec2 offset(0, 0);

	if (!bEnableAnimation.get() || pointsString.empty()) {
		return offset;
	}

	float fontScale = fontSize.get() / 150.0f;

	switch ((AnimMode)animationMode.get()) {
	case ANIM_NOISE: {
		float maxDisp = ofMap(animPower.get(), 0, 1, 0, ANIM_NOISE_MAX * fontScale, true);
		offset = vec2(
					 ofSignedNoise(phase, 0.0f),
					 ofSignedNoise(phase, 233.0f))
			* maxDisp;
		break;
	}

	case ANIM_WAVE: {
		float freq = ofMap(animWaveFreq.get(), 0, 1, ANIM_WAVE_FREQ_MIN, ANIM_WAVE_FREQ_MAX, true);
		float amp = ofMap(animIntensity.get(), 0, 1, 0, ANIM_WAVE_MAX * fontScale, true);
		float wave = sin(pointsString[index].x * freq + t * TWO_PI) * amp;
		offset = vec2(0, wave);
		break;
	}

	case ANIM_SPIRAL: {
		if (pointsString.size() < 2) break;

		float angle = atan2(pointsString[index].y - textCenter.y, pointsString[index].x - textCenter.x);
		float distance = glm::distance(pointsString[index], textCenter);
		float tightness = ofMap(animSpiral.get(), 0, 1, ANIM_SPIRAL_TIGHT_MIN, ANIM_SPIRAL_TIGHT_MAX, true);
		float maxDisp = ofMap(animPower.get(), 0, 1, 0, ANIM_SPIRAL_MAX * fontScale, true);

		float spiralPhase = distance * tightness + t * TWO_PI;
		float spiralOffset = sin(spiralPhase) * maxDisp;

		offset = vec2(cos(angle) * spiralOffset, sin(angle) * spiralOffset);
		break;
	}

	case ANIM_PULSE: {
		if (pointsString.size() < 2) break;

		float distance = glm::distance(pointsString[index], textCenter);
		float maxPulse = ofMap(animPulseIntensity.get(), 0, 1, 0, ANIM_PULSE_MAX * fontScale, true);
		float pulsePhase = sin(t * TWO_PI * 0.5f) * maxPulse;

		if (distance > 0.5f) {
			vec2 direction = normalize(pointsString[index] - textCenter);
			offset = direction * pulsePhase;
		}
		break;
	}

	case ANIM_ORBIT: {
		if (pointsString.size() < 2) break;

		float angle = atan2(pointsString[index].y - textCenter.y, pointsString[index].x - textCenter.x);
		angle += t * TWO_PI * 0.3f;

		float distance = glm::distance(pointsString[index], textCenter);
		vec2 newPos = textCenter + vec2(cos(angle), sin(angle)) * distance;
		offset = newPos - pointsString[index];
		break;
	}
	}

	return offset;
}

//--------------------------------------------------------------
ofColor OrganicText::getPointColor(int index, vec2 position, float phase) const {
	ofColor color = ofColor::white;

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
		float timeFactor = (sin(t * colorSpeed.get() * TWO_PI) + 1.0f) * 0.5f;

		ofColor c1 = color1.get();
		ofColor c2 = color2.get();
		ofColor c3 = color3.get();

		if (indexFactor < 0.5f) {
			color = c1.lerp(c2, indexFactor * 2.0f);
		} else {
			color = c2.lerp(c3, (indexFactor - 0.5f) * 2.0f);
		}

		color = color.lerp(c3, timeFactor * colorMixFactor.get() * 0.4f);
		break;
	}

	case COLOR_DISTANCE: {
		float distance = glm::distance(position, textCenter);
		float distFactor = ofMap(distance, 0, COLOR_DISTANCE_MAX, 0, 1, true);

		ofColor c1 = color1.get();
		ofColor c2 = color2.get();
		ofColor c3 = color3.get();

		if (distFactor < COLOR_DISTANCE_INNER) {
			color = c1.lerp(c2, distFactor / COLOR_DISTANCE_INNER);
		} else if (distFactor < COLOR_DISTANCE_MIDDLE) {
			float localT = (distFactor - COLOR_DISTANCE_INNER) / (COLOR_DISTANCE_MIDDLE - COLOR_DISTANCE_INNER);
			color = c2.lerp(c3, localT);
		} else {
			color = c3;
		}
		break;
	}
	}

	if (bColorByDistance) {
		float distance = glm::distance(position, textCenter);
		float alpha = ofMap(distance, 0, COLOR_DISTANCE_MAX, COLOR_ALPHA_CENTER, COLOR_ALPHA_EDGE, true);
		color.a = alpha;
	}

	return color;
}

//--------------------------------------------------------------
void OrganicText::drawShape(vec2 position, float size, ShapeType shape, float rotation) const {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(rotation);
	float h = size * ofMap(shapeRatio.get(), 0.f, 1.f, 1.f, 10.f);

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
			float angle = (static_cast<float>(i) * TWO_PI) / (static_cast<float>(points) * 2.0f);
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
void OrganicText::initTrails() {
	pointTrails.clear();
	pointTrails.resize(pointsString.size());

	int tl = (int)ofMap(trailLength.get(), 0.f, 1.f, TRAILS_LENGTH_MIN, TRAILS_LENGTH_MAX, true);
	for (size_t i = 0; i < pointsString.size(); i++) {
		pointTrails[i].resize(tl);
		for (int j = 0; j < tl; j++) {
			pointTrails[i][j] = pointsString[i];
		}
	}
}

//--------------------------------------------------------------
void OrganicText::updateTrails() {
	for (size_t i = 0; i < pointsString.size() && i < pointTrails.size(); i++) {
		float phase = t + 0.123f * static_cast<float>(i);
		vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
		vec2 currentPos = pointsString[i] + offset;

		for (int j = static_cast<int>(pointTrails[i].size()) - 1; j > 0; j--) {
			pointTrails[i][j] = pointTrails[i][j - 1];
		}
		pointTrails[i][0] = currentPos;
	}
}

//--------------------------------------------------------------
void OrganicText::drawConnections() const {
	if (!bDrawConnections.get() || pointsString.size() < 2) return;

	float maxDist = connectDistance.get();
	float quality = ofClamp(connectQuality.get(), 0.1f, 1.0f);
	int skipFactor = ofClamp(static_cast<int>(1.0f / quality), 1, 100);

	int maxConPerPoint = bConnectNearOnly ? CONNECTIONS_MAX_PER_POINT_NEAR : CONNECTIONS_MAX_PER_POINT_FAR;

	// Reset cached count
	cachedConnectionCount = 0;
	ofPushStyle();
	ofSetLineWidth(connectLineWidth);

	for (size_t i = 0; i < pointsString.size(); i += skipFactor) {
		float phase1 = t + 0.123f * static_cast<float>(i);
		vec2 offset1 = getAnimatedOffset(static_cast<int>(i), phase1);
		vec2 pos1 = pointsString[i] + offset1;

		int connectionsDrawn = 0;
		int searchLimit = bConnectNearOnly ? ofClamp(CONNECTIONS_SEARCH_NEAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i)) : ofClamp(CONNECTIONS_SEARCH_FAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i));

		for (int offset = 1; offset < searchLimit && connectionsDrawn < maxConPerPoint; offset += skipFactor) {
			size_t j = i + offset;
			if (j >= pointsString.size()) break;

			float phase2 = t + 0.123f * static_cast<float>(j);
			vec2 offset2 = getAnimatedOffset(static_cast<int>(j), phase2);
			vec2 pos2 = pointsString[j] + offset2;

			float dist = glm::distance(pos1, pos2);

			if (dist < maxDist) {
				float alpha = ofMap(dist, 0, maxDist, connectAlpha.get(), 0, true);
				ofSetColor(colorConnection.get(), alpha);
				ofDrawLine(pos1, pos2);
				connectionsDrawn++;
				cachedConnectionCount++;
			}
		}
	}

	ofPopStyle();
}

//--

//--------------------------------------------------------------
void OrganicText::drawDebug() const {
	ofPushStyle();

	// Smooth alpha blinking using sine wave
	float t = ofGetElapsedTimef(); // Elapsed time in seconds
	float speed = 1.0f; // Blink speed (cycles per second)
	float alpha = (sin(TWO_PI * speed * t) * 0.5f + 0.5f) * DEBUG_ALPHA_MAX + DEBUG_ALPHA_MIN_OFFSET;
	// sin oscillates -1..1 → remap to 0..1 → scale to 0..255
	ofSetColor(colorDebug.r, colorDebug.g, colorDebug.b, static_cast<int>(alpha));

	ofNoFill();
	ofSetLineWidth(1);

	// Text center crosshair
	float crossSize = 2.5f;
	ofDrawLine(textCenter - vec2(crossSize, 0), textCenter + vec2(crossSize, 0));
	ofDrawLine(textCenter - vec2(0, crossSize), textCenter + vec2(0, crossSize));
	ofDrawCircle(textCenter, 2);

	// All sample points
	ofFill();
	for (const auto & point : pointsString) {
		ofDrawCircle(point, 3);
	}

	// Bounding box
	if (!pointsString.empty()) {
		vec2 minP = pointsString[0];
		vec2 maxP = pointsString[0];
		for (const auto & point : pointsString) {
			minP = glm::min(minP, point);
			maxP = glm::max(maxP, point);
		}

		ofNoFill();
		ofSetLineWidth(3);
		ofDrawRectangle(minP.x, minP.y, maxP.x - minP.x, maxP.y - minP.y);

		//#if 0
		//		// Dimensions text
		//		ofDrawBitmapStringHighlight(
		//			"W:" + ofToString(maxP.x - minP.x, 0) + " H:" + ofToString(maxP.y - minP.y, 0),
		//			minP.x, minP.y - 20,
		//			ofColor(255, 0, 255,static_cast<int>(alpha)),
		//			ofColor(0, 0, 0));
		//#endif
	}

	//#if 0
	//	// Show normalized densityMinGap mapped value
	//	float fontScale = fontSize.get() / 150.0f;
	//	float minGapMapped = ofMap(densityMinGap.get(), 0, 1, DENSITY_MIN_SPACING_MIN, DENSITY_MIN_SPACING_MAX, true) * fontScale;
	//	ofDrawBitmapStringHighlight(
	//		"MinGap: " + ofToString(densityMinGap.get(), 2) + " -> " + ofToString(minGapMapped, 1) + "px",
	//		textCenter.x - 100, textCenter.y + fontSize.get()*0.65f,
	//		ofColor(255, 0, 255,static_cast<int>(alpha)),
	//		ofColor(0, 0, 0));
	//#endif

	ofPopStyle();
}

//--

//--------------------------------------------------------------
void OrganicText::draw() {
	auto td = ofGetElapsedTimeMicros();

	float zoomFactor = 1.0f + (zoomGlobal.get() * ZOOM_MAX_X);

	ofPushMatrix();

	float centerX = ofGetWidth() * 0.5f;
	float centerY = ofGetHeight() * 0.5f;
	ofTranslate(centerX, centerY);
	ofScale(zoomFactor, zoomFactor);

	ofTranslate(-font.stringWidth(sText) * 0.5f, font.stringHeight(sText) * 0.5f);

	// Layer 1: Connections
	if (bDrawConnections) {
		drawConnections();
	}

	// Layer 2: Trails
	if (bDrawTrails) {
		updateTrails();

		ofPushStyle();
		ofSetLineWidth(trailLineWidth);
		float tf = ofMap(trailFade, 0.f, 1.f, TRAILS_FADE_MIN, TRAILS_FADE_MAX, true);

		for (size_t i = 0; i < pointTrails.size(); i++) {
			for (size_t j = 1; j < pointTrails[i].size(); j++) {
				float fadeAmount = pow(tf, static_cast<float>(j));
				float alpha = fadeAmount * TRAILS_ALPHA_MAX;

				ofSetColor(colorTrails.get(), alpha);
				ofDrawLine(pointTrails[i][j - 1], pointTrails[i][j]);
			}
		}

		ofPopStyle();
	}

	// Layer 3: Shapes
	if (bDrawShapes) {
		for (size_t i = 0; i < pointsString.size(); i++) {
			ofPushStyle();

			float phase = t + 0.123f * static_cast<float>(i);
			vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
			vec2 finalPos = pointsString[i] + offset;

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

			float rotation = ofMap(shapeRotation.get(), 0, 1, 0, 360);

			drawShape(finalPos, pointSize, (ShapeType)shapeType.get(), rotation);

			ofPopStyle();
		}
	}

	// Layer 4: Outline
	if (bDrawOutline) {
		if (!bDebugDraw) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(colorOutline.get());
			ofSetLineWidth(OUTLINE_WIDTH_BASE * zoomFactor);
			font.drawStringAsShapes(sText, 0, 0);
			ofPopStyle();
		}
	} else if (bDebugDraw) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(colorDebug, DEBUG_ALPHA_MAX);
		ofSetLineWidth(1.f);
		font.drawStringAsShapes(sText, 0, 0);
		ofPopStyle();
	}

	// Layer 5: Debug (always on top)
	if (bDebugDraw) {
		drawDebug();
	}

	ofPopMatrix();

	// Debug bench measuring drawing performance
	tBench = ofGetElapsedTimeMicros() - td;
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

	int totalPoints = pointsString.size();

	int totalTrailPoints = 0;
	for (const auto & trail : pointTrails) {
		totalTrailPoints += trail.size();
	}

	// Use cached connection count from last draw
	int activeConnections = cachedConnectionCount;

	string perfStatus = (fps >= (targetFPS * 0.9f)) ? "GOOD" : ((fps <= (targetFPS * 0.5f)) ? "OK" : "POOR");
	ofColor perfColor = (fps >= (targetFPS * 0.9f)) ? ofColor(100, 255, 100) : ((fps >= (targetFPS * 0.5f) ? ofColor(255, 255, 100) : ofColor(255, 100, 100)));

	std::vector<string> lines;
	lines.push_back("ORGANIC");
	lines.push_back("TEXT");
	lines.push_back("");
	lines.push_back("PERFORMANCE");
	lines.push_back("FPS      " + ofToString(fps, 0) + " [" + ofToString(targetFPS, 0) + "] " + perfStatus + "");
	lines.push_back("Frame    " + ofToString(frameTime, 0) + " ms");
	lines.push_back("Draw t   " + ofToString(tBench) + " mics");
	lines.push_back("");
	lines.push_back("GEOMETRY");
	lines.push_back("Points   " + ofToString(totalPoints));
	lines.push_back("Shapes   " + ofToString(bDrawShapes.get() ? totalPoints : 0));
	lines.push_back("Connects " + ofToString(bDrawConnections.get() ? activeConnections : 0));
	lines.push_back("Trails   " + ofToString(bDrawTrails.get() ? totalTrailPoints : 0));
	lines.push_back("");
	lines.push_back("CONFIG");
	lines.push_back("Font     " + ofToString(fontSize.get(), 0) + "px");
	lines.push_back("Density  " + ofToString(densityAmount.get(), 2));
	lines.push_back("Animate  " + string(bEnableAnimation.get() ? "ON" : "OFF"));
	lines.push_back("Shape    " + shapeTypeName.get());
	lines.push_back("Color    " + colorModeName.get());
	lines.push_back("Anim     " + animationModeName.get());
	lines.push_back("");
	lines.push_back("Font     " + ofToString(fontSize.get(), 0) + "px");
	lines.push_back("");
	if (bKeys) {
		lines.push_back("KEYS");
		lines.push_back("");
		lines.push_back("PARAMS");
		lines.push_back("< >      Zoom");
		lines.push_back("UP/DOWN  Anima Speed");
		lines.push_back("+/-      Point Density");
		lines.push_back("");
		lines.push_back("O        Outline");
		lines.push_back("F        Shape Fill");
		lines.push_back("L        Connections");
		lines.push_back("T        Trails");
		lines.push_back("B        Background Color");
		lines.push_back("");
		lines.push_back("C        Color Modes");
		lines.push_back("A        Animation Modes");
		lines.push_back("R        Reset all");
	}

	float lineHeight = 16;
	float padding = 10;
	float boxWidth = 240;
	float boxHeight = lines.size() * lineHeight + padding * 2;

	float boxX;
	float boxY;

	if (bGui) {
		// linked to gui anchor
		boxX = gui.getPosition().x - 246;
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

	// // Decoration Border
	// ofSetColor(perfColor);
	// ofNoFill();
	// ofSetLineWidth(2);
	// ofDrawRectangle(boxX, boxY, boxWidth, boxHeight);

	// Text
	for (size_t i = 0; i < lines.size(); i++) {
		float textX = boxX + padding;
		float textY = boxY + padding + (i + 1) * lineHeight - 2;

		if (lines[i].find("FPS:") != string::npos) {
			ofSetColor(perfColor);
		} else if (lines[i].find("===") != string::npos) {
			ofSetColor(255, 200, 0);
		} else if (lines[i].find("Points:") != string::npos || lines[i].find("Connections:") != string::npos) {
			if (totalPoints > 1500 || activeConnections > 5000) {
				ofSetColor(255, 150, 0);
			} else {
				ofSetColor(255);
			}
		} else {
			ofSetColor(255);
		}

		ofDrawBitmapString(lines[i], textX, textY);
	}

	ofPopStyle();
	ofPopMatrix();
}

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
		//refreshPointsString();
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
	g.minimizeAll();
}

//--------------------------------------------------------------
void OrganicText::exit() {
	ofLogNotice("OrganicText") << "exit()";

	if (bAutosave) saveSettings();
}

//--

//--------------------------------------------------------------
// RESET FUNCTIONS
//--------------------------------------------------------------

//--------------------------------------------------------------
void OrganicText::resetPreset() {
	ofLogNotice("OrganicText") << "resetPreset()";

	resetDensityParams();
	resetShapeParams();
	resetColorModes();
	resetGlobalColorParams();
	resetAnimationParams();
	resetConnectionParams();
}

//--------------------------------------------------------------
void OrganicText::resetAll() {
	ofLogNotice("OrganicText") << "resetAll()";

	resetPreset();
	resetFonts();

	zoomGlobal.set(0.f);
	t = 0.0f;

	//refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::randomAll() {
	ofLogNotice("OrganicText") << "randomAll()";

	randomizeDensityParams();
	randomizeShapeParams();
	randomizeColorModes();
	randomizeGlobalColorParams();
	randomizeAnimationParams();
	randomizeConnectionParams();

	//refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::resetFonts() {
	ofLogNotice("OrganicText") << "resetFonts()";

	//fontPath.set("NotoSansMono-Regular.ttf");
	fontSize.set(150);
	letterSpacing.set(0);
}

void OrganicText::resetDensityParams() {
	ofLogNotice("OrganicText") << "resetDensityParams()";

	densitySpacing.set(0.25f);
	densityAmount.set(0.8f);
	densityMinGap.set(0.1f);

	//refreshPointsString();
}

void OrganicText::resetShapeParams() {
	ofLogNotice("OrganicText") << "resetShapeParams()";

	bDrawShapes.set(true);
	bDrawFill.set(true);
	shapeSize.set(0.1f);
	shapeSizeMin.set(0.f);
	shapeType.set(0);
	shapeRatio.set(.5f);
	shapeRotation.set(0.0f);
}

void OrganicText::resetColorModes() {
	ofLogNotice("OrganicText") << "resetColorModes()";

	colorMode.set(3);
	colorSpeed.set(0.5f);
	colorMixFactor.set(0.4f);
	bColorByDistance.set(false);
}

void OrganicText::resetGlobalColorParams() {
	ofLogNotice("OrganicText") << "resetGlobalColorParams()";

	color1.set(ofColor(120, 180, 255));
	color2.set(ofColor(180, 140, 255));
	color3.set(ofColor(140, 200, 240));
	colorConnection.set(ofColor(150, 180, 255, 80));
	colorOutline.set(ofColor(60, 60, 60));
}

void OrganicText::resetAnimationParams() {
	ofLogNotice("OrganicText") << "resetAnimationParams()";

	animationMode.set(0);
	animSpeed.set(0.8f);
	animPower.set(0.05f);
	animWaveFreq.set(0.3f);
	animIntensity.set(0.2f);
	animSpiral.set(0.2f);
	animPulseIntensity.set(0.2f);
}

void OrganicText::resetConnectionParams() {
	ofLogNotice("OrganicText") << "resetConnectionParams()";

	bDrawConnections.set(false);
	connectDistance.set(30.0f);
	connectLineWidth.set(1.5f);
	connectAlpha.set(100.0f);
	connectQuality.set(0.5f);
	bConnectNearOnly.set(true);
	bDrawTrails.set(false);
	trailLineWidth.set(1.5f);
	trailLength.set(0.5);
	trailFade.set(0.5f);
}

//--------------------------------------------------------------
// RANDOMIZE FUNCTIONS
//--------------------------------------------------------------

void OrganicText::randomizeDensityParams() {
	densitySpacing.set(ofRandom(densitySpacing.getMin(), densitySpacing.getMax()));
	densityAmount.set(ofRandom(densityAmount.getMin(), densityAmount.getMax()));
	densityMinGap.set(ofRandom(densityMinGap.getMin(), densityMinGap.getMax()));

	//refreshPointsString();
}

void OrganicText::randomizeShapeParams() {
	shapeSize.set(ofRandom(shapeSize.getMin(), shapeSize.getMax()));
	shapeSizeMin.set(ofRandom(shapeSizeMin.getMin(), shapeSizeMin.getMax()));
	shapeType.set(static_cast<int>(ofRandom(0, 6)));
	shapeRatio.set(ofRandom(shapeRatio.getMin(), shapeRatio.getMax()));
	shapeRotation.set(ofRandom(shapeRotation.getMin(), shapeRotation.getMax()));
}

void OrganicText::randomizeColorModes() {
	colorMode.set(static_cast<int>(ofRandom(0, 5)));
	colorSpeed.set(ofRandom(colorSpeed.getMin(), colorSpeed.getMax()));
	colorMixFactor.set(ofRandom(colorMixFactor.getMin(), colorMixFactor.getMax()));
	bColorByDistance.set(ofRandom(1.0f) > 0.5f);
}

void OrganicText::randomizeGlobalColorParams() {
	color1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	colorOutline.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	colorConnection.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	colorTrails.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}

void OrganicText::randomizeAnimationParams() {
	if (!bEnableAnimation) bEnableAnimation = true;
	animationMode.set(static_cast<int>(ofRandom(0, 5)));
	animSpeed.set(ofRandom(animSpeed.getMin(), animSpeed.getMax()));
	animPower.set(ofRandom(animPower.getMin(), animPower.getMax()));
	animWaveFreq.set(ofRandom(animWaveFreq.getMin(), animWaveFreq.getMax()));
	animIntensity.set(ofRandom(animIntensity.getMin(), animIntensity.getMax()));
	animSpiral.set(ofRandom(animSpiral.getMin(), animSpiral.getMax()));
	animPulseIntensity.set(ofRandom(animPulseIntensity.getMin(), animPulseIntensity.getMax()));
}

void OrganicText::randomizeConnectionParams() {
	connectDistance.set(ofRandom(connectDistance.getMin(), connectDistance.getMax()));
	connectAlpha.set(ofRandom(connectAlpha.getMin(), connectAlpha.getMax()));
	connectQuality.set(ofRandom(connectQuality.getMin(), connectQuality.getMax()));
	bDrawConnections.set(ofRandom(1.0f) > 0.3f);
	bConnectNearOnly.set(ofRandom(1.0f) > 0.5f);
	bDrawTrails.set(ofRandom(1.0f) > 0.3f);
	trailLength.set(ofRandom(trailLength.getMin(), trailLength.getMax()));
	trailLineWidth.set(ofRandom(trailLineWidth.getMin(), trailLineWidth.getMax()));
	trailFade.set(ofRandom(trailFade.getMin(), trailFade.getMax()));
}

//--

//--------------------------------------------------------------
void OrganicText::keyPressed(ofKeyEventArgs & eventArgs) {
	if (!bKeys) return;

	const int key = eventArgs.key;

	if (key == 'd') {
		bDebugDraw.set(!bDebugDraw.get());
	} else if (key == 'D') {
		bHelp.set(!bHelp.get());
	} else if (key == 'b' || key == 'B') {
		static bool darkBg = true;
		darkBg = !darkBg;
		ofBackground(darkBg ? 0 : 255);
	} else if (key == 'r' || key == 'R') {
		resetAll();
	}

	else if (key == 'c' || key == 'C') {
		colorMode.set((colorMode.get() + 1) % 5);
	} else if (key == 'a' || key == 'A') {
		animationMode.set((animationMode.get() + 1) % 5);
	} else if (key == '+' || key == '=') {
		densityAmount.set(ofClamp(densityAmount.get() + 0.2f, 0.1f, 5.0f));
	} else if (key == '-') {
		densityAmount.set(ofClamp(densityAmount.get() - 0.2f, 0.1f, 5.0f));
	}

	else if (key == OF_KEY_UP) {
		animSpeed.set(ofClamp(animSpeed.get() + 0.1f, 0.1f, 3.0f));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(ofClamp(animSpeed.get() - 0.1f, 0.1f, 3.0f));
	} else if (key == OF_KEY_LEFT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() - 0.1f, 0.0f, 1.0f));
	} else if (key == OF_KEY_RIGHT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() + 0.1f, 0.0f, 1.0f));
	}

	else if (key == 't' || key == 'T') {
		bDrawTrails.set(!bDrawTrails.get());
	} else if (key == 'l' || key == 'L') {
		bDrawConnections.set(!bDrawConnections.get());
	} else if (key == 'o' || key == 'O') {
		bDrawOutline.set(!bDrawOutline.get());
	} else if (key == 'f' || key == 'F') {
		bDrawFill.set(!bDrawFill.get());
	}
}

////--------------------------------------------------------------
//ofxGuiGroup & OrganicText::getGroupGui(){
//	return gui.getGroup(paramsPreset.getName());
//}
