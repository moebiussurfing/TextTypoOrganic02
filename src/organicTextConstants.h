#pragma once

// ============================================================================
// ORGANIC TEXT - CONSTANTS DEFINITIONS
// ============================================================================
// All constant values used across the OrganicText class
// Separated for better code organization and maintainability
// ============================================================================

#define FIX_ORGANIC_TEXT_TWEEN_TRAILS_PROBLEMS // Draw weird glitches/problems when tweeing between presets..

//----------------------------------------------------------------------------
// OFAPP CONSTANTS
//----------------------------------------------------------------------------

#define OFWORKS_DEMO_APP_DISTRIBUTION // Uncomment for the deployment release version

//---

// Window title
const std::string OFWORKS_DEMO_APP_TITLE = "organicText v0.2";

// Window size

// Custom size
constexpr int OFWORKS_DEMO_APP_WIDTH = 1920;
constexpr int OFWORKS_DEMO_APP_HEIGHT = 1080;

// Default text
constexpr const char * ORGANIC_TEXT_DEFAULT_STRING = "ofWorks";

// Default font
#if 1
constexpr const char * ORGANIC_TEXT_FONT_DEFAULT = "fonts/GeistMono-Medium.ttf";
// constexpr const std::string ORGANIC_TEXT_FONT_DEFAULT = "NotoSansMono-Regular.ttf";
#else
	// Bundled OF fonts
	// ttf file not required
	#include "ofMain.h"
constexpr const char * ORGANIC_TEXT_FONT_DEFAULT = OF_TTF_SANS;
//constexpr const char * = OF_TTF_SERIF;
//constexpr const char * = OF_TTF_MONO;
#endif

//----------------------------------------------------------------------------
// DRAWING & ANIMATION CONSTANTS
//----------------------------------------------------------------------------

constexpr float ORGANIC_TEXT_FPS = 60.f;
//constexpr float ORGANIC_TEXT_FPS = 120.f;

constexpr float ZOOM_GLOBAL_SCALE_MIN = 0.2f;
constexpr float ZOOM_GLOBAL_SCALE_MAX = 2.1f; // QHD 2K calibrated aprox
constexpr float ZOOM_GLOBAL_AUTO_PADDING = 200.0f; // Pixels

// Density Constants
constexpr float DENSITY_SPACING_MIN = 1.5f;
constexpr float DENSITY_SPACING_MAX = 50.0f;

// Animation Displacement Constants
constexpr float ANIM_NOISE_MAX = 35.0f;
constexpr float ANIM_WAVE_MAX = 60.0f;
constexpr float ANIM_SPIRAL_MAX = 45.0f;
constexpr float ANIM_PULSE_MAX = 40.0f;

// Animation Frequency Constants
constexpr float ANIM_WAVE_FREQ_MIN = 0.001f;
constexpr float ANIM_WAVE_FREQ_MAX = 0.04f;
constexpr float ANIM_SPIRAL_TIGHT_MIN = 0.002f;
constexpr float ANIM_SPIRAL_TIGHT_MAX = 0.025f;
constexpr float ANIM_SPEED_MAX = 8.f;

// Time System
constexpr float BASE_TIME_STEP = 0.008f;

// Color Constants
constexpr float COLOR_DISTANCE_MAX = 250.0f;
constexpr float COLOR_DISTANCE_INNER = 0.4f;
constexpr float COLOR_DISTANCE_MIDDLE = 0.7f;
constexpr float COLOR_ALPHA_CENTER = 255.0f;
constexpr float COLOR_ALPHA_EDGE = 80.0f;

// Connection Constants
constexpr int CONNECTIONS_SEARCH_NEAR = 50;
constexpr int CONNECTIONS_SEARCH_FAR = 100;
constexpr int CONNECTIONS_MAX_PER_POINT_NEAR = 3;
constexpr int CONNECTIONS_MAX_PER_POINT_FAR = 8;
constexpr float CONNECTIONS_MAX_LINE_WIDTH = 3.f;

// Trails Constants
constexpr float TRAILS_ALPHA_MAX = 255.0f; // Full alpha range
constexpr float TRAILS_LINE_WIDTH_MAX = 5.f; // Line width
constexpr float TRAILS_LENGTH_MIN = 3.f; // Amount trails per group
constexpr float TRAILS_LENGTH_MAX = 100.f; // Amount trails per group - longer trails
constexpr float TRAILS_FADE_MIN = 0.5f; // More transparent at minimum
constexpr float TRAILS_FADE_MAX = 1.0f; // Fully opaque at maximum

// Shape Constants
constexpr float SHAPE_MAX_RADIUS = 50.0f;
constexpr float SHAPE_MIN_RADIUS = 0.0f;
constexpr float SHAPE_ROTATION_SPEED = 0.2f;
constexpr float SHAPE_SIZE_NOISE_SCALE = 0.5f;
constexpr float SHAPE_SIZE_INDEX_SCALE = 0.01f;

// Debug Constants
constexpr int DEBUG_ALPHA_MAX = 48;
constexpr int DEBUG_ALPHA_MIN_OFFSET = 16;
constexpr float DEBUG_SPEED = .2f;

// Outline Constants
constexpr float OUTLINE_WIDTH_BASE = 0.5f;
constexpr float OUTLINE_THICKNESS_MAX = 10.0f;

// Mouse Interaction Constants
constexpr float MOUSE_RADIUS_INTERACT_MAX = 100.0f;
constexpr float MOUSE_RADIUS_INTERACT_MIN = 10.0f;
constexpr float MAX_SCALE_POWER = 3.0f;

// Line Tweaks Constants
constexpr float LINE_TWEAKS_EDGE_PAD = 0.18f; // Extra pad outside text width (fraction)

//----------------------------------------------------------------------------
// ENUMERATIONS
//----------------------------------------------------------------------------

enum ShapeType {
	SHAPE_CIRCLE = 0,
	SHAPE_RECTANGLE = 1,
	SHAPE_TRIANGLE = 2,
	SHAPE_STAR = 3,
	SHAPE_CROSS = 4,
	SHAPE_POINT = 5
};

enum ColorMode {
	COLOR_GLOBAL_1 = 0,
	COLOR_GLOBAL_2 = 1,
	COLOR_GLOBAL_3 = 2,
	COLOR_GLOBAL_MIX = 3,
	COLOR_DISTANCE = 4
};

enum AnimMode {
	ANIM_NOISE = 0,
	ANIM_WAVE = 1,
	ANIM_SPIRAL = 2,
	ANIM_PULSE = 3,
	ANIM_ORBIT = 4
};
