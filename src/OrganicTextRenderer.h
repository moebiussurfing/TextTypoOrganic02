#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <ofMain.h>

#include "organicTextConstants.h"

class OrganicText;

class OrganicTextRenderer {
public:
  OrganicTextRenderer() = default;

  void setup(OrganicText* owner);
  void update();
  void draw();
  void drawDebug() const;
  void refreshPointsString();

  glm::vec2 lineTweakToTextSpace(const glm::vec2& normalized) const;
  glm::vec2 textToScreen(const glm::vec2& textPos) const;
  float getZoomScale() const;

private:
  std::vector<glm::vec2> sampleStringPoints(const std::string& s, float ds) const;
  void drawShape(glm::vec2 position, float size, ShapeType shape, float rotation = 0) const;
  void drawShapes();
  void drawConnections() const;
  void updateTrails();
  void drawTrails();

  ofColor getPointColor(int index, glm::vec2 position, float phase) const;
  glm::vec2 getAnimatedOffset(int index, float phase) const;
  float getMouseInfluence(glm::vec2 position) const;
  float getInfluenceFrom(glm::vec2 position, const glm::vec2& sourcePos, float radiusParam) const;
  float getCombinedInfluence(glm::vec2 position) const;

  OrganicText* owner_ = nullptr;
};
