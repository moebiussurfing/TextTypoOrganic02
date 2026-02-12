#include <cmath>

#include "OrganicTextRenderer.h"

#include "organicText.h"

//--------------------------------------------------------------
void OrganicTextRenderer::setup(OrganicText* owner) {
  owner_ = owner;
}

//--------------------------------------------------------------
void OrganicTextRenderer::update() {
  if (!owner_) return;

  auto* o = owner_;

  if (o->bEnableAnimation.get()) {
    float dt = ofGetLastFrameTime();
    float normalizedDt = dt / (1.0f / o->targetFPS);
    o->t += BASE_TIME_STEP * o->animSpeed.get() * ANIM_SPEED_MAX * normalizedDt;
  }

  o->fps = ofGetFrameRate();
  o->frameTime = 1000.0f / ofClamp(o->fps, 0.1f, 10000.0f);

  o->bDebugLowFPS = (o->fps < (o->targetFPS * 0.75f));

  if (o->bFlagRefreshFont) {
    o->refreshFont();
    o->bFlagRefreshFont = false;
  }

  float centerX = ofGetWidth() * 0.5f;
  float centerY = ofGetHeight() * 0.5f;

  o->tweenPosition.update();

  if (o->bLineTweaks.get()) {
    o->lineLocalPos = o->tweenPosition.getValue();
  }
  if (o->bMouseTweaks.get()) {
    o->mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
  }

  if (o->bMouseTweaks.get()) {
    float zoomFactor = getZoomScale();

    glm::vec2 translated = o->mousePos - glm::vec2(centerX, centerY);
    glm::vec2 scaled = translated / zoomFactor;

    float textOffsetX = -o->data->getTextWidth() * 0.5f;
    float textOffsetY = o->data->getTextHeight() * 0.5f;
    o->mouseLocalPos = scaled - glm::vec2(textOffsetX, textOffsetY);
  }

  bool mouseInBounds = false;
  if (o->bMouseTweaks.get()) {
    mouseInBounds |= (o->mouseLocalPos.x >= 0 && o->mouseLocalPos.x <= o->data->getTextWidth() && o->mouseLocalPos.y >= -o->data->getTextHeight() && o->mouseLocalPos.y <= 0);
  }
  if (o->bLineTweaks.get()) {
    mouseInBounds |= (o->lineLocalPos.x >= 0 && o->lineLocalPos.x <= o->data->getTextWidth() && o->lineLocalPos.y >= -o->data->getTextHeight() && o->lineLocalPos.y <= 0);
  }
  o->bMouseInBounds = mouseInBounds;

  if (o->bDebug) {
    float t = ofGetElapsedTimef();
    float speed = DEBUG_SPEED;
    float alpha = (sin(glm::two_pi<float>() * speed * t) * 0.5f + 0.5f) * DEBUG_ALPHA_MAX + DEBUG_ALPHA_MIN_OFFSET;
    o->colorDebugBlink = ofColor(o->colorDebug.r, o->colorDebug.g, o->colorDebug.b, static_cast<int>(alpha));
  }

  o->tweenInPoint.update();
  o->tweenOutPoint.update();
}

//--------------------------------------------------------------
void OrganicTextRenderer::draw() {
  if (!owner_) return;

  auto* o = owner_;

  auto td = ofGetElapsedTimeMicros();

  float zoomFactor = getZoomScale();

  float centerX = ofGetWidth() * 0.5f;
  float centerY = ofGetHeight() * 0.5f;

  ofPushMatrix();
  {
    ofTranslate(centerX, centerY);
    ofScale(zoomFactor, zoomFactor);

    ofTranslate(-o->font.stringWidth(o->sText) * 0.5f, o->font.stringHeight(o->sText) * 0.5f);

    if (o->bDrawShapes && o->bShapeBack) {
      drawShapes();
    }

    if (o->bDrawConnections) {
      drawConnections();
    }

    if (o->bDrawTrails) {
      updateTrails();
      drawTrails();
    }

    if (o->bDrawShapes && !o->bShapeBack) {
      drawShapes();
    }
  }
  ofPopMatrix();

  o->timeDrawBenchmark = ofGetElapsedTimeMicros() - td;
}

