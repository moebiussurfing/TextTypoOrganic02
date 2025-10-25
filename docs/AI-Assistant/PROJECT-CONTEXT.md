# PROJECT-CONTEXT.md

## ESSENTIAL INFO

- **Main Purpose**: Real-time text visualization with organic animations and effects
- **Project Type**: openFrameworks C++ creative coding application
- **Current Status**: PRODUCTION READY - All core features implemented

## PROJECT STRUCTURE
- The used openFrameworks root folder for my system is located into: `D:\OF\of_v0.12.1_vs_64_release`. We're going to call this folder named as `openframeworks\` too, to keep things simple, but it'll depend on the platform and version you use.
- Current project is located into: `openframeworks\apps\myApps\TextTypoOrganic02`
- For an OF (openFrameworks) project placed into: `openframeworks\apps\myApps\myProject\`.
- Addons (ofxAddons) are located into: `openframeworks\addons\`.

```
TextTypoOrganic02/
├── src/
│   ├── main.cpp			# main app
│   ├── ofApp.cpp			# main app
│   ├── ofApp.h				# main app
│   ├── organicText.cpp 	# our main class
│   └── organicText.h		# our main class
├── addons.make -> named addons (ofxAddons) dependencies
	# OF Project Generator will include:
	\ofxGui 					# UI lib
	\ofxSurfingPresetsLite 	# presets manager
	\ofxSurfingHelpersLite 	# required helpers
```

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

### VISUAL SCENE  (all ofParameter<T>)
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

