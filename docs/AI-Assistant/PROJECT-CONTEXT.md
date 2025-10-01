# 🤖 PROJECT CONTEXT - TextTypoOrganic02

## ESSENTIAL INFO FOR AI ASSISTANTS

**Project Type**: openFrameworks C++ creative coding application  
**Current Status**: ✅ PRODUCTION READY - All core features implemented  
**Main Purpose**: Real-time text visualization with organic animations and effects  

## PROJECT STRUCTURE
```
src/
├── main.cpp                 # Entry point
├── ofApp.h/.cpp            # Wrapper (delegates to OrganicText)
├── organicText.h/.cpp      # CORE ENGINE (main work here)
└── organicTextPresets.h/.cpp # 10 visual presets (0-9 keys)
```

## CORE CLASSES & RESPONSIBILITIES

### `OrganicText` (PRIMARY CLASS - 90% of functionality)
- **Text sampling**: `sampleStringPoints()` - converts "ARB" text to point cloud
- **Animation**: `calculateAnimation()` - 5 modes (Noise, Wave, Spiral, Pulse, Orbit)  
- **Rendering**: `draw()` - shapes, connections, trails, debug info
- **Colors**: `updateColors()` - global palette with mixing algorithms
- **GUI**: ofxPanel with organized parameter groups
- **Presets**: `loadPreset(0-9)` - instant visual configurations

### `ofApp` (WRAPPER - minimal functionality)
- Just delegates setup(), update(), draw(), keyPressed() to OrganicText
- Handles application lifecycle and auto-save on exit

## KEY PARAMETERS (all ofParameter<T>)
```cpp
// Density - how many points
pointDensity (0-1), contourSampling (0-1), pointsSpacing (1-50)

// Shapes  
shapeType (enum 0-5), shapeRadius (1-50), shapeRotation (0-360)

// Animation
animationMode (enum 0-5), animationSpeed (0-5), noiseSize (0.001-0.1)

// Colors
colorMode (enum 0-4), globalColor1/2/3 (ofColor), colorMixFactor (0-1)

// Effects
connectionDistance (10-200), trailLength (5-100), sceneZoom (0-1 → 1x-5x)
```

## CURRENT STATE
- ✅ Zero compilation errors
- ✅ 10 working presets (number keys 0-9)
- ✅ All features implemented and stable
- ✅ Settings auto-save/load
- ✅ Complete documentation

## IMMEDIATE TODO (see /TODO/Current-Tasks.md)
- Add code comments to complex functions
- Add input validation  
- GUI tooltips for parameters
- Version display and FPS counter

## COMMON MODIFICATIONS
- **New preset**: Add to `organicTextPresets.cpp`, define parameter values
- **New animation**: Add enum to `AnimationMode`, implement in `calculateAnimation()`
- **New shape**: Add enum to `ShapeType`, implement in `drawShape()`
- **GUI changes**: Modify parameter groups in `setupParameters()`

## BUILD REQUIREMENTS
- openFrameworks 0.12.1
- Visual Studio 2019+
- Font file: `bin/data/NotoSansMono-Regular.ttf`
- Windows only (current build)

## FOR AI ASSISTANTS: MOST USEFUL FILES
1. **`/AI-Assistant/QUICK-COMMANDS.md`** - Common operations
2. **`/TODO/Current-Tasks.md`** - What needs to be done NOW
3. **`/Developer/Architecture.md`** - Detailed code structure
4. **`src/organicText.h`** - Main class interface