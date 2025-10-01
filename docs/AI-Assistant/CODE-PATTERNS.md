# 💻 CODE PATTERNS - TextTypoOrganic02

## CODING CONVENTIONS & PATTERNS

### NAMING CONVENTIONS
```cpp
// Parameters - camelCase
ofParameter<float> pointDensity;
ofParameter<bool> bDrawShapes;    // booleans start with 'b'
ofParameter<int> shapeType;       // enums are int

// Functions - camelCase  
void sampleStringPoints();
void calculateAnimation();
void updateColors();

// Classes - PascalCase
class OrganicText;
class OrganicTextPresets;

// Enums - UPPER_CASE
enum ShapeType {
    SHAPE_CIRCLE = 0,
    SHAPE_RECTANGLE = 1
};
```

### PARAMETER SETUP PATTERN
```cpp
// 1. Declare in header (.h)
ofParameter<float> yourParameter;
ofParameterGroup yourGroup;

// 2. Setup in setup() function
yourParameter.set("Display Name", defaultValue, minValue, maxValue);
yourGroup.add(yourParameter);
gui.add(yourGroup);

// 3. Use in code
float value = yourParameter.get();
yourParameter.set(newValue);
```

### ANIMATION CALCULATION PATTERN
```cpp
void OrganicText::calculateAnimation() {
    float time = ofGetElapsedTimef() * animationSpeed.get();
    
    for(int i = 0; i < pointsString.size(); i++) {
        ofPoint basePos = pointsString[i];
        ofPoint offset(0, 0);
        
        switch(animationMode.get()) {
            case ANIMATION_YOUR_MODE:
                // Your animation algorithm here
                offset.x = sin(basePos.x * 0.01 + time) * 20;
                offset.y = cos(basePos.y * 0.01 + time) * 20;
                break;
        }
        
        animatedPoints[i] = basePos + offset;
    }
}
```

### COLOR CALCULATION PATTERN
```cpp
ofColor OrganicText::calculatePointColor(int pointIndex, ofPoint position) {
    ofColor color;
    
    switch(colorMode.get()) {
        case COLOR_YOUR_MODE:
            // Your color algorithm here
            float factor = /* calculate based on position, time, etc */;
            color = globalColor1.get().lerp(globalColor2.get(), factor);
            break;
    }
    
    return color;
}
```

### SHAPE DRAWING PATTERN
```cpp
void OrganicText::drawShape(ofPoint position, float size, ofColor color) {
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(position);
    
    switch(shapeType.get()) {
        case SHAPE_YOUR_SHAPE:
            // Your drawing code here
            ofDrawCircle(0, 0, size);
            break;
    }
    
    ofPopMatrix();
}
```

### PRESET DEFINITION PATTERN
```cpp
void OrganicTextPresets::loadPresetYourName() {
    // Reset everything first (optional)
    resetAllParameters();
    
    // Set core parameters
    pointDensity.set(0.6);
    shapeType.set(SHAPE_CIRCLE);
    shapeRadius.set(15);
    
    // Set animation
    animationMode.set(ANIMATION_WAVE);
    animationSpeed.set(2.0);
    
    // Set colors
    globalColor1.set(ofColor(255, 100, 100));  // Red
    globalColor2.set(ofColor(100, 100, 255));  // Blue
    colorMode.set(COLOR_GLOBAL_MIX);
    
    // Set effects
    bDrawConnections.set(true);
    connectionDistance.set(80);
    bDrawTrails.set(false);
}
```

### ERROR HANDLING PATTERN
```cpp
void OrganicText::yourFunction() {
    // Validate inputs
    if(pointsString.empty()) {
        ofLogWarning() << "No points to process";
        return;
    }
    
    // Check parameter ranges
    float density = ofClamp(pointDensity.get(), 0.0, 1.0);
    
    // Safe array access
    if(index >= 0 && index < pointsString.size()) {
        // process pointsString[index]
    }
    
    // Font validation
    if(!font.isLoaded()) {
        ofLogError() << "Font not loaded";
        return;
    }
}
```

### GUI ORGANIZATION PATTERN
```cpp
void OrganicText::setupParameters() {
    // Create groups
    densityGroup.setName("Density");
    shapeGroup.setName("Shape");
    
    // Add parameters to groups
    densityGroup.add(pointDensity);
    densityGroup.add(contourSampling);
    
    shapeGroup.add(shapeType);
    shapeGroup.add(shapeRadius);
    
    // Add groups to main GUI
    gui.add(densityGroup);
    gui.add(shapeGroup);
}
```

### PERFORMANCE OPTIMIZATION PATTERNS
```cpp
// Only recalculate when needed
if(needsResample) {
    sampleStringPoints();
    needsResample = false;
}

// Spatial optimization for connections
if(distance < connectionDistance.get()) {
    // only draw connection if within range
}

// Batch operations
ofSetColor(color);
for(auto& point : points) {
    ofDrawCircle(point, radius);
}
```

### DEBUGGING PATTERNS
```cpp
// Debug output
if(DEBUG_MODE) {
    ofLogNotice() << "Function: " << __FUNCTION__ << " Line: " << __LINE__;
    ofLogNotice() << "Parameter value: " << yourParameter.get();
}

// Visual debug
if(bShowDebug.get()) {
    ofSetColor(255, 0, 0);  // Red for debug
    ofDrawCircle(debugPoint, 5);
    ofDrawBitmapString("Debug: " + ofToString(value), 10, 30);
}

// Performance monitoring
float startTime = ofGetElapsedTimeMillis();
// ... your code ...
float duration = ofGetElapsedTimeMillis() - startTime;
if(duration > 16) {  // > 60 FPS
    ofLogWarning() << "Slow function: " << duration << "ms";
}
```

### OPENFRAMEWORKS SPECIFIC PATTERNS
```cpp
// Vector operations
ofVec2f direction = target - source;
direction.normalize();
direction *= speed;

// Color operations
ofColor result = color1.lerp(color2, factor);
result.setBrightness(brightness);

// Math utilities
float mapped = ofMap(input, inputMin, inputMax, outputMin, outputMax);
float clamped = ofClamp(value, min, max);
float noise = ofNoise(x * scale, y * scale, time);

// Random utilities
float randomFloat = ofRandom(min, max);
int randomInt = ofRandom(count);
```