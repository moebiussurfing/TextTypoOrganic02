# PROJECT-CONTEXT.md

## ESSENTIAL INFO

- **Main Purpose**: Real-time text visualization with organic animations and effects
- **Project Type**: openFrameworks C++ creative coding application
- **Current Status**: PRODUCTION READY - All core features implemented

## PROJECT STRUCTURE
- See `FILE-STRUCTURE.md` for detailed file organization and addons.
- The used openFrameworks root folder for my system is located into: `D:\OF\of_v0.12.1_release`. We're going to call this folder named as `openframeworks\` too, to keep things simple, but it'll depend on the platform and version you use.
- Current project is located into: `openframeworks\apps\myApps\TextTypoOrganic02`
- For an OF (openFrameworks) project placed into: `openframeworks\apps\myApps\myProject\`.
- Addons (ofxAddons) are located into: `openframeworks\addons\`.

## CORE CLASSES & RESPONSIBILITIES

### OrganicText (PRIMARY CLASS)
- **Text sampling**: `sampleStringPoints()` - converts [MY-TEXT] text to point cloud
- **Animation**: `calculateAnimation()` - points animation using one of 5 modes (Noise, Wave, Spiral, Pulse, Orbit)
- **Rendering**: `draw()` - shapes, connections, trails, debug info
- **Colors**: `updateColors()` - global palette with mixing algorithms
- **GUI**: `ofxPanel` from `ofxGui` with organized parameter groups
- **Presets**: using `ofxSurfingPresetsLite` when enabled for instant visual configurations

### ofApp
- Desktop app: Handles application lifecycle and auto-save on exit
- Calls setup(), update(), draw() etc from `OrganicText` object

## ofxAddons / addons
- The function of the presets manager for designing themes and switching scenes will be handled by the `ofxSurfingPresetsLite` addon when it is enabled.

## KEY PARAMETERS

### VISUAL SCENE
```cpp
// Density - how many points
pointDensity, contourSampling, pointsSpacing...

// Shapes  
shapeType, shapeRadius, shapeRotation...

// Animation
animationMode, animationSpeed, noiseSize...

// Colors
colorMode, globalColor1/2/3 (ofColor), colorMixFactor...

// Effects
connectionDistance, trailLength, sceneZoom...
```