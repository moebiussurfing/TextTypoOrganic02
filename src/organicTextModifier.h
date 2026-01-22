#pragma once

#include "ofMain.h"

using namespace glm;

/// @brief Individual modifier that can influence organic text points
/// Can be mouse-based or autonomous particle-based
class OrganicTextModifier {
public:
  enum ModifierType {
    MODIFIER_MOUSE = 0,
    MODIFIER_PARTICLE = 1
  };

  OrganicTextModifier(ModifierType type = MODIFIER_PARTICLE);
  ~OrganicTextModifier();

  //--

  // Update & Draw
  
  /// @brief Update modifier state (animation, position, etc)
  void update(float deltaTime, float targetFPS);
  
  /// @brief Draw visual representation of modifier
  void draw(int width, int height) const;

  //--

  // Position
  
  /// @brief Get current position in normalized coordinates (0-1)
  vec2 getPosition() const;
  
  /// @brief Set position in normalized coordinates (0-1)
  void setPosition(const vec2& pos);
  
  /// @brief Get position in screen coordinates
  vec2 getScreenPosition(int width, int height) const;

  //--

  // Properties
  
  /// @brief Get influence radius (normalized 0-1)
  float getRadius() const;
  
  /// @brief Set influence radius (normalized 0-1)
  void setRadius(float r);
  
  /// @brief Get influence strength (0-1)
  float getInfluenceStrength() const;
  
  /// @brief Set influence strength (0-1)
  void setInfluenceStrength(float strength);

  //--

  // Animation (for particles)
  
  /// @brief Set velocity for particle animation (normalized per second)
  void setVelocity(const vec2& vel);
  
  /// @brief Set angular velocity (degrees per second)
  void setAngularVelocity(float angVel);
  
  /// @brief Set bounds for particle (normalized 0-1)
  void setBounds(const ofRectangle& bounds);
  
  /// @brief Get current rotation angle
  float getAngle() const;

  //--

  // Type & State
  
  /// @brief Get modifier type
  ModifierType getType() const;
  
  /// @brief Check if modifier is active
  bool isActive() const;
  
  /// @brief Set active state
  void setActive(bool active);
  
  /// @brief Set visual color
  void setColor(const ofColor& col);
  
  /// @brief Get visual color
  ofColor getColor() const;

private:
  ModifierType type;
  bool bActive;

  // Position & influence
  vec2 position;           // Normalized 0-1
  float radius;            // Normalized 0-1
  float influenceStrength; // 0-1

  // Animation (for particles)
  vec2 velocity;           // Normalized per second
  float angle;             // Current rotation angle
  float angularVelocity;   // Degrees per second
  ofRectangle bounds;      // Normalized size (width/height)

  // Visual
  ofColor color;
};
