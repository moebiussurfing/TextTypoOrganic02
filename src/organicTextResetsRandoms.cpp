#include "organicTextResetsRandoms.h"
#include "organicText.h"

//--

//--------------------------------------------------------------
// RESET FUNCTIONS
//--------------------------------------------------------------

//--------------------------------------------------------------
void organicTextResetsRandoms::resetPreset(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetPreset()";
	
	resetShapeParams(ot);
	resetDensityParams(ot);
	resetColorModes(ot);
	resetGlobalColorParams(ot);
	resetAnimationParams(ot);
	resetConnectionParams(ot);
	resetMouseTweaks(ot);
	resetLineTweaks(ot);
}

//--------------------------------------------------------------
void organicTextResetsRandoms::resetAll(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetAll()";

	// Preset
	resetPreset(ot);
	resetFonts(ot);

	// Session
	ot->zoomGlobal.set(0.f);
	ot->bAutoZoomGlobal = true;
	ot->colorOutline.set(ofColor::black);

	ot->t = 0.0f;
}

//--------------------------------------------------------------
void organicTextResetsRandoms::randomPreset(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomPreset()";
	
	randomizeDensityParams(ot);
	randomizeShapeParams(ot);
	randomizeColorModes(ot);
	randomizeGlobalColorParams(ot);
	randomizeAnimationParams(ot);
	randomizeConnectionParams(ot);
}

//--------------------------------------------------------------
void organicTextResetsRandoms::resetFonts(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetFonts()";
	
	//ot->fontPath.set("NotoSansMono-Regular.ttf");
	ot->fontSize.set(150);
	ot->letterSpacing.set(0.0f);
}

void organicTextResetsRandoms::resetDensityParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetDensityParams()";
	
	ot->densitySpacing.set(0.2f);
}

void organicTextResetsRandoms::resetShapeParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetShapeParams()";
	
	ot->bDrawShapes.set(true);
	ot->bDrawFill.set(true);
	ot->bShapeBack.set(false);
	ot->shapeSize.set(0.5f);
	ot->shapeSizeMin.set(0.3f);
	ot->shapeType.set(0);
	ot->shapeRatio.set(.5f);
	ot->shapeRotation.set(0.0f);
}

void organicTextResetsRandoms::resetColorModes(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetColorModes()";
	
	ot->colorMode.set(3);
	ot->colorSpeed.set(1.0f);
	ot->colorMixFactor.set(0.5f);
	ot->bColorByDistance.set(false);
	ot->colorInner.set(0.4f);
	ot->colorDistMiddle.set(0.7f);
	ot->colorAlphaRange.set(0.7f);
}

void organicTextResetsRandoms::resetGlobalColorParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetGlobalColorParams()";
	
	ot->color1.set(ofColor::cyan);
	ot->color2.set(ofColor::magenta);
	ot->color3.set(ofColor::yellow);
	ot->colorConnection.set(ofColor::white);
	ot->colorTrails.set(ofColor::black);
}

void organicTextResetsRandoms::resetAnimationParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetAnimationParams()";
	
	ot->bEnableAnimation.set(true);
	ot->animationMode.set(0);
	ot->animSpeed.set(0.2f);
	ot->animPower.set(0.1f);
	ot->animWaveFreq.set(0.3f);
	ot->animIntensity.set(0.2f);
	ot->animSpiral.set(0.2f);
	ot->animPulseIntensity.set(0.2f);
	ot->animOriginX.set(0.5f);
}

void organicTextResetsRandoms::resetConnectionParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetConnectionParams()";
	
	ot->bDrawConnections.set(false);
	ot->connectDistance.set(30.0f);
	ot->connectLineWidth.set(1.0f);
	ot->connectAlpha.set(0.5f);
	ot->connectQuality.set(1.0f);
	ot->bConnectNearOnly.set(true);
	ot->bDrawTrails.set(false);
	ot->trailLineWidth.set(1.0f);
	ot->trailLength.set(0.5);
	ot->trailFade.set(0.5f);
}

void organicTextResetsRandoms::resetMouseTweaks(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetMouseTweaks()";
	
	ot->bMouseTweaks.set(true);
	ot->bMouseControlOrigin.set(false);
	ot->radiusMouse.set(0.1f);
	ot->bMouseHighlightPoints.set(false);
	ot->colorMouseHighlight.set(ofColor(0, 150, 255));
	ot->mouseInfluenceStrength.set(0.5f);
	ot->bMouseDisplacePoints.set(false);
	ot->mouseDisplacePower.set(0.5f); // 0.5 = neutral (no displacement)
	ot->bMouseScaleShapes.set(false);
	ot->mouseScalePower.set(0.5f);
}

void organicTextResetsRandoms::resetLineTweaks(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetLineTweaks()";

	ot->bLineTweaks.set(true);
	ot->radiusLineMouse.set(0.1f);
	ot->vLineFrom.set(glm::vec2(-1.0f, 0.0f));
	ot->vLineTo.set(glm::vec2(1.0f, 0.0f));
	ot->lineTweaksDuration.set(5.0f);
}

