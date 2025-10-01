# API Reference - TextTypoOrganic02

## Core Classes

### OrganicText Class

Main visualization engine that handles all text processing, animation, and rendering.

#### Public Methods

##### Setup & Lifecycle
```cpp
void setup()
```
Initializes the organic text system, loads fonts, sets up GUI, and configures default parameters.

```cpp
void update()  
```
Updates animations, colors, and other time-based parameters each frame.

```cpp
void draw()
```
Renders the complete visualization including shapes, connections, trails, and debug info.

```cpp
void keyPressed(int key)
```
Handles keyboard input for presets, toggles, and parameter adjustments.
- **key**: ASCII code of pressed key

```cpp
void saveSettings()
```
Saves current parameter values to JSON file for persistence.

```cpp
void loadSettings()
```
Loads previously saved parameter values from JSON file.

##### Preset System
```cpp
void loadPreset(int presetNumber)
```
Loads a complete visual preset configuration.
- **presetNumber**: Integer 0-9 corresponding to built-in presets

#### Core Processing Methods

##### Text Sampling
```cpp
void sampleStringPoints()
```
**Purpose**: Extracts points from text outline based on current density settings
**Process**:
1. Renders text to get outline polylines
2. Samples points along contours based on density
3. Applies spacing constraints
4. Stores result in `pointsString` vector

**Affected by parameters**:
- `pointDensity` (0-1): Controls sampling frequency  
- `contourSampling` (0-1): Fine-tunes distribution
- `pointsSpacing` (1-50): Base spacing between points
- `minSpacing` (1-20): Minimum allowed distance

##### Animation Calculation
```cpp
void calculateAnimation()
```
**Purpose**: Calculates animated positions for all points based on current animation mode
**Animation Modes**:
- `ANIMATION_NONE`: Static positioning
- `ANIMATION_NOISE`: Perlin noise displacement
- `ANIMATION_WAVE`: Sine wave patterns  
- `ANIMATION_SPIRAL`: Rotating spiral motion
- `ANIMATION_PULSE`: Rhythmic pulsing from center
- `ANIMATION_ORBIT`: Orbital movement around center

**Affected by parameters**:
- `animationMode`: Which algorithm to use
- `animationSpeed` (0-5): Overall animation rate
- `noiseSize` (0.001-0.1): Scale for noise-based animations

##### Color System
```cpp
void updateColors()
```
**Purpose**: Calculates colors for all visual elements based on current color mode
**Color Modes**:
- `COLOR_GLOBAL_1/2/3`: Individual global colors
- `COLOR_GLOBAL_MIX`: Blend of all three global colors
- `COLOR_DISTANCE`: Mix colors based on distance from center

**Affected by parameters**:
- `colorMode`: Which color algorithm to use
- `colorSpeed` (0-5): Rate of color transitions
- `colorMixFactor` (0-1): Blend amount between colors
- `globalColor1/2/3`: Base color palette

#### Rendering Methods

##### Shape Drawing
```cpp
void drawShape(ofPoint position, float size, ofColor color)
```
**Purpose**: Renders individual shape at specified position
**Parameters**:
- **position**: Screen coordinates for shape center
- **size**: Shape dimensions (radius for circles, side length for squares)
- **color**: RGBA color for the shape

**Shape Types**:
- `SHAPE_CIRCLE`: Filled circle
- `SHAPE_RECTANGLE`: Filled rectangle
- `SHAPE_TRIANGLE`: Filled triangle with adjustable ratio
- `SHAPE_STAR`: 5-pointed star
- `SHAPE_CROSS`: Plus-sign cross
- `SHAPE_POINT`: Simple point/pixel

##### Connection System
```cpp
void drawConnections()
```
**Purpose**: Draws lines between nearby points based on distance threshold
**Algorithm**:
1. For each point, check all other points
2. If distance < connectionDistance, draw line
3. Apply alpha based on distance (closer = more opaque)

**Performance**: O(n²) complexity - expensive with many points

##### Trail System
```cpp
void updateTrails()
void drawTrails()
```
**Purpose**: Creates particle trails following animated points
**Process**:
1. `updateTrails()`: Adds current positions to trail history
2. `drawTrails()`: Renders trail points with fading alpha

**Parameters**:
- `trailLength` (5-100): Number of trail points per shape
- `trailFade` (0.8-0.99): How quickly trails fade

#### Debug Visualization
```cpp
void drawDebugInfo()
```
**Purpose**: Renders technical overlay showing algorithm internals
**Displays**:
- Original sample points from text
- Bounding boxes and coordinate system
- Current parameter values
- Performance metrics

## Parameter System

### Parameter Groups

All parameters use openFrameworks `ofParameter` system for automatic GUI generation and serialization.

#### Density Parameters
```cpp
ofParameter<float> pointDensity;        // 0-1, default 0.5
ofParameter<float> contourSampling;     // 0-1, default 0.8  
ofParameter<float> pointsSpacing;       // 1-50, default 10
ofParameter<float> minSpacing;          // 1-20, default 5
```

