#include "organicText.h"
#include <algorithm>
#include <cmath>

//--------------------------------------------------------------
OrganicText::OrganicText() {
	ofAddListener(ofEvents().update, this, &OrganicText::update);
}

//--------------------------------------------------------------
OrganicText::~OrganicText() {
	ofRemoveListener(ofEvents().update, this, &OrganicText::update);
}

//--------------------------------------------------------------
void OrganicText::exit() {
	saveSettings();
}

//--------------------------------------------------------------
void OrganicText::setupParams() {
	// Basic parameters
	bDebugDraw.set("Debug Draw", false);
	bDebugDrawInfo.set("Debug Info", false);
	bDrawFill.set("Fill", true);
	bDrawShapes.set("Shapes", true);
	bEnableAnimation.set("Animate", true);
	bDrawOutline.set("Outline", false);
	zoomGlobal.set("Zoom", 0.0f, 0.0f, 1.0f);
	sText.set("Text", ORGANICTEXT);

	// Font parameters
	fontPath.set("Font Path", "NotoSansMono-Regular.ttf");
	fontSize.set("Font Size", 150, 50, 500);

	// Density group (simplified names)
	resetDensity.set("Reset");
	randomDensity.set("Random");
	densitySpacing.set("Spacing", 0.2, 0.05, 1);
	densityAmount.set("Amount", 1.0, 0.1, 5.0);
	densityMinGap.set("Min Gap", 0.1, 0.0, 1.0); // Now normalized 0-1

	// Shape group
	resetShape.set("Reset");
	randomShape.set("Random");
	shapeType.set("Type", 0, 0, 5);
	shapeTypeName.set("Name", "Circle");
	shapeTypeName.setSerializable(false);
	shapePointRadius.set("Size", 0.5, 0, 1);
	shapePointsRadiusMin.set("Min Size", 0.3, 0, 1);
	shapeTriangleRatio.set("Tri Ratio", 1.0, 0.5, 2.0);
	shapeRotation.set("Rotation", 0, 0, 360);

	// Color group
	resetColor.set("Reset");
	randomColor.set("Random");
	colorMode.set("Mode", 3, 0, 4);
	colorModeName.set("Mode Name", "Mix");
	colorModeName.setSerializable(false);
	colorSpeed.set("Speed", 1.0, 0.1, 5.0);
	colorMixFactor.set("Mix", 0.5, 0.0, 1.0);
	bColorByDistance.set("By Dist", false);

	// Colors group
	resetGlobalColors.set("Reset");
	randomGlobalColors.set("Random");
	color1.set("Color 1", ofColor::cyan);
	color2.set("Color 2", ofColor::magenta);
	color3.set("Color 3", ofColor::yellow);
	colorOutline.set("Outline", ofColor::white);
	colorConnection.set("Connect", ofColor::white);

	// Animation group
	resetAnimation.set("Reset");
	randomAnimation.set("Random");
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
	resetConnection.set("Reset");
	randomConnection.set("Random");
	bDrawConnections.set("Draw", false);
	connectDistance.set("Distance", 30, 5, 100);
	connectAlpha.set("Alpha", 100, 0, 255);
	bConnectNearOnly.set("Near Only", true);
	connectQuality.set("Quality", 1.0, 0.1, 1.0);

	// Trail group
	bDrawTrails.set("Trails", false);
	trailLength.set("Length", 10, 3, 50);
	trailFade.set("Fade", 0.9, 0.5, 0.99);

	// Global reset
	resetAll.set("Reset All");

	// Organize groups
	fontGroup.setName("Font");
	fontGroup.add(fontPath);
	fontGroup.add(fontSize);

	densityGroup.setName("Density");
	densityGroup.add(densitySpacing);
	densityGroup.add(densityAmount);
	densityGroup.add(densityMinGap);
	densityGroup.add(randomDensity);
	densityGroup.add(resetDensity);

	shapeGroup.setName("Shape");
	shapeGroup.add(bDrawFill);
	shapeGroup.add(shapeType);
	shapeGroup.add(shapeTypeName);
	shapeGroup.add(shapePointRadius);
	shapeGroup.add(shapePointsRadiusMin);
	shapeGroup.add(shapeTriangleRatio);
	shapeGroup.add(shapeRotation);
	shapeGroup.add(randomShape);
	shapeGroup.add(resetShape);

	colorModesGroup.setName("Color Modes");
	colorModesGroup.add(colorMode);
	colorModesGroup.add(colorModeName);
	colorModesGroup.add(colorSpeed);
	colorModesGroup.add(colorMixFactor);
	colorModesGroup.add(bColorByDistance);
	colorModesGroup.add(randomColor);
	colorModesGroup.add(resetColor);

	colorGlobalGroup.setName("Colors");
	colorGlobalGroup.add(color1);
	colorGlobalGroup.add(color2);
	colorGlobalGroup.add(color3);
	colorGlobalGroup.add(colorOutline);
	colorGlobalGroup.add(colorConnection);
	colorGlobalGroup.add(randomGlobalColors);
	colorGlobalGroup.add(resetGlobalColors);

	animGroup.setName("Animation");
	animGroup.add(bEnableAnimation);
	animGroup.add(animationMode);
	animGroup.add(animationModeName);
	animGroup.add(animSpeed);
	animGroup.add(animPower);
	animGroup.add(animWaveFreq);
	animGroup.add(animIntensity);
	animGroup.add(animSpiral);
	animGroup.add(animPulseIntensity);
	animGroup.add(randomAnimation);
	animGroup.add(resetAnimation);

	connectionGroup.setName("Connections");
	connectionGroup.add(bDrawConnections);
	connectionGroup.add(connectDistance);
	connectionGroup.add(connectAlpha);
	connectionGroup.add(connectQuality);
	connectionGroup.add(bConnectNearOnly);
	connectionGroup.add(bDrawTrails);
	connectionGroup.add(trailLength);
	connectionGroup.add(trailFade);
	connectionGroup.add(resetConnection);
	connectionGroup.add(randomConnection);

	parameters.setName("OrganicText");
	parameters.add(sText);
	parameters.add(zoomGlobal);
	parameters.add(bDrawOutline);
	parameters.add(bDrawShapes);
	parameters.add(bDrawConnections);
	parameters.add(bEnableAnimation);

	parameters.add(fontGroup);
	parameters.add(shapeGroup);
	parameters.add(densityGroup);
	parameters.add(colorGlobalGroup);
	parameters.add(colorModesGroup);
	parameters.add(animGroup);
	parameters.add(connectionGroup);
	parameters.add(bDebugDraw);
	parameters.add(bDebugDrawInfo);
	parameters.add(resetAll);
}

