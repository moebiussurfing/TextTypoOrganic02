#pragma once
#include "ofMain.h"

#include "ofxSurfingPresetsLite.h"

//----

class SurfingPresetsLiteOfxGui : public SurfingPresetsLite {

public:
	ofxPanel gui;
	ofxPanel guiParams;
	SurfingOfxGuiPanelsManager guiManager;

	//----

public:
	void setupGui() override {
		ofLogNotice("SurfingPresetsLite") << "setupGui()";

		gui.setup(parameters);
		guiParams.setup(paramsPreset);

		guiManager.setup(&gui);
		guiManager.add(&gui, bGui);
		guiManager.add(&guiParams, bGuiParams);
		guiManager.startup();

		refreshGui();
	}
	
//	//TODO useful to collapse ui sub panels
//	ofxGuiGroup & getGroupGui(){
//		return guiManager.guis[2]->getGroup(paramsPreset.getName();
//	}
	
	//TODO: collapse all presets folders
	void refreshGui() override {
		ofLogNotice("SurfingPresetsLite") << "refreshGui()";

		gui.getGroup(paramsManager.getName()).minimize();
		gui.getGroup(paramsKit.getName()).minimize();
		gui.getGroup(paramsAdvanced.getName()).minimize();
		gui.getGroup(paramsAdvanced.getName()).getGroup(paramsInternal.getName()).minimize();
	}

	void drawGui() {
		if (!bGui) return;
		drawHelp();

		guiManager.draw();

		//ofxSurfing::setGuiPositionRightTo(guiParams,gui);
		//gui.draw();
		//if (bGuiParams) guiParams.draw();
	}

	void drawHelp() override {
		if (!bHelp) return;

		if (bGui && bGuiParams)
			ofxSurfing::ofDrawBitmapStringBox(sHelp, &guiParams);
		else if (bGui && !bGuiParams)
			ofxSurfing::ofDrawBitmapStringBox(sHelp, &gui);
	}
};
