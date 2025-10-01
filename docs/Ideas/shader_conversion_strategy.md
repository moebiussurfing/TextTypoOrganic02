# Shader Conversion Strategy for OrganicText

This document outlines how to convert the OrganicText generative algorithm from CPU-based processing to GPU-based shaders for massive performance improvements.

## Current CPU Architecture

The current system works as follows:
1. **Text sampling**: Extract point positions from font paths
2. **Animation calculations**: Apply noise/wave/spiral animations to each point
3. **Color calculations**: Compute colors based on position, time, and distance
4. **Shape rendering**: Draw individual shapes (circles, rectangles, etc.) for each point
5. **Connection rendering**: Draw lines between nearby points
6. **Trail rendering**: Track and render point histories

## Proposed GPU/Shader Architecture

### 1. Data Structure Changes

#### Vertex Buffer Objects (VBOs)
```cpp
// Replace vector<vec2> pointsString with:
ofVbo pointsVBO;
ofVbo instanceDataVBO;

struct InstanceData {
    glm::vec2 basePosition;    // Original sampled position
    float pointIndex;          // Index for animations
    float radiusMultiplier;    // Size variation
};
```

#### Texture-based Data Storage
```cpp
// Store point trails and connections in textures
ofFbo trailDataTexture;      // RGB = position, A = age
ofFbo connectionTexture;     // For complex connection patterns
```

### 2. Shader Implementation Strategy

#### Vertex Shader (points.vert)
```glsl
#version 330

// Attributes
in vec2 basePosition;
in float pointIndex;
in float radiusMultiplier;

// Uniforms (from our current parameters)
uniform float time;
uniform float animSpeed;
uniform float noiseSize;
uniform int animationMode;
uniform float waveFrequency;
uniform float waveAmplitude;
uniform float spiralTightness;
uniform float pulseIntensity;
uniform vec2 textCenter;
uniform float sceneZoom;

// Outputs
out float vPointIndex;
out vec2 vAnimatedPosition;
out float vPointSize;

vec2 getAnimatedOffset(vec2 basePos, float index, float phase) {
    if (animationMode == 0) { // ANIM_NOISE
        return vec2(
            snoise(vec2(phase, 0.0)) * noiseSize,
            snoise(vec2(phase, 0.233)) * noiseSize
        );
    } else if (animationMode == 1) { // ANIM_WAVE
        float wave = sin(basePos.x * waveFrequency + time * animSpeed) * waveAmplitude;
        return vec2(0.0, wave);
    } else if (animationMode == 2) { // ANIM_SPIRAL
        vec2 centerDir = basePos - textCenter;
        float angle = atan(centerDir.y, centerDir.x);
        float distance = length(centerDir);
        float spiralOffset = sin(distance * spiralTightness + time * animSpeed) * noiseSize;
        return vec2(cos(angle), sin(angle)) * spiralOffset;
    } else if (animationMode == 3) { // ANIM_PULSE
        vec2 direction = normalize(basePos - textCenter);
        float pulse = sin(time * animSpeed * 2.0) * pulseIntensity;
        return direction * pulse;
    } else if (animationMode == 4) { // ANIM_ORBIT
        vec2 centerDir = basePos - textCenter;
        float angle = atan(centerDir.y, centerDir.x) + time * animSpeed * 0.1;
        float distance = length(centerDir);
        vec2 newPos = textCenter + vec2(cos(angle), sin(angle)) * distance;
        return newPos - basePos;
    }
    return vec2(0.0);
}

void main() {
    float phase = time + 0.123 * pointIndex;
    vec2 animatedOffset = getAnimatedOffset(basePosition, pointIndex, phase);
    vAnimatedPosition = basePosition + animatedOffset;
    
    vPointIndex = pointIndex;
    vPointSize = radiusMultiplier;
    
    // Apply scene zoom and center
    vec2 finalPos = vAnimatedPosition * sceneZoom;
    gl_Position = vec4(finalPos, 0.0, 1.0);
    gl_PointSize = vPointSize * sceneZoom;
}
```

#### Fragment Shader (points.frag)
```glsl
#version 330

// Uniforms for colors
uniform vec3 globalColor1;
uniform vec3 globalColor2;
uniform vec3 globalColor3;
uniform int colorMode;
uniform float colorSpeed;
uniform float colorMixFactor;
uniform float time;
uniform vec2 textCenter;
uniform int shapeType;
uniform bool bFill;

// Inputs
in float vPointIndex;
in vec2 vAnimatedPosition;
in float vPointSize;

out vec4 fragColor;

vec3 getPointColor(vec2 position, float index, float phase) {
    if (colorMode == 0) return globalColor1;
    if (colorMode == 1) return globalColor2;
    if (colorMode == 2) return globalColor3;
    if (colorMode == 3) {
        // Mix all three colors
        float t1 = sin(phase * colorSpeed) * 0.5 + 0.5;
        float t2 = cos(phase * colorSpeed * 1.3) * 0.5 + 0.5;
        vec3 color = mix(globalColor1, globalColor2, t1);
        return mix(color, globalColor3, t2);
    }
    if (colorMode == 4) {
        // Distance-based coloring
        float distance = length(position - textCenter);
        float t = smoothstep(0.0, 200.0, distance);
        return mix(globalColor1, globalColor2, t);
    }
    return globalColor1;
}

void drawShape(vec2 uv, int shape, bool fill) {
    float alpha = 0.0;
    
    if (shape == 0) { // CIRCLE
        float dist = length(uv);
        alpha = fill ? step(dist, 0.5) : smoothstep(0.4, 0.5, dist) - smoothstep(0.5, 0.6, dist);
    } else if (shape == 1) { // RECTANGLE
        vec2 d = abs(uv) - vec2(0.4);
        alpha = fill ? step(max(d.x, d.y), 0.0) : 
                       smoothstep(0.05, 0.0, abs(max(d.x, d.y)));
    } else if (shape == 5) { // POINT
        float dist = length(uv);
        alpha = 1.0 - smoothstep(0.0, 0.3, dist);
    }
    // Add other shapes...
    
    if (alpha < 0.01) discard;
    fragColor.a = alpha;
}

void main() {
    vec2 uv = (gl_PointCoord - 0.5) * 2.0; // -1 to 1
    
    float phase = time + 0.123 * vPointIndex;
    vec3 color = getPointColor(vAnimatedPosition, vPointIndex, phase);
    
    fragColor = vec4(color, 1.0);
    drawShape(uv, shapeType, bFill);
}
```

