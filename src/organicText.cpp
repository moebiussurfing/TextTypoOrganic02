#include "organicText.h"

//--------------------------------------------------------------
void OrganicText::setup() {
	ofBackground(0); // Changed to black for better color effects
	ofSetFrameRate(60);

	// Basic parameters
	bDebug.set("Debug", false);
	bFill.set("Fill", true);
	bPlain.set("Plain", false);
	bShowOutline.set("Show Outline", false);
	bDrawShapes.set("Draw Shapes", true);
	bEnableAnimation.set("Enable Animation", true);
	sText.set("Text", ORGANICTEXT);

	// Density group
	bEnableDensity.set("Enable Density", true);
	pointsSpacing.set("Spacing", 0.2, 0.05, 1);
	pointDensity.set("Point Density", 1.0, 0.1, 5.0);
	minSpacing.set("Min Spacing", 0.1, 0.01, 0.5);
	contourSampling.set("Contour Sampling", 2.0, 0.5, 10.0);

	// Shape group
	bEnableShape.set("Enable Shape", true);
	pointRadius.set("Radius", 0.5, 0, 1);
	pointsRadiusMin.set("Radius Min", 0.3, 0, 1);
	shapeType.set("Shape", 0, 0, 4);
	triangleRatio.set("Triangle Ratio", 1.0, 0.5, 2.0);
	shapeRotation.set("Shape Rotation", 0, 0, 360);

	// Color group
	bEnableColor.set("Enable Color", true);
	colorMode.set("Color Mode", 1, 0, 8);
	colorSpeed.set("Color Speed", 1.0, 0.1, 5.0);
	hueShift.set("Hue Shift", 0, 0, 360);
	saturation.set("Saturation", 255, 0, 255);
	brightness.set("Brightness", 255, 0, 255);
	bColorByDistance.set("Color by Distance", false);

	// Global color group
	bEnableGlobalColor.set("Enable Global Color", true);
	globalColor1.set("Global Color 1", ofColor::cyan);
	globalColor2.set("Global Color 2", ofColor::magenta);
	globalColor3.set("Global Color 3", ofColor::yellow);
	globalColorMix.set("Global Color Mix", 0.5, 0.0, 1.0);

	// Animation group
	bEnableAnimationGroup.set("Enable Animation Group", true);
	animationMode.set("Animation Mode", 0, 0, 4);
	animSpeed.set("Animation Speed", 1.0, 0.1, 3.0);
	noiseSize.set("Noise Size", 5, 0, 50);
	waveFrequency.set("Wave Frequency", 0.02, 0.001, 0.1);
	waveAmplitude.set("Wave Amplitude", 20, 0, 100);
	spiralTightness.set("Spiral Tightness", 0.01, 0.001, 0.05);
	pulseIntensity.set("Pulse Intensity", 10, 0, 50);

	// Connection group
	bEnableConnection.set("Enable Connection", true);
	bDrawConnections.set("Draw Connections", false);
	connectionDistance.set("Connection Distance", 30, 5, 100);
	connectionAlpha.set("Connection Alpha", 100, 0, 255);
	bOnlyNearConnections.set("Only Near Connections", true);

	// Trail group (part of connection group)
	bDrawTrails.set("Draw Trails", false);
	trailLength.set("Trail Length", 10, 3, 50);
	trailFade.set("Trail Fade", 0.9, 0.5, 0.99);

	// Organize parameters in groups
	densityGroup.setName("Density");
	densityGroup.add(bEnableDensity);
	densityGroup.add(pointsSpacing);
	densityGroup.add(pointDensity);
	densityGroup.add(minSpacing);
	densityGroup.add(contourSampling);
	densityGroup.add(resetDensity);
	densityGroup.add(randomDensity);

	shapeGroup.setName("Shape");
	shapeGroup.add(bEnableShape);
	shapeGroup.add(shapeType);
	shapeGroup.add(pointRadius);
	shapeGroup.add(pointsRadiusMin);
	shapeGroup.add(triangleRatio);
	shapeGroup.add(shapeRotation);
	shapeGroup.add(resetShape);
	shapeGroup.add(randomShape);

	colorGroup.setName("Colors");
	colorGroup.add(bEnableColor);
	colorGroup.add(colorMode);
	colorGroup.add(colorSpeed);
	colorGroup.add(hueShift);
	colorGroup.add(saturation);
	colorGroup.add(brightness);
	colorGroup.add(bColorByDistance);
	colorGroup.add(resetColor);
	colorGroup.add(randomColor);

	globalColorGroup.setName("Global Colors");
	globalColorGroup.add(bEnableGlobalColor);
	globalColorGroup.add(globalColor1);
	globalColorGroup.add(globalColor2);
	globalColorGroup.add(globalColor3);
	globalColorGroup.add(globalColorMix);
	globalColorGroup.add(resetGlobalColor);
	globalColorGroup.add(randomGlobalColor);

	animGroup.setName("Animation");
	animGroup.add(bEnableAnimationGroup);
	animGroup.add(animationMode);
	animGroup.add(animSpeed);
	animGroup.add(noiseSize);
	animGroup.add(waveFrequency);
	animGroup.add(waveAmplitude);
	animGroup.add(spiralTightness);
	animGroup.add(pulseIntensity);
	animGroup.add(resetAnimation);
	animGroup.add(randomAnimation);

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
	parameters.add(bDebug);
	parameters.add(bFill);
	parameters.add(bShowOutline);
	parameters.add(bDrawShapes);
	parameters.add(bEnableAnimation);
	parameters.add(densityGroup);
	parameters.add(shapeGroup);
	parameters.add(colorGroup);
	parameters.add(globalColorGroup);
	parameters.add(animGroup);
	parameters.add(connectionGroup);
	parameters.add(sText);
	parameters.add(resetAll);

	// Event listeners
	e_PointsSize = pointsSpacing.newListener([this](float & v) { refreshPointsString(); });
	e_PointsRadius = pointRadius.newListener([this](float & v) { refreshPointsString(); });
	e_sText = sText.newListener([this](string & s) { refreshPointsString(); });
	e_PointDensity = pointDensity.newListener([this](float & v) { refreshPointsString(); });
	
	// Add listener for contour sampling
	contourSampling.newListener([this](float & v) { refreshPointsString(); });

	// Reset and randomize listeners
	resetDensity.addListener(this, &OrganicText::resetDensityParams);
	resetShape.addListener(this, &OrganicText::resetShapeParams);
	resetColor.addListener(this, &OrganicText::resetColorParams);
	resetGlobalColor.addListener(this, &OrganicText::resetGlobalColorParams);
	resetAnimation.addListener(this, &OrganicText::resetAnimationParams);
	resetConnection.addListener(this, &OrganicText::resetConnectionParams);
	resetAll.addListener(this, &OrganicText::resetAllParams);

	randomDensity.addListener(this, &OrganicText::randomizeDensityParams);
	randomShape.addListener(this, &OrganicText::randomizeShapeParams);
	randomColor.addListener(this, &OrganicText::randomizeColorParams);
	randomGlobalColor.addListener(this, &OrganicText::randomizeGlobalColorParams);
	randomAnimation.addListener(this, &OrganicText::randomizeAnimationParams);
	randomConnection.addListener(this, &OrganicText::randomizeConnectionParams);

	// Auto-save on exit (removing window event that doesn't exist in OF 0.12.1)
	// e_WindowClosed = ofEvents().windowClosed.newListener([this](ofEventArgs & args) { saveSettings(); });

	gui.setup(parameters);

	t = 0.0;
	textCenter = vec2(0, 0);

	float sz = 150;
	font.load("NotoSansMono-Regular.ttf", sz, false, false, true);

	refreshPointsString();

	// Load settings if they exist
	loadSettings();
}

