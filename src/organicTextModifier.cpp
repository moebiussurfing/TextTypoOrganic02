#include "organicTextModifier.h"

//--------------------------------------------------------------
OrganicTextModifier::OrganicTextModifier(ModifierType type) {
  this->type = type;
  this->bActive = true;
  
  // Default values
  position = vec2(0.5f, 0.5f);
  radius = 0.1f;
  influenceStrength = 1.0f;
  
  // Animation defaults
  velocity = vec2(0.0f, 0.0f);
  angle = 0.0f;
  angularVelocity = 0.0f;
  bounds = ofRectangle(0.1f, 0.1f, 0.05f, 0.05f); // Small default size
  
  // Visual
  color = ofColor(255, 255, 0, 180); // Yellow with transparency
}

//--------------------------------------------------------------
OrganicTextModifier::~OrganicTextModifier() {
}

//--------------------------------------------------------------
void OrganicTextModifier::update(float deltaTime, float targetFPS) {
  if (!bActive) return;
  
  // Only animate particles, not mouse
  if (type == MODIFIER_PARTICLE) {
    // Normalize deltaTime
    float normalizedDt = deltaTime / (1.0f / targetFPS);
    
    // Update position
    position.x += velocity.x * normalizedDt;
    position.y += velocity.y * normalizedDt;
    
    // Update rotation
    angle += angularVelocity * normalizedDt;
    
    // Wrap around screen edges (considering bounds size)
    if (position.x < -bounds.width) {
      position.x = 1.0f;
    }
    if (position.x > 1.0f) {
      position.x = -bounds.width;
    }
    if (position.y < -bounds.height) {
      position.y = 1.0f;
    }
    if (position.y > 1.0f) {
      position.y = -bounds.height;
    }
  }
}

//--------------------------------------------------------------
void OrganicTextModifier::draw(int width, int height) const {
  if (!bActive) return;
  
  ofPushMatrix();
  ofPushStyle();
  
  // Get screen position
  vec2 screenPos = getScreenPosition(width, height);
  
  // Draw influence radius
  ofNoFill();
  ofSetColor(color, color.a * 0.3f);
  ofSetLineWidth(2.0f);
  float screenRadius = radius * std::min(width, height);
  ofDrawCircle(screenPos, screenRadius);
  
  // Draw particle bounds (for particle type)
  if (type == MODIFIER_PARTICLE) {
    ofPushMatrix();
    ofTranslate(screenPos.x, screenPos.y);
    ofRotateDeg(angle);
    
    // Draw rotated rectangle
    ofFill();
    ofSetColor(color);
    float w = bounds.width * width;
    float h = bounds.height * height;
    ofDrawRectangle(-w * 0.5f, -h * 0.5f, w, h);
    
    ofPopMatrix();
  } else {
    // Draw mouse indicator
    ofFill();
    ofSetColor(color);
    ofDrawCircle(screenPos, 5.0f);
  }
  
  ofPopStyle();
  ofPopMatrix();
}

//--------------------------------------------------------------
vec2 OrganicTextModifier::getPosition() const {
  return position;
}

//--------------------------------------------------------------
void OrganicTextModifier::setPosition(const vec2& pos) {
  position = pos;
}

//--------------------------------------------------------------
vec2 OrganicTextModifier::getScreenPosition(int width, int height) const {
  return vec2(position.x * width, position.y * height);
}

//--------------------------------------------------------------
float OrganicTextModifier::getRadius() const {
  return radius;
}

//--------------------------------------------------------------
void OrganicTextModifier::setRadius(float r) {
  radius = ofClamp(r, 0.0f, 1.0f);
}

//--------------------------------------------------------------
float OrganicTextModifier::getInfluenceStrength() const {
  return influenceStrength;
}

//--------------------------------------------------------------
void OrganicTextModifier::setInfluenceStrength(float strength) {
  influenceStrength = ofClamp(strength, 0.0f, 1.0f);
}

//--------------------------------------------------------------
void OrganicTextModifier::setVelocity(const vec2& vel) {
  velocity = vel;
}

//--------------------------------------------------------------
void OrganicTextModifier::setAngularVelocity(float angVel) {
  angularVelocity = angVel;
}

//--------------------------------------------------------------
void OrganicTextModifier::setBounds(const ofRectangle& b) {
  bounds = b;
}

//--------------------------------------------------------------
float OrganicTextModifier::getAngle() const {
  return angle;
}

//--------------------------------------------------------------
OrganicTextModifier::ModifierType OrganicTextModifier::getType() const {
  return type;
}

//--------------------------------------------------------------
bool OrganicTextModifier::isActive() const {
  return bActive;
}

//--------------------------------------------------------------
void OrganicTextModifier::setActive(bool active) {
  bActive = active;
}

//--------------------------------------------------------------
void OrganicTextModifier::setColor(const ofColor& col) {
  color = col;
}

//--------------------------------------------------------------
ofColor OrganicTextModifier::getColor() const {
  return color;
}