//--------------------------------------------------------------
void OrganicText::setupCallbacks() {
	// Font listeners
	e_FontPath = fontPath.newListener([this](string & s) { reloadFont(); });
	e_FontSize = fontSize.newListener([this](float & f) { reloadFont(); });

	// Density listeners
	e_DensitySpacing = densitySpacing.newListener([this](float & v) { refreshPointsString(); });
	e_DensityAmount = densityAmount.newListener([this](float & v) { refreshPointsString(); });
	e_sText = sText.newListener([this](string & s) { refreshPointsString(); });

	// Mode name listeners
	shapeType.addListener(this, &OrganicText::updateShapeTypeName);
	colorMode.addListener(this, &OrganicText::updateColorModeName);
	animationMode.addListener(this, &OrganicText::updateAnimationModeName);

	// Reset listeners
	e_ResetDensity = resetDensity.newListener([this](void) { resetDensityParams(); });
	e_ResetShape = resetShape.newListener([this](void) { resetShapeParams(); });
	e_ResetColor = resetColor.newListener([this](void) { resetColorParams(); });
	e_ResetGlobalColor = resetGlobalColors.newListener([this](void) { resetGlobalColorParams(); });
	e_ResetAnimation = resetAnimation.newListener([this](void) { resetAnimationParams(); });
	e_ResetConnection = resetConnection.newListener([this](void) { resetConnectionParams(); });
	e_ResetAll = resetAll.newListener([this](void) { resetAllParams(); });

	// Random listeners
	e_RandomDensity = randomDensity.newListener([this](void) { randomizeDensityParams(); });
	e_RandomShape = randomShape.newListener([this](void) { randomizeShapeParams(); });
	e_RandomColor = randomColor.newListener([this](void) { randomizeColorParams(); });
	e_RandomGlobalColor = randomGlobalColors.newListener([this](void) { randomizeGlobalColorParams(); });
	e_RandomAnimation = randomAnimation.newListener([this](void) { randomizeAnimationParams(); });
	e_RandomConnection = randomConnection.newListener([this](void) { randomizeConnectionParams(); });
}

