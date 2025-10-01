# Code Architecture - TextTypoOrganic02

## Project Structure

```
src/
├── main.cpp                    # Application entry point
├── ofApp.h/.cpp               # Main application class (minimal wrapper)
├── organicText.h/.cpp         # Core visualization engine  
└── organicTextPresets.h/.cpp  # Preset system definitions
```

## Core Architecture

### Design Principles
- **Modular Design**: Clear separation between app wrapper and core engine
- **Parameter-Driven**: All behavior controlled via ofParameter system
- **Event-Driven**: Efficient updates only when parameters change
- **Performance-Conscious**: Optimized for real-time visualization

### Class Hierarchy

#### `ofApp` (Application Wrapper)
**Purpose**: Minimal openFrameworks lifecycle wrapper
**Responsibilities**:
- Setup, update, draw delegation to OrganicText
- Keyboard event handling
- Application exit with auto-save

```cpp
class ofApp : public ofBaseApp {
    OrganicText organicText;  // Main engine instance
    
    void setup() { organicText.setup(); }
    void update() { organicText.update(); }
    void draw() { organicText.draw(); }
    void keyPressed(int key) { organicText.keyPressed(key); }
    void exit() { organicText.saveSettings(); }
};
```

#### `OrganicText` (Core Engine)
**Purpose**: Complete text visualization system
**Responsibilities**:
- Text sampling and point generation
- Shape rendering and animation
- Color management and mixing
- GUI parameter management
- Settings persistence

```cpp
class OrganicText {
    // Core systems
    ofTrueTypeFont font;
    vector<ofPoint> pointsString;
    ofParameterGroup parameters;
    ofxPanel gui;
    
    // Main functions
    void setup();
    void update();
    void draw();
    void sampleStringPoints();
    void calculateAnimation();
    void updateColors();
};
```

#### `OrganicTextPresets` (Preset System)
**Purpose**: Predefined visual configurations
**Responsibilities**:
- 10 complete scene presets (0-9)
- Preset loading and application
- Parameter value definitions

## Core Systems

### 1. Text Sampling System
**File**: `organicText.cpp::sampleStringPoints()`

**Process**:
1. Load font and render text to get outline
2. Sample points along text contours based on density
3. Apply spacing constraints and filtering
4. Store as vector of screen coordinates

**Key Parameters**:
- `pointDensity`: Controls sampling frequency
- `contourSampling`: Fine-tunes distribution
- `pointsSpacing`: Base distance between points
- `minSpacing`: Minimum allowed distance

### 2. Animation System
**File**: `organicText.cpp::calculateAnimation()`

**Modes**:
- **ANIMATION_NONE**: Static positioning
- **ANIMATION_NOISE**: Perlin noise displacement
- **ANIMATION_WAVE**: Sine wave patterns
- **ANIMATION_SPIRAL**: Rotating spiral motion
- **ANIMATION_PULSE**: Rhythmic pulsing from center
- **ANIMATION_ORBIT**: Orbital movement around center

**Implementation**:
```cpp
switch(animationMode.get()) {
    case ANIMATION_NOISE:
        offset.x = ofNoise(basePos.x * noiseSize + time) * animationSpeed;
        break;
    case ANIMATION_WAVE:
        offset.y = sin(basePos.x * waveFreq + time) * animationSpeed;
        break;
    // ... other modes
}
```

### 3. Color System
**File**: `organicText.cpp::updateColors()`

**Color Modes**:
- **COLOR_GLOBAL_1/2/3**: Individual global colors
- **COLOR_GLOBAL_MIX**: Blend of all three global colors
- **COLOR_DISTANCE**: Distance-based color mixing

**Implementation**:
```cpp
switch(colorMode.get()) {
    case COLOR_GLOBAL_MIX:
        color = globalColor1 * mixFactor + 
                globalColor2 * (1-mixFactor) + 
                globalColor3 * timeFactor;
        break;
    case COLOR_DISTANCE:
        float dist = distance(point, center);
        color = lerp(globalColor1, globalColor2, dist/maxDist);
        break;
}
```

### 4. Rendering System
**File**: `organicText.cpp::draw()`

**Render Pipeline**:
1. Apply scene transformations (zoom, center)
2. Calculate point positions with animation
3. Update colors for current frame
4. Render connections between nearby points
5. Render shapes at each point position
6. Render trails following animated points
7. Optional debug visualization overlay

### 5. GUI Parameter System
**File**: `organicText.cpp::setupParameters()`

**Parameter Groups**:
- **Density Group**: Point sampling controls
- **Shape Group**: Shape type and appearance
- **Colors Group**: Color mode and mixing
- **Global Colors Group**: Base color palette
- **Animation Group**: Animation mode and speed
- **Connections Group**: Connections and trails

**Benefits**:
- Automatic GUI generation from parameters
- Built-in serialization for save/load
- Type safety and range validation
- Event-driven updates

## Performance Considerations

### Optimization Strategies

#### Point Management
- **Spatial Partitioning**: For connection calculations
- **Dirty Flags**: Only recalculate when parameters change
- **Object Pooling**: Reuse trail point objects

#### Rendering Optimization  
- **Batch Drawing**: Group similar operations
- **View Frustum Culling**: Skip off-screen elements
- **LOD System**: Reduce detail at high zoom levels

#### Memory Management
- **Trail Length Limits**: Prevent unbounded growth
- **Periodic Cleanup**: Clear old trail data
- **Smart Allocation**: Pre-allocate common objects

### Performance Metrics
- **Target**: 60 FPS at density 0.5
- **Acceptable**: 30 FPS at density 0.8
- **Memory**: < 100MB for typical usage
- **Startup**: < 3 seconds cold start

## Extension Points

### Adding New Animation Modes
1. Add enum value to `AnimationMode`
2. Implement case in `calculateAnimation()`
3. Add mode-specific parameters if needed
4. Update GUI and presets

### Adding New Shape Types
1. Add enum value to `ShapeType`
2. Implement case in `drawShape()`
3. Add shape-specific parameters
4. Update presets that use shapes

### Adding New Color Modes
1. Add enum value to `ColorMode`
2. Implement case in `updateColors()`
3. Add color-specific parameters
4. Test with existing presets

## Future Architecture Considerations

### Planned Improvements
- **GPU Shader Pipeline**: Move calculations to GPU
- **Multi-threading**: Parallel processing for connections
- **Plugin System**: Modular animation/color systems
- **3D Extension**: Z-axis support for volumetric effects

### Scalability Targets
- **10x Performance**: Via GPU implementation
- **100x Points**: Support for very high density
- **Real-time**: < 16ms frame time guaranteed
- **Memory Efficiency**: < 1MB per 1000 points
