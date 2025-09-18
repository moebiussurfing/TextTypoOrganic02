#include "organicText.h"
//--------------------------------------------------------------
OrganicText::OrganicText() {
	ofAddListener(ofEvents().update, this, &OrganicText::update);
	ofAddListener(ofEvents().keyPressed, this, &OrganicText::keyPressed);
}

//--------------------------------------------------------------
OrganicText::~OrganicText() {
	ofRemoveListener(ofEvents().update, this, &OrganicText::update);
	ofRemoveListener(ofEvents().keyPressed, this, &OrganicText::keyPressed);
}

//--------------------------------------------------------------
void OrganicText::setup() {
	ofBackground(255);
	ofSetFrameRate(60);

	bDebug.set("Debug", false);
	bFill.set("Fill", false);
	bPlain.set("Plain", true);
	noiseSize.set("Noise", 0, 0, 20);
	pointsSpacing.set("Spacing", 0.2, 0, 1);
	pointRadius.set("Radius", 0.5, 0, 1);
	pointsRadiusMin.set("Radius Min", 0.5, 0, 1);
	sText.set("Text", ORGANICTEXT);

	parameters.setName("OrganicText");
	parameters.add(bDebug);
	parameters.add(bFill);
	parameters.add(bPlain);
	parameters.add(noiseSize);
	parameters.add(pointsSpacing);
	parameters.add(pointsRadiusMin);
	parameters.add(pointRadius);
	parameters.add(sText);

	e_PointsSize = pointsSpacing.newListener([this](float & v) {
		refreshPointsString();
	});

	e_PointsRadius = pointRadius.newListener([this](float & v) {
		refreshPointsString();
	});

	e_sText = sText.newListener([this](string & s) {
		refreshPointsString();
	});

	gui.setup(parameters);

	t = 0.0;

	float sz = 150;
	font.load("NotoSansMono-Regular.ttf", sz, false, false, true);

	refreshPointsString();
}

//--------------------------------------------------------------
void OrganicText::refreshPointsString() {
	float sz = ofMap(pointsSpacing, 0, 1, 1, 10, true);
	pointsString = sampleStringPoints(sText, sz);
}

//--------------------------------------------------------------
void OrganicText::update(ofEventArgs & args) {
	update();
}

//--------------------------------------------------------------
void OrganicText::update() {
	t += 0.01;
}

//--------------------------------------------------------------
void OrganicText::draw() {
	ofPushMatrix();

	// Set origin so the text is centered
	ofTranslate(ofGetWidth() / 2 - font.stringWidth(sText) / 2, ofGetHeight() / 2 + font.stringHeight(sText) / 2);

	for (int i = 0; i < pointsString.size(); i++) {
		ofPushStyle();
		if (bFill)
			ofFill();
		else
			ofNoFill();

		// Shifted point
		float phase = t + 0.123 * i;

		vec2 offset = vec2(ofSignedNoise(phase, 0.0), ofSignedNoise(phase, 0.233))
			* noiseSize.get();

		vec2 newPoint = pointsString[i] + offset;

		// Interpolate color
		ofColor clr1 = ofColor(ofColor::black);
		ofColor clr2 = ofColor(ofColor::gray);
		ofColor c = clr1.lerp(clr2, ofNoise(phase, 123.232));
		if (bPlain) c = ofColor::black;
		ofSetColor(c);

		// Varying radius
		float rmin = ofMap(pointsRadiusMin, 0, 1, MIN_RADIUS, MAX_RADIUS, true);
		float r = ofMap(pointRadius, 0, 1, rmin, MAX_RADIUS, true);
		float pointSize = ofNoise(phase, 0.7232) * r;
		ofDrawCircle(newPoint, pointSize);

		if (bDebug) {
			ofFill();
			ofSetColor(ofColor::red);
			ofDrawCircle(pointsString[i], 1);
		}

		ofPopStyle();
	}
	ofPopMatrix();

	gui.draw();
}

//--------------------------------------------------------------
void OrganicText::keyPressed(ofKeyEventArgs & eventArgs) {
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << " : " << key;

	//--

	if (false) {
	}

	else if (key == 'G' && !mod_ALT) {
	}
}

//--------------------------------------------------------------
vector<vec2> OrganicText::sampleStringPoints(string s, float ds) {
	vector<ofPath> paths = font.getStringAsPoints(s, false, false);

	vector<vec2> points;
	// Iterate through all paths
	for (int i = 0; i < paths.size(); i++) {
		// A single ofPath can actually consist of multiple sub-paths (ofPolylines),
		// so iterate through these also
		vector<ofPolyline> polylines = paths[i].getOutline();
		for (const ofPolyline & poly : polylines) {
			// get total length of polygon
			float length = poly.getPerimeter();
			// step along the polygon and get points
			for (float s = 0.0; s < length; s += ds) {
				points.push_back(poly.getPointAtLength(s));
			}
		}
	}
	return points;
}

//--------------------------------------------------------------
void OrganicText::exit() {
}
