# CONTEXT.md

## ESSENTIAL INFO

- **Main Purpose**: Real-time organic text visualization with animated shapes, trails, and connections
- **Project Type**: openFrameworks C++ creative coding application
- **Current Status**: Active development; core system stable with ongoing feature work

## PROJECT STRUCTURE
- See `FILE-STRUCTURE.md` for detailed file organization and addons.
- Project location: `openframeworks/apps/myApps/TextTypoOrganic02` (platform path may vary).
- Addons live in `openframeworks/addons` and are listed in `addons.make`.

## CORE CLASSES & RESPONSIBILITIES

### OrganicText (PRIMARY CLASS)
- **Text sampling**: `sampleStringPoints()` → outline to point cloud
- **Animation**: `getAnimatedOffset()` with 5 modes (Noise, Wave, Spiral, Pulse, Orbit)
- **Rendering**: `draw()` with layered shapes, connections, trails, outline, debug
- **Data**: `OrganicTextData` centralizes base points, animated cache, trails, metrics
- **Modifiers**: `OrganicTextModifier` handles mouse/particle influence
- **GUI/Presets**: `ofxGui` groups + `ofxSurfingPresetsLite` integration

### ofApp
- App lifecycle and window handling
- Presets browsing, scene switching, and UI mode toggles

## ofxAddons / addons
- `ofxSurfingPresetsLite` (presets + GUI integration)
- `ofxSurfingHelpersLite`, `ofxTweenLite`, `ofxGui`

## KEY PARAMETERS (EXAMPLES)
- **Text & Density**: `sText`, `densitySpacing`, `fontSize`
- **Shapes**: `shapeType`, `shapeSize`, `shapeRotation`, `bDrawFill`
- **Animation**: `animationMode`, `animSpeed`, `animPower`, `animOriginX`
- **Colors**: `colorMode`, `color1/2/3`, `colorMixFactor`, `colorInner`
- **Effects**: `bDrawConnections`, `connectDistance`, `bDrawTrails`, `trailLength`
