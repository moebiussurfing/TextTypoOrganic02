#pragma once

#include "ofMain.h"

// Forward declaration
class OrganicText;

class OrganicTextPresets {
public:
	// Main preset loading function
	static void loadPreset(OrganicText * ot, int presetNumber);

	// Individual preset functions (0-9)
	static void loadPreset0_Minimal(OrganicText * ot); // Minimal clean look
	static void loadPreset1_CyberWave(OrganicText * ot); // Cyberpunk aesthetic
	static void loadPreset2_OrganicFlow(OrganicText * ot); // Natural flowing
	static void loadPreset3_NeonPulse(OrganicText * ot); // High energy neon
	static void loadPreset4_CosmicDance(OrganicText * ot); // Ethereal space
	static void loadPreset5_RetroGrid(OrganicText * ot); // 80s retro style
	static void loadPreset6_BioLuminous(OrganicText * ot); // Bioluminescent organisms
	static void loadPreset7_QuantumField(OrganicText * ot); // Quantum particle field
	static void loadPreset8_TribalRitual(OrganicText * ot); // Tribal ceremonial
	static void loadPreset9_GalaxyStorm(OrganicText * ot); // Galaxy storm effect

	static void loadColorOnlyPreset_Sunset(OrganicText * ot);
	static void loadColorOnlyPreset_Ocean(OrganicText * ot);
	static void loadColorOnlyPreset_Forest(OrganicText * ot);
	static void loadAnimOnlyPreset_Chaos(OrganicText * ot);
	static void loadAnimOnlyPreset_Zen(OrganicText * ot);
	static void loadAnimOnlyPreset_Electric(OrganicText * ot);
	static void loadShapeOnlyPreset_Geometric(OrganicText * ot);
	static void loadShapeOnlyPreset_Organic(OrganicText * ot);
	static void loadShapeOnlyPreset_Minimal(OrganicText * ot);
};
