#pragma once

#include "ofMain.h"

// Forward declaration
class OrganicText;

class organicTextResetsRandoms {

public:
	// Reset functions
	static void resetDensityParams(OrganicText * ot);
	static void resetShapeParams(OrganicText * ot);
	static void resetColorModes(OrganicText * ot);
	static void resetGlobalColorParams(OrganicText * ot);
	static void resetAnimationParams(OrganicText * ot);
	static void resetConnectionParams(OrganicText * ot);
	static void resetFonts(OrganicText * ot);
	static void resetAll(OrganicText * ot);
	static void resetPreset(OrganicText * ot);
	static void resetMouseTweaks(OrganicText * ot);
	static void randomAll(OrganicText * ot);

	// Randomize functions
	static void randomizeDensityParams(OrganicText * ot);
	static void randomizeShapeParams(OrganicText * ot);
	static void randomizeColorModes(OrganicText * ot);
	static void randomizeGlobalColorParams(OrganicText * ot);
	static void randomizeAnimationParams(OrganicText * ot);
	static void randomizeConnectionParams(OrganicText * ot);
};
