# TextTypoOrganic02 - Changelog

## Compilation Fixes Applied

### 1. Fixed Linking Errors
- **sampleStringPoints function**: Removed `const` qualifier from function declaration and implementation to allow access to parameter values
- **drawDebugInfo function**: Added complete implementation for debug visualization
- **OrganicTextPresets**: Fixed static function references and removed duplicate constructor

### 2. Fixed Parameter Name Inconsistencies
- **bEnableShapes** → **bDrawShapes**: Renamed for consistency with draw operations
- **bEnableFill** → **bFill**: Simplified naming and fixed all references
- **bShowOutline**, **bDrawOutline**: Consolidated to use `bDrawOutline` consistently
- Added **sceneZoom** parameter for zoom functionality (0-1 maps to 1x-5x zoom)

### 3. Fixed C++ Syntax Issues
- **constexpr → const**: Changed `constexpr` declarations to `const` for compatibility with older C++ standards
- **std::min/std::max**: Added `#include <algorithm>` and ensured all min/max calls use `std::` prefix
- **Integer division**: Fixed potential overflow issues with proper casting

### 4. Parameter Organization and Naming Convention
Applied consistent naming conventions:
- **Draw parameters**: Prefixed with "Draw" (e.g., `bDrawShapes`, `bDrawOutline`)
- **Enable parameters**: Prefixed with "Enable" (e.g., `bEnableAnimation`, `bEnableDensity`)
- **Reset/Random functions**: Named with clear action verbs

### 5. Preset System Reorganization
- **organicText.h/.cpp**: Only contains `loadPreset(int presetNumber)` function
- **organicTextPresets.h/.cpp**: Contains all individual preset implementations (0-9)
- **Preset categories**: 
  - 0-9: Full scene presets
  - Additional functions for color-only, animation-only, and shape-only presets

### 6. New Features Added
- **Scene Zoom**: 0-1 parameter that scales the entire scene 1x-5x
- **Debug Mode**: Enhanced debug visualization showing:
  - Text center point and coordinate system
  - Original sample points
  - Bounding box
  - Sample point visualization
- **SHAPE_POINT**: New shape type for minimal point visualization
- **Enhanced Density Control**: Improved contour sampling for better point distribution

### 7. GUI Organization
Parameters are now organized in logical groups:
- **Density**: Point spacing, density, and sampling controls
- **Shape**: Shape type, size, and appearance controls  
- **Colors**: Color mode and mixing controls
- **Global Colors**: The three main color sources
- **Animation**: All animation parameters
- **Connections**: Connection and trail settings

Each group has:
- Enable/disable toggle at the top
- Parameters in the middle
- Random and Reset buttons at the bottom

### 8. Preset System (0-9 Keys)
- **0**: Minimal - Clean, simple aesthetic
- **1**: CyberWave - Futuristic cyberpunk style
- **2**: OrganicFlow - Natural, flowing movement
- **3**: NeonPulse - High energy pulsing neon
- **4**: CosmicDance - Ethereal space-like movement
- **5**: RetroGrid - 80s synthwave style
- **6**: BioLuminous - Bioluminescent organisms
- **7**: QuantumField - Quantum particle field effect
- **8**: TribalRitual - Tribal ceremonial style
- **9**: GalaxyStorm - Galaxy storm effect

### 9. Settings Persistence
- **Auto-save**: Settings automatically save on application exit
- **JSON format**: Uses openFrameworks native JSON serialization
- **Parameter groups**: All parameter groups are saved/loaded together

### 10. Color System Simplification
Removed complex color modes and consolidated to global color system:
- **COLOR_GLOBAL_1/2/3**: Use individual global colors
- **COLOR_GLOBAL_MIX**: Blend all three colors
- **COLOR_DISTANCE**: Mix colors based on distance from center

This provides simpler, more predictable color control while maintaining flexibility.

## Build Status
All compilation errors have been addressed:
- ✅ Fixed unresolved external symbols
- ✅ Fixed const/non-const method issues  
- ✅ Fixed parameter name mismatches
- ✅ Fixed C++ standard compatibility issues
- ✅ Fixed integer division and overflow warnings
- ✅ Organized code structure properly

The application should now compile successfully and provide the enhanced functionality described above.