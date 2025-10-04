#include "organicText.h"
#include "organicTextPresets.h"
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
	// Basic parameters - Simplified names
	bDebugDraw.set("Debug Draw", false);
	bDebugDrawInfo.set("Debug Draw Info", false);
	bDrawFill.set("Fill", true);
	bDrawShapes.set("Draw Shapes", true);
	bEnableAnimation.set("Animate", true);
	bDrawOutline.set("Draw Outline", false);
	zoomGlobal.set("Zoom", 0.0f, 0.0f, 1.0f); // 0=1x, 1=5x zoom
	sText.set("Text", ORGANICTEXT);

	// Density group - Simplified names, removed bEnableDensity
	resetDensity.set("Reset");
	randomDensity.set("Random");
	densityPointsSpacing.set("Spacing", 0.2, 0.05, 1);
	densityPoints.set("Density", 1.0, 0.1, 5.0);
	densityMinSpacing.set("Min Gap", 0.1, 0.01, 0.5);
	densityContourSampling.set("Sampling", 2.0, 0.5, 10.0);

	// Shape group - Simplified names, removed bEnableShape + add shape name
	resetShape.set("Reset");
	randomShape.set("Random");
	shapeType.set("Type", 0, 0, 5);
	shapeTypeName.set("Shape Name", "Circle"); // NEW: Shows current shape name
	shapeTypeName.setSerializable(false); // Don't save to settings
	shapePointRadius.set("Size", 0.5, 0, 1);
	shapePointsRadiusMin.set("Min Size", 0.3, 0, 1);
	shapeTriangleRatio.set("Ratio", 1.0, 0.5, 2.0);
	shapeRotation.set("Rotation", 0, 0, 360);

	// Color group - Remove "Color" prefix, removed bEnableColor + add mode name
	resetColor.set("Reset");
	randomColor.set("Random");
	colorMode.set("Mode", 3, 0, 4); // Default to COLOR_GLOBAL_MIX
	colorModeName.set("Mode Name", "Mix");
	colorModeName.setSerializable(false); // Don't save to settings
	colorSpeed.set("Speed", 1.0, 0.1, 5.0);
	colorMixFactor.set("Mix", 0.5, 0.0, 1.0);
	bColorByDistance.set("By Distance", false);

	// Colors group - Simplified, removed bEnableGlobalColor
	resetGlobalColors.set("Reset");
	randomGlobalColors.set("Random");
	color1.set("Color 1", ofColor::cyan);
	color2.set("Color 2", ofColor::magenta);
	color3.set("Color 3", ofColor::yellow);

	// NEW: Outline and connection colors
	colorOutline.set("Color Outline", ofColor::white);
	colorConnection.set("Color Connection", ofColor::white);

	// Animation group - Simplified, removed bEnableAnimationGroup + add mode name
	resetAnimation.set("Reset");
	randomAnimation.set("Random");
	animationMode.set("Mode", 0, 0, 4);
	animationModeName.set("Mode Name", "Noise");
	animationModeName.setSerializable(false); // Don't save to settings
	animSpeed.set("Speed", 1.0, 0.1, 3.0);
	animPower.set("Power", 0.1, 0.0, 1.0); // Normalized 0-1
	animWaveFrequency.set("Wave", 0.5, 0.0, 1.0); // Normalized 0-1
	animIntensity.set("Intensity", 0.2, 0.0, 1.0); // Normalized 0-1
	animSpiral.set("Spiral", 0.2, 0.0, 1.0); // Normalized 0-1
	animPulseIntensity.set("Pulse", 0.2, 0.0, 1.0); // Normalized 0-1

	// Connection group - Simplified names + performance optimization
	resetConnection.set("Reset");
	randomConnection.set("Random");
	bDrawConnections.set("Draw Connections", false);
	connectionsDistance.set("Distance", 30, 5, 100);
	connectionsAlpha.set("Alpha", 100, 0, 255);
	bConnectionOnlyNear.set("Near Only", true);
	connectionQuality.set("Quality", 1.0, 0.1, 1.0); // NEW: 1.0=full quality, 0.1=10% connections

	// Trail group (part of connection group) - Simplified names
	bDrawTrails.set("Trails", false);
	trailLength.set("Length", 10, 3, 50);
	trailFade.set("Fade", 0.9, 0.5, 0.99);

	// Global reset
	resetAll.set("Reset All");

	// Organize parameters in groups
	densityGroup.setName("Density");
	densityGroup.add(densityPointsSpacing);
	densityGroup.add(densityPoints);
	densityGroup.add(densityMinSpacing);
	densityGroup.add(densityContourSampling);
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

	colorModesGroup.setName("Colors Modes");
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
	animGroup.add(animWaveFrequency);
	animGroup.add(animIntensity);
	animGroup.add(animSpiral);
	animGroup.add(animPulseIntensity);
	animGroup.add(randomAnimation);
	animGroup.add(resetAnimation);

	connectionGroup.setName("Connections");
	connectionGroup.add(bDrawConnections);
	connectionGroup.add(connectionsDistance);
	connectionGroup.add(connectionsAlpha);
	connectionGroup.add(connectionQuality);
	connectionGroup.add(bConnectionOnlyNear);
	connectionGroup.add(bDrawTrails);
	connectionGroup.add(trailLength);
	connectionGroup.add(trailFade);
	connectionGroup.add(resetConnection);
	connectionGroup.add(randomConnection);

	parameters.setName("OrganicText Enhanced");

	parameters.add(sText);
	parameters.add(zoomGlobal);
	parameters.add(bDrawOutline);
	parameters.add(bDrawShapes);
	parameters.add(bDrawConnections);
	parameters.add(bEnableAnimation);

	// Groups
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

	// Event listeners
	e_PointsSize = densityPointsSpacing.newListener([this](float & v) { refreshPointsString(); });
	e_PointsRadius = shapePointRadius.newListener([this](float & v) { refreshPointsString(); });
	e_sText = sText.newListener([this](string & s) { refreshPointsString(); });
	e_PointDensity = densityPoints.newListener([this](float & v) { refreshPointsString(); });
	e_ContourSampling = densityContourSampling.newListener([this](float & v) { refreshPointsString(); });

	// Mode name update listeners - NEW
	shapeType.addListener(this, &OrganicText::updateShapeTypeName);
	colorMode.addListener(this, &OrganicText::updateColorModeName);
	animationMode.addListener(this, &OrganicText::updateAnimationModeName);

	e_ResetDensity = resetDensity.newListener([this](void) { resetDensityParams(); });
	e_ResetShape = resetShape.newListener([this](void) { resetShapeParams(); });
	e_ResetColor = resetColor.newListener([this](void) { resetColorParams(); });
	e_ResetGlobalColor = resetGlobalColors.newListener([this](void) { resetGlobalColorParams(); });
	e_ResetAnimation = resetAnimation.newListener([this](void) { resetAnimationParams(); });
	e_ResetConnection = resetConnection.newListener([this](void) { resetConnectionParams(); });
	e_ResetAll = resetAll.newListener([this](void) { resetAllParams(); });

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

	//--

	// Setup GUI

	gui.setup(parameters);
	gui.getGroup(densityGroup.getName()).minimizeAll();
	gui.getGroup(shapeGroup.getName()).minimizeAll();
	gui.getGroup(colorModesGroup.getName()).minimizeAll();
	gui.getGroup(colorGlobalGroup.getName()).minimizeAll();
	gui.getGroup(animGroup.getName()).minimizeAll();
	gui.getGroup(connectionGroup.getName()).minimizeAll();
	gui.getGroup(colorGlobalGroup.getName()).minimizeAll();
	gui.minimizeAll();

	//--

	// Initialization

	t = 0.0;
	textCenter = vec2(0, 0);

	float sz = 150;
	font.load("NotoSansMono-Regular.ttf", sz, false, false, true);

	refreshPointsString();

	resetAllParams(); // set default app states here instead of above when setting up parameters

	// Initialize mode names - NEW
	int dummy = 0;
	updateShapeTypeName(dummy);
	updateColorModeName(dummy);
	updateAnimationModeName(dummy);

	// Load settings if they exist
	loadSettings();
}

