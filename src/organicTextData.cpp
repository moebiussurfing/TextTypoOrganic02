#include "organicTextData.h"

//--------------------------------------------------------------
OrganicTextData::OrganicTextData() {
  textCenter = vec2(0, 0);
  textWidth = 0.0f;
  textHeight = 0.0f;
}

//--------------------------------------------------------------
OrganicTextData::~OrganicTextData() {
  clear();
}

//--------------------------------------------------------------
void OrganicTextData::setBasePoints(const std::vector<vec2>& points) {
  pointsString = points;
}

//--------------------------------------------------------------
void OrganicTextData::initTrails(int trailLength) {
  ofLogNotice("OrganicTextData") << "initTrails() length:" << trailLength;
  
  pointTrails.clear();
  pointTrails.resize(pointsString.size());
  pointsAnimatedCache.assign(pointsString.size(), vec2(0, 0));
  
  for (std::size_t i = 0; i < pointsString.size(); i++) {
    pointTrails[i].resize(trailLength);
    for (int j = 0; j < trailLength; j++) {
      pointTrails[i][j] = pointsString[i];
    }
    pointsAnimatedCache[i] = pointsString[i];
  }
}

//--------------------------------------------------------------
void OrganicTextData::updateTrailPoint(std::size_t pointIndex, const vec2& position) {
  if (pointIndex >= pointTrails.size()) return;
  
  // Shift trail history
  for (int j = static_cast<int>(pointTrails[pointIndex].size()) - 1; j > 0; j--) {
    pointTrails[pointIndex][j] = pointTrails[pointIndex][j - 1];
  }
  
  // Set new position
  pointTrails[pointIndex][0] = position;
}

//--------------------------------------------------------------
void OrganicTextData::setCachedAnimatedPoint(std::size_t index, const vec2& position) {
  if (index >= pointsAnimatedCache.size()) {
    resizeCache(index + 1);
  }
  pointsAnimatedCache[index] = position;
}

//--------------------------------------------------------------
void OrganicTextData::setTextMetrics(float width, float height, const vec2& center) {
  textWidth = width;
  textHeight = height;
  textCenter = center;
}

//--------------------------------------------------------------
const std::vector<vec2>& OrganicTextData::getBasePoints() const {
  return pointsString;
}

//--------------------------------------------------------------
const std::vector<std::vector<vec2>>& OrganicTextData::getTrails() const {
  return pointTrails;
}

//--------------------------------------------------------------
const std::vector<vec2>& OrganicTextData::getAnimatedCache() const {
  return pointsAnimatedCache;
}

//--------------------------------------------------------------
std::vector<vec2>& OrganicTextData::getAnimatedCacheMutable() {
  return pointsAnimatedCache;
}

//--------------------------------------------------------------
std::size_t OrganicTextData::getPointCount() const {
  return pointsString.size();
}

//--------------------------------------------------------------
vec2 OrganicTextData::getTextCenter() const {
  return textCenter;
}

//--------------------------------------------------------------
float OrganicTextData::getTextWidth() const {
  return textWidth;
}

//--------------------------------------------------------------
float OrganicTextData::getTextHeight() const {
  return textHeight;
}

//--------------------------------------------------------------
void OrganicTextData::clear() {
  pointsString.clear();
  pointTrails.clear();
  pointsAnimatedCache.clear();
  textCenter = vec2(0, 0);
  textWidth = 0.0f;
  textHeight = 0.0f;
}

//--------------------------------------------------------------
void OrganicTextData::resizeCache(std::size_t size) {
  pointsAnimatedCache.resize(size);
}

//--------------------------------------------------------------
bool OrganicTextData::isValid() const {
  return !pointsString.empty();
}