//--------------------------------------------------------------
void OrganicTextRenderer::drawDebug() const {
  if (!owner_) return;

  auto* o = owner_;

  float zoomFactor = getZoomScale();
  float centerX = ofGetWidth() * 0.5f;
  float centerY = ofGetHeight() * 0.5f;
  glm::vec2 textOffset(-o->data->getTextWidth() * 0.5f, o->data->getTextHeight() * 0.5f);

  ofPushMatrix();
  {
    ofTranslate(centerX, centerY);
    ofScale(zoomFactor, zoomFactor);
    ofTranslate(textOffset);

    ofPushStyle();

    ofSetColor(o->colorDebugBlink);

    ofNoFill();
    ofSetLineWidth(1.2f);

    float crossSize = 7;
    glm::vec2 textCenter = o->data->getTextCenter();
    ofDrawLine(textCenter - glm::vec2(crossSize, 0), textCenter + glm::vec2(crossSize, 0));
    ofDrawLine(textCenter - glm::vec2(0, crossSize), textCenter + glm::vec2(0, crossSize));
    ofDrawCircle(textCenter, crossSize * 0.7f);

    {
      ofSetColor(o->colorDebugBlink);

      ofFill();
      const auto& pointsString = o->data->getBasePoints();
      for (const auto& point : pointsString) {
        ofDrawCircle(point, 1.f);
      }
    }

    ofPopStyle();

    if (o->bMouseTweaks.get()) {
      ofPushStyle();
      ofFill();
      ofSetColor(o->colorDebugBlink);
      float rMouse = ofMap(o->radiusMouse.get(), 0.f, 1.f, MOUSE_RADIUS_INTERACT_MIN, MOUSE_RADIUS_INTERACT_MAX, true);
      ofDrawCircle(o->mouseLocalPos, rMouse);
      ofPopStyle();
    }

    if (o->bLineTweaks.get()) {
      ofPushStyle();
      ofFill();
      ofSetColor(o->colorDebugBlink);
      float rLine = ofMap(o->radiusLineMouse.get(), 0.f, 1.f, MOUSE_RADIUS_INTERACT_MIN, MOUSE_RADIUS_INTERACT_MAX, true);
      ofDrawCircle(o->lineLocalPos, rLine);
      ofPopStyle();
    }

    if (o->bLineTweaks.get()) {
      ofPushStyle();
      ofSetColor(o->colorDebugBlink);

      glm::vec2 startText = lineTweakToTextSpace(o->vLineFrom.get());
      glm::vec2 endText = lineTweakToTextSpace(o->vLineTo.get());
      glm::vec2 currentText = o->tweenPosition.getValue();

      ofDrawCircle(startText, 4);
      ofDrawCircle(endText, 4);
      ofDrawLine(startText, endText);
      ofDrawCircle(currentText, 10);
      ofPopStyle();
    }

    if (o->bDebug) {
      ofPushStyle();
      ofNoFill();
      ofSetColor(o->colorDebugBlink);
      ofSetLineWidth(1.f);
      o->font.drawStringAsShapes(o->sText, 0, 0);
      ofPopStyle();
    }
  }
  ofPopMatrix();
}

//--------------------------------------------------------------
std::vector<glm::vec2> OrganicTextRenderer::sampleStringPoints(const std::string& s, float ds) const {
  if (!owner_) return {};

  auto* o = owner_;

  ofLogNotice("OrganicText") << "sampleStringPoints() s:" << s << ", ds:" << ds;

  std::vector<glm::vec2> points;
  if (s.empty()) return points;

  std::vector<ofPath> paths = o->font.getStringAsPoints(s, true, false);

  for (auto& path : paths) {
    std::vector<ofPolyline> polylines = path.getOutline();

    for (auto& polyline : polylines) {
      if (polyline.size() == 0) continue;

      float totalLength = polyline.getPerimeter();
      int numSamples = static_cast<int>(totalLength / ds);
      numSamples = ofClamp(numSamples, 3, 100000);

      for (int i = 0; i < numSamples; i++) {
        float position = static_cast<float>(i) / static_cast<float>(numSamples - 1);
        glm::vec2 point = polyline.getPointAtPercent(position);
        points.push_back(point);
      }
    }
  }

  return points;
}

