# TextTypoOrganic02

An enhanced openFrameworks application that creates organic, animated visualizations from text using customizable shapes, colors, and animations.

*Enhanced version based on original code from [PFAD/examples/week_5/organicTypographyWorked](https://github.com/colormotor/PFAD/tree/main/examples/week_5/organicTypographyWorked)*

## Features

### Core Functionality
- **Text-to-Points Sampling**: Extracts points from text outlines with configurable density
- **Multiple Shape Types**: Circle, Rectangle, Triangle, Star, Cross, and Point shapes
- **Advanced Animation System**: 5 different animation modes (Noise, Wave, Spiral, Pulse, Orbit)
- **Flexible Color System**: Global color palette with multiple mixing modes
- **Connection System**: Dynamic connections between nearby points with customizable trails
- **Real-time Parameter Control**: Full GUI with organized parameter groups

### Visual Effects
- **Scene Zoom**: Smooth zoom from 1x to 5x magnification
- **Shape Animations**: Rotating, scaling, and morphing shapes
- **Color Transitions**: Smooth color blending based on time, position, or distance
- **Trail Effects**: Particle-like trails following animated points
- **Debug Visualization**: Technical view showing algorithm internals

### Preset System
10 carefully crafted presets accessible via number keys (0-9):

- **0 - Minimal**: Clean, simple aesthetic
- **1 - CyberWave**: Futuristic cyberpunk style  
- **2 - OrganicFlow**: Natural, flowing movement
- **3 - NeonPulse**: High energy pulsing neon
- **4 - CosmicDance**: Ethereal space-like movement
- **5 - RetroGrid**: 80s synthwave style
- **6 - BioLuminous**: Bioluminescent organisms
- **7 - QuantumField**: Quantum particle field effect
- **8 - TribalRitual**: Tribal ceremonial style
- **9 - GalaxyStorm**: Galaxy storm effect

## Screenshot
![](Capture.PNG)

## Controls

### Keyboard Shortcuts
- **0-9**: Load preset scenes
- **Shift + 1-5**: Quick shape selection
- **C**: Cycle through color modes
- **A**: Cycle through animation modes
- **+/-**: Adjust point density
- **↑/↓**: Adjust animation speed
- **←/→**: Adjust scene zoom
- **T**: Toggle trails
- **L**: Toggle connections
- **O**: Toggle text outline
- **F**: Toggle shape fill
- **B**: Toggle background color
- **R**: Reset to defaults
- **Ctrl+S**: Save settings
- **Ctrl+L**: Load settings

### GUI Parameters

#### Density Group
- **Point Density**: Controls the number of points sampled from text
- **Contour Sampling**: Fine-tunes how points are distributed along text contours
- **Points Spacing**: Base spacing between sampled points
- **Min Spacing**: Minimum allowed distance between points

#### Shape Group  
- **Shape Type**: Select from 6 different shape types
- **Radius/Size**: Control shape dimensions
- **Triangle Ratio**: Adjust triangle proportions
- **Shape Rotation**: Rotate shapes over time

#### Colors Group
- **Color Mode**: How colors are applied (Global 1/2/3, Mix, Distance)
- **Color Speed**: Rate of color transitions
- **Color Mix Factor**: Blend amount between colors
- **Color by Distance**: Distance-based color modification

#### Global Colors Group
- **Global Color 1/2/3**: The three main colors used throughout the system

#### Animation Group
- **Animation Mode**: Choose from 5 animation algorithms
- **Animation Speed**: Overall animation rate
- **Noise Size**: Scale for noise-based animations
- **Wave/Spiral/Pulse Parameters**: Mode-specific controls

#### Connections Group
- **Draw Connections**: Enable line connections between nearby points
- **Connection Distance**: Maximum distance for connections
- **Connection Alpha**: Transparency of connection lines
- **Draw Trails**: Enable particle trails
- **Trail Length/Fade**: Trail appearance parameters

## Technical Details

### Requirements
- openFrameworks 0.12.1 or compatible
- Visual Studio 2019 or compatible C++ compiler
- Windows (current build configuration)

### Dependencies
- ofxGui (included with openFrameworks)
- Standard C++ libraries (algorithm, vector, string)

### Project Structure
```
src/
├── main.cpp              # Application entry point
├── ofApp.h/.cpp          # Main application class
├── organicText.h/.cpp    # Core text visualization engine
└── organicTextPresets.h/.cpp  # Preset definitions

docs/
├── README.md             # This file
└── CHANGELOG.md          # Detailed change log
```

### Code Architecture
- **Modular Design**: Separate classes for core functionality and presets
- **Parameter System**: Full ofParameter integration for GUI and persistence
- **Event-Driven**: Efficient updates only when parameters change
- **Performance Optimized**: Spatial optimization for connections and trails

### Settings Persistence
Settings are automatically saved on exit and loaded on startup using openFrameworks JSON serialization. All parameter groups maintain their state between sessions.

## Building

1. Ensure openFrameworks 0.12.1 is properly installed
2. Open `TextTypoOrganic02.vcxproj` in Visual Studio
3. Build in Release mode for optimal performance
4. Ensure the font file `NotoSansMono-Regular.ttf` is in the `bin/data/` folder

## Usage Tips

1. **Start with Presets**: Use number keys 0-9 to explore different visual styles
2. **Experiment with Density**: Higher density creates more detailed but slower renders
3. **Combine Effects**: Mix connections, trails, and animations for complex visuals
4. **Use Debug Mode**: Enable debug to understand the underlying algorithm
5. **Save Configurations**: Use Ctrl+S to save your favorite parameter combinations

## Performance Notes

- Higher point density significantly impacts performance
- Connection calculations scale quadratically with point count
- Trails add memory overhead proportional to trail length
- Debug mode adds rendering overhead

For best performance, start with lower density values and optimize based on your target framerate.

## TODO / Future Enhancements
- ✅ Enhanced preset system with 10 different scenes
- ✅ Advanced animation modes and color mixing
- ✅ Debug visualization and performance optimization
- 🔄 Make some 3D meshes for volumetric effects
- 🔄 Add audio reactive features
- 🔄 Implement particle physics system
- 🔄 Add export functionality (image/video)

---

*Built with openFrameworks - Creative Coding Toolkit*