//--------------------------------------------------------------
void OrganicText::setup() {
	setupParams();
	setupCallbacks();

	// Setup GUI
	gui.setup(parameters);
	gui.getGroup(fontGroup.getName()).minimizeAll();
	gui.getGroup(densityGroup.getName()).minimizeAll();
	gui.getGroup(shapeGroup.getName()).minimizeAll();
	gui.getGroup(colorModesGroup.getName()).minimizeAll();
	gui.getGroup(colorGlobalGroup.getName()).minimizeAll();
	gui.getGroup(animGroup.getName()).minimizeAll();
	gui.getGroup(connectionGroup.getName()).minimizeAll();
	gui.minimizeAll();

	// Initialize
	t = 0.0;
	textCenter = vec2(0, 0);

	// Load font
	reloadFont();

	// Set defaults
	resetAllParams();

	// Initialize mode names
	int dummy = 0;
	updateShapeTypeName(dummy);
	updateColorModeName(dummy);
	updateAnimationModeName(dummy);

	// Graphics setup
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	// Load saved settings
	loadSettings();

	ofLogNotice("OrganicText") << "Setup complete - Target FPS: " << targetFPS;
}

//--------------------------------------------------------------
void OrganicText::reloadFont() {
	bool success = font.load(fontPath.get(), fontSize.get(), false, false, true);

	if (success) {
		ofLogNotice("OrganicText") << "Font loaded: " << fontPath.get() << " @ " << fontSize.get() << "px";
		refreshPointsString();
	} else {
		ofLogError("OrganicText") << "Failed to load font: " << fontPath.get();
	}
}

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

	string wt = ("FPS: " + ofToString(fps, 0) + " / " + ofToString(targetFPS, 0) + " | " + ofToString(frameTime, 2) + "ms");
	ofSetWindowTitle(wt);
}

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
	pointTrails.clear();
	pointTrails.resize(pointsString.size());
	for (size_t i = 0; i < pointsString.size(); i++) {
		pointTrails[i].resize(trailLength.get());
		for (int j = 0; j < trailLength.get(); j++) {
			pointTrails[i][j] = pointsString[i];
		}
	}

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

	switch (shape) {
	case SHAPE_CIRCLE:
		ofDrawCircle(0, 0, size);
		break;

	case SHAPE_RECTANGLE:
		ofDrawRectangle(-size * 0.5f, -size * 0.5f, size, size);
		break;

	case SHAPE_TRIANGLE: {
		float h = size * shapeTriangleRatio.get();
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
		star.draw();
		break;
	}

	case SHAPE_CROSS: {
		float thickness = size * 0.2f;
		ofDrawRectangle(-thickness * 0.5f, -size * 0.5f, thickness, size);
		ofDrawRectangle(-size * 0.5f, -thickness * 0.5f, size, thickness);
		break;
	}

	case SHAPE_POINT: {
		ofDrawCircle(0, 0, size * 0.3f);
		break;
	}
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void OrganicText::updateTrails() {
	if (!bDrawTrails) return;

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
}

//--------------------------------------------------------------
void OrganicText::drawDebug() const {
	ofPushStyle();

	// Bright magenta - visible on any background
	ofSetColor(255, 0, 255);
	ofNoFill();
	ofSetLineWidth(2);

	// Text center crosshair
	float crossSize = 20;
	ofDrawLine(textCenter - vec2(crossSize, 0), textCenter + vec2(crossSize, 0));
	ofDrawLine(textCenter - vec2(0, crossSize), textCenter + vec2(0, crossSize));
	ofDrawCircle(textCenter, 8);

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

		// Dimensions text
		ofDrawBitmapStringHighlight(
			"W:" + ofToString(maxP.x - minP.x, 0) + " H:" + ofToString(maxP.y - minP.y, 0),
			minP.x, minP.y - 5,
			ofColor(255, 0, 255),
			ofColor(0, 0, 0));
	}

	// Show normalized densityMinGap mapped value
	float fontScale = fontSize.get() / 150.0f;
	float minGapMapped = ofMap(densityMinGap.get(), 0, 1, DENSITY_MIN_SPACING_MIN, DENSITY_MIN_SPACING_MAX, true) * fontScale;
	ofDrawBitmapStringHighlight(
		"MinGap: " + ofToString(densityMinGap.get(), 2) + " -> " + ofToString(minGapMapped, 1) + "px",
		textCenter.x - 100, textCenter.y + 40,
		ofColor(255, 0, 255),
		ofColor(0, 0, 0));

	ofPopStyle();
}

