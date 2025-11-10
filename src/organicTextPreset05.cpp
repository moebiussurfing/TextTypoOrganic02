#include "organicTextPreset05.h"
#include "organicText.h"

//--------------------------------------------------------------
void organicTextPreset05::applyPreset05(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyPreset05()";
	
	applyDrawFlags(ot);
	applyAnimationParams(ot);
	applyColorModesParams(ot);
	applyColorParams(ot);
	applyConnectionsParams(ot);
	applyDensityParams(ot);
	applyShapeParams(ot);
	applyMouseTweaksParams(ot);
	applyTrailsParams(ot);
}

//--------------------------------------------------------------
void organicTextPreset05::applyDrawFlags(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyDrawFlags()";
	
	ot->bEnableAnimation.set(true);
	ot->bDrawConnections.set(true);
	ot->bDrawFill.set(true);
	ot->bDrawShapes.set(true);
	ot->bDrawTrails.set(true);
}

//--------------------------------------------------------------
void organicTextPreset05::applyAnimationParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyAnimationParams()";
	
	// Animation group values
	ot->bEnableAnimation.set(true);
	ot->animIntensity.set(0.897959f);
	ot->animationMode.set(3);
	ot->animOriginX.set(0.72449f);
	ot->animPower.set(1.0f);
	ot->animPulseIntensity.set(1.0f);
	ot->animSpeed.set(0.510204f);
	ot->animSpiral.set(0.239944f);
	ot->animWaveFreq.set(0.586735f);
}

//--------------------------------------------------------------
void organicTextPreset05::applyColorModesParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyColorModesParams()";
	
	ot->colorAlphaRange.set(0.5f);
	ot->bColorByDistance.set(true);
	ot->colorDistMiddle.set(0.729592f);
	ot->colorInner.set(0.306122f);
	ot->colorMixFactor.set(1.0f);
	ot->colorMode.set(3);
	ot->colorSpeed.set(2.5f);
}

//--------------------------------------------------------------
void organicTextPreset05::applyColorParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyColorParams()";
	
	// Color_1: "0, 1, 255, 255"
	ot->color1.set(ofColor(0, 1, 255, 255));
	
	// Color_2: "7, 71, 255, 255"
	ot->color2.set(ofColor(7, 71, 255, 255));
	
	// Color_3: "14, 0, 255, 162"
	ot->color3.set(ofColor(14, 0, 255, 162));
	
	// Color_Connections: "255, 255, 255, 255"
	ot->colorConnection.set(ofColor(255, 255, 255, 255));
	
	// Color_Trails: "255, 0, 111, 255"
	ot->colorTrails.set(ofColor(255, 0, 111, 255));
}

//--------------------------------------------------------------
void organicTextPreset05::applyConnectionsParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyConnectionsParams()";
	
	ot->connectAlpha.set(0.688776f);
	ot->connectDistance.set(68.4949f);
	ot->bDrawConnections.set(true);
	ot->connectLineWidth.set(1.0f);
	ot->bConnectNearOnly.set(true);
	ot->connectQuality.set(0.494898f);
}

//--------------------------------------------------------------
void organicTextPreset05::applyDensityParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyDensityParams()";
	
	ot->densitySpacing.set(0.195408f);
}

//--------------------------------------------------------------
void organicTextPreset05::applyShapeParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyShapeParams()";
	
	ot->bDrawFill.set(true);
	ot->shapeSizeMin.set(0.102041f);
	ot->shapeRatio.set(0.266672f);
	ot->shapeRotation.set(0.54717f);
	ot->shapeSize.set(0.295937f);
	ot->shapeType.set(0);
	// Note: "Back" parameter not found in OrganicText class
}

//--------------------------------------------------------------
void organicTextPreset05::applyMouseTweaksParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyMouseTweaksParams()";
	
	// Color: "255, 0, 104, 255"
	ot->colorMouseHighlight.set(ofColor(255, 0, 104, 255));
	
	ot->mouseDisplacePower.set(0.352041f);
	ot->bMouseDisplacePoints.set(true);
	ot->bMouseHighlightPoints.set(true);
	ot->mouseInfluenceStrength.set(0.663265f);
	ot->mouseScalePower.set(0.596939f);
	ot->bMouseScaleShapes.set(true);
	ot->radiusMouse.set(0.755102f);
	ot->bMouseControlOrigin.set(true);
}

//--------------------------------------------------------------
void organicTextPreset05::applyTrailsParams(OrganicText * ot) {
	ofLogNotice("organicTextPreset05") << "applyTrailsParams()";
	
	ot->bDrawTrails.set(true);
	ot->trailFade.set(0.397959f);
	ot->trailLength.set(0.69898f);
	ot->trailLineWidth.set(0.1f);
}
