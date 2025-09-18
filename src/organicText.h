#pragma once

#include "ofMain.h"
#include "ofxGui.h"
using namespace glm;

#define ORGANICTEXT "ARB"
#define MAX_RADIUS 50
#define MIN_RADIUS 1

class OrganicText
{
public:

	OrganicText();
	~OrganicText();

	void setup();

	void update();
	void draw();
	void update(ofEventArgs & args);
	void keyPressed(ofKeyEventArgs &eventArgs);
	void exit();

	string pathSettings = "OrganicText.json";
	
	ofParameterGroup parameters;
	ofParameter<bool> bKeys;
	ofParameter<bool> bDebug;
	ofParameter<bool> bFill;
	ofParameter<bool> bPlain;
	ofParameter<float> noiseSize;
	ofParameter<float> pointsSpacing;
	ofParameter<float> pointRadius;
	ofParameter<float> pointsRadiusMin;
	ofParameter<string> sText;

	ofEventListener e_PointsRadius;
	ofEventListener e_PointsSize;
	ofEventListener e_sText;

	// Samples points along a text string with a distance "ds" between each consecutive point
	vector<vec2> sampleStringPoints(string s, float ds);

	vector<vec2> pointsString;
	ofTrueTypeFont font;
	float t;

	ofxPanel gui;

	void refreshPointsString();

private:

};

