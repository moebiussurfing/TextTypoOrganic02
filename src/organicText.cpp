#include "organicText.h"
#include "organicTextPresets.h"
#include <algorithm>
#include <cmath>

//--------------------------------------------------------------
void OrganicText::setup() {
	ofBackground(0); // Changed to black for better color effects
	ofSetFrameRate(60);

	// Basic parameters
	bDebug.set("Debug", false);
	bDrawFill.set("Draw Fill", true);
	bEnablePlain.set("Enable Plain", false);
	bDrawOutline.set("Draw Outline", false);
	bDrawShapes.set("Draw Shapes", true); // Renamed from bEnableShapes
	bEnableAnimation.set("Enable Animation", true);
	sceneZoom.set("Scene Zoom", 0.0f, 0.0f, 1.0f); // 0=1x, 1=5x zoom
	sText.set("Text", ORGANICTEXT);

	// Density group
	bEnableDensity.set("Enable Density", true);
	resetDensity.set("Reset Density");
	randomDensity.set("Random Density");
	pointsSpacing.set("Spacing", 0.2, 0.05, 1);
	pointDensity.set("Point Density", 1.0, 0.1, 5.0);
	minSpacing.set("Min Spacing", 0.1, 0.01, 0.5);
	contourSampling.set("Contour Sampling", 2.0, 0.5, 10.0);

	// Shape group
	bEnableShape.set("Enable Shape", true);
	resetShape.set("Reset Shape");
	randomShape.set("Random Shape");
	pointRadius.set("Radius", 0.5, 0, 1);
	pointsRadiusMin.set("Radius Min", 0.3, 0, 1);
	shapeType.set("Shape", 0, 0, 5); // Updated max to include SHAPE_POINT
	triangleRatio.set("Triangle Ratio", 1.0, 0.5, 2.0);
	shapeRotation.set("Shape Rotation", 0, 0, 360);

	// Simplified color group (based on global colors only)
	bEnableColor.set("Enable Color", true);
	resetColor.set("Reset Color");
	randomColor.set("Random Color");
	colorMode.set("Color Mode", 3, 0, 4); // Default to COLOR_GLOBAL_MIX
	colorSpeed.set("Color Speed", 1.0, 0.1, 5.0);
	colorMixFactor.set("Color Mix Factor", 0.5, 0.0, 1.0);
	bColorByDistance.set("Color by Distance", false);

	// Global color group
	bEnableGlobalColor.set("Enable Global Color", true);
	resetGlobalColor.set("Reset Global Color");
	randomGlobalColor.set("Random Global Color");
	globalColor1.set("Global Color 1", ofColor::cyan);
	globalColor2.set("Global Color 2", ofColor::magenta);
	globalColor3.set("Global Color 3", ofColor::yellow);

	// Animation group
	bEnableAnimationGroup.set("Enable Animation Group", true);
	resetAnimation.set("Reset Animation");
	randomAnimation.set("Random Animation");
	animationMode.set("Animation Mode", 0, 0, 4);
	animSpeed.set("Animation Speed", 1.0, 0.1, 3.0);
	noiseSize.set("Noise Size", 5, 0, 50);
	waveFrequency.set("Wave Frequency", 0.02, 0.001, 0.1);
	waveAmplitude.set("Wave Amplitude", 20, 0, 100);
	spiralTightness.set("Spiral Tightness", 0.01, 0.001, 0.05);
	pulseIntensity.set("Pulse Intensity", 10, 0, 50);

	// Connection group
	bEnableConnection.set("Enable Connection", true);
	resetConnection.set("Reset Connection");
	randomConnection.set("Random Connection");
	bDrawConnections.set("Draw Connections", false);
	connectionDistance.set("Connection Distance", 30, 5, 100);
	connectionAlpha.set("Connection Alpha", 100, 0, 255);
	bOnlyNearConnections.set("Only Near Connections", true);

	// Trail group (part of connection group)
	bDrawTrails.set("Draw Trails", false);
	trailLength.set("Trail Length", 10, 3, 50);
	trailFade.set("Trail Fade", 0.9, 0.5, 0.99);

	// Global reset
	resetAll.set("Reset All");

	// Organize parameters in groups
	densityGroup.setName("Density");
	densityGroup.add(bEnableDensity);
	densityGroup.add(pointsSpacing);
	densityGroup.add(pointDensity);
	densityGroup.add(minSpacing);
	densityGroup.add(contourSampling);
	densityGroup.add(randomDensity);
	densityGroup.add(resetDensity);

	shapeGroup.setName("Shape");
	shapeGroup.add(bEnableShape);
	shapeGroup.add(shapeType);
	shapeGroup.add(pointRadius);
	shapeGroup.add(pointsRadiusMin);
	shapeGroup.add(triangleRatio);
	shapeGroup.add(shapeRotation);
	shapeGroup.add(randomShape);
	shapeGroup.add(resetShape);

	colorGroup.setName("Colors");
	colorGroup.add(bEnableColor);
	colorGroup.add(colorMode);
	colorGroup.add(colorSpeed);
	colorGroup.add(colorMixFactor);
	colorGroup.add(bColorByDistance);
	colorGroup.add(randomColor);
	colorGroup.add(resetColor);

	globalColorGroup.setName("Global Colors");
	globalColorGroup.add(bEnableGlobalColor);
	globalColorGroup.add(globalColor1);
	globalColorGroup.add(globalColor2);
	globalColorGroup.add(globalColor3);
	globalColorGroup.add(randomGlobalColor);
	globalColorGroup.add(resetGlobalColor);

	animGroup.setName("Animation");
	animGroup.add(bEnableAnimationGroup);
	animGroup.add(animationMode);
	animGroup.add(animSpeed);
	animGroup.add(noiseSize);
	animGroup.add(waveFrequency);
	animGroup.add(waveAmplitude);
	animGroup.add(spiralTightness);
	animGroup.add(pulseIntensity);
	animGroup.add(randomAnimation);
	animGroup.add(resetAnimation);

	connectionGroup.setName("Connections");
	connectionGroup.add(bEnableConnection);
	connectionGroup.add(bDrawConnections);
	connectionGroup.add(connectionDistance);
	connectionGroup.add(connectionAlpha);
	connectionGroup.add(bOnlyNearConnections);
	connectionGroup.add(bDrawTrails);
	connectionGroup.add(trailLength);
	connectionGroup.add(trailFade);
	connectionGroup.add(resetConnection);
	connectionGroup.add(randomConnection);

	parameters.setName("OrganicText Enhanced");

	parameters.add(sText);
	parameters.add(bDrawOutline);
	parameters.add(bDrawFill);
	parameters.add(bDrawShapes);
	parameters.add(sceneZoom);
	parameters.add(bDrawConnections);

	parameters.add(bEnableDensity);
	parameters.add(bEnableShape);
	parameters.add(bEnableColor);
	parameters.add(bEnableGlobalColor);
	parameters.add(bEnableAnimationGroup);
	parameters.add(bEnableAnimation);

	parameters.add(densityGroup);
	parameters.add(shapeGroup);
	parameters.add(colorGroup);
	parameters.add(globalColorGroup);
	parameters.add(animGroup);
	parameters.add(connectionGroup);
	parameters.add(bDebug);
	parameters.add(resetAll);

	// Event listeners
	e_PointsSize = pointsSpacing.newListener([this](float & v) { refreshPointsString(); });
	e_PointsRadius = pointRadius.newListener([this](float & v) { refreshPointsString(); });
	e_sText = sText.newListener([this](string & s) { refreshPointsString(); });
	e_PointDensity = pointDensity.newListener([this](float & v) { refreshPointsString(); });
	e_ContourSampling = contourSampling.newListener([this](float & v) { refreshPointsString(); });

	e_ResetDensity = resetDensity.newListener([this](void) { resetDensityParams(); });
	e_ResetShape = resetShape.newListener([this](void) { resetShapeParams(); });
	e_ResetColor = resetColor.newListener([this](void) { resetColorParams(); });
	e_ResetGlobalColor = resetGlobalColor.newListener([this](void) { resetGlobalColorParams(); });
	e_ResetAnimation = resetAnimation.newListener([this](void) { resetAnimationParams(); });
	e_ResetConnection = resetConnection.newListener([this](void) { resetConnectionParams(); });
	e_ResetAll = resetAll.newListener([this](void) { resetAllParams(); });

	e_RandomDensity = randomDensity.newListener([this](void) { randomizeDensityParams(); });
	e_RandomShape = randomShape.newListener([this](void) { randomizeShapeParams(); });
	e_RandomColor = randomColor.newListener([this](void) { randomizeColorParams(); });
	e_RandomGlobalColor = randomGlobalColor.newListener([this](void) { randomizeGlobalColorParams(); });
	e_RandomAnimation = randomAnimation.newListener([this](void) { randomizeAnimationParams(); });
	e_RandomConnection = randomConnection.newListener([this](void) { randomizeConnectionParams(); });

	// Auto-save on exit (removing window event that doesn't exist in OF 0.12.1)
	// e_WindowClosed = ofEvents().windowClosed.newListener([this](ofEventArgs & args) { saveSettings(); });

	gui.setup(parameters);
	gui.getGroup(densityGroup.getName()).minimizeAll();
	gui.getGroup(shapeGroup.getName()).minimizeAll();
	gui.getGroup(colorGroup.getName()).minimizeAll();
	gui.getGroup(globalColorGroup.getName()).minimizeAll();
	gui.getGroup(animGroup.getName()).minimizeAll();
	gui.getGroup(connectionGroup.getName()).minimizeAll();
	gui.getGroup(globalColorGroup.getName()).minimizeAll();
	gui.minimizeAll();

	t = 0.0;
	textCenter = vec2(0, 0);

	float sz = 150;
	font.load("NotoSansMono-Regular.ttf", sz, false, false, true);

	refreshPointsString();

	// Load settings if they exist
	loadSettings();
}

