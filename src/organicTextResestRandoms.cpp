#include "organicTextResestRandoms.h"
#include "organicText.h"

//--

//--------------------------------------------------------------
// RESET FUNCTIONS
//--------------------------------------------------------------

//--------------------------------------------------------------
void organicTextResestRandoms::resetPreset(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetPreset()";
	resetDensityParams(ot);
	resetShapeParams(ot);
	resetColorModes(ot);
	resetGlobalColorParams(ot);
	resetAnimationParams(ot);
	resetConnectionParams(ot);
}

//--------------------------------------------------------------
void organicTextResestRandoms::resetAll(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetAll()";

	resetPreset(ot);
	resetFonts(ot);

	ot->zoomGlobal.set(0.f);
	ot->bAutoZoomGlobal = true;

	ot->t = 0.0f;
}

//--------------------------------------------------------------
void organicTextResestRandoms::randomAll(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomAll()";
	randomizeDensityParams(ot);
	randomizeShapeParams(ot);
	randomizeColorModes(ot);
	randomizeGlobalColorParams(ot);
	randomizeAnimationParams(ot);
	randomizeConnectionParams(ot);
}

//--------------------------------------------------------------
void organicTextResestRandoms::resetFonts(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetFonts()";
	//ot->fontPath.set("NotoSansMono-Regular.ttf");
	ot->fontSize.set(150);
	ot->letterSpacing.set(0);
}

void organicTextResestRandoms::resetDensityParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetDensityParams()";
	ot->densitySpacing.set(0.2f);
}

void organicTextResestRandoms::resetShapeParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetShapeParams()";
	ot->bDrawShapes.set(true);
	ot->bDrawFill.set(true);
	ot->shapeSize.set(0.1f);
	ot->shapeSizeMin.set(0.f);
	ot->shapeType.set(0);
	ot->shapeRatio.set(.5f);
	ot->shapeRotation.set(0.0f);
}

void organicTextResestRandoms::resetColorModes(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetColorModes()";
	ot->colorMode.set(3);
	ot->colorSpeed.set(0.5f);
	ot->colorMixFactor.set(0.4f);
	ot->bColorByDistance.set(false);
}

void organicTextResestRandoms::resetGlobalColorParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetGlobalColorParams()";
	ot->color1.set(ofColor(120, 180, 255));
	ot->color2.set(ofColor(180, 140, 255));
	ot->color3.set(ofColor(140, 200, 240));
	ot->colorConnection.set(ofColor(150, 180, 255, 80));
	ot->colorOutline.set(ofColor(60, 60, 60));
}

void organicTextResestRandoms::resetAnimationParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetAnimationParams()";
	ot->animationMode.set(0);
	ot->animSpeed.set(0.8f);
	ot->animPower.set(0.05f);
	ot->animWaveFreq.set(0.3f);
	ot->animIntensity.set(0.2f);
	ot->animSpiral.set(0.2f);
	ot->animPulseIntensity.set(0.2f);
}

void organicTextResestRandoms::resetConnectionParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "resetConnectionParams()";
	ot->bDrawConnections.set(false);
	ot->connectDistance.set(30.0f);
	ot->connectLineWidth.set(1.5f);
	ot->connectAlpha.set(0.5f);
	ot->connectQuality.set(0.5f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);
	ot->trailLineWidth.set(1.5f);
	ot->trailLength.set(0.5);
	ot->trailFade.set(0.5f);
}

//--------------------------------------------------------------
// RANDOMIZE FUNCTIONS
//--------------------------------------------------------------

void organicTextResestRandoms::randomizeDensityParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeDensityParams()";
	ot->densitySpacing.set(ofRandom(ot->densitySpacing.getMin(), ot->densitySpacing.getMax()));
}

void organicTextResestRandoms::randomizeShapeParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeShapeParams()";
	ot->shapeSize.set(ofRandom(ot->shapeSize.getMin(), ot->shapeSize.getMax()));
	ot->shapeSizeMin.set(ofRandom(ot->shapeSizeMin.getMin(), ot->shapeSizeMin.getMax()));
	ot->shapeType.set(static_cast<int>(ofRandom(0, 6)));
	ot->shapeRatio.set(ofRandom(ot->shapeRatio.getMin(), ot->shapeRatio.getMax()));
	ot->shapeRotation.set(ofRandom(ot->shapeRotation.getMin(), ot->shapeRotation.getMax()));
}

void organicTextResestRandoms::randomizeColorModes(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeColorModes()";
	ot->colorMode.set(static_cast<int>(ofRandom(0, 5)));
	ot->colorSpeed.set(ofRandom(ot->colorSpeed.getMin(), ot->colorSpeed.getMax()));
	ot->colorMixFactor.set(ofRandom(ot->colorMixFactor.getMin(), ot->colorMixFactor.getMax()));
	ot->bColorByDistance.set(ofRandom(1.0f) > 0.5f);
}

void organicTextResestRandoms::randomizeGlobalColorParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeGlobalColorParams()";
	ot->color1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	ot->color2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	ot->color3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	ot->colorOutline.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	ot->colorConnection.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	ot->colorTrails.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}

void organicTextResestRandoms::randomizeAnimationParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeAnimationParams()";
	if (!ot->bEnableAnimation) ot->bEnableAnimation = true;
	ot->animationMode.set(static_cast<int>(ofRandom(0, 5)));
	ot->animSpeed.set(ofRandom(ot->animSpeed.getMin(), ot->animSpeed.getMax()));
	ot->animPower.set(ofRandom(ot->animPower.getMin(), ot->animPower.getMax()));
	ot->animWaveFreq.set(ofRandom(ot->animWaveFreq.getMin(), ot->animWaveFreq.getMax()));
	ot->animIntensity.set(ofRandom(ot->animIntensity.getMin(), ot->animIntensity.getMax()));
	ot->animSpiral.set(ofRandom(ot->animSpiral.getMin(), ot->animSpiral.getMax()));
	ot->animPulseIntensity.set(ofRandom(ot->animPulseIntensity.getMin(), ot->animPulseIntensity.getMax()));
}

void organicTextResestRandoms::randomizeConnectionParams(OrganicText * ot) {
	ofLogNotice("organicTextResestRandoms") << "randomizeConnectionParams()";
	ot->connectDistance.set(ofRandom(ot->connectDistance.getMin(), ot->connectDistance.getMax()));
	ot->connectAlpha.set(ofRandom(ot->connectAlpha.getMin(), ot->connectAlpha.getMax()));
	ot->connectQuality.set(ofRandom(ot->connectQuality.getMin(), ot->connectQuality.getMax()));
	ot->bDrawConnections.set(ofRandom(1.0f) > 0.3f);
	ot->bConnectNearOnly.set(ofRandom(1.0f) > 0.5f);
	ot->bDrawTrails.set(ofRandom(1.0f) > 0.3f);
	ot->trailLength.set(ofRandom(ot->trailLength.getMin(), ot->trailLength.getMax()));
	ot->trailLineWidth.set(ofRandom(ot->trailLineWidth.getMin(), ot->trailLineWidth.getMax()));
	ot->trailFade.set(ofRandom(ot->trailFade.getMin(), ot->trailFade.getMax()));
}