//--------------------------------------------------------------
vector<vec2> OrganicText::sampleStringPoints(const string& s, float ds) const {
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
	case COLOR_PLAIN:
		color = ofColor::white;
		break;

	case COLOR_RAINBOW: {
		float hue = fmod(hueShift.get() + (phase * colorSpeed.get() * 50), 360);
		color.setHsb(hue, saturation.get(), brightness.get());
		break;
	}

	case COLOR_GRADIENT: {
		float hue = ofMap(static_cast<float>(index), 0.0f, static_cast<float>(pointsString.size() - 1), 0.0f, 360.0f);
		hue = fmod(hue + hueShift.get(), 360.0f);
		color.setHsb(hue, saturation.get(), brightness.get());
		break;
	}

	case COLOR_NOISE: {
		float hue = ofNoise(phase * 0.5, t * colorSpeed.get() * 0.1) * 360;
		hue = fmod(hue + hueShift.get(), 360);
		color.setHsb(hue, saturation.get(), brightness.get());
		break;
	}

	case COLOR_DISTANCE: {
		float distance = glm::distance(position, textCenter);
		float maxDist = 200; // Approximate max distance
		float hue = ofMap(distance, 0, maxDist, 0, 360, true);
		hue = fmod(hue + hueShift.get(), 360);
		color.setHsb(hue, saturation.get(), brightness.get());
		break;
	}

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
		float mixFactor = globalColorMix.get();
		// Animate the mix factor with time for dynamic color mixing
		float animatedMix = (sin(t * colorSpeed.get()) + 1.0f) * 0.5f;
		mixFactor = ofLerp(mixFactor, animatedMix, 0.3f);
		
		// Mix between color1 and color2 based on index, then blend with color3
		float indexMix = static_cast<float>(index) / static_cast<float>(pointsString.size());
		ofColor color1 = globalColor1.get();
		ofColor color2 = globalColor2.get();
		ofColor color3 = globalColor3.get();
		ofColor color12 = color1.lerp(color2, indexMix);
		color = color12.lerp(color3, mixFactor);
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
			float angle = (static_cast<float>(i) * PI) / static_cast<float>(points);
			float radius = (i % 2 == 0) ? size : size * 0.4f;
			star.addVertex(cos(angle) * radius, sin(angle) * radius);
		}
		star.close();
		if (bFill)
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
void OrganicText::draw() {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 - font.stringWidth(sText) / 2,
		ofGetHeight() / 2 + font.stringHeight(sText) / 2);

	// Show original text outline
	if (bShowOutline) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(ofColor::darkGray);
		ofSetLineWidth(1);
		font.drawStringAsShapes(sText, 0, 0);
		ofPopStyle();
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

			if (bFill)
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
				ofDrawCircle(pointsString[i], 2);
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
	if (key >= '1' && key <= '5') {
		shapeType.set(key - '1');
	}

	// Color mode controls
	else if (key == 'c' || key == 'C') {
		int nextMode = (colorMode.get() + 1) % 9; // Updated to include global colors
		colorMode.set(nextMode);
	}

	// Animation mode controls
	else if (key == 'a' || key == 'A') {
		int nextAnim = (animationMode.get() + 1) % 5;
		animationMode.set(nextAnim);
	}

	// Density controls
	else if (key == '+' || key == '=') {
		pointDensity.set(min(5.0f, pointDensity.get() + 0.2f));
	} else if (key == '-') {
		pointDensity.set(std::max(0.1f, pointDensity.get() - 0.2f));
	}

	// Speed controls
	else if (key == OF_KEY_UP) {
		animSpeed.set(min(3.0f, animSpeed.get() + 0.1f));
	} else if (key == OF_KEY_DOWN) {
		animSpeed.set(std::max(0.1f, animSpeed.get() - 0.1f));
	}

	// Toggle features
	else if (key == 't' || key == 'T') {
		bDrawTrails.set(!bDrawTrails.get());
	} else if (key == 'l' || key == 'L') {
		bDrawConnections.set(!bDrawConnections.get());
	} else if (key == 'o' || key == 'O') {
		bShowOutline.set(!bShowOutline.get());
	} else if (key == 'f' || key == 'F') {
		bFill.set(!bFill.get());
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
	colorMode.set(1);
	colorSpeed.set(1.0f);
	hueShift.set(0.0f);
	saturation.set(255.0f);
	brightness.set(255.0f);
	bColorByDistance.set(false);
}

