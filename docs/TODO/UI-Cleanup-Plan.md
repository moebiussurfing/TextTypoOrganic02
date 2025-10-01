# UI Parameter Cleanup Plan - TextTypoOrganic02

## 1. REMOVE UNUSED ENABLE PARAMETERS
✅ Analysis shows these bEnable* are used but could be simplified:
- bEnableDensity - Only used in conditional checks, can be removed
- bEnableShape - Only used in conditional checks, can be removed  
- bEnableColor - Only used in conditional checks, can be removed
- bEnableGlobalColor - Only used in conditional checks, can be removed
- bEnableAnimationGroup - Redundant with bEnableAnimation

## 2. SIMPLIFY PARAMETER NAMES (Gaming UI Style)

### Current → New Names:
**Basic:**
- sceneZoom → "Zoom"
- bDrawShapes → "Draw"  
- bEnableAnimation → "Animate"
- bDrawOutline → "Outline"
- bDrawFill → "Fill"

**Density:**
- pointDensity → "Density"
- pointsSpacing → "Spacing" 
- minSpacing → "Min Gap"
- contourSampling → "Sampling"

**Shape:**
- shapeType → "Type"
- pointRadius → "Size"
- pointsRadiusMin → "Min Size"
- triangleRatio → "Ratio"
- shapeRotation → "Rotation"

**Colors:** (Remove "Color" prefix since in Colors group)
- colorMode → "Mode"
- colorSpeed → "Speed" 
- colorMixFactor → "Mix"
- globalColor1 → "Color 1"
- globalColor2 → "Color 2"
- globalColor3 → "Color 3"

**Animation:** (Normalize 0-1, generic names)
- animationMode → "Mode"
- animSpeed → "Speed"
- noiseSize → "Power" (0-1)
- waveFrequency → "Wave" (0-1)
- waveAmplitude → "Intensity" (0-1) 
- spiralTightness → "Spiral" (0-1)
- pulseIntensity → "Pulse" (0-1)

**Connections:**
- bDrawConnections → "Draw"
- connectionDistance → "Distance"
- connectionAlpha → "Alpha"
- bDrawTrails → "Trails"

## 3. UNIVERSAL BUTTON NAMES
- All "Reset X" → "Reset"
- All "Random X" → "Random"

## 4. ADD MODE NAME STRINGS
Add string parameters showing current mode name:
- shapeTypeName (Circle, Rectangle, etc.) - setSerializable(false)
- animationModeName (Noise, Wave, etc.) - setSerializable(false)
- colorModeName (Global 1, Mix, etc.) - setSerializable(false)

## 5. ADD NEW COLOR PARAMETERS
- outlineColor - Color for text outline drawing
- connectionColor - Color for connection lines

## 6. OPTIMIZE CONNECTIONS PERFORMANCE  
- Add connectionQuality parameter (0-1) to reduce line count
- Implement connection interpolation/culling

## 7. NORMALIZE ANIMATION PARAMETERS
All animation-specific params should be 0-1 range and shared between modes where possible.