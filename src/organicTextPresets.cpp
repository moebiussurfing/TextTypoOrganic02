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
// PRESET 0: MINIMAL - Clean and simple
void OrganicTextPresets::loadPreset0_Minimal(OrganicText* ot) {
    // Minimal colors: Black, white, gray
    ot->color1.set(ofColor::white);
    ot->color2.set(ofColor::lightGray);
    ot->color3.set(ofColor::gray);
    ot->colorMode.set(0); // COLOR_GLOBAL_1
    ot->colorSpeed.set(0.5f);
    ot->colorMixFactor.set(0.2f);
    
    // Low density, clean
    ot->densityPoints.set(1.0f);
    ot->densityContourSampling.set(2.0f);
    ot->densityPointsSpacing.set(0.3f);
    
    // Simple circles
    ot->shapeType.set(0); // SHAPE_CIRCLE
    ot->shapePointRadius.set(0.4f);
    ot->shapePointsRadiusMin.set(0.2f);
    
    // No animation for clean look
    ot->animationMode.set(0); // ANIM_NOISE
    ot->animSpeed.set(0.3f);
    ot->animPower.set(2.0f);
    
    // No connections or trails
    ot->bDrawConnections.set(false);
    ot->bDrawTrails.set(false);
    
    // Enable all systems
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 1: CYBER WAVE - Futuristic cyberpunk aesthetic
void OrganicTextPresets::loadPreset1_CyberWave(OrganicText* ot) {
    // Colors: Electric blue, neon green, bright cyan
    ot->color1.set(ofColor(0, 255, 255));     // Cyan
    ot->color2.set(ofColor(0, 255, 100));     // Electric green
    ot->color3.set(ofColor(100, 150, 255));   // Electric blue
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(2.5f);
    ot->colorMixFactor.set(0.8f);
    
    // Dense particles with connections
    ot->densityPoints.set(3.0f);
    ot->densityContourSampling.set(7.0f);
    ot->densityPointsSpacing.set(0.15f);
    
    // Small circles with trails
    ot->shapeType.set(0); // SHAPE_CIRCLE
    ot->shapePointRadius.set(0.3f);
    ot->shapePointsRadiusMin.set(0.1f);
    
    // Wave animation
    ot->animationMode.set(1); // ANIM_WAVE
    ot->animSpeed.set(1.8f);
    ot->animWaveFrequency.set(0.05f);
    ot->animIntensity.set(15.0f);
    
    // Connections and trails
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(25.0f);
    ot->connectionsAlpha.set(80.0f);
    ot->bDrawTrails.set(true);
    ot->trailLength.set(15);
    ot->trailFade.set(0.85f);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 2: ORGANIC FLOW - Natural, flowing organic movement
void OrganicTextPresets::loadPreset2_OrganicFlow(OrganicText* ot) {
    // Colors: Warm earth tones
    ot->color1.set(ofColor(255, 180, 100));   // Warm orange
    ot->color2.set(ofColor(180, 255, 120));   // Soft green
    ot->color3.set(ofColor(255, 200, 150));   // Warm beige
    ot->colorMode.set(4); // COLOR_DISTANCE
    ot->colorSpeed.set(0.8f);
    ot->colorMixFactor.set(0.6f);
    
    // Medium density
    ot->densityPoints.set(2.0f);
    ot->densityContourSampling.set(4.0f);
    ot->densityPointsSpacing.set(0.25f);
    
    // Varied circles
    ot->shapeType.set(0); // SHAPE_CIRCLE
    ot->shapePointRadius.set(0.7f);
    ot->shapePointsRadiusMin.set(0.4f);
    
    // Spiral animation
    ot->animationMode.set(2); // ANIM_SPIRAL
    ot->animSpeed.set(1.2f);
    ot->animSpiral.set(0.02f);
    ot->animPower.set(8.0f);
    
    // Subtle connections
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(40.0f);
    ot->connectionsAlpha.set(50.0f);
    ot->bDrawTrails.set(false);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 3: NEON PULSE - High energy pulsing neon
void OrganicTextPresets::loadPreset3_NeonPulse(OrganicText* ot) {
    // Colors: Hot neon colors
    ot->color1.set(ofColor(255, 0, 150));     // Hot pink
    ot->color2.set(ofColor(255, 255, 0));     // Bright yellow
    ot->color3.set(ofColor(150, 0, 255));     // Electric purple
    ot->colorMode.set(0); // COLOR_GLOBAL_1
    ot->colorSpeed.set(3.0f);
    ot->colorMixFactor.set(0.9f);
    
    // High density
    ot->densityPoints.set(4.0f);
    ot->densityContourSampling.set(8.0f);
    ot->densityPointsSpacing.set(0.1f);
    
    // Stars with rotation
    ot->shapeType.set(3); // SHAPE_STAR
    ot->shapePointRadius.set(0.4f);
    ot->shapePointsRadiusMin.set(0.2f);
    ot->shapeRotation.set(45.0f);
    
    // Pulse animation
    ot->animationMode.set(3); // ANIM_PULSE
    ot->animSpeed.set(2.5f);
    ot->animPulseIntensity.set(25.0f);
    
    // No connections, focus on shapes
    ot->bDrawConnections.set(false);
    ot->bDrawTrails.set(false);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 4: COSMIC DANCE - Ethereal space-like movement
void OrganicTextPresets::loadPreset4_CosmicDance(OrganicText* ot) {
    // Colors: Deep space colors
    ot->color1.set(ofColor(100, 150, 255));   // Deep blue
    ot->color2.set(ofColor(200, 100, 255));   // Purple
    ot->color3.set(ofColor(255, 200, 100));   // Warm gold
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(0.5f);
    ot->colorMixFactor.set(0.4f);
    ot->bColorByDistance.set(true);
    
    // Sparse but elegant
    ot->densityPoints.set(1.5f);
    ot->densityContourSampling.set(3.0f);
    ot->densityPointsSpacing.set(0.4f);
    
    // Mixed shapes
    ot->shapeType.set(2); // SHAPE_TRIANGLE
    ot->shapePointRadius.set(0.8f);
    ot->shapePointsRadiusMin.set(0.3f);
    ot->shapeTriangleRatio.set(1.5f);
    
    // Orbital animation
    ot->animationMode.set(4); // ANIM_ORBIT
    ot->animSpeed.set(0.6f);
    ot->animPower.set(12.0f);
    
    // Long distance connections with trails
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(60.0f);
    ot->connectionsAlpha.set(30.0f);
    ot->bConnectionOnlyNear.set(false);
    ot->bDrawTrails.set(true);
    ot->trailLength.set(25);
    ot->trailFade.set(0.95f);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 5: RETRO GRID - 80s retro synthwave style
void OrganicTextPresets::loadPreset5_RetroGrid(OrganicText* ot) {
    // Colors: Synthwave palette
    ot->color1.set(ofColor(255, 0, 128));     // Hot pink
    ot->color2.set(ofColor(0, 255, 255));     // Cyan
    ot->color3.set(ofColor(128, 0, 255));     // Purple
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(1.5f);
    ot->colorMixFactor.set(0.7f);
    
    // Grid-like density
    ot->densityPoints.set(2.5f);
    ot->densityContourSampling.set(5.0f);
    ot->densityPointsSpacing.set(0.2f);
    
    // Rectangles for grid feel
    ot->shapeType.set(1); // SHAPE_RECTANGLE
    ot->shapePointRadius.set(0.5f);
    ot->shapePointsRadiusMin.set(0.3f);
    ot->shapeRotation.set(0.0f);
    
    // Wave animation for retro feel
    ot->animationMode.set(1); // ANIM_WAVE
    ot->animSpeed.set(1.0f);
    ot->animWaveFrequency.set(0.03f);
    ot->animIntensity.set(10.0f);
    
    // Grid connections
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(35.0f);
    ot->connectionsAlpha.set(60.0f);
    ot->bConnectionOnlyNear.set(true);
    ot->bDrawTrails.set(false);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 6: BIOLUMINOUS - Bioluminescent organisms
void OrganicTextPresets::loadPreset6_BioLuminous(OrganicText* ot) {
    // Colors: Bioluminescent colors
    ot->color1.set(ofColor(0, 255, 150));     // Aqua green
    ot->color2.set(ofColor(100, 200, 255));   // Blue glow
    ot->color3.set(ofColor(200, 255, 100));   // Lime glow
    ot->colorMode.set(4); // COLOR_DISTANCE
    ot->colorSpeed.set(2.0f);
    ot->colorMixFactor.set(0.8f);
    ot->bColorByDistance.set(true);
    
    // Organic density
    ot->densityPoints.set(3.5f);
    ot->densityContourSampling.set(6.0f);
    ot->densityPointsSpacing.set(0.18f);
    
    // Small glowing circles
    ot->shapeType.set(0); // SHAPE_CIRCLE
    ot->shapePointRadius.set(0.35f);
    ot->shapePointsRadiusMin.set(0.15f);
    
    // Gentle noise for organic feel
    ot->animationMode.set(0); // ANIM_NOISE
    ot->animSpeed.set(0.8f);
    ot->animPower.set(6.0f);
    
    // Organic connections with trails
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(20.0f);
    ot->connectionsAlpha.set(40.0f);
    ot->bDrawTrails.set(true);
    ot->trailLength.set(20);
    ot->trailFade.set(0.9f);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 7: QUANTUM FIELD - Quantum particle field effect
void OrganicTextPresets::loadPreset7_QuantumField(OrganicText* ot) {
    // Colors: Quantum field colors
    ot->color1.set(ofColor(255, 255, 255));   // Pure white
    ot->color2.set(ofColor(150, 150, 255));   // Quantum blue
    ot->color3.set(ofColor(255, 150, 255));   // Quantum pink
    ot->colorMode.set(3); // COLOR_GLOBAL_MIX
    ot->colorSpeed.set(3.5f);
    ot->colorMixFactor.set(0.6f);
    
    // Very high density for particle field
    ot->densityPoints.set(5.0f);
    ot->densityContourSampling.set(9.0f);
    ot->densityPointsSpacing.set(0.08f);
    
    // Tiny points
    ot->shapeType.set(5); // SHAPE_POINT (new)
    ot->shapePointRadius.set(0.1f);
    ot->shapePointsRadiusMin.set(0.05f);
    
    // Chaotic noise for quantum uncertainty
    ot->animationMode.set(0); // ANIM_NOISE
    ot->animSpeed.set(3.0f);
    ot->animPower.set(15.0f);
    
    // Many short connections
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(15.0f);
    ot->connectionsAlpha.set(30.0f);
    ot->bConnectionOnlyNear.set(true);
    ot->bDrawTrails.set(false);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 8: TRIBAL RITUAL - Tribal ceremonial style
void OrganicTextPresets::loadPreset8_TribalRitual(OrganicText* ot) {
    // Colors: Earth and fire
    ot->color1.set(ofColor(255, 100, 0));     // Fire orange
    ot->color2.set(ofColor(200, 50, 0));      // Deep red
    ot->color3.set(ofColor(255, 200, 100));   // Golden yellow
    ot->colorMode.set(1); // COLOR_GLOBAL_2
    ot->colorSpeed.set(1.8f);
    ot->colorMixFactor.set(0.5f);
    
    // Ritual density
    ot->densityPoints.set(2.8f);
    ot->densityContourSampling.set(4.5f);
    ot->densityPointsSpacing.set(0.22f);
    
    // Crosses for tribal symbols
    ot->shapeType.set(4); // SHAPE_CROSS
    ot->shapePointRadius.set(0.6f);
    ot->shapePointsRadiusMin.set(0.4f);
    ot->shapeRotation.set(15.0f);
    
    // Pulsing like ritual drums
    ot->animationMode.set(3); // ANIM_PULSE
    ot->animSpeed.set(1.5f);
    ot->animPulseIntensity.set(12.0f);
    
    // Tribal connections
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(45.0f);
    ot->connectionsAlpha.set(70.0f);
    ot->bDrawTrails.set(false);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
}

//--------------------------------------------------------------
// PRESET 9: GALAXY STORM - Galaxy storm effect
void OrganicTextPresets::loadPreset9_GalaxyStorm(OrganicText* ot) {
    // Colors: Galaxy colors
    ot->color1.set(ofColor(100, 0, 200));     // Deep purple
    ot->color2.set(ofColor(255, 150, 0));     // Star gold
    ot->color3.set(ofColor(0, 100, 255));     // Nebula blue
    ot->colorMode.set(4); // COLOR_DISTANCE
    ot->colorSpeed.set(2.2f);
    ot->colorMixFactor.set(0.9f);
    ot->bColorByDistance.set(true);
    
    // Storm-like density
    ot->densityPoints.set(3.8f);
    ot->densityContourSampling.set(7.5f);
    ot->densityPointsSpacing.set(0.12f);
    
    // Stars for galaxy
    ot->shapeType.set(3); // SHAPE_STAR
    ot->shapePointRadius.set(0.5f);
    ot->shapePointsRadiusMin.set(0.2f);
    ot->shapeRotation.set(90.0f);
    
    // Orbital storm motion
    ot->animationMode.set(4); // ANIM_ORBIT
    ot->animSpeed.set(2.0f);
    ot->animPower.set(20.0f);
    
    // Storm connections with long trails
    ot->bDrawConnections.set(true);
    ot->connectionsDistance.set(50.0f);
    ot->connectionsAlpha.set(45.0f);
    ot->bConnectionOnlyNear.set(false);
    ot->bDrawTrails.set(true);
    ot->trailLength.set(30);
    ot->trailFade.set(0.92f);
    
    // Enable all
    ot->bDrawShapes.set(true);
    ot->bEnableAnimation.set(true);
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