//--------------------------------------------------------------
void OrganicText::drawDebugInfo() const {
	ofPushStyle();

	int totalPoints = pointsString.size();

	int totalTrailPoints = 0;
	for (const auto & trail : pointTrails) {
		totalTrailPoints += trail.size();
	}

	// Use cached connection count from last draw
	int activeConnections = cachedConnectionCount;

	string perfStatus = fps >= 55 ? "GOOD" : (fps >= 30 ? "OK" : "POOR");
	ofColor perfColor = fps >= 55 ? ofColor(100, 255, 100) : (fps >= 30 ? ofColor(255, 255, 100) : ofColor(255, 100, 100));

	vector<string> lines;
	lines.push_back("=== PERFORMANCE ===");
	lines.push_back("FPS: " + ofToString(fps, 1) + " / " + ofToString(targetFPS, 0) + " (" + perfStatus + ")");
	lines.push_back("Frame: " + ofToString(frameTime, 2) + " ms");
	lines.push_back("");
	lines.push_back("=== GEOMETRY ===");
	lines.push_back("Points: " + ofToString(totalPoints));
	lines.push_back("Shapes: " + ofToString(bDrawShapes.get() ? totalPoints : 0));
	lines.push_back("Trails: " + ofToString(bDrawTrails.get() ? totalTrailPoints : 0));
	lines.push_back("Connections: " + ofToString(bDrawConnections.get() ? activeConnections : 0));
	lines.push_back("");
	lines.push_back("=== CONFIG ===");
	lines.push_back("Font: " + ofToString(fontSize.get(), 0) + "px");
	lines.push_back("Density: " + ofToString(densityAmount.get(), 2));
	lines.push_back("Animate: " + string(bEnableAnimation.get() ? "ON" : "OFF"));
	lines.push_back("Shape: " + shapeTypeName.get());
	lines.push_back("Color: " + colorModeName.get());
	lines.push_back("Anim: " + animationModeName.get());

	float lineHeight = 16;
	float padding = 10;
	float boxWidth = 240;
	float boxHeight = lines.size() * lineHeight + padding * 2;

	float boxX = ofGetWidth() - boxWidth - 15;
	float boxY = 15;

	// Background
	ofSetColor(0, 0, 0, 220);
	ofFill();
	ofDrawRectangle(boxX, boxY, boxWidth, boxHeight);

	// Border
	ofSetColor(perfColor);
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawRectangle(boxX, boxY, boxWidth, boxHeight);

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
}

//--------------------------------------------------------------
void OrganicText::draw() {
	float zoomFactor = 1.0f + (zoomGlobal.get() * ZOOM_MAX_X);

	ofPushMatrix();

	float centerX = ofGetWidth() * 0.5f;
	float centerY = ofGetHeight() * 0.5f;
	ofTranslate(centerX, centerY);
	ofScale(zoomFactor, zoomFactor);

	ofTranslate(-font.stringWidth(sText) * 0.5f, font.stringHeight(sText) * 0.5f);

	updateTrails();

	// Layer 1: Connections
	if (bDrawConnections) {
		drawConnections();
	}

	// Layer 2: Trails
	if (bDrawTrails) {
		for (size_t i = 0; i < pointTrails.size(); i++) {
			for (size_t j = 1; j < pointTrails[i].size(); j++) {
				float fadeAmount = pow(trailFade.get(), static_cast<float>(j));
				float alpha = fadeAmount * TRAIL_MAX_ALPHA;

				ofSetColor(colorConnection.get(), alpha);
				ofDrawLine(pointTrails[i][j - 1], pointTrails[i][j]);
			}
		}
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

			float minSize = ofMap(shapePointsRadiusMin.get(), 0, 1, MIN_RADIUS, MAX_RADIUS, true);
			float maxSize = ofMap(shapePointRadius.get(), 0, 1, minSize, MAX_RADIUS, true);

			float sizeNoise = ofNoise(phase * SHAPE_SIZE_NOISE_SCALE, static_cast<float>(i) * SHAPE_SIZE_INDEX_SCALE);
			float pointSize = ofLerp(minSize, maxSize, sizeNoise);

			float rotation = shapeRotation.get();
			if (bEnableAnimation.get()) {
				rotation += t * 360.0f * animSpeed.get() * SHAPE_ROTATION_SPEED;
			}

			drawShape(finalPos, pointSize, (ShapeType)shapeType.get(), rotation);

			ofPopStyle();
		}
	}

	// Layer 4: Outline
	if (bDrawOutline) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(colorOutline.get());
		ofSetLineWidth(OUTLINE_WIDTH_BASE / zoomFactor);
		font.drawStringAsShapes(sText, 0, 0);
		ofPopStyle();
	}

	// Layer 5: Debug (always on top)
	if (bDebugDraw) {
		drawDebug();
	}

	ofPopMatrix();

	// UI overlays
	gui.draw();

	if (bDebugDrawInfo) {
		drawDebugInfo();
	}
}

