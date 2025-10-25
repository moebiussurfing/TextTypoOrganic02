# PROJECT-CONTEXT.md

## ESSENTIAL INFO

**Main Purpose**: Real-time text visualization with organic animations and effects  
**Project Type**: openFrameworks C++ creative coding application
**Current Status**: PRODUCTION READY - All core features implemented

## PROJECT STRUCTURE
```
├── src/
│   ├── main.cpp
│   ├── ofApp.cpp
│   ├── ofApp.h
│   ├── organicText.cpp
│   └── organicText.h
├── addons.make -> ofxAddons Dependencies
	ofxGui
	ofxSurfingHelpersLite
	ofxSurfingPresetsLite
```

## CORE CLASSES & RESPONSIBILITIES

### OrganicText (PRIMARY CLASS)
- **Text sampling**: `sampleStringPoints()` - converts "ARB" text to point cloud
- **Animation**: `calculateAnimation()` - 5 modes (Noise, Wave, Spiral, Pulse, Orbit)  
- **Rendering**: `draw()` - shapes, connections, trails, debug info
- **Colors**: `updateColors()` - global palette with mixing algorithms
- **GUI**: ofxPanel with organized parameter groups
- **Presets**: `loadPreset(0-9)` - instant visual configurations

### ofApp
- Desktop app: Handles application lifecycle and auto-save on exit
- Calls setup(), update(), draw() etc from OrganicText object

## ofxAddons
- The function of the presets manager for designing themes and switching scenes will be handled by the 'ofxSurfingPresetsLite' programme when it is enabled.

## KEY PARAMETERS (all ofParameter<T>)

### VISUAL SCENE
```cpp
// Density - how many points
pointDensity, contourSampling, pointsSpacing

// Shapes  
shapeType, shapeRadius, shapeRotation

// Animation
animationMode, animationSpeed, noiseSize

// Colors
colorMode, globalColor1/2/3 (ofColor), colorMixFactor

// Effects
connectionDistance, trailLength, sceneZoom
```

