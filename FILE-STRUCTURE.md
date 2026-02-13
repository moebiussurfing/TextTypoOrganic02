# Project File Structure

```
TextTypoOrganic02/
├── docs/
│   ├── Developer/
│   │   ├── Future/
│   │   │   ├── FUTURE-FEATURES.md
│   │   │   └── FUTURE-ROADMAP.md
│   │   └── Learning/
│   │       ├── CPP-CONCEPTS.md
│   │       └── SHADER-CONVERSION-STRATEGY.md
│   ├── User/
│   │   └── QUICK-START.md
│   ├── AGENTS.md
│   ├── CHANGELOG.md
│   ├── CONTEXT.md
│   ├── RULES.md
│   ├── TODO.md
│   └── _AGENTS_START_HERE.md
├── libs/
│   ├── ofxPostProcessing/
│   │   ├── src/
│   │   │   ├── ACESFilmicToneMappingPass.h
│   │   │   ├── BadTVPass.h
│   │   │   ├── BleachBypassPass.cpp
│   │   │   ├── BleachBypassPass.h
│   │   │   ├── BloomPass.cpp
│   │   │   ├── BloomPass.h
│   │   │   ├── ColorInvert.h
│   │   │   ├── ContrastPass.cpp
│   │   │   ├── ContrastPass.h
│   │   │   ├── ConvolutionPass.cpp
│   │   │   ├── ConvolutionPass.h
│   │   │   ├── DigitalGlitchPass.h
│   │   │   ├── DitherPass.h
│   │   │   ├── DofAltPass.cpp
│   │   │   ├── DofAltPass.h
│   │   │   ├── DofPass.cpp
│   │   │   ├── DofPass.h
│   │   │   ├── DotScreenPass.cpp
│   │   │   ├── DotScreenPass.hpp
│   │   │   ├── EdgePass.cpp
│   │   │   ├── EdgePass.h
│   │   │   ├── FakeSSSPass.cpp
│   │   │   ├── FakeSSSPass.h
│   │   │   ├── FilmGrainLinesPass.cpp
│   │   │   ├── FilmGrainLinesPass.hpp
│   │   │   ├── FirePass.h
│   │   │   ├── FogPass.h
│   │   │   ├── FxaaPass.cpp
│   │   │   ├── FxaaPass.h
│   │   │   ├── GlitchAutomatedPass.h
│   │   │   ├── GodRaysPass.cpp
│   │   │   ├── GodRaysPass.h
│   │   │   ├── HorizontalTiltShifPass.cpp
│   │   │   ├── HorizontalTiltShifPass.h
│   │   │   ├── HsbShiftPass.cpp
│   │   │   ├── HsbShiftPass.h
│   │   │   ├── KaleidoscopePass.cpp
│   │   │   ├── KaleidoscopePass.h
│   │   │   ├── LUTPass.cpp
│   │   │   ├── LUTPass.h
│   │   │   ├── LimbDarkeningPass.cpp
│   │   │   ├── LimbDarkeningPass.h
│   │   │   ├── NoisePass.h
│   │   │   ├── NoiseWarpPass.cpp
│   │   │   ├── NoiseWarpPass.h
│   │   │   ├── PixelatePass.cpp
│   │   │   ├── PixelatePass.h
│   │   │   ├── PostProcessing.cpp
│   │   │   ├── PostProcessing.h
│   │   │   ├── RGBShiftPass.cpp
│   │   │   ├── RGBShiftPass.h
│   │   │   ├── RenderPass.cpp
│   │   │   ├── RenderPass.h
│   │   │   ├── RimHighlightingPass.cpp
│   │   │   ├── RimHighlightingPass.h
│   │   │   ├── SSAOPass.cpp
│   │   │   ├── SSAOPass.h
│   │   │   ├── SlantShiftPass.h
│   │   │   ├── SpaceColorMovePass.h
│   │   │   ├── SuperPass.h
│   │   │   ├── TiltShiftPass.h
│   │   │   ├── ToonPass.cpp
│   │   │   ├── ToonPass.h
│   │   │   ├── VerticalTiltShifPass.cpp
│   │   │   ├── VerticalTiltShifPass.h
│   │   │   ├── ZoomBlurPass.cpp
│   │   │   ├── ZoomBlurPass.h
│   │   │   └── ofxPostProcessing.h
│   │   └── readme.md
│   ├── ofxSurfingHelpersLite/
│   │   ├── src/
│   │   │   ├── SurfingFilesManager.cpp
│   │   │   ├── SurfingFilesManager.h
│   │   │   ├── ofxSurfingHelpersLite.h
│   │   │   ├── ofxSurfingOfxGui.h
│   │   │   └── ofxSurfingSerializers.h
│   │   └── README.md
│   ├── ofxSurfingPresetsLite/
│   │   ├── src/
│   │   │   ├── ofxSurfingHelpersParameters.h
│   │   │   ├── ofxSurfingPresetsLite.h
│   │   │   ├── ofxSurfingPresetsLiteImgui.h
│   │   │   └── ofxSurfingPresetsLiteOfxGui.h
│   │   └── README.md
│   └── ofxTweenLite/
│       ├── src/
│       │   ├── ofxTweenLite.h
│       │   └── ofxTweenLiteHelper.h
│       └── README.md
├── src/
│   ├── OrganicTextRenderer.cpp
│   ├── OrganicTextRenderer.h
│   ├── main.cpp
│   ├── ofApp.cpp
│   ├── ofApp.h
│   ├── ofxDC_Utilities.h
│   ├── ofxPostProcessingManager.cpp
│   ├── ofxPostProcessingManager.h
│   ├── organicText.cpp
│   ├── organicText.h
│   ├── organicTextConstants.h
│   ├── organicTextData.cpp
│   ├── organicTextData.h
│   ├── organicTextPreset.cpp
│   ├── organicTextPreset.h
│   ├── organicTextResetsRandoms.cpp
│   ├── organicTextResetsRandoms.h
│   ├── organicTextScene.cpp
│   ├── organicTextScene.h
│   ├── presetSlideshow.cpp
│   └── presetSlideshow.h
├── Capture-v0.1.PNG
├── Capture-v0.3.PNG
├── FILE-STRUCTURE.md
├── README.md
├── addons.make
└── generate-FILE-STRUCTURE.py
```

---

## Used Addons (from addons.make)

- `ofxGui`

### OpenFrameworks Paths

- OF root path (relative to project root): `../../../`

- OF addons path (relative to project root): `../../addons/`
