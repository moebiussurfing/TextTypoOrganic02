#include "organicTextPresets.h"
#include "organicText.h"

//--------------------------------------------------------------
// Main preset loading function
void OrganicTextPresets::loadPreset(OrganicText* ot, int presetNumber) {
    switch(presetNumber) {
        case 0: loadPreset0_Minimal(ot); break;
        case 1: loadPreset1_CyberWave(ot); break;
        case 2: loadPreset2_OrganicFlow(ot); break;
        case 3: loadPreset3_NeonPulse(ot); break;
        case 4: loadPreset4_CosmicDance(ot); break;
        case 5: loadPreset5_RetroGrid(ot); break;
        case 6: loadPreset6_BioLuminous(ot); break;
        case 7: loadPreset7_QuantumField(ot); break;
        case 8: loadPreset8_TribalRitual(ot); break;
        case 9: loadPreset9_GalaxyStorm(ot); break;
        default: loadPreset0_Minimal(ot); break; // Default to minimal
    }
}

//--------------------------------------------------------------
// PRESET 0: MINIMAL - Clean minimalist aesthetic
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset0_Minimal(OrganicText * ot) {
	ot->color1.set(ofColor::white);
	ot->color2.set(ofColor(200, 200, 200));
	ot->color3.set(ofColor(150, 150, 150));
	ot->colorMode.set(0);
	ot->colorSpeed.set(0.3f);
	ot->colorMixFactor.set(0.2f);

	ot->densitySpacing.set(0.35f);
	ot->densityAmount.set(0.5f);
	ot->densityMinGap.set(0.15f);

	ot->shapeType.set(0);
	ot->shapePointRadius.set(0.3f);
	ot->shapePointsRadiusMin.set(0.2f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(0);
	ot->animSpeed.set(0.5f);
	ot->animPower.set(0.05f);

	ot->bDrawConnections.set(false);
	ot->bDrawTrails.set(false);
	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(true);
}

//--------------------------------------------------------------
// PRESET 1: CYBER WAVE - Futuristic cyberpunk
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset1_CyberWave(OrganicText * ot) {
	ot->color1.set(ofColor(0, 255, 255));
	ot->color2.set(ofColor(0, 200, 255));
	ot->color3.set(ofColor(100, 150, 255));
	ot->colorMode.set(3);
	ot->colorSpeed.set(0.8f);
	ot->colorMixFactor.set(0.6f);

	ot->densitySpacing.set(0.2f);
	ot->densityAmount.set(1.2f);
	ot->densityMinGap.set(0.08f);

	ot->shapeType.set(5); // POINT
	ot->shapePointRadius.set(0.2f);
	ot->shapePointsRadiusMin.set(0.1f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(1); // WAVE
	ot->animSpeed.set(1.0f);
	ot->animWaveFreq.set(0.3f);
	ot->animIntensity.set(0.15f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(25.0f);
	ot->connectAlpha.set(100.0f);
	ot->connectQuality.set(0.5f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(true);
	ot->trailLength.set(8);
	ot->trailFade.set(0.85f);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);

	ot->colorConnection.set(ofColor(150, 200, 255, 80));
}

//--------------------------------------------------------------
// PRESET 2: ORGANIC FLOW - Natural flowing movement
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset2_OrganicFlow(OrganicText * ot) {
	ot->color1.set(ofColor(255, 180, 100));
	ot->color2.set(ofColor(180, 255, 120));
	ot->color3.set(ofColor(255, 200, 150));
	ot->colorMode.set(4); // DISTANCE
	ot->colorSpeed.set(0.5f);
	ot->colorMixFactor.set(0.5f);

	ot->densitySpacing.set(0.3f);
	ot->densityAmount.set(0.8f);
	ot->densityMinGap.set(0.12f);

	ot->shapeType.set(0); // CIRCLE
	ot->shapePointRadius.set(0.6f);
	ot->shapePointsRadiusMin.set(0.3f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(2); // SPIRAL
	ot->animSpeed.set(0.8f);
	ot->animSpiral.set(0.15f);
	ot->animPower.set(0.12f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(35.0f);
	ot->connectAlpha.set(60.0f);
	ot->connectQuality.set(0.4f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(true);
}

//--------------------------------------------------------------
// PRESET 3: NEON PULSE - High energy pulsing
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset3_NeonPulse(OrganicText * ot) {
	ot->color1.set(ofColor(255, 0, 150));
	ot->color2.set(ofColor(255, 255, 0));
	ot->color3.set(ofColor(150, 0, 255));
	ot->colorMode.set(3); // MIX
	ot->colorSpeed.set(1.5f);
	ot->colorMixFactor.set(0.8f);

	ot->densitySpacing.set(0.18f);
	ot->densityAmount.set(1.5f);
	ot->densityMinGap.set(0.05f);

	ot->shapeType.set(3); // STAR
	ot->shapePointRadius.set(0.35f);
	ot->shapePointsRadiusMin.set(0.2f);
	ot->shapeRotation.set(45.0f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(3); // PULSE
	ot->animSpeed.set(1.2f);
	ot->animPulseIntensity.set(0.25f);

	ot->bDrawConnections.set(false);
	ot->bDrawTrails.set(false);
	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// PRESET 4: COSMIC DANCE - Ethereal space movement
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset4_CosmicDance(OrganicText * ot) {
	ot->color1.set(ofColor(100, 150, 255));
	ot->color2.set(ofColor(200, 100, 255));
	ot->color3.set(ofColor(255, 200, 100));
	ot->colorMode.set(3);
	ot->colorSpeed.set(0.4f);
	ot->colorMixFactor.set(0.4f);
	ot->bColorByDistance.set(true);

	ot->densitySpacing.set(0.4f);
	ot->densityAmount.set(0.6f);
	ot->densityMinGap.set(0.15f);

	ot->shapeType.set(2); // TRIANGLE
	ot->shapePointRadius.set(0.5f);
	ot->shapePointsRadiusMin.set(0.3f);
	ot->shapeTriangleRatio.set(1.3f);
	ot->bDrawFill.set(false);

	ot->animationMode.set(4); // ORBIT
	ot->animSpeed.set(0.6f);
	ot->animPower.set(0.15f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(50.0f);
	ot->connectAlpha.set(40.0f);
	ot->connectQuality.set(0.3f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(true);
	ot->trailLength.set(15);
	ot->trailFade.set(0.92f);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// PRESET 5: RETRO GRID - 80s synthwave aesthetic
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset5_RetroGrid(OrganicText * ot) {
	ot->color1.set(ofColor(255, 0, 128));
	ot->color2.set(ofColor(0, 255, 255));
	ot->color3.set(ofColor(128, 0, 255));
	ot->colorMode.set(3);
	ot->colorSpeed.set(0.7f);
	ot->colorMixFactor.set(0.6f);

	ot->densitySpacing.set(0.25f);
	ot->densityAmount.set(1.0f);
	ot->densityMinGap.set(0.1f);

	ot->shapeType.set(1); // RECTANGLE
	ot->shapePointRadius.set(0.4f);
	ot->shapePointsRadiusMin.set(0.25f);
	ot->shapeRotation.set(0.0f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(1); // WAVE
	ot->animSpeed.set(0.8f);
	ot->animWaveFreq.set(0.2f);
	ot->animIntensity.set(0.1f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(30.0f);
	ot->connectAlpha.set(80.0f);
	ot->connectQuality.set(0.6f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(true);
}

//--------------------------------------------------------------
// PRESET 6: BIOLUMINOUS - Glowing organisms
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset6_BioLuminous(OrganicText * ot) {
	ot->color1.set(ofColor(0, 255, 150));
	ot->color2.set(ofColor(100, 200, 255));
	ot->color3.set(ofColor(200, 255, 100));
	ot->colorMode.set(4); // DISTANCE
	ot->colorSpeed.set(1.0f);
	ot->colorMixFactor.set(0.7f);
	ot->bColorByDistance.set(true);

	ot->densitySpacing.set(0.22f);
	ot->densityAmount.set(1.3f);
	ot->densityMinGap.set(0.08f);

	ot->shapeType.set(0);
	ot->shapePointRadius.set(0.3f);
	ot->shapePointsRadiusMin.set(0.15f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(0); // NOISE
	ot->animSpeed.set(0.7f);
	ot->animPower.set(0.08f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(22.0f);
	ot->connectAlpha.set(60.0f);
	ot->connectQuality.set(0.5f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(true);
	ot->trailLength.set(12);
	ot->trailFade.set(0.88f);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// PRESET 7: QUANTUM FIELD - Particle field effect
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset7_QuantumField(OrganicText * ot) {
	ot->color1.set(ofColor(255, 255, 255));
	ot->color2.set(ofColor(150, 150, 255));
	ot->color3.set(ofColor(255, 150, 255));
	ot->colorMode.set(3);
	ot->colorSpeed.set(1.8f);
	ot->colorMixFactor.set(0.6f);

	ot->densitySpacing.set(0.12f);
	ot->densityAmount.set(2.0f);
	ot->densityMinGap.set(0.05f);

	ot->shapeType.set(5); // POINT
	ot->shapePointRadius.set(0.15f);
	ot->shapePointsRadiusMin.set(0.08f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(0); // NOISE
	ot->animSpeed.set(1.5f);
	ot->animPower.set(0.18f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(18.0f);
	ot->connectAlpha.set(50.0f);
	ot->connectQuality.set(0.4f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// PRESET 8: TRIBAL RITUAL - Ceremonial style
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset8_TribalRitual(OrganicText * ot) {
	ot->color1.set(ofColor(255, 100, 0));
	ot->color2.set(ofColor(200, 50, 0));
	ot->color3.set(ofColor(255, 200, 100));
	ot->colorMode.set(1); // Single color 2
	ot->colorSpeed.set(0.9f);
	ot->colorMixFactor.set(0.5f);

	ot->densitySpacing.set(0.26f);
	ot->densityAmount.set(1.1f);
	ot->densityMinGap.set(0.1f);

	ot->shapeType.set(4); // CROSS
	ot->shapePointRadius.set(0.5f);
	ot->shapePointsRadiusMin.set(0.35f);
	ot->shapeRotation.set(15.0f);
	ot->bDrawFill.set(true);

	ot->animationMode.set(3); // PULSE
	ot->animSpeed.set(1.0f);
	ot->animPulseIntensity.set(0.15f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(40.0f);
	ot->connectAlpha.set(80.0f);
	ot->connectQuality.set(0.5f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// PRESET 9: GALAXY STORM - Space storm effect
//--------------------------------------------------------------
void OrganicTextPresets::loadPreset9_GalaxyStorm(OrganicText * ot) {
	ot->color1.set(ofColor(100, 0, 200));
	ot->color2.set(ofColor(255, 150, 0));
	ot->color3.set(ofColor(0, 100, 255));
	ot->colorMode.set(4); // DISTANCE
	ot->colorSpeed.set(1.1f);
	ot->colorMixFactor.set(0.8f);
	ot->bColorByDistance.set(true);

	ot->densitySpacing.set(0.16f);
	ot->densityAmount.set(1.6f);
	ot->densityMinGap.set(0.06f);

	ot->shapeType.set(3); // STAR
	ot->shapePointRadius.set(0.4f);
	ot->shapePointsRadiusMin.set(0.2f);
	ot->shapeRotation.set(90.0f);
	ot->bDrawFill.set(false);

	ot->animationMode.set(4); // ORBIT
	ot->animSpeed.set(1.3f);
	ot->animPower.set(0.22f);

	ot->bDrawConnections.set(true);
	ot->connectDistance.set(45.0f);
	ot->connectAlpha.set(60.0f);
	ot->connectQuality.set(0.35f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(true);
	ot->trailLength.set(18);
	ot->trailFade.set(0.9f);

	ot->bDrawShapes.set(true);
	ot->bEnableAnimation.set(true);
	ot->bDrawOutline.set(false);
}

//--------------------------------------------------------------
// COLOR ONLY PRESETS
//--------------------------------------------------------------

void OrganicTextPresets::loadColorOnlyPreset_Sunset(OrganicText* ot) {
    ot->color1.set(ofColor(255, 150, 100));   // Orange
    ot->color2.set(ofColor(255, 100, 150));   // Pink
    ot->color3.set(ofColor(255, 200, 100));   // Yellow
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(1.0f);
    ot->colorMixFactor.set(0.6f);
}

void OrganicTextPresets::loadColorOnlyPreset_Ocean(OrganicText* ot) {
    ot->color1.set(ofColor(0, 150, 255));     // Ocean blue
    ot->color2.set(ofColor(0, 255, 200));     // Turquoise
    ot->color3.set(ofColor(100, 200, 255));   // Light blue
    ot->colorMode.set(4); // COLOR_DISTANCE
    ot->colorSpeed.set(0.8f);
    ot->colorMixFactor.set(0.7f);
}

void OrganicTextPresets::loadColorOnlyPreset_Forest(OrganicText* ot) {
    ot->color1.set(ofColor(100, 200, 100));   // Forest green
    ot->color2.set(ofColor(150, 255, 150));   // Light green
    ot->color3.set(ofColor(200, 150, 100));   // Brown
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(0.6f);
    ot->colorMixFactor.set(0.4f);
}

//--------------------------------------------------------------
// ANIMATION ONLY PRESETS
//--------------------------------------------------------------

void OrganicTextPresets::loadAnimOnlyPreset_Chaos(OrganicText* ot) {
    ot->animationMode.set(0); // ANIM_NOISE
    ot->animSpeed.set(3.5f);
    ot->animPower.set(25.0f);
}

void OrganicTextPresets::loadAnimOnlyPreset_Zen(OrganicText* ot) {
    ot->animationMode.set(2); // ANIM_SPIRAL
    ot->animSpeed.set(0.3f);
    ot->animSpiral.set(0.005f);
    ot->animPower.set(3.0f);
}

void OrganicTextPresets::loadAnimOnlyPreset_Electric(OrganicText* ot) {
    ot->animationMode.set(3); // ANIM_PULSE
    ot->animSpeed.set(4.0f);
    ot->animPulseIntensity.set(30.0f);
}

//--------------------------------------------------------------
// SHAPE ONLY PRESETS
//--------------------------------------------------------------

void OrganicTextPresets::loadShapeOnlyPreset_Geometric(OrganicText* ot) {
    ot->shapeType.set(1); // SHAPE_RECTANGLE
    ot->shapePointRadius.set(0.6f);
    ot->shapePointsRadiusMin.set(0.4f);
    ot->shapeRotation.set(45.0f);
}

void OrganicTextPresets::loadShapeOnlyPreset_Organic(OrganicText* ot) {
    ot->shapeType.set(0); // SHAPE_CIRCLE
    ot->shapePointRadius.set(0.8f);
    ot->shapePointsRadiusMin.set(0.2f);
    ot->shapeRotation.set(0.0f);
}

void OrganicTextPresets::loadShapeOnlyPreset_Minimal(OrganicText* ot) {
    ot->shapeType.set(5); // SHAPE_POINT
    ot->shapePointRadius.set(0.2f);
    ot->shapePointsRadiusMin.set(0.1f);
    ot->shapeRotation.set(0.0f);
}
