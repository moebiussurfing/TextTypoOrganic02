#pragma once

#include "ofMain.h"

using namespace glm;

/// @brief Centralized data storage for OrganicText point management
/// Manages base points, trails, animated cache, and text metrics
class OrganicTextData {
public:
  OrganicTextData();
  ~OrganicTextData();

  //--

  // Setters
  
  /// @brief Set the base points sampled from text outline
  void setBasePoints(const std::vector<vec2>& points);
  
  /// @brief Initialize trail buffers with specified length per point
  void initTrails(int trailLength);
  
  /// @brief Update a single trail point position
  void updateTrailPoint(std::size_t pointIndex, const vec2& position);
  
  /// @brief Set cached animated position for a specific point
  void setCachedAnimatedPoint(std::size_t index, const vec2& position);
  
  /// @brief Set text metrics (width, height, center)
  void setTextMetrics(float width, float height, const vec2& center);

  //--

  // Getters
  
  /// @brief Get const reference to base points
  const std::vector<vec2>& getBasePoints() const;
  
  /// @brief Get const reference to trail data
  const std::vector<std::vector<vec2>>& getTrails() const;
  
  /// @brief Get const reference to animated cache
  const std::vector<vec2>& getAnimatedCache() const;
  
  /// @brief Get mutable reference to animated cache for direct updates
  std::vector<vec2>& getAnimatedCacheMutable();
  
  /// @brief Get total number of base points
  std::size_t getPointCount() const;
  
  /// @brief Get calculated text center
  vec2 getTextCenter() const;
  
  /// @brief Get text width
  float getTextWidth() const;
  
  /// @brief Get text height
  float getTextHeight() const;

  //--

  // Utilities
  
  /// @brief Clear all data structures
  void clear();
  
  /// @brief Resize animated cache to match point count
  void resizeCache(std::size_t size);
  
  /// @brief Check if data is valid (has points)
  bool isValid() const;

private:
  std::vector<vec2> pointsString;
  std::vector<std::vector<vec2>> pointTrails;
  std::vector<vec2> pointsAnimatedCache;
  
  vec2 textCenter;
  float textWidth;
  float textHeight;
};
