# User Manual - TextTypoOrganic02

## Overview

TextTypoOrganic02 transforms text into organic, animated visualizations using customizable shapes, colors, and animations. The application displays "ARB" text by default and renders it as animated particles and shapes.

## Complete Controls Reference

### Keyboard Shortcuts

#### Presets (Instant Results)
- **0-9** - Load complete preset scenes
- **Shift + 1-5** - Quick shape selection (Circle, Rectangle, Triangle, Star, Cross)

#### Navigation & View
- **←/→** - Adjust scene zoom (1x to 5x magnification)
- **↑/↓** - Adjust animation speed
- **+/-** - Adjust point density

#### Visual Toggles
- **T** - Toggle trails/particle effects
- **L** - Toggle connections between points  
- **O** - Toggle text outline
- **F** - Toggle shape fill
- **B** - Toggle background color

#### Mode Cycling
- **C** - Cycle through color modes
- **A** - Cycle through animation modes

#### System Controls
- **R** - Reset all parameters to defaults
- **Ctrl+S** - Save current settings
- **Ctrl+L** - Load saved settings

### GUI Parameter Groups

The right panel contains organized parameter groups. Each group has:
- **Enable/Disable toggle** at the top
- **Parameters** in the middle  
- **Random** and **Reset** buttons at the bottom

#### Density Group
- **Point Density** (0-1): Controls number of points sampled from text
- **Contour Sampling** (0-1): Fine-tunes point distribution along text contours
- **Points Spacing** (1-50): Base spacing between sampled points
- **Min Spacing** (1-20): Minimum allowed distance between points

#### Shape Group
- **Shape Type**: Choose from Circle, Rectangle, Triangle, Star, Cross, Point
- **Radius/Size** (1-50): Control shape dimensions
- **Triangle Ratio** (0.5-2): Adjust triangle proportions (triangles only)
- **Shape Rotation** (0-360): Rotate shapes over time

#### Colors Group
- **Color Mode**: How colors are applied
  - **Global 1/2/3**: Use individual global colors
  - **Global Mix**: Blend all three global colors
  - **Distance**: Mix colors based on distance from center
- **Color Speed** (0-5): Rate of color transitions
- **Color Mix Factor** (0-1): Blend amount between colors
- **Color by Distance** (0-1): Distance-based color modification strength

#### Global Colors Group
- **Global Color 1/2/3**: The three main colors used throughout the system
- Click color bars to open color picker

#### Animation Group
- **Animation Mode**: Choose algorithm
  - **None**: Static positioning
  - **Noise**: Perlin noise-based movement
  - **Wave**: Sine wave patterns
  - **Spiral**: Rotating spiral motion
  - **Pulse**: Rhythmic pulsing from center
  - **Orbit**: Orbital movement around center
- **Animation Speed** (0-5): Overall animation rate
- **Noise Size** (0.001-0.1): Scale for noise-based animations
- **Wave/Spiral/Pulse Parameters**: Mode-specific fine controls

#### Connections Group
- **Draw Connections**: Enable line connections between nearby points
- **Connection Distance** (10-200): Maximum distance for connections
- **Connection Alpha** (0-255): Transparency of connection lines
- **Draw Trails**: Enable particle trails
- **Trail Length** (5-100): Number of trail points
- **Trail Fade** (0.8-0.99): How quickly trails fade

## Visual Presets Explained

### 0 - Minimal
Clean, minimal aesthetic with simple shapes and subtle animation.
**Best for**: Professional presentations, clean backgrounds

### 1 - CyberWave  
Futuristic cyberpunk style with bright neons and grid-like connections.
**Best for**: Tech demos, gaming content, sci-fi themes

### 2 - OrganicFlow
Natural, flowing movement with organic colors and smooth animations.
**Best for**: Nature themes, relaxing visuals, artistic displays

### 3 - NeonPulse
High energy pulsing neon with bright colors and rhythmic motion.
**Best for**: Music videos, energetic content, party visuals

### 4 - CosmicDance
Ethereal space-like movement with cosmic colors and flowing trails.
**Best for**: Space themes, meditation, ambient displays

### 5 - RetroGrid
80s synthwave style with retro colors and geometric patterns.
**Best for**: Retro themes, nostalgia content, vintage aesthetics

### 6 - BioLuminous
Bioluminescent organism style with glowing effects and organic movement.
**Best for**: Nature documentaries, underwater themes, biological concepts

### 7 - QuantumField
Quantum particle field effect with scientific visualization aesthetics.
**Best for**: Scientific presentations, technical demos, physics concepts

### 8 - TribalRitual
Tribal ceremonial style with warm earth tones and rhythmic patterns.
**Best for**: Cultural content, world music, spiritual themes

### 9 - GalaxyStorm
Galaxy storm effect with swirling cosmic patterns and stellar colors.
**Best for**: Space content, dramatic effects, cosmic themes

## Tips for Best Results

### Performance Optimization
- **Start with lower density** (0.3-0.5) for smooth performance
- **Reduce connections** if frame rate drops
- **Shorter trails** use less memory
- **Higher zoom levels** may affect performance

### Visual Design
- **Combine presets** as starting points, then customize
- **Use trails sparingly** for clean looks
- **Match colors** to your content theme
- **Experiment with zoom** for different perspectives

### Creative Workflow
1. **Start with a preset** that matches your mood
2. **Adjust density** for detail level
3. **Fine-tune colors** to match your needs
4. **Experiment with animation speed**
5. **Save configurations** you like (Ctrl+S)

## Troubleshooting

### Common Issues
- **Low frame rate**: Reduce point density or connection distance
- **No animation**: Check that animation mode isn't "None"
- **Black screen**: Try pressing R to reset parameters
- **Missing shapes**: Ensure shape drawing is enabled in GUI

### Settings Problems
- **Settings won't save**: Check file permissions in application folder
- **Presets don't work**: Restart application, try different preset
- **GUI not responding**: Click in main window first, then try GUI

### Performance Issues
- **Stuttering animation**: Lower density below 0.5
- **Memory usage**: Reduce trail length and restart periodically
- **Slow startup**: Check for font file in bin/data/ folder

For technical issues, see the Developer documentation or contact support.