//--------------------------------------------------------------
void OrganicTextRenderer::refreshPointsString() {
  if (!owner_) return;

  auto* o = owner_;

  ofLogNotice("OrganicText") << "refreshPointsString()";

  float finalSpacing = ofMap(o->densitySpacing.get(), 0, 1, DENSITY_SPACING_MIN, DENSITY_SPACING_MAX, true);

  std::vector<glm::vec2> sampledPoints = sampleStringPoints(o->sText, finalSpacing);
  o->data->setBasePoints(sampledPoints);

  int tl = static_cast<int>(ofMap(o->trailLength.get(), 0.f, 1.f, TRAILS_LENGTH_MIN, TRAILS_LENGTH_MAX, true));
  o->data->initTrails(tl);

  const auto& points = o->data->getBasePoints();
  if (!points.empty()) {
    glm::vec2 sum(0, 0);
    for (const auto& p : points) {
      sum += p;
    }
    glm::vec2 center = sum / static_cast<float>(points.size());

    float width = o->font.stringWidth(o->sText);
    float height = o->font.stringHeight(o->sText);
    o->data->setTextMetrics(width, height, center);
  }

  if (o->bAutoZoomGlobal) {
    o->refreshWindowResized();
  }
}

//--------------------------------------------------------------
glm::vec2 OrganicTextRenderer::getAnimatedOffset(int index, float phase) const {
  if (!owner_) return glm::vec2(0, 0);

  auto* o = owner_;

  glm::vec2 offset(0, 0);

  const auto& pointsString = o->data->getBasePoints();
  if (!o->bEnableAnimation.get() || pointsString.empty()) {
    return offset;
  }

  float fontScale = o->fontSize.get() / 150.0f;

  float customOriginX = o->data->getTextWidth() * o->animOriginX.get();
  float customOriginY = o->data->getTextCenter().y;

  if ((o->bMouseTweaks.get() || o->bLineTweaks.get()) && o->bMouseControlOrigin.get() && (AnimMode)o->animationMode.get() != ANIM_WAVE) {
    glm::vec2 controlOrigin = o->mouseLocalPos;
    if (o->bMouseTweaks.get() && o->bLineTweaks.get()) {
      controlOrigin = (o->mouseLocalPos + o->lineLocalPos) * 0.5f;
    } else if (o->bLineTweaks.get()) {
      controlOrigin = o->lineLocalPos;
    }
    customOriginX = controlOrigin.x;
    customOriginY = controlOrigin.y;
  }

  glm::vec2 customOrigin = glm::vec2(customOriginX, customOriginY);

  switch ((AnimMode)o->animationMode.get()) {
    case ANIM_NOISE: {
      float maxDisp = ofMap(o->animPower.get(), 0, 1, 0, ANIM_NOISE_MAX * fontScale, true);

      if ((o->bMouseTweaks.get() || o->bLineTweaks.get()) && o->bMouseControlOrigin.get()) {
        float combinedInfluence = getCombinedInfluence(pointsString[index]);
        maxDisp *= (1.0f - combinedInfluence * 2.f);
      }

      offset = glm::vec2(ofSignedNoise(phase, 0.0f), ofSignedNoise(phase, 233.0f)) * maxDisp;
      break;
    }

    case ANIM_WAVE: {
      float freq = ofMap(o->animWaveFreq.get(), 0, 1, ANIM_WAVE_FREQ_MIN, ANIM_WAVE_FREQ_MAX, true);
      float amp = ofMap(o->animIntensity.get(), 0, 1, 0, ANIM_WAVE_MAX * fontScale, true);

      float distFromOrigin = pointsString[index].x - customOriginX;
      float wave = sin(distFromOrigin * freq + o->t * glm::two_pi<float>()) * amp;
      offset = glm::vec2(0, wave);
      break;
    }

    case ANIM_SPIRAL: {
      if (pointsString.size() < 2) break;

      float angle = atan2(pointsString[index].y - customOrigin.y, pointsString[index].x - customOrigin.x);
      float distance = glm::distance(pointsString[index], customOrigin);
      float tightness = ofMap(o->animSpiral.get(), 0, 1, ANIM_SPIRAL_TIGHT_MIN, ANIM_SPIRAL_TIGHT_MAX, true);
      float maxDisp = ofMap(o->animPower.get(), 0, 1, 0, ANIM_SPIRAL_MAX * fontScale, true);

      float spiralPhase = distance * tightness + o->t * glm::two_pi<float>();
      float spiralOffset = sin(spiralPhase) * maxDisp;

      offset = glm::vec2(cos(angle) * spiralOffset, sin(angle) * spiralOffset);
      break;
    }

    case ANIM_PULSE: {
      if (pointsString.size() < 2) break;

      float distance = glm::distance(pointsString[index], customOrigin);
      float maxPulse = ofMap(o->animPulseIntensity.get(), 0, 1, 0, ANIM_PULSE_MAX * fontScale, true);
      float pulsePhase = sin(o->t * glm::two_pi<float>() * 0.5f) * maxPulse;

      if (distance > 0.5f) {
        glm::vec2 direction = glm::normalize(pointsString[index] - customOrigin);
        offset = direction * pulsePhase;
      }
      break;
    }

    case ANIM_ORBIT: {
      if (pointsString.size() < 2) break;

      float angle = atan2(pointsString[index].y - customOrigin.y, pointsString[index].x - customOrigin.x);
      angle += o->t * glm::two_pi<float>() * 0.3f;

      float distance = glm::distance(pointsString[index], customOrigin);
      glm::vec2 newPos = customOrigin + glm::vec2(cos(angle), sin(angle)) * distance;
      offset = newPos - pointsString[index];
      break;
    }
  }

  return offset;
}

