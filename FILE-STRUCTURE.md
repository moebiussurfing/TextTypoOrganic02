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
- `ofxPostProcessing`
- `ofxSurfingHelpersLite`
- `ofxSurfingPresetsLite`
- `ofxTweenLite`

### OpenFrameworks Paths

- OF root path (relative to project root): `../../../`

- OF addons path (relative to project root): `../../addons/`