void organicTextResetsRandoms::resetBg(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "resetBg()";

	ot->bBgGradient.set(false);
	ot->bgColor1.set(ofColor(10));
	ot->bgColor1.set(ofColor(40));
}

//--------------------------------------------------------------
// RANDOMIZE FUNCTIONS
//--------------------------------------------------------------

void organicTextResetsRandoms::randomizeDensityParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeDensityParams()";
	
	ot->densitySpacing.set(ofRandom(ot->densitySpacing.getMin(), ot->densitySpacing.getMax()));
}

void organicTextResetsRandoms::randomizeShapeParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeShapeParams()";
	
	ot->shapeSize.set(ofRandom(ot->shapeSize.getMin(), ot->shapeSize.getMax()));
	ot->shapeSizeMin.set(ofRandom(ot->shapeSizeMin.getMin(), ot->shapeSizeMin.getMax()));
	ot->shapeType.set(static_cast<int>(ofRandom(0, 6)));
	ot->shapeRatio.set(ofRandom(ot->shapeRatio.getMin(), ot->shapeRatio.getMax()));
	ot->shapeRotation.set(ofRandom(ot->shapeRotation.getMin(), ot->shapeRotation.getMax()));
}

void organicTextResetsRandoms::randomizeColorModes(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeColorModes()";
	
	ot->colorMode.set(static_cast<int>(ofRandom(0, 5)));
	ot->colorSpeed.set(ofRandom(ot->colorSpeed.getMin(), ot->colorSpeed.getMax()));
	ot->colorMixFactor.set(ofRandom(ot->colorMixFactor.getMin(), ot->colorMixFactor.getMax()));
	ot->bColorByDistance.set(ofRandom(1.0f) > 0.5f);
	ot->colorInner.set(ofRandom(ot->colorInner.getMin(), ot->colorInner.getMax()));
	ot->colorDistMiddle.set(ofRandom(ot->colorDistMiddle.getMin(), ot->colorDistMiddle.getMax()));
	ot->colorAlphaRange.set(ofRandom(ot->colorAlphaRange.getMin(), ot->colorAlphaRange.getMax()));
}

void organicTextResetsRandoms::randomizeGlobalColorParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeGlobalColorParams()";
	
	ot->color1.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(225, 255)));
	ot->color2.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255, ofRandom(225, 255))));
	ot->color3.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(225, 255)));
	//ot->colorOutline.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(225, 255)));
	ot->colorConnection.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(225, 255)));
	ot->colorTrails.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(225, 255)));
}

void organicTextResetsRandoms::randomizeAnimationParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeAnimationParams()";
	
	if (!ot->bEnableAnimation) ot->bEnableAnimation = true;
	// ot->animationMode.set(static_cast<int>(ofRandom(0, 5)));
	ot->animSpeed.set(ofRandom(ot->animSpeed.getMin(), ot->animSpeed.getMax()));
	ot->animPower.set(ofRandom(ot->animPower.getMin(), ot->animPower.getMax()));
	ot->animWaveFreq.set(ofRandom(ot->animWaveFreq.getMin(), ot->animWaveFreq.getMax()));
	ot->animIntensity.set(ofRandom(ot->animIntensity.getMin(), ot->animIntensity.getMax()));
	ot->animSpiral.set(ofRandom(ot->animSpiral.getMin(), ot->animSpiral.getMax()));
	ot->animPulseIntensity.set(ofRandom(ot->animPulseIntensity.getMin(), ot->animPulseIntensity.getMax()));
	ot->animOriginX.set(ofRandom(ot->animOriginX.getMin(), ot->animOriginX.getMax()));
}

void organicTextResetsRandoms::randomizeConnectionParams(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeConnectionParams()";
	
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

void organicTextResetsRandoms::randomizeMouseTweaks(OrganicText * ot) {
	ofLogNotice("organicTextResetsRandoms") << "randomizeMouseTweaks()";
	
	// ot->bMouseControlOrigin.set(ofRandom() > 0.5f);
	// ot->radiusMouse.set(ofRandom(ot->radiusMouse.getMin(), ot->radiusMouse.getMax()));
	// ot->bMouseHighlightPoints.set(ofRandom() > 0.5f);
	ot->colorMouseHighlight.set(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(128, 255)));
	ot->mouseInfluenceStrength.set(ofRandom(ot->mouseInfluenceStrength.getMin(), ot->mouseInfluenceStrength.getMax()));
	// ot->bMouseDisplacePoints.set(ofRandom() > 0.5f);
	ot->mouseDisplacePower.set(ofRandom(ot->mouseDisplacePower.getMin(), ot->mouseDisplacePower.getMax()));
	// ot->bMouseScaleShapes.set(ofRandom() > 0.5f);
	ot->mouseScalePower.set(ofRandom(ot->mouseScalePower.getMin(), ot->mouseScalePower.getMax()));
}