//--------------------------------------------------------------
float OrganicTextRenderer::getMouseInfluence(glm::vec2 position) const {
  if (!owner_) return 0.0f;

  auto* o = owner_;
  return getInfluenceFrom(position, o->mouseLocalPos, o->radiusMouse.get());
}

float OrganicTextRenderer::getInfluenceFrom(glm::vec2 position, const glm::vec2& sourcePos, float radiusParam) const {
  if (!owner_) return 0.0f;

  auto* o = owner_;

  float radiusPixels = ofMap(radiusParam, 0.f, 1.f, MOUSE_RADIUS_INTERACT_MIN, MOUSE_RADIUS_INTERACT_MAX, true);
  float distToSource = glm::distance(position, sourcePos);

  if (distToSource >= radiusPixels) {
    return 0.0f;
  }

  float influence = ofMap(distToSource, 0, radiusPixels, 1.0f, 0.0f, true);

  influence *= o->mouseInfluenceStrength.get();

  float power = 0.7f;
  influence = std::pow(influence, power);

  return influence;
}

float OrganicTextRenderer::getCombinedInfluence(glm::vec2 position) const {
  if (!owner_) return 0.0f;

  auto* o = owner_;

  float total = 0.0f;
  if (o->bMouseTweaks.get()) {
    total += getInfluenceFrom(position, o->mouseLocalPos, o->radiusMouse.get());
  }
  if (o->bLineTweaks.get()) {
    total += getInfluenceFrom(position, o->lineLocalPos, o->radiusLineMouse.get());
  }
  return ofClamp(total, 0.0f, 1.0f);
}

//--------------------------------------------------------------
glm::vec2 OrganicTextRenderer::lineTweakToTextSpace(const glm::vec2& normalized) const {
  if (!owner_) return glm::vec2(0, 0);

  auto* o = owner_;

  float padX = o->data->getTextWidth() * LINE_TWEAKS_EDGE_PAD;
  float x = ofMap(normalized.x, -1.0f, 1.0f, -padX, o->data->getTextWidth() + padX, true);
  float y = ofMap(normalized.y, -1.0f, 1.0f, -o->data->getTextHeight(), 0.0f, true);
  return glm::vec2(x, y);
}