//--------------------------------------------------------------
void OrganicText::resetGlobalColorParams() {
	globalColor1.set(ofColor::cyan);
	globalColor2.set(ofColor::magenta);
	globalColor3.set(ofColor::yellow);
	globalColorMix.set(0.5f);
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
	bFill.set(true);
	bShowOutline.set(false);
	bDrawShapes.set(true);
	bEnableAnimation.set(true);
	
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
	shapeRotation.set(ofRandom(shapeRotation.getMin(), shapeRotation.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeColorParams() {
	colorMode.set(static_cast<int>(ofRandom(colorMode.getMin(), colorMode.getMax() + 1)));
	colorSpeed.set(ofRandom(colorSpeed.getMin(), colorSpeed.getMax()));
	hueShift.set(ofRandom(hueShift.getMin(), hueShift.getMax()));
	saturation.set(ofRandom(saturation.getMin(), saturation.getMax()));
	brightness.set(ofRandom(brightness.getMin(), brightness.getMax()));
	bColorByDistance.set(ofRandom(1.0f) > 0.5f);
}

//--------------------------------------------------------------
void OrganicText::randomizeGlobalColorParams() {
	globalColor1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	globalColor2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	globalColor3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	globalColorMix.set(ofRandom(globalColorMix.getMin(), globalColorMix.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeAnimationParams() {
	animationMode.set(static_cast<int>(ofRandom(animationMode.getMin(), animationMode.getMax() + 1)));
	animSpeed.set(ofRandom(animSpeed.getMin(), animSpeed.getMax()));
	noiseSize.set(ofRandom(noiseSize.getMin(), noiseSize.getMax()));
	waveFrequency.set(ofRandom(waveFrequency.getMin(), waveFrequency.getMax()));
	waveAmplitude.set(ofRandom(waveAmplitude.getMin(), waveAmplitude.getMax()));
	spiralTightness.set(ofRandom(spiralTightness.getMin(), spiralTightness.getMax()));
	pulseIntensity.set(ofRandom(pulseIntensity.getMin(), pulseIntensity.getMax()));
}

//--------------------------------------------------------------
void OrganicText::randomizeConnectionParams() {
	bDrawConnections.set(ofRandom(1.0f) > 0.5f);
	connectionDistance.set(ofRandom(connectionDistance.getMin(), connectionDistance.getMax()));
	connectionAlpha.set(ofRandom(connectionAlpha.getMin(), connectionAlpha.getMax()));
	bOnlyNearConnections.set(ofRandom(1.0f) > 0.5f);
	bDrawTrails.set(ofRandom(1.0f) > 0.5f);
	trailLength.set(static_cast<int>(ofRandom(trailLength.getMin(), trailLength.getMax() + 1)));
	trailFade.set(ofRandom(trailFade.getMin(), trailFade.getMax()));
}
