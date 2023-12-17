#pragma once

#include "ofMain.h"
#include "organicText.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	OrganicText t;
};