//--------------------------------------------------------------
vector<vec2> OrganicText::sampleStringPoints(const string& s, float ds) {
	vector<vec2> points;
	if (s.empty()) return points;
	
	// Get the paths from the font
	vector<ofPath> paths = font.getStringAsPoints(s, true, false);
	
	for (auto& path : paths) {
		// Get polylines from each path
		vector<ofPolyline> polylines = path.getOutline();
		
		for (auto& polyline : polylines) {
			if (polyline.size() == 0) continue;
			
			// Improved contour sampling
			float totalLength = polyline.getPerimeter();
			float samplingStep = ds / contourSampling.get(); // Use new contour sampling parameter
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
	// Only refresh if density is enabled
	if (!bEnableDensity.get()) {
		pointsString.clear();
		return;
	}
	
	float baseSpacing = ofMap(pointsSpacing, 0, 1, 0.5, 10, true);
	float densityMultiplier = pointDensity.get();
	float finalSpacing = baseSpacing / densityMultiplier;
	finalSpacing = std::max(finalSpacing, minSpacing.get());

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
	if (!bEnableAnimation.get() || !bEnableAnimationGroup.get()) {
		return offset;
	}

	switch ((AnimMode)animationMode.get()) {
	case ANIM_NOISE:
		offset = vec2(ofSignedNoise(phase, 0.0), ofSignedNoise(phase, 0.233)) * noiseSize.get();
		break;

	case ANIM_WAVE: {
		float wave = sin(pointsString[index].x * waveFrequency.get() + t * animSpeed.get()) * waveAmplitude.get();
		offset = vec2(0, wave);
		break;
	}

	case ANIM_SPIRAL: {
		float angle = atan2(pointsString[index].y - textCenter.y, pointsString[index].x - textCenter.x);
		float distance = glm::distance(pointsString[index], textCenter);
		float spiralOffset = sin(distance * spiralTightness.get() + t * animSpeed.get()) * noiseSize.get();
		offset = vec2(cos(angle) * spiralOffset, sin(angle) * spiralOffset);
		break;
	}

	case ANIM_PULSE: {
		float distance = glm::distance(pointsString[index], textCenter);
		float pulse = sin(t * animSpeed.get() * 2) * pulseIntensity.get();
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
	
	// Check if color is enabled
	if (!bEnableColor.get() && !bEnableGlobalColor.get()) {
		return color; // Return white if both color systems are disabled
	}

	switch ((ColorMode)colorMode.get()) {
	case COLOR_GLOBAL_1:
		color = globalColor1.get();
		break;

	case COLOR_GLOBAL_2:
		color = globalColor2.get();
		break;

	case COLOR_GLOBAL_3:
		color = globalColor3.get();
		break;

	case COLOR_GLOBAL_MIX: {
		// Mix between all 3 colors based on index and time
		float indexMix = static_cast<float>(index) / static_cast<float>(pointsString.size());
		float timeMix = (sin(t * colorSpeed.get()) + 1.0f) * 0.5f;
		float mixFactor = colorMixFactor.get();
		
		// Create a smooth blend between the three colors
		ofColor color1 = globalColor1.get();
		ofColor color2 = globalColor2.get();
		ofColor color3 = globalColor3.get();
		
		// First mix between color1 and color2 based on index
		ofColor color12 = color1.lerp(color2, indexMix);
		// Then mix with color3 based on time and mix factor
		color = color12.lerp(color3, timeMix * mixFactor);
		break;
	}

	case COLOR_DISTANCE: {
		float distance = glm::distance(position, textCenter);
		float maxDist = 200.0f;
		float distanceFactor = ofMap(distance, 0, maxDist, 0, 1, true);
		
		// Mix between colors based on distance
		ofColor color1 = globalColor1.get();
		ofColor color2 = globalColor2.get();
		ofColor color3 = globalColor3.get();
		
		if (distanceFactor < 0.5f) {
			color = color1.lerp(color2, distanceFactor * 2.0f);
		} else {
			color = color2.lerp(color3, (distanceFactor - 0.5f) * 2.0f);
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
		float h = size * triangleRatio.get();
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
	if (!bDrawTrails || !bEnableConnection.get()) return;

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
	if (!bDrawConnections || !bEnableConnection.get() || pointsString.size() < 2) return;

	ofSetColor(255, connectionAlpha.get());

	for (size_t i = 0; i < pointsString.size(); i++) {
		float phase1 = t + 0.123f * static_cast<float>(i);
		vec2 offset1 = getAnimatedOffset(static_cast<int>(i), phase1);
		vec2 pos1 = pointsString[i] + offset1;

		int maxConnections = bOnlyNearConnections ? 3 : static_cast<int>(pointsString.size());
		int connections = 0;

		for (size_t j = i + 1; j < pointsString.size() && connections < maxConnections; j++) {
			float phase2 = t + 0.123f * static_cast<float>(j);
			vec2 offset2 = getAnimatedOffset(static_cast<int>(j), phase2);
			vec2 pos2 = pointsString[j] + offset2;

			float distance = glm::distance(pos1, pos2);
			if (distance < connectionDistance.get()) {
				float alpha = ofMap(distance, 0, connectionDistance.get(), connectionAlpha.get(), 0);
				ofSetColor(255, alpha);
				ofDrawLine(pos1, pos2);
				connections++;
			}
		}
	}
}

//--------------------------------------------------------------
void OrganicText::drawDebugInfo() const {
	if (!bDebug.get()) return;
	
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
	for (const auto& point : pointsString) {
		ofDrawCircle(point, 2);
	}
	
	// Draw bounding box
	if (!pointsString.empty()) {
		vec2 minPoint = pointsString[0];
		vec2 maxPoint = pointsString[0];
		for (const auto& point : pointsString) {
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
void OrganicText::draw() {
	// Calculate zoom factor (0-1 maps to 1x-5x)
	float zoomFactor = 1.0f + (sceneZoom.get() * 4.0f);
	
	ofPushMatrix();
	
	// Center the content and apply zoom
	float centerX = ofGetWidth() / 2.0f;
	float centerY = ofGetHeight() / 2.0f;
	ofTranslate(centerX, centerY);
	ofScale(zoomFactor, zoomFactor);
	
	// Move to text position (considering the zoom scaling)
	ofTranslate(-font.stringWidth(sText) / 2.0f, font.stringHeight(sText) / 2.0f);

	// Show original text outline
	if (bDrawOutline) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(ofColor::darkGray);
		ofSetLineWidth(1 / zoomFactor); // Adjust line width for zoom
		font.drawStringAsShapes(sText, 0, 0);
		ofPopStyle();
	}

	// Debug mode visualization
	if (bDebug) {
		drawDebugInfo();
	}

	// Update trails
	updateTrails();

	// Draw connections
	drawConnections();

	// Draw trails
	if (bDrawTrails && bEnableConnection.get()) {
		for (size_t i = 0; i < pointTrails.size(); i++) {
			for (size_t j = 1; j < pointTrails[i].size(); j++) {
				float alpha = pow(trailFade.get(), static_cast<float>(j)) * 255.0f;
				ofSetColor(255, alpha);
				ofDrawLine(pointTrails[i][j - 1], pointTrails[i][j]);
			}
		}
	}

	// Draw main points (only if shapes are enabled)
	if (bDrawShapes && bEnableShape.get()) {
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
			float rmin = ofMap(pointsRadiusMin, 0, 1, MIN_RADIUS, MAX_RADIUS, true);
			float r = ofMap(pointRadius, 0, 1, rmin, MAX_RADIUS, true);
			float pointSize = ofNoise(phase, 0.7232f) * r;

			// Rotation for shapes
			float rotation = shapeRotation.get() + (t * animSpeed.get() * 10.0f);

			// Draw shape
			drawShape(newPoint, pointSize, (ShapeType)shapeType.get(), rotation);

			if (bDebug) {
				ofFill();
				ofSetColor(ofColor::red);
				ofDrawCircle(pointsString[i], 2 / zoomFactor); // Adjust debug circle size for zoom
			}

			ofPopStyle();
		}
	}

	ofPopMatrix();
	gui.draw();
}

//--------------------------------------------------------------
void OrganicText::update() {
	if (bEnableAnimation.get()) {
		t += 0.01f * animSpeed.get();
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
		pointDensity.set(std::min(5.0f, pointDensity.get() + 0.2f));
	} else if (key == '-') {
		pointDensity.set(std::max(0.1f, pointDensity.get() - 0.2f));
	}

	// Speed controls
	else if (key == OF_KEY_UP) {
		animSpeed.set(std::min(3.0f, animSpeed.get() + 0.1f));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(std::max(0.1f, animSpeed.get() - 0.1f));
	}

	// Zoom controls
	else if (key == OF_KEY_LEFT) {
		sceneZoom.set(std::max(0.0f, sceneZoom.get() - 0.1f));
	} else if (key == OF_KEY_RIGHT) {
		sceneZoom.set(std::min(1.0f, sceneZoom.get() + 0.1f));
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
		pointDensity.set(1.0f);
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

//--------------------------------------------------------------
void OrganicText::exit() {
	saveSettings();
}

//--------------------------------------------------------------
void OrganicText::resetDensityParams() {
	pointsSpacing.set(0.2f);
	pointDensity.set(1.0f);
	minSpacing.set(0.1f);
	contourSampling.set(2.0f);
	refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::resetShapeParams() {
	pointRadius.set(0.5f);
	pointsRadiusMin.set(0.3f);
	shapeType.set(0);
	triangleRatio.set(1.0f);
	shapeRotation.set(0.0f);
}

//--------------------------------------------------------------
void OrganicText::resetColorParams() {
	colorMode.set(3); // COLOR_GLOBAL_MIX
	colorSpeed.set(1.0f);
	colorMixFactor.set(0.5f);
	bColorByDistance.set(false);
}

//--------------------------------------------------------------
void OrganicText::resetGlobalColorParams() {
	globalColor1.set(ofColor::cyan);
	globalColor2.set(ofColor::magenta);
	globalColor3.set(ofColor::yellow);
}

//--------------------------------------------------------------
void OrganicText::resetAnimationParams() {
	animationMode.set(0);
	animSpeed.set(1.0f);
	noiseSize.set(5.0f);
	waveFrequency.set(0.02f);
	waveAmplitude.set(20.0f);
	spiralTightness.set(0.01f);
	pulseIntensity.set(10.0f);
}

//--------------------------------------------------------------
void OrganicText::resetConnectionParams() {
	bDrawConnections.set(false);
	connectionDistance.set(30.0f);
	connectionAlpha.set(100.0f);
	bOnlyNearConnections.set(true);
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
	bDebug.set(false);
	bDrawFill.set(true);
	bDrawOutline.set(false);
	bDrawShapes.set(true);
	bEnableAnimation.set(true);
	sceneZoom.set(0.0f);
	
	// Reset enable flags
	bEnableDensity.set(true);
	bEnableShape.set(true);
	bEnableColor.set(true);
	bEnableGlobalColor.set(true);
	bEnableAnimationGroup.set(true);
	bEnableConnection.set(true);
	
	// Reset time
	t = 0.0f;
}

//--------------------------------------------------------------
void OrganicText::loadPreset(int presetNumber) {
	OrganicTextPresets::loadPreset(this, presetNumber);
}

//--------------------------------------------------------------
void OrganicText::randomizeDensityParams() {
	pointsSpacing.set(ofRandom(pointsSpacing.getMin(), pointsSpacing.getMax()));
	pointDensity.set(ofRandom(pointDensity.getMin(), pointDensity.getMax()));
	minSpacing.set(ofRandom(minSpacing.getMin(), minSpacing.getMax()));
	contourSampling.set(ofRandom(contourSampling.getMin(), contourSampling.getMax()));
	refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::randomizeShapeParams() {
	pointRadius.set(ofRandom(pointRadius.getMin(), pointRadius.getMax()));
	pointsRadiusMin.set(ofRandom(pointsRadiusMin.getMin(), pointsRadiusMin.getMax()));
	shapeType.set(static_cast<int>(ofRandom(shapeType.getMin(), shapeType.getMax() + 1)));
	triangleRatio.set(ofRandom(triangleRatio.getMin(), triangleRatio.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeColorParams() {
	colorMode.set(static_cast<int>(ofRandom(colorMode.getMin(), colorMode.getMax() + 1)));
	colorSpeed.set(ofRandom(colorSpeed.getMin(), colorSpeed.getMax()));
	colorMixFactor.set(ofRandom(colorMixFactor.getMin(), colorMixFactor.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeGlobalColorParams() {
	globalColor1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	globalColor2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	globalColor3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}

//--------------------------------------------------------------
void OrganicText::randomizeAnimationParams() {
	animationMode.set(static_cast<int>(ofRandom(animationMode.getMin(), animationMode.getMax() + 1)));
	animSpeed.set(ofRandom(animSpeed.getMin(), animSpeed.getMax()));
	noiseSize.set(ofRandom(noiseSize.getMin(), noiseSize.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeConnectionParams() {
	connectionDistance.set(ofRandom(connectionDistance.getMin(), connectionDistance.getMax()));
	connectionAlpha.set(ofRandom(connectionAlpha.getMin(), connectionAlpha.getMax()));
	bOnlyNearConnections.set(ofRandom(1.0f) > 0.5f);
	bDrawConnections.set(ofRandom(1.0f) > 0.3f);
}