//--------------------------------------------------------------
glm::vec2 OrganicTextRenderer::textToScreen(const glm::vec2& textPos) const {
  if (!owner_) return glm::vec2(0, 0);

  auto* o = owner_;

  float zoomFactor = getZoomScale();
  float centerX = ofGetWidth() * 0.5f;
  float centerY = ofGetHeight() * 0.5f;
  glm::vec2 offset = glm::vec2(-o->data->getTextWidth() * 0.5f, o->data->getTextHeight() * 0.5f);
  return glm::vec2(centerX, centerY) + (textPos + offset) * zoomFactor;
}

//--------------------------------------------------------------
float OrganicTextRenderer::getZoomScale() const {
  if (!owner_) return 1.0f;

  auto* o = owner_;

  const float normalized = ofClamp(o->zoomGlobal.get(), 0.0f, 1.0f);
  return ofLerp(ZOOM_GLOBAL_SCALE_MIN, ZOOM_GLOBAL_SCALE_MAX, normalized);
}

//--------------------------------------------------------------
ofColor OrganicTextRenderer::getPointColor(int index, glm::vec2 position, float phase) const {
  if (!owner_) return ofColor::white;

  auto* o = owner_;

  ofColor color = ofColor(ofColor::white, 255);

  const auto& pointsString = o->data->getBasePoints();
  if (pointsString.empty()) return color;

  switch ((ColorMode)o->colorMode.get()) {
    case COLOR_GLOBAL_1:
      color = o->color1.get();
      break;

    case COLOR_GLOBAL_2:
      color = o->color2.get();
      break;

    case COLOR_GLOBAL_3:
      color = o->color3.get();
      break;

    case COLOR_GLOBAL_MIX: {
      float indexFactor = static_cast<float>(index) / ofClamp(static_cast<float>(pointsString.size()), 1.0f, 100000.0f);
      float timeFactor = (sin(o->t * o->colorSpeed.get() * glm::two_pi<float>()) + 1.0f) * 0.5f;

      ofColor c1 = o->color1.get();
      ofColor c2 = o->color2.get();
      ofColor c3 = o->color3.get();

      float innerPoint = o->colorInner.get();
      if (indexFactor < innerPoint) {
        color = c1.lerp(c2, indexFactor / innerPoint);
      } else {
        color = c2.lerp(c3, (indexFactor - innerPoint) / (1.0f - innerPoint));
      }

      color = color.lerp(c3, timeFactor * o->colorMixFactor.get() * 0.4f);

      if (o->colorAlphaRange.get() > 0.01f) {
        float alphaMin = ofMap(o->colorAlphaRange.get(), 0, 1, 255, 50, true);
        float alpha = ofMap(indexFactor, 0, 1, 255, alphaMin, true);
        color.a = alpha;
      }
      break;
    }

    case COLOR_DISTANCE: {
      float distance = glm::distance(position, o->data->getTextCenter());
      float distFactor = ofMap(distance, 0, COLOR_DISTANCE_MAX, 0, 1, true);

      ofColor c1 = o->color1.get();
      ofColor c2 = o->color2.get();
      ofColor c3 = o->color3.get();

      float innerPoint = o->colorInner.get();
      float middlePoint = o->colorDistMiddle.get();

      if (distFactor < innerPoint) {
        color = c1.lerp(c2, distFactor / innerPoint);
      } else if (distFactor < middlePoint) {
        float localT = (distFactor - innerPoint) / (middlePoint - innerPoint);
        color = c2.lerp(c3, localT);
      } else {
        color = c3;
      }

      if (o->colorAlphaRange.get() > 0.01f) {
        float alphaCenter = 255.0f;
        float alphaEdge = ofMap(o->colorAlphaRange.get(), 0, 1, 255, 50, true);
        float alpha = ofMap(distance, 0, COLOR_DISTANCE_MAX, alphaCenter, alphaEdge, true);
        color.a = alpha;
      }
      break;
    }
  }

  if (o->bColorByDistance) {
    float distance = glm::distance(position, o->data->getTextCenter());
    float alphaEdge = ofMap(o->colorAlphaRange.get(), 0, 1, 255, 0, true);
    float alpha = ofMap(distance, 0, COLOR_DISTANCE_MAX, 255, alphaEdge, true);
    color.a = alpha;
  }

  if ((o->bMouseTweaks.get() || o->bLineTweaks.get()) && o->bMouseHighlightPoints.get()) {
    float influence = getCombinedInfluence(position);
    if (influence > 0.0f) {
      color = color.lerp(o->colorMouseHighlight.get(), influence);
    }
  }

  return color;
}