#### Connection Shader (connections.geom)
```glsl
#version 330
layout(points) in;
layout(line_strip, max_vertices = 64) out;

uniform float connectionDistance;
uniform sampler2D pointPositions; // All point positions
uniform int numPoints;

void main() {
    vec2 currentPos = gl_in[0].gl_Position.xy;
    
    for (int i = 0; i < numPoints; i++) {
        vec2 otherPos = texelFetch(pointPositions, ivec2(i, 0), 0).xy;
        float dist = distance(currentPos, otherPos);
        
        if (dist < connectionDistance && dist > 0.0) {
            gl_Position = vec4(currentPos, 0.0, 1.0);
            EmitVertex();
            gl_Position = vec4(otherPos, 0.0, 1.0);
            EmitVertex();
            EndPrimitive();
        }
    }
}
```

### 3. C++ Implementation Changes

#### New GPU-based OrganicText class structure:
```cpp
class OrganicTextGPU {
private:
    // GPU resources
    ofVbo pointsVBO;
    ofShader pointShader;
    ofShader connectionShader;
    ofFbo renderTarget;
    
    // Point data
    vector<InstanceData> pointData;
    
    // Uniforms (keep existing ofParameter system)
    // All existing parameters remain the same!
    
public:
    void setupGPU();
    void updateUniforms();
    void drawGPU();
};
```

#### Implementation:
```cpp
void OrganicTextGPU::setupGPU() {
    // Convert existing pointsString to GPU format
    pointData.clear();
    for (int i = 0; i < pointsString.size(); i++) {
        InstanceData data;
        data.basePosition = pointsString[i];
        data.pointIndex = i;
        data.radiusMultiplier = ofRandom(0.5, 1.0);
        pointData.push_back(data);
    }
    
    // Upload to VBO
    pointsVBO.setVertexData(&pointData[0], pointData.size(), GL_STATIC_DRAW);
    pointsVBO.setVertexAttribute(0, 2, GL_FLOAT, false, sizeof(InstanceData), 0); // basePosition
    pointsVBO.setVertexAttribute(1, 1, GL_FLOAT, false, sizeof(InstanceData), 8); // pointIndex
    pointsVBO.setVertexAttribute(2, 1, GL_FLOAT, false, sizeof(InstanceData), 12); // radiusMultiplier
    
    // Load shaders
    pointShader.load("shaders/points.vert", "shaders/points.frag");
}

void OrganicTextGPU::updateUniforms() {
    pointShader.begin();
    pointShader.setUniform1f("time", t);
    pointShader.setUniform1f("animSpeed", animSpeed.get());
    pointShader.setUniform1f("noiseSize", noiseSize.get());
    pointShader.setUniform1i("animationMode", animationMode.get());
    pointShader.setUniform3f("globalColor1", globalColor1.get().r/255.0f, globalColor1.get().g/255.0f, globalColor1.get().b/255.0f);
    // ... all other uniforms
    pointShader.end();
}

void OrganicTextGPU::drawGPU() {
    updateUniforms();
    
    pointShader.begin();
    pointsVBO.draw(GL_POINTS, 0, pointData.size());
    pointShader.end();
}
```

## Performance Improvements Expected

### Massive Performance Gains:

1. **Point Processing**: 
   - CPU: ~1,000 points at 60fps = limited by CPU single-thread performance
   - GPU: ~100,000+ points at 60fps = parallel processing on thousands of cores

2. **Animation Calculations**:
   - CPU: Serial processing of each point's animation
   - GPU: All points animated simultaneously in parallel

3. **Color Calculations**:
   - CPU: Individual color computation per point
   - GPU: Parallel color computation for all points

4. **Memory Bandwidth**:
   - CPU: RAM access with higher latency
   - GPU: Ultra-fast VRAM access optimized for parallel operations

### Estimated Performance Multiplier:
- **10x to 100x more points** possible
- **Higher frame rates** with complex animations
- **Real-time parameter changes** without frame drops
- **Complex visual effects** that were impossible before

## Migration Strategy

### Phase 1: Basic GPU conversion
1. Convert point rendering to instanced drawing
2. Move animations to vertex shader
3. Keep existing UI system unchanged

### Phase 2: Advanced GPU features
1. Add geometry shader for connections
2. Implement GPU-based trails using transform feedback
3. Add post-processing effects

### Phase 3: Full GPU pipeline
1. Generate text samples on GPU
2. Dynamic point generation based on zoom level
3. Advanced particle effects and physics

## Benefits of This Approach

1. **UI Preservation**: All existing ofParameter GUI controls remain identical
2. **Feature Parity**: All current features can be replicated on GPU
3. **Extensibility**: Opens door for advanced effects impossible on CPU
4. **Future-Proof**: Modern approach that will scale with better hardware

The shader approach would transform this from a CPU-bound visualization into a massively parallel GPU-accelerated system while maintaining the exact same user interface and parameter system!