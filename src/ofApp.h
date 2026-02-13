#pragma once

#include <ofMain.h>

#include "organicTextScene.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void drawGui();
	void exit();
	void windowResized(int w, int h);
	void keyPressed(ofKeyEventArgs & eventArgs);
	void mousePressed(int x, int y, int button);
	void mouseMoved(int x, int y);

private:
	OrganicTextScene scene_;
};