#### Shape Parameters
```cpp
ofParameter<int> shapeType;             // 0-5, see ShapeType enum
ofParameter<float> shapeRadius;         // 1-50, default 10
ofParameter<float> triangleRatio;       // 0.5-2, default 1
ofParameter<float> shapeRotation;       // 0-360, default 0
ofParameter<bool> bDrawShapes;          // true/false
ofParameter<bool> bFill;                // true/false
```

#### Color Parameters
```cpp
ofParameter<int> colorMode;             // 0-4, see ColorMode enum
ofParameter<float> colorSpeed;          // 0-5, default 1
ofParameter<float> colorMixFactor;      // 0-1, default 0.5
ofParameter<ofColor> globalColor1;      // RGB color
ofParameter<ofColor> globalColor2;      // RGB color  
ofParameter<ofColor> globalColor3;      // RGB color
```

#### Animation Parameters
```cpp
ofParameter<int> animationMode;         // 0-5, see AnimationMode enum
ofParameter<float> animationSpeed;      // 0-5, default 1
ofParameter<float> noiseSize;           // 0.001-0.1, default 0.01
```

#### Connection Parameters
```cpp
ofParameter<bool> bDrawConnections;     // true/false
ofParameter<float> connectionDistance;  // 10-200, default 50
ofParameter<int> connectionAlpha;       // 0-255, default 100
ofParameter<bool> bDrawTrails;          // true/false
ofParameter<int> trailLength;           // 5-100, default 20
ofParameter<float> trailFade;           // 0.8-0.99, default 0.95
```

### Enumerations

#### ShapeType
```cpp
enum ShapeType {
    SHAPE_CIRCLE = 0,      // Filled circle
    SHAPE_RECTANGLE = 1,   // Filled rectangle
    SHAPE_TRIANGLE = 2,    // Filled triangle
    SHAPE_STAR = 3,        // 5-pointed star
    SHAPE_CROSS = 4,       // Plus-sign cross
    SHAPE_POINT = 5        // Simple point
};
```

#### AnimationMode  
```cpp
enum AnimationMode {
    ANIMATION_NONE = 0,    // Static positioning
    ANIMATION_NOISE = 1,   // Perlin noise displacement
    ANIMATION_WAVE = 2,    // Sine wave patterns
    ANIMATION_SPIRAL = 3,  // Rotating spiral motion
    ANIMATION_PULSE = 4,   // Rhythmic pulsing
    ANIMATION_ORBIT = 5    // Orbital movement
};
```

#### ColorMode
```cpp
enum ColorMode {
    COLOR_GLOBAL_1 = 0,    // Use globalColor1 only
    COLOR_GLOBAL_2 = 1,    // Use globalColor2 only  
    COLOR_GLOBAL_3 = 2,    // Use globalColor3 only
    COLOR_GLOBAL_MIX = 3,  // Blend all three colors
    COLOR_DISTANCE = 4     // Distance-based mixing
};
```

## Data Structures

### Core Data Members
```cpp
class OrganicText {
private:
    // Text processing
    ofTrueTypeFont font;               // Loaded font for text rendering
    vector<ofPoint> pointsString;      // Sampled points from text
    vector<ofPoint> animatedPoints;    // Current animated positions
    
    // GUI system
    ofxPanel gui;                      // Main parameter panel
    ofParameterGroup parameters;       // All parameters grouped
    
    // Rendering state
    vector<vector<ofPoint>> trails;    // Trail history for each point
    ofColor currentColors[MAX_POINTS]; // Current color for each point
    
    // Performance
    bool needsResample;                // Flag to recalculate points
    float lastUpdateTime;              // For animation timing
};
```

### Performance Considerations

#### Computational Complexity
- **Point Sampling**: O(n) where n = text outline length
- **Animation**: O(p) where p = number of points
- **Connections**: O(p²) - most expensive operation  
- **Trails**: O(p × trail_length)

#### Memory Usage
- **Base**: ~1MB for typical configuration
- **Points**: ~24 bytes per point (position + color + trail)
- **Trails**: ~8 bytes × trail_length × point_count
- **GUI**: ~100KB for parameter system

#### Optimization Tips
- Keep `pointDensity` < 0.7 for smooth performance
- Reduce `connectionDistance` if frame rate drops
- Shorter `trailLength` reduces memory usage
- Disable connections entirely for maximum performance

## Extension Guidelines

### Adding New Animation Modes
1. **Add enum value** to `AnimationMode`
2. **Implement algorithm** in `calculateAnimation()` switch statement
3. **Add parameters** if needed (follow naming convention)
4. **Update presets** to use new mode
5. **Test performance** with high point densities

### Adding New Shape Types
1. **Add enum value** to `ShapeType`
2. **Implement rendering** in `drawShape()` switch statement  
3. **Add shape-specific parameters** if needed
4. **Update GUI** to show new option
5. **Test with all presets**

### Adding New Color Modes
1. **Add enum value** to `ColorMode`
2. **Implement algorithm** in `updateColors()` switch statement
3. **Add color-specific parameters** if needed
4. **Ensure compatibility** with existing presets
5. **Test visual quality** across different scenarios

For more implementation details, see the Architecture documentation.