//--------------------------------------------------------------
void OrganicText::update(ofEventArgs & args) {
	update();
}

//--------------------------------------------------------------
void OrganicText::update() {
	if (bEnableAnimation.get()) {
		t += 0.01f * animSpeed.get();
	}

	fps = ofGetFrameRate();
	frameTime = 1000.0f / std::max(fps, 0.1f); // Avoid division by zero
	string wt = ("FPS: " + ofToString(fps, 0) + "    Frame Time: " + ofToString(frameTime, 2) + " ms");
	ofSetWindowTitle(wt);
}

//--------------------------------------------------------------
vector<vec2> OrganicText::sampleStringPoints(const string & s, float ds) {
	vector<vec2> points;
	if (s.empty()) return points;

	// Get the paths from the font
	vector<ofPath> paths = font.getStringAsPoints(s, true, false);

	for (auto & path : paths) {
		// Get polylines from each path
		vector<ofPolyline> polylines = path.getOutline();

		for (auto & polyline : polylines) {
			if (polyline.size() == 0) continue;

			// Improved contour sampling
			float totalLength = polyline.getPerimeter();
			float samplingStep = ds / densityContourSampling.get(); // Use new contour sampling parameter
			int numSamples = static_cast<int>(totalLength / samplingStep);

			if (numSamples < 3) numSamples = 3; // Minimum samples

			// Sample points evenly along the perimeter
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
	// Always refresh points (removed bEnableDensity check)
	// Removed: if (!bEnableDensity.get()) check

	float baseSpacing = ofMap(densityPointsSpacing, 0, 1, 0.5, 10, true);
	float densityMultiplier = densityPoints.get();
	float finalSpacing = baseSpacing / densityMultiplier;
	finalSpacing = std::max(finalSpacing, densityMinSpacing.get());

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

	// Calculate text center for distance-based effects
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

	// Check if animation is enabled globally and for the group
	if (!bEnableAnimation.get() || !bEnableAnimation.get()) {
		return offset;
	}

	switch ((AnimMode)animationMode.get()) {
	case ANIM_NOISE:
		offset = vec2(ofSignedNoise(phase, 0.0), ofSignedNoise(phase, 0.233)) * (animPower.get() * 50.0f); // Scale 0-1 to 0-50
		break;

	case ANIM_WAVE: {
		float freq = animWaveFrequency.get() * 0.1f; // Scale 0-1 to 0-0.1
		float amp = animIntensity.get() * 100.0f; // Scale 0-1 to 0-100
		float wave = sin(pointsString[index].x * freq + t * animSpeed.get()) * amp;
		offset = vec2(0, wave);
		break;
	}

	case ANIM_SPIRAL: {
		float angle = atan2(pointsString[index].y - textCenter.y, pointsString[index].x - textCenter.x);
		float distance = glm::distance(pointsString[index], textCenter);
		float tightness = animSpiral.get() * 0.05f; // Scale 0-1 to 0-0.05
		float power = animPower.get() * 50.0f; // Scale 0-1 to 0-50
		float spiralOffset = sin(distance * tightness + t * animSpeed.get()) * power;
		offset = vec2(cos(angle) * spiralOffset, sin(angle) * spiralOffset);
		break;
	}

	case ANIM_PULSE: {
		float distance = glm::distance(pointsString[index], textCenter);
		float intensity = animPulseIntensity.get() * 50.0f; // Scale 0-1 to 0-50
		float pulse = sin(t * animSpeed.get() * 2) * intensity;
		vec2 direction = normalize(pointsString[index] - textCenter);
		offset = direction * pulse;
		break;
	}

	case ANIM_ORBIT: {
		float angle = atan2(pointsString[index].y - textCenter.y, pointsString[index].x - textCenter.x);
		angle += t * animSpeed.get() * 0.1;
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

	// Always calculate color (removed enable checks)
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
		// Mix between all 3 colors based on index and time
		float indexMix = static_cast<float>(index) / static_cast<float>(pointsString.size());
		float timeMix = (sin(t * colorSpeed.get()) + 1.0f) * 0.5f;
		float mixFactor = colorMixFactor.get();

		// Create a smooth blend between the three colors
		ofColor color1_ = color1.get();
		ofColor color2_ = color2.get();
		ofColor color3_ = color3.get();

		// First mix between color1 and color2 based on index
		ofColor color12 = color1_.lerp(color2, indexMix);
		// Then mix with color3 based on time and mix factor
		color = color12.lerp(color3, timeMix * mixFactor);
		break;
	}

	case COLOR_DISTANCE: {
		float distance = glm::distance(position, textCenter);
		float maxDist = 200.0f;
		float distanceFactor = ofMap(distance, 0, maxDist, 0, 1, true);

		// Mix between colors based on distance
		ofColor color1_ = color1.get();
		ofColor color2_ = color2.get();
		ofColor color3_ = color3.get();

		if (distanceFactor < 0.5f) {
			color = color1_.lerp(color2, distanceFactor * 2.0f);
		} else {
			color = color2_.lerp(color3, (distanceFactor - 0.5f) * 2.0f);
		}
		break;
	}
	}

	if (bColorByDistance) {
		float distance = glm::distance(position, textCenter);
		float alpha = ofMap(distance, 0, 200, 255, 50, true);
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
		ofDrawRectangle(-size / 2.0f, -size / 2.0f, size, size);
		break;

	case SHAPE_TRIANGLE: {
		float h = size * shapeTriangleRatio.get();
		ofDrawTriangle(0, -h / 2.0f, -size / 2.0f, h / 2.0f, size / 2.0f, h / 2.0f);
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
		if (bDrawFill.get())
			star.draw();
		else
			star.draw();
		break;
	}

	case SHAPE_CROSS: {
		float thickness = size * 0.2f;
		ofDrawRectangle(-thickness / 2.0f, -size / 2.0f, thickness, size);
		ofDrawRectangle(-size / 2.0f, -thickness / 2.0f, size, thickness);
		break;
	}

	case SHAPE_POINT: {
		// Just draw a simple point/small circle
		ofDrawCircle(0, 0, size * 0.3f);
		break;
	}
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void OrganicText::updateTrails() {
	if (!bDrawTrails || !true) return;

	for (size_t i = 0; i < pointsString.size() && i < pointTrails.size(); i++) {
		float phase = t + 0.123f * static_cast<float>(i);
		vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
		vec2 currentPos = pointsString[i] + offset;

		// Shift trail positions
		for (int j = static_cast<int>(pointTrails[i].size()) - 1; j > 0; j--) {
			pointTrails[i][j] = pointTrails[i][j - 1];
		}
		pointTrails[i][0] = currentPos;
	}
}

//--------------------------------------------------------------
void OrganicText::drawConnections() const {
	if (!bDrawConnections || !true || pointsString.size() < 2) return;

	// Use custom connection color instead of white
	ofSetColor(colorConnection.get(), connectionsAlpha.get());

	for (size_t i = 0; i < pointsString.size(); i++) {
		float phase1 = t + 0.123f * static_cast<float>(i);
		vec2 offset1 = getAnimatedOffset(static_cast<int>(i), phase1);
		vec2 pos1 = pointsString[i] + offset1;

		int maxConnections = bConnectionOnlyNear ? 3 : static_cast<int>(pointsString.size());
		int connections = 0;

		for (size_t j = i + 1; j < pointsString.size() && connections < maxConnections; j++) {
			float phase2 = t + 0.123f * static_cast<float>(j);
			vec2 offset2 = getAnimatedOffset(static_cast<int>(j), phase2);
			vec2 pos2 = pointsString[j] + offset2;

			float distance = glm::distance(pos1, pos2);
			if (distance < connectionsDistance.get()) {
				float alpha = ofMap(distance, 0, connectionsDistance.get(), connectionsAlpha.get(), 0);
				ofSetColor(colorConnection, alpha);
				ofDrawLine(pos1, pos2);
				connections++;
			}
		}
	}
}

//--------------------------------------------------------------
void OrganicText::drawDebug() const {
	//if (!bDebugDraw.get()) return;

	ofPushStyle();
	ofSetColor(ofColor::red);
	ofNoFill();
	ofSetLineWidth(1);

	// Draw center point
	ofDrawCircle(textCenter, 5);

	// Draw coordinate system
	ofDrawLine(textCenter - vec2(20, 0), textCenter + vec2(20, 0));
	ofDrawLine(textCenter - vec2(0, 20), textCenter + vec2(0, 20));

	// Draw original sample points
	ofSetColor(ofColor::yellow);
	for (const auto & point : pointsString) {
		ofDrawCircle(point, 2);
	}

	// Draw bounding box
	if (!pointsString.empty()) {
		vec2 minPoint = pointsString[0];
		vec2 maxPoint = pointsString[0];
		for (const auto & point : pointsString) {
			minPoint.x = std::min(minPoint.x, point.x);
			minPoint.y = std::min(minPoint.y, point.y);
			maxPoint.x = std::max(maxPoint.x, point.x);
			maxPoint.y = std::max(maxPoint.y, point.y);
		}
		ofSetColor(ofColor::green);
		ofDrawRectangle(minPoint.x, minPoint.y, maxPoint.x - minPoint.x, maxPoint.y - minPoint.y);
	}

	ofPopStyle();
}

//--------------------------------------------------------------
void OrganicText::drawDebugInfo() const {
	//if (!bDebugDrawInfo.get()) return;

	ofPushStyle();

	// === INTERNAL APP METRICS ===
	int pointCount = pointsString.size();

	// Trail system metrics
	int totalTrailPoints = 0;
	int activeTrails = 0;
	for (const auto & trail : pointTrails) {
		totalTrailPoints += trail.size();
		if (!trail.empty()) activeTrails++;
	}

	// Connection system metrics
	int activeConnections = 0;
	float connectionCost = 0.0f; // O(n²) computational cost indicator
	if (bDrawConnections.get() && true) {
		float maxDist = connectionsDistance.get();
		connectionCost = pointCount * pointCount; // Shows O(n²) nature

		// Count actual connections being drawn
		for (int i = 0; i < pointCount; i++) {
			for (int j = i + 1; j < pointCount; j++) {
				if (distance(pointsString[i], pointsString[j]) <= maxDist) {
					activeConnections++;
				}
			}
		}
	}

	// Memory usage estimation (rough)
	int estimatedMemoryKB = (pointCount * static_cast<int>(sizeof(vec2))) / 1024 + (totalTrailPoints * static_cast<int>(sizeof(vec2))) / 1024 + 100; // Base app memory

	// Performance status
	string perfStatus = "GOOD";
	if (fps < 30)
		perfStatus = "POOR";
	else if (fps < 45)
		perfStatus = "OK";

	// === BUILD INFO STRINGS ===
	vector<string> infoLines;
	infoLines.push_back("=== APP PERFORMANCE ===");
	infoLines.push_back("FPS: " + ofToString(fps, 0) + " (" + perfStatus + ")");
	infoLines.push_back("Frame Time: " + ofToString(frameTime, 0) + " ms");
	infoLines.push_back("");
	infoLines.push_back("=== RENDERING LOAD ===");
	infoLines.push_back("Text Points: " + ofToString(pointCount));
	infoLines.push_back("Trail Points: " + ofToString(totalTrailPoints));
	infoLines.push_back("Active Trails: " + ofToString(activeTrails));
	infoLines.push_back("Connections: " + ofToString(activeConnections));
	infoLines.push_back("Connection Cost: " + ofToString(connectionCost, 0));
	infoLines.push_back("");
	infoLines.push_back("=== SYSTEM STATUS ===");
	infoLines.push_back("Memory ~: " + ofToString(estimatedMemoryKB) + " KB");
	infoLines.push_back("Animation: " + string(bEnableAnimation.get() ? "ON" : "OFF"));
	infoLines.push_back("Zoom Level: " + ofToString(1.0f + (zoomGlobal.get() * ZOOM_MAX_X), 1) + "x");
	infoLines.push_back("Current Preset: " + sText.get());

	// === DRAW PERFORMANCE BOX ===
	float lineHeight = 14;
	float padding = 8;
	float boxWidth = 220;
	float boxHeight = infoLines.size() * lineHeight + (padding * 2);

	// Position at top-right, but leave space for GUI
	float boxX = ofGetWidth() - boxWidth - 10;
	float boxY = 10;

	// Black semi-transparent background
	ofSetColor(0, 0, 0, 180);
	ofFill();
	ofDrawRectangle(boxX, boxY, boxWidth, boxHeight);

	// White border
	ofSetColor(255, 255, 255, 255);
	ofNoFill();
	ofSetLineWidth(1);
	ofDrawRectangle(boxX, boxY, boxWidth, boxHeight);

	// Draw text lines
	ofSetColor(255, 255, 255, 255);
	for (size_t i = 0; i < infoLines.size(); i++) {
		float textX = boxX + padding;
		float textY = boxY + padding + (i + 1) * lineHeight;

		// Color code important metrics
		if (infoLines[i].find("FPS:") != string::npos) {
			if (fps < 30)
				ofSetColor(255, 100, 100); // Red for poor FPS
			else if (fps < 45)
				ofSetColor(255, 255, 100); // Yellow for ok FPS
			else
				ofSetColor(100, 255, 100); // Green for good FPS
		} else if (infoLines[i].find("Connection Cost:") != string::npos && connectionCost > 10000) {
			ofSetColor(255, 200, 100); // Orange for high computational cost
		} else {
			ofSetColor(255, 255, 255); // White for normal text
		}

		ofDrawBitmapString(infoLines[i], textX, textY);
	}

	ofPopStyle();
}

//--------------------------------------------------------------
void OrganicText::draw() {
	// Calculate zoom factor (0-1 maps to 1x-5x)
	float zoomFactor = 1.0f + (zoomGlobal.get() * ZOOM_MAX_X);

	ofPushMatrix();

	// Center the content and apply zoom
	float centerX = ofGetWidth() / 2.0f;
	float centerY = ofGetHeight() / 2.0f;
	ofTranslate(centerX, centerY);
	ofScale(zoomFactor, zoomFactor);

	// Move to text position (considering the zoom scaling)
	ofTranslate(-font.stringWidth(sText) / 2.0f, font.stringHeight(sText) / 2.0f);

	// Update trails
	updateTrails();

	// Draw connections
	drawConnections();

	// Draw trails
	if (bDrawTrails && true) {
		for (size_t i = 0; i < pointTrails.size(); i++) {
			for (size_t j = 1; j < pointTrails[i].size(); j++) {
				float alpha = pow(trailFade.get(), static_cast<float>(j)) * 255.0f;
				ofSetColor(255, alpha);
				ofDrawLine(pointTrails[i][j - 1], pointTrails[i][j]);
			}
		}
	}

	// Draw main points (only if shapes are enabled)
	if (bDrawShapes && true) {
		for (size_t i = 0; i < pointsString.size(); i++) {
			ofPushStyle();

			float phase = t + 0.123f * static_cast<float>(i);
			vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
			vec2 newPoint = pointsString[i] + offset;

			// Set color
			ofColor color = getPointColor(static_cast<int>(i), newPoint, phase);
			ofSetColor(color);

			if (bDrawFill.get())
				ofFill();
			else
				ofNoFill();

			// Varying size
			float rmin = ofMap(shapePointsRadiusMin, 0, 1, MIN_RADIUS, MAX_RADIUS, true);
			float r = ofMap(shapePointRadius, 0, 1, rmin, MAX_RADIUS, true);
			float pointSize = ofNoise(phase, 0.7232f) * r;

			// Rotation for shapes
			float rotation = shapeRotation.get() + (t * animSpeed.get() * 10.0f);

			// Draw shape
			drawShape(newPoint, pointSize, (ShapeType)shapeType.get(), rotation);

			if (bDebugDraw) {
				ofFill();
				ofSetColor(ofColor::red);
				ofDrawCircle(pointsString[i], 2 / zoomFactor); // Adjust debug circle size for zoom
			}

			ofPopStyle();
		}
	}

	//--

	// Show original text outline with custom color
	if (bDrawOutline) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(colorOutline.get()); // NEW: Use custom outline color
		ofSetLineWidth(1 / zoomFactor); // Adjust line width for zoom
		font.drawStringAsShapes(sText, 0, 0);
		ofPopStyle();
	}

	// Debug mode visualization
	if (bDebugDraw) {
		drawDebug();
	}

	ofPopMatrix();

	//--

	gui.draw();

	// Draw performance info box (outside transformations)
	if (bDebugDrawInfo) {
		drawDebugInfo();
	}
}

//--------------------------------------------------------------
void OrganicText::keyPressed(ofKeyEventArgs & eventArgs) {
	const int key = eventArgs.key;
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	// Shape controls
	if (key >= '0' && key <= '9') {
		// Load preset based on number key
		int presetNumber = key - '0';
		loadPreset(presetNumber);
	}

	// Preset controls (keys 1,2,3,4 with modifiers) - REMOVED, now use direct number keys
	// Shape controls with Shift modifier
	else if (key >= '1' && key <= '5' && mod_SHIFT) {
		shapeType.set(key - '1');
	}

	// Color mode controls (simplified)
	else if (key == 'c' || key == 'C') {
		int nextMode = (colorMode.get() + 1) % 5; // 5 color modes now
		colorMode.set(nextMode);
	}

	// Animation mode controls
	else if (key == 'a' || key == 'A') {
		int nextAnim = (animationMode.get() + 1) % 5;
		animationMode.set(nextAnim);
	}

	// Density controls
	else if (key == '+' || key == '=') {
		densityPoints.set(std::min(5.0f, densityPoints.get() + 0.2f));
	} else if (key == '-') {
		densityPoints.set(std::max(0.1f, densityPoints.get() - 0.2f));
	}

	// Speed controls
	else if (key == OF_KEY_UP) {
		animSpeed.set(std::min(3.0f, animSpeed.get() + 0.1f));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(std::max(0.1f, animSpeed.get() - 0.1f));
	}

	// Zoom controls
	else if (key == OF_KEY_LEFT) {
		zoomGlobal.set(std::max(0.0f, zoomGlobal.get() - 0.1f));
	} else if (key == OF_KEY_RIGHT) {
		zoomGlobal.set(std::min(1.0f, zoomGlobal.get() + 0.1f));
	}

	// Toggle features
	else if (key == 't' || key == 'T') {
		bDrawTrails.set(!bDrawTrails.get());
	} else if (key == 'l' || key == 'L') {
		bDrawConnections.set(!bDrawConnections.get());
	} else if (key == 'o' || key == 'O') {
		bDrawOutline.set(!bDrawOutline.get());
	} else if (key == 'f' || key == 'F') {
		bDrawFill.set(!bDrawFill.get());
	}

	// Debug modes
	else if (key == 'D') {
		bDebugDraw.set(!bDebugDraw.get());
	}else if ( key == 'd') {
		bDebugDrawInfo.set(!bDebugDrawInfo.get());
	}

	// Background color
	else if (key == 'b' || key == 'B') {
		static bool darkBg = true;
		darkBg = !darkBg;
		ofBackground(darkBg ? 0 : 255);
	}

	// Reset to defaults
	else if (key == 'r' || key == 'R') {
		t = 0;
		animSpeed.set(1.0f);
		densityPoints.set(1.0f);
		colorMode.set(1);
		animationMode.set(0);
	}

	// Save settings
	else if (key == 's' || key == 'S') {
		if (mod_CONTROL || mod_COMMAND) {
			saveSettings();
		}
	}

	// Load settings
	else if (key == 'l' || key == 'L') {
		if (mod_CONTROL || mod_COMMAND) {
			loadSettings();
		}
	}
}

//--------------------------------------------------------------
void OrganicText::saveSettings() {
	ofJson settings;
	ofSerialize(settings, parameters);
	ofSavePrettyJson(pathSettings, settings);
	ofLogNotice("OrganicText") << "Settings saved to " << pathSettings;
}

//--------------------------------------------------------------
void OrganicText::loadSettings() {
	ofFile file(pathSettings);
	if (file.exists()) {
		ofJson settings = ofLoadJson(pathSettings);
		ofDeserialize(settings, parameters);
		refreshPointsString(); // Update points after loading
		ofLogNotice("OrganicText") << "Settings loaded from " << pathSettings;
	} else {
		ofLogNotice("OrganicText") << "Settings file not found: " << pathSettings;
	}
}

//--

// All default settings must be settled here, instead of in setup() ofParamas init.

//--------------------------------------------------------------
void OrganicText::resetDensityParams() {
	densityPointsSpacing.set(0.2f);
	densityPoints.set(0.2f);
	densityMinSpacing.set(0.1f);
	densityContourSampling.set(2.0f);
	refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::resetShapeParams() {
	bDrawFill.set(false);
	shapePointRadius.set(0.f);
	shapePointsRadiusMin.set(0.2f);
	shapeType.set(0);
	shapeTriangleRatio.set(1.0f);
	shapeRotation.set(0.0f);
}

//--------------------------------------------------------------
void OrganicText::resetColorParams() {
	colorMode.set(0);
	colorSpeed.set(1.0f);
	colorMixFactor.set(0.5f);
	bColorByDistance.set(false);
}

//--------------------------------------------------------------
void OrganicText::resetGlobalColorParams() {
	color1.set(ofColor::orange);
	color2.set(ofColor::greenYellow);
	color3.set(ofColor::lightSkyBlue);
	colorConnection.set(ofColor::yellow);
	colorOutline.set(ofColor::black);
}

//--------------------------------------------------------------
void OrganicText::resetAnimationParams() {
	animationMode.set(0);
	animSpeed.set(1.0f);
	animPower.set(0.1f);
	animWaveFrequency.set(0.02f);
	animIntensity.set(0.1f);
	animSpiral.set(0.1f);
	animPulseIntensity.set(0.1f);
}

//--------------------------------------------------------------
void OrganicText::resetConnectionParams() {
	bDrawConnections.set(false);
	connectionsDistance.set(20.0f);
	connectionsAlpha.set(255.f);
	bConnectionOnlyNear.set(false);
	bDrawTrails.set(false);
	trailLength.set(10);
	trailFade.set(0.9f);
}

//--------------------------------------------------------------
void OrganicText::resetAllParams() {
	// Reset all groups
	resetDensityParams();
	resetShapeParams();
	resetColorParams();
	resetGlobalColorParams();
	resetAnimationParams();
	resetConnectionParams();

	// Reset basic parameters
	//bDebugDraw.set(false);
	//bDebugDrawInfo.set(false);
	bDrawOutline.set(false);
	bDrawShapes.set(true);
	bEnableAnimation.set(false);
	zoomGlobal.set(0.1f);

	// Removed all bEnable parameter settings (not needed)
	// Reset time
	t = 0.0f;
}

//--------------------------------------------------------------
void OrganicText::loadPreset(int presetNumber) {
	OrganicTextPresets::loadPreset(this, presetNumber);
}

//--------------------------------------------------------------
void OrganicText::randomizeDensityParams() {
	densityPointsSpacing.set(ofRandom(densityPointsSpacing.getMin(), densityPointsSpacing.getMax()));
	densityPoints.set(ofRandom(densityPoints.getMin(), densityPoints.getMax()));
	densityMinSpacing.set(ofRandom(densityMinSpacing.getMin(), densityMinSpacing.getMax()));
	densityContourSampling.set(ofRandom(densityContourSampling.getMin(), densityContourSampling.getMax()));
	refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::randomizeShapeParams() {
	shapePointRadius.set(ofRandom(shapePointRadius.getMin(), shapePointRadius.getMax()));
	shapePointsRadiusMin.set(ofRandom(shapePointsRadiusMin.getMin(), shapePointsRadiusMin.getMax()));
	shapeType.set(static_cast<int>(ofRandom(shapeType.getMin(), shapeType.getMax() + 1)));
	shapeTriangleRatio.set(ofRandom(shapeTriangleRatio.getMin(), shapeTriangleRatio.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeColorParams() {
	colorMode.set(static_cast<int>(ofRandom(colorMode.getMin(), colorMode.getMax() + 1)));
	colorSpeed.set(ofRandom(colorSpeed.getMin(), colorSpeed.getMax()));
	colorMixFactor.set(ofRandom(colorMixFactor.getMin(), colorMixFactor.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeGlobalColorParams() {
	color1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	color3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}

//--------------------------------------------------------------
void OrganicText::randomizeAnimationParams() {
	animationMode.set(static_cast<int>(ofRandom(animationMode.getMin(), animationMode.getMax() + 1)));
	animSpeed.set(ofRandom(animSpeed.getMin(), animSpeed.getMax()));
	animPower.set(ofRandom(animPower.getMin(), animPower.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeConnectionParams() {
	connectionsDistance.set(ofRandom(connectionsDistance.getMin(), connectionsDistance.getMax()));
	connectionsAlpha.set(ofRandom(connectionsAlpha.getMin(), connectionsAlpha.getMax()));
	connectionQuality.set(ofRandom(connectionQuality.getMin(), connectionQuality.getMax())); // NEW
	bConnectionOnlyNear.set(ofRandom(1.0f) > 0.5f);
	bDrawConnections.set(ofRandom(1.0f) > 0.3f);
}

//--------------------------------------------------------------
void OrganicText::updateShapeTypeName(int &) {
	switch (shapeType.get()) {
	case SHAPE_CIRCLE: shapeTypeName.set("Circle"); break;
	case SHAPE_RECTANGLE: shapeTypeName.set("Rectangle"); break;
	case SHAPE_TRIANGLE: shapeTypeName.set("Triangle"); break;
	case SHAPE_STAR: shapeTypeName.set("Star"); break;
	case SHAPE_CROSS: shapeTypeName.set("Cross"); break;
	case SHAPE_POINT: shapeTypeName.set("Point"); break;
	default: shapeTypeName.set("Unknown"); break;
	}
}

//--------------------------------------------------------------
void OrganicText::updateColorModeName(int &) {
	switch (colorMode.get()) {
	case COLOR_GLOBAL_1: colorModeName.set("Color 1"); break;
	case COLOR_GLOBAL_2: colorModeName.set("Color 2"); break;
	case COLOR_GLOBAL_3: colorModeName.set("Color 3"); break;
	case COLOR_GLOBAL_MIX: colorModeName.set("Mix"); break;
	case COLOR_DISTANCE: colorModeName.set("Distance"); break;
	default: colorModeName.set("Unknown"); break;
	}
}

//--------------------------------------------------------------
void OrganicText::updateAnimationModeName(int &) {
	switch (animationMode.get()) {
	case ANIM_NOISE: animationModeName.set("Noise"); break;
	case ANIM_WAVE: animationModeName.set("Wave"); break;
	case ANIM_SPIRAL: animationModeName.set("Spiral"); break;
	case ANIM_PULSE: animationModeName.set("Pulse"); break;
	case ANIM_ORBIT: animationModeName.set("Orbit"); break;
	default: animationModeName.set("Unknown"); break;
	}
}
