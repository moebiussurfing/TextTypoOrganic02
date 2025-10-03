# 🚀 QUICK COMMANDS - For AI Assistants

## FREQUENT DEVELOPMENT TASKS

### BUILD & RUN
```bash
# Build (in Visual Studio or command line)
msbuild TextTypoOrganic02.vcxproj /p:Configuration=Release

# Run
./bin/TextTypoOrganic02.exe
```

### TESTING PRESETS
```cpp
// Test all presets work
for(int i = 0; i <= 9; i++) {
    loadPreset(i);
    // verify no crashes, visual looks correct
}
```

### ADD NEW PRESET
```cpp
// 1. In organicTextPresets.h - add declaration:
void loadPreset11();

// 2. In organicTextPresets.cpp - implement:
void OrganicTextPresets::loadPreset11() {
    pointDensity.set(0.6);
    shapeType.set(SHAPE_CIRCLE);
    animationMode.set(ANIMATION_WAVE);
    globalColor1.set(ofColor::red);
    // ... set all parameters
}

// 3. In organicText.cpp keyPressed() - add case:
case '11': loadPreset(11); break;
```

### ADD NEW ANIMATION MODE
```cpp
// 1. In organicText.h - add to enum:
enum AnimationMode {
    ANIMATION_NONE = 0,
    // ... existing modes
    ANIMATION_YOUR_NEW_MODE = 6
};

// 2. In organicText.cpp calculateAnimation() - add case:
case ANIMATION_YOUR_NEW_MODE:
    offset.x = /* your algorithm */;
    offset.y = /* your algorithm */;
    break;

// 3. Update GUI dropdown in setupParameters()
```

### ADD NEW SHAPE TYPE
```cpp
// 1. In organicText.h - add to enum:
enum ShapeType {
    // ... existing shapes
    SHAPE_YOUR_NEW_SHAPE = 6
};

// 2. In organicText.cpp drawShape() - add case:
case SHAPE_YOUR_NEW_SHAPE:
    // your drawing code
    break;
```

### COMMON PARAMETER PATTERNS
```cpp
// Boolean toggle
ofParameter<bool> bYourFeature;
bYourFeature.set("Your Feature", true);

// Ranged float
ofParameter<float> yourValue;
yourValue.set("Your Value", 0.5, 0.0, 1.0);

// Color picker
ofParameter<ofColor> yourColor;
yourColor.set("Your Color", ofColor::white);

// Add to parameter group
yourGroup.add(bYourFeature);
yourGroup.add(yourValue);
yourGroup.add(yourColor);
```

### DEBUG COMMON ISSUES
```cpp
// Check parameter values
ofLogNotice() << "pointDensity: " << pointDensity.get();

// Check point count
ofLogNotice() << "Points: " << pointsString.size();

// Verify font loaded
if(!font.isLoaded()) {
    ofLogError() << "Font not loaded!";
}

// Check performance
float fps = ofGetFrameRate();
if(fps < 30) ofLogWarning() << "Low FPS: " << fps;
```

### KEYBOARD SHORTCUTS (for testing)
- **0-9**: Load presets
- **R**: Reset all parameters  
- **T**: Toggle trails
- **L**: Toggle connections
- **←/→**: Zoom in/out
- **↑/↓**: Animation speed
- **Ctrl+S**: Save settings

### PARAMETER GROUPS
```cpp
// Main groups (see setupParameters())
densityGroup     // Point sampling controls
shapeGroup       // Shape appearance  
colorsGroup      // Color mixing
globalColorsGroup // Color palette
animationGroup   // Animation controls
connectionsGroup // Lines and trails
```

### PERFORMANCE TIPS
- Keep `pointDensity` < 0.7 for smooth 60 FPS
- Reduce `connectionDistance` if frame rate drops
- Shorter `trailLength` uses less memory
- Use Release build for testing performance

### FILES TO MODIFY MOST OFTEN
1. **`src/organicText.cpp`** - Core functionality
2. **`src/organicTextPresets.cpp`** - New presets
3. **`src/organicText.h`** - Add new parameters/enums
4. **`docs/TODO/Current-Tasks.md`** - Update task list