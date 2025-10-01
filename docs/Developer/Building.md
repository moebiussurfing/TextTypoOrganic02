# Building TextTypoOrganic02

## Prerequisites

### Required Software
- **Visual Studio 2019 or newer** (Community Edition is fine)
- **openFrameworks 0.12.1** ([download here](https://openframeworks.cc/download/))
- **Git** (for cloning repository)

### System Requirements
- **OS**: Windows 10 or newer
- **RAM**: 4GB minimum, 8GB recommended
- **Graphics**: OpenGL 3.0+ support
- **Disk**: 2GB free space (includes openFrameworks)

## Setup Instructions

### 1. Install openFrameworks
1. Download **openFrameworks 0.12.1 for Visual Studio**
2. Extract to `C:\openFrameworks` (or preferred location)
3. Navigate to `examples\graphics\polygonExample`
4. Open and build project to verify OF installation

### 2. Clone/Copy Project
```bash
# If using git
git clone [repository-url] apps/myApps/TextTypoOrganic02

# Or manually copy project to:
# openFrameworks/apps/myApps/TextTypoOrganic02/
```

### 3. Required Font File
Ensure `NotoSansMono-Regular.ttf` is in `bin/data/` folder:
- Download from [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans+Mono)
- Place in `TextTypoOrganic02/bin/data/NotoSansMono-Regular.ttf`

## Building the Project

### Method 1: Visual Studio (Recommended)
1. Open `TextTypoOrganic02.vcxproj` in Visual Studio
2. Set build configuration to **Release** for best performance
3. Build → Build Solution (Ctrl+Shift+B)
4. Run with F5 or Ctrl+F5

### Method 2: Command Line
```cmd
# Navigate to project directory
cd apps\myApps\TextTypoOrganic02

# Build release version
msbuild TextTypoOrganic02.vcxproj /p:Configuration=Release /p:Platform=x64
```

## Project Configuration

### Build Configurations

#### Debug Configuration
- **Use for**: Development and debugging
- **Features**: 
  - Full error checking
  - Console output enabled
  - Debug symbols included
  - Slower execution
- **Output**: `bin/TextTypoOrganic02_debug.exe`

#### Release Configuration  
- **Use for**: Final builds and distribution
- **Features**:
  - Optimized code
  - Minimal logging
  - Best performance
  - Smaller executable
- **Output**: `bin/TextTypoOrganic02.exe`

### Dependencies Already Included
- **ofxGui**: Parameter interface (part of openFrameworks)
- **Standard libraries**: algorithm, vector, string

## Project Structure
```
TextTypoOrganic02/
├── src/                    # Source code
│   ├── main.cpp           # Application entry
│   ├── ofApp.h/.cpp       # Main app class
│   ├── organicText.h/.cpp # Core engine
│   └── organicTextPresets.h/.cpp # Presets
├── bin/                   # Executables and runtime files
│   ├── data/             # Required data files
│   │   └── NotoSansMono-Regular.ttf
│   └── TextTypoOrganic02.exe
├── TextTypoOrganic02.vcxproj    # Visual Studio project
├── TextTypoOrganic02.sln        # Visual Studio solution
└── docs/                  # Documentation
```

## Common Build Issues

### Problem: "Cannot open include file 'ofMain.h'"
**Cause**: openFrameworks path not configured correctly
**Solution**:
1. Verify openFrameworks is installed in expected location
2. Check project properties → VC++ Directories
3. Ensure Include Directories points to OF headers

### Problem: "LNK2019: unresolved external symbol"
**Cause**: openFrameworks libraries not linked correctly
**Solution**:
1. Check project properties → Linker → Input
2. Verify all required .lib files are listed
3. Ensure Library Directories points to OF libs

### Problem: "Font could not be loaded"
**Cause**: Missing font file in bin/data/
**Solution**:
1. Download `NotoSansMono-Regular.ttf` from Google Fonts
2. Place in `bin/data/` folder
3. Verify file name matches exactly

### Problem: Application crashes on startup
**Cause**: Missing Visual C++ Runtime
**Solution**:
1. Install latest [Visual C++ Redistributable](https://docs.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist)
2. Restart system
3. Try running again

## Development Workflow

### Recommended Setup
1. **Use Release mode** for testing (better performance)
2. **Switch to Debug mode** only when debugging issues
3. **Keep console window open** to see any error messages
4. **Test presets first** after any changes

### Code Modification Guidelines
1. **Test existing functionality** before making changes
2. **Use consistent naming** with existing code
3. **Add comments** for complex algorithms
4. **Test with multiple presets** to ensure compatibility

### Performance Testing
```cpp
// Add to draw() method for FPS monitoring
float fps = ofGetFrameRate();
if(fps < 30) {
    ofLogWarning() << "Low FPS: " << fps;
}
```

## Advanced Build Options

### Custom Preprocessor Definitions
Add to project properties → C/C++ → Preprocessor:
- `DEBUG_MODE`: Enable debug features
- `PERFORMANCE_LOG`: Enable performance logging
- `VERBOSE_OUTPUT`: Extra console output

### Optimization Settings
For maximum performance:
1. **Optimization**: Maximum Optimization (/O2)
2. **Inline Function Expansion**: Any Suitable (/Ob2)  
3. **Enable Intrinsic Functions**: Yes (/Oi)
4. **Whole Program Optimization**: Yes

### Static Linking (Optional)
To reduce external dependencies:
1. **Runtime Library**: Multi-threaded (/MT)
2. Link statically with OF libraries
3. Results in larger executable but fewer .dll dependencies

## Deployment

### Files Required for Distribution
```
TextTypoOrganic02/
├── TextTypoOrganic02.exe
├── data/
│   └── NotoSansMono-Regular.ttf
└── [Visual C++ Runtime if not installed on target system]
```

### Creating Installation Package
1. **Copy required files** to clean folder
2. **Test on clean system** without development tools
3. **Include VC++ Redistributable** installer if needed
4. **Create zip or installer** as preferred

## Cross-Platform Notes

### Current Status
- **Fully tested**: Windows 10/11 with Visual Studio
- **Should work**: Other Windows versions with proper setup
- **Not tested**: macOS, Linux (but openFrameworks supports these)

### Porting to Other Platforms
1. **macOS**: Use Xcode project generator from OF
2. **Linux**: Use Makefile or Code::Blocks
3. **Update font paths** for different file systems
4. **Test all functionality** on target platform

## Troubleshooting Build Issues

### Clean Build Steps
1. **Clean Solution** (Build → Clean Solution)
2. **Delete bin and obj folders**
3. **Rebuild Solution** (Build → Rebuild Solution)

### Reset Project Settings
1. **Close Visual Studio**
2. **Delete .vs folder** (hidden folder in project directory)
3. **Reopen project**
4. **Reconfigure build settings**

### Verify openFrameworks Installation
1. **Build OF examples** first (polygonExample recommended)
2. **Check OF version** matches project requirements
3. **Verify all OF addons** are present

For additional help, consult the openFrameworks community forum or documentation.