//--------------------------------------------------------------
void OrganicText::keyPressed(ofKeyEventArgs & eventArgs) {
	const int key = eventArgs.key;
	bool mod_CMD = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CTRL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	if (key >= '0' && key <= '9') {
		loadPreset(key - '0');
	} else if (key >= '1' && key <= '5' && mod_SHIFT) {
		shapeType.set(key - '1');
	} else if (key == 'c' || key == 'C') {
		colorMode.set((colorMode.get() + 1) % 5);
	} else if (key == 'a' || key == 'A') {
		animationMode.set((animationMode.get() + 1) % 5);
	} else if (key == '+' || key == '=') {
		densityAmount.set(ofClamp(densityAmount.get() + 0.2f, 0.1f, 5.0f));
	} else if (key == '-') {
		densityAmount.set(ofClamp(densityAmount.get() - 0.2f, 0.1f, 5.0f));
	} else if (key == OF_KEY_UP) {
		animSpeed.set(ofClamp(animSpeed.get() + 0.1f, 0.1f, 3.0f));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(ofClamp(animSpeed.get() - 0.1f, 0.1f, 3.0f));
	} else if (key == OF_KEY_LEFT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() - 0.1f, 0.0f, 1.0f));
	} else if (key == OF_KEY_RIGHT) {
		zoomGlobal.set(ofClamp(zoomGlobal.get() + 0.1f, 0.0f, 1.0f));
	} else if (key == 't' || key == 'T') {
		bDrawTrails.set(!bDrawTrails.get());
	} else if (key == 'l' || key == 'L') {
		bDrawConnections.set(!bDrawConnections.get());
	} else if (key == 'o' || key == 'O') {
		bDrawOutline.set(!bDrawOutline.get());
	} else if (key == 'f' || key == 'F') {
		bDrawFill.set(!bDrawFill.get());
	} else if (key == 'D') {
		bDebugDraw.set(!bDebugDraw.get());
	} else if (key == 'd') {
		bDebugDrawInfo.set(!bDebugDrawInfo.get());
	} else if (key == 'b' || key == 'B') {
		static bool darkBg = true;
		darkBg = !darkBg;
		ofBackground(darkBg ? 0 : 255);
	} else if (key == 'r' || key == 'R') {
		resetAllParams();
	} else if (key == 's' || key == 'S') {
		if (mod_CTRL || mod_CMD) {
			saveSettings();
		}
	} else if (key == 'l' || key == 'L') {
		if (mod_CTRL || mod_CMD) {
			loadSettings();
		}
	}
}

//--------------------------------------------------------------
void OrganicText::saveSettings() {
	ofJson settings;
	ofSerialize(settings, parameters);
	ofSavePrettyJson(pathSettings, settings);
	ofLogNotice("OrganicText") << "Settings saved";
}

//--------------------------------------------------------------
void OrganicText::loadSettings() {
	ofFile file(pathSettings);
	if (file.exists()) {
		ofJson settings = ofLoadJson(pathSettings);
		ofDeserialize(settings, parameters);
		refreshPointsString();
		ofLogNotice("OrganicText") << "Settings loaded";
	}
}

//--------------------------------------------------------------
// RESET FUNCTIONS
//--------------------------------------------------------------

void OrganicText::resetAllParams() {
	bDrawFill.set(true);
	bDrawShapes.set(true);
	bDrawOutline.set(false);
	bEnableAnimation.set(true);
	zoomGlobal.set(0.0f);

	densitySpacing.set(0.25f);
	densityAmount.set(0.8f);
	densityMinGap.set(0.1f);

	shapeType.set(0);
	shapePointRadius.set(0.4f);
	shapePointsRadiusMin.set(0.3f);
	shapeTriangleRatio.set(1.0f);
	shapeRotation.set(0.0f);

	colorMode.set(3);
	colorSpeed.set(0.5f);
	colorMixFactor.set(0.4f);
	bColorByDistance.set(false);

	color1.set(ofColor(120, 180, 255));
	color2.set(ofColor(180, 140, 255));
	color3.set(ofColor(140, 200, 240));
	colorOutline.set(ofColor(60, 60, 60));
	colorConnection.set(ofColor(150, 180, 255, 80));

	animationMode.set(0);
	animSpeed.set(0.8f);
	animPower.set(0.15f);
	animWaveFreq.set(0.3f);
	animIntensity.set(0.2f);
	animSpiral.set(0.2f);
	animPulseIntensity.set(0.2f);

	bDrawConnections.set(false);
	connectDistance.set(30.0f);
	connectAlpha.set(100.0f);
	connectQuality.set(0.5f);
	bConnectNearOnly.set(true);

	bDrawTrails.set(false);
	trailLength.set(10);
	trailFade.set(0.9f);

	t = 0.0f;
	refreshPointsString();
}

void OrganicText::resetDensityParams() {
	densitySpacing.set(0.25f);
	densityAmount.set(0.8f);
	densityMinGap.set(0.1f);
	refreshPointsString();
}

void OrganicText::resetShapeParams() {
	bDrawFill.set(true);
	shapePointRadius.set(0.4f);
	shapePointsRadiusMin.set(0.3f);
	shapeType.set(0);
	shapeTriangleRatio.set(1.0f);
	shapeRotation.set(0.0f);
}

void OrganicText::resetColorParams() {
	colorMode.set(3);
	colorSpeed.set(0.5f);
	colorMixFactor.set(0.4f);
	bColorByDistance.set(false);
}

void OrganicText::resetGlobalColorParams() {
	color1.set(ofColor(120, 180, 255));
	color2.set(ofColor(180, 140, 255));
	color3.set(ofColor(140, 200, 240));
	colorConnection.set(ofColor(150, 180, 255, 80));
	colorOutline.set(ofColor(60, 60, 60));
}

void OrganicText::resetAnimationParams() {
	animationMode.set(0);
	animSpeed.set(0.8f);
	animPower.set(0.15f);
	animWaveFreq.set(0.3f);
	animIntensity.set(0.2f);
	animSpiral.set(0.2f);
	animPulseIntensity.set(0.2f);
}

void OrganicText::resetConnectionParams() {
	bDrawConnections.set(false);
	connectDistance.set(30.0f);
	connectAlpha.set(100.0f);
	connectQuality.set(0.5f);
	bConnectNearOnly.set(true);
	bDrawTrails.set(false);
	trailLength.set(10);
	trailFade.set(0.9f);
}

//--------------------------------------------------------------
// RANDOMIZE FUNCTIONS
//--------------------------------------------------------------

void OrganicText::randomizeDensityParams() {
	densitySpacing.set(ofRandom(0.05f, 1.0f));
	densityAmount.set(ofRandom(0.1f, 5.0f));
	densityMinGap.set(ofRandom(0.0f, 1.0f));
	refreshPointsString();
}

void OrganicText::randomizeShapeParams() {
	shapePointRadius.set(ofRandom(0.0f, 1.0f));
	shapePointsRadiusMin.set(ofRandom(0.0f, 1.0f));
	shapeType.set(static_cast<int>(ofRandom(0, 6)));
	shapeTriangleRatio.set(ofRandom(0.5f, 2.0f));
}

void OrganicText::randomizeColorParams() {
	colorMode.set(static_cast<int>(ofRandom(0, 5)));
	colorSpeed.set(ofRandom(0.1f, 5.0f));
	colorMixFactor.set(ofRandom(0.0f, 1.0f));
}

void OrganicText::randomizeGlobalColorParams() {
	color1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}

void OrganicText::randomizeAnimationParams() {
	animationMode.set(static_cast<int>(ofRandom(0, 5)));
	animSpeed.set(ofRandom(0.1f, 3.0f));
	animPower.set(ofRandom(0.0f, 1.0f));
}

void OrganicText::randomizeConnectionParams() {
	connectDistance.set(ofRandom(5.0f, 100.0f));
	connectAlpha.set(ofRandom(0.0f, 255.0f));
	connectQuality.set(ofRandom(0.1f, 1.0f));
	bConnectNearOnly.set(ofRandom(1.0f) > 0.5f);
	bDrawConnections.set(ofRandom(1.0f) > 0.3f);
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
void OrganicText::loadPreset(int presetNumber) {
	ofLogNotice("OrganicText") << "Loading preset " << presetNumber;
	// Preset implementation will go in separate file
}