//--------------------------------------------------------------
void OrganicTextRenderer::drawShape(glm::vec2 position, float size, ShapeType shape, float rotation) const {
  if (!owner_) return;

  auto* o = owner_;

  ofPushMatrix();
  ofTranslate(position);
  ofRotateDeg(rotation);
  float h = size * ofMap(o->shapeRatio.get(), 0.f, 1.f, 1.f, 10.f, true);

  switch (shape) {
    case SHAPE_CIRCLE:
      ofDrawCircle(0, 0, size);
      break;

    case SHAPE_RECTANGLE:
      ofDrawRectangle(-size * 0.5f, -size * 0.5f, size, h);
      break;

    case SHAPE_TRIANGLE: {
      ofDrawTriangle(0, -h * 0.5f, -size * 0.5f, h * 0.5f, size * 0.5f, h * 0.5f);
      break;
    }

    case SHAPE_STAR: {
      ofPolyline star;
      int points = 5;
      for (int i = 0; i < points * 2; i++) {
        float angle = (static_cast<float>(i) * glm::two_pi<float>()) / (static_cast<float>(points) * 2.0f);
        float radius = (i % 2 == 0) ? size : size * 0.4f;
        star.addVertex(cos(angle) * radius, sin(angle) * radius);
      }
      star.close();

      ofPath starPath;
      starPath.setFilled(o->bDrawFill.get());
      starPath.setFillColor(ofGetStyle().color);
      starPath.setStrokeColor(ofGetStyle().color);
      starPath.setStrokeWidth(1.0f);

      starPath.moveTo(star[0]);
      for (std::size_t i = 1; i < star.size(); ++i) {
        starPath.lineTo(star[i]);
      }
      starPath.close();

      starPath.draw();
      break;
    }

    case SHAPE_CROSS: {
      float thickness = size * 0.2f;
      ofDrawRectangle(-thickness * 0.5f, -size * 0.5f, thickness, size);
      ofDrawRectangle(-size * 0.5f, -thickness * 0.5f, size, thickness);
      break;
    }

    case SHAPE_POINT: {
      ofDrawCircle(0, 0, size * 0.05f);
      break;
    }
  }

  ofPopMatrix();
}

//--------------------------------------------------------------
void OrganicTextRenderer::updateTrails() {
  if (!owner_) return;

  auto* o = owner_;

  const auto& pointsString = o->data->getBasePoints();
  const auto& pointsAnimatedCache = o->data->getAnimatedCache();

  for (std::size_t i = 0; i < pointsString.size(); i++) {
    glm::vec2 currentPos;
    if (i < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
      currentPos = pointsAnimatedCache[i];
    } else {
      float phase = o->t + 0.123f * static_cast<float>(i);
      glm::vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
      currentPos = pointsString[i] + offset;
    }

    o->data->updateTrailPoint(i, currentPos);
  }
}

//--------------------------------------------------------------
void OrganicTextRenderer::drawConnections() const {
  if (!owner_) return;

  auto* o = owner_;

  const auto& pointsString = o->data->getBasePoints();
  if (!o->bDrawConnections.get() || pointsString.size() < 2) return;

  float maxDist = o->connectDistance.get();
  float quality = ofClamp(o->connectQuality.get(), 0.1f, 1.0f);
  int skipFactor = ofClamp(static_cast<int>(1.0f / quality), 1, 100);

  int maxConPerPoint = o->bConnectNearOnly ? CONNECTIONS_MAX_PER_POINT_NEAR : CONNECTIONS_MAX_PER_POINT_FAR;

  o->cachedConnectionCount = 0;
  ofPushStyle();
  ofSetLineWidth(o->connectLineWidth);

  ofMesh connectionMesh;
  connectionMesh.setMode(OF_PRIMITIVE_LINES);

  const auto& pointsAnimatedCache = o->data->getAnimatedCache();

  for (std::size_t i = pointsString.size() * o->inPoint.get(); i < pointsString.size() && i < pointsString.size() * o->outPoint.get(); i += skipFactor) {
    glm::vec2 pos1;
    if (i < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
      pos1 = pointsAnimatedCache[i];
    } else {
      float phase1 = o->t + 0.123f * static_cast<float>(i);
      glm::vec2 offset1 = getAnimatedOffset(static_cast<int>(i), phase1);
      pos1 = pointsString[i] + offset1;
    }

    int connectionsDrawn = 0;
    int searchLimit = o->bConnectNearOnly ? ofClamp(CONNECTIONS_SEARCH_NEAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i)) : ofClamp(CONNECTIONS_SEARCH_FAR, 1, static_cast<int>(pointsString.size()) - static_cast<int>(i));

    for (int offset = 1; offset < searchLimit && connectionsDrawn < maxConPerPoint; offset += skipFactor) {
      std::size_t j = i + offset;
      if (j >= pointsString.size()) break;

      glm::vec2 pos2;
      if (j < pointsAnimatedCache.size() && pointsAnimatedCache.size() == pointsString.size()) {
        pos2 = pointsAnimatedCache[j];
      } else {
        float phase2 = o->t + 0.123f * static_cast<float>(j);
        glm::vec2 offset2 = getAnimatedOffset(static_cast<int>(j), phase2);
        pos2 = pointsString[j] + offset2;
      }

      float dist = glm::distance(pos1, pos2);

      if (dist < maxDist) {
        float alpha = ofMap(dist, 0, maxDist, 255, 0, true);
        float acolor = ofMap(o->colorConnection.get().a, 0, 255, 0.f, 1.f, true);
        float oPower = 2.f;
        alpha = ofMap(alpha * (acolor * oPower * o->connectAlpha.get()), 0, 255, 0, 255, true);

        ofColor connectionColor = o->colorConnection.get();
        connectionColor.a = alpha;

        glm::vec3 p1(pos1.x, pos1.y, 0.0f);
        glm::vec3 p2(pos2.x, pos2.y, 0.0f);

        connectionMesh.addVertex(p1);
        connectionMesh.addColor(connectionColor);
        connectionMesh.addVertex(p2);
        connectionMesh.addColor(connectionColor);

        connectionsDrawn++;
        o->cachedConnectionCount++;
      }
    }
  }

  if (connectionMesh.getNumVertices() > 0) {
    connectionMesh.draw();
  }

  ofPopStyle();
}

//--------------------------------------------------------------
void OrganicTextRenderer::drawTrails() {
  if (!owner_) return;

  auto* o = owner_;

#ifdef FIX_ORGANIC_TEXT_TWEEN_TRAILS_PROBLEMS
  if (o->isTweening()) return;
#endif

  const auto& pointsString = o->data->getBasePoints();
  const auto& pointTrails = o->data->getTrails();

  ofPushStyle();
  ofSetLineWidth(o->trailLineWidth);
  float tf = ofMap(o->trailFade, 0.f, 1.f, TRAILS_FADE_MIN, TRAILS_FADE_MAX, true);

  ofMesh trailMesh;
  trailMesh.setMode(OF_PRIMITIVE_LINES);

  for (std::size_t i = pointsString.size() * o->inPoint.get(); i < pointTrails.size() && i < pointsString.size() * o->outPoint.get(); i++) {
    if (pointTrails[i].size() < 2) continue;

    for (std::size_t j = 1; j < pointTrails[i].size(); j++) {
      float fadeAmount = pow(tf, static_cast<float>(j));
      float alpha = fadeAmount * TRAILS_ALPHA_MAX;

      ofColor segmentColor = o->colorTrails.get();
      segmentColor.a = alpha;

      glm::vec3 p1(pointTrails[i][j - 1].x, pointTrails[i][j - 1].y, 0.0f);
      glm::vec3 p2(pointTrails[i][j].x, pointTrails[i][j].y, 0.0f);

      trailMesh.addVertex(p1);
      trailMesh.addColor(segmentColor);
      trailMesh.addVertex(p2);
      trailMesh.addColor(segmentColor);
    }
  }

  if (trailMesh.getNumVertices() > 0) {
    trailMesh.draw();
  }

  ofPopStyle();
}

//--------------------------------------------------------------
void OrganicTextRenderer::drawShapes() {
  if (!owner_) return;

  auto* o = owner_;

  const auto& pointsString = o->data->getBasePoints();

  if (o->data->getAnimatedCache().size() != pointsString.size()) {
    o->data->resizeCache(pointsString.size());
  }

  for (std::size_t i = pointsString.size() * o->inPoint.get(); i < pointsString.size() && i < pointsString.size() * o->outPoint.get(); i++) {
    ofPushStyle();

    float phase = o->t + 0.123f * static_cast<float>(i);
    glm::vec2 offset = getAnimatedOffset(static_cast<int>(i), phase);
    glm::vec2 finalPos = pointsString[i] + offset;

    float mouseInfluence = 0.0f;
    float lineInfluence = 0.0f;
    if (o->bMouseTweaks.get()) {
      mouseInfluence = getInfluenceFrom(finalPos, o->mouseLocalPos, o->radiusMouse.get());
    }
    if (o->bLineTweaks.get()) {
      lineInfluence = getInfluenceFrom(finalPos, o->lineLocalPos, o->radiusLineMouse.get());
    }
    float totalInfluence = ofClamp(mouseInfluence + lineInfluence, 0.0f, 1.0f);

    glm::vec2 influenceSourcePos = o->mouseLocalPos;
    if (o->bMouseTweaks.get() && o->bLineTweaks.get()) {
      influenceSourcePos = (mouseInfluence >= lineInfluence) ? o->mouseLocalPos : o->lineLocalPos;
    } else if (o->bLineTweaks.get()) {
      influenceSourcePos = o->lineLocalPos;
    }

    if (o->bMouseDisplacePoints.get() && totalInfluence > 0.0f) {
      glm::vec2 direction = glm::normalize(finalPos - influenceSourcePos);

      float powerCentered = (o->mouseDisplacePower.get() - 0.5f) * 2.0f;

      float maxDisplacement = 50.0f;
      float displacement = totalInfluence * powerCentered * maxDisplacement;

      finalPos += direction * displacement;
    }

    o->data->setCachedAnimatedPoint(i, finalPos);

    ofColor color = getPointColor(static_cast<int>(i), finalPos, phase);

    ofSetColor(color);

    if (o->bDrawFill.get()) {
      ofFill();
    } else {
      ofNoFill();
    }

    float maxSize = ofMap(o->shapeSize.get(), 0, 1, SHAPE_MIN_RADIUS, SHAPE_MAX_RADIUS, true);
    float minSize = ofMap(o->shapeSizeMin.get(), 0, 1, 0, maxSize, true);

    float sizeNoise = ofNoise(phase * SHAPE_SIZE_NOISE_SCALE, static_cast<float>(i) * SHAPE_SIZE_INDEX_SCALE);
    float pointSize = ofLerp(minSize, maxSize, sizeNoise);

    if (o->bMouseScaleShapes.get() && totalInfluence > 0.0f) {
      float powerCentered = (o->mouseScalePower.get() - 0.5f) * 2.0f;
      float scaleMultiplier = 1.0f + (totalInfluence * powerCentered * MAX_SCALE_POWER);
      pointSize *= scaleMultiplier;
    }

    float rotation = ofMap(o->shapeRotation.get(), 0, 1, 0, 360, true);

    drawShape(finalPos, pointSize, (ShapeType)o->shapeType.get(), rotation);

    if (o->bDebug) {
      ofSetColor(o->colorDebug);
      ofDrawCircle(finalPos, 2.f);
    }

    ofPopStyle();
  }
}
