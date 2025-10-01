# Known Bugs - TextTypoOrganic02

## 🐛 Issues Under Investigation

### Performance Related
- **High density performance drop** - Frame rate drops when density > 0.8
  - Workaround: Keep density < 0.7
- **Memory growth with long trails** - Memory increases over time
  - Workaround: Restart periodically or use shorter trails

### GUI Related  
- **Parameter refresh lag** - Some sliders don't update immediately when presets load
  - Workaround: Move slider slightly to refresh

### Rendering Related
- **Zoom edge cases** - Very high zoom levels (> 4x) may clip elements
  - Workaround: Use moderate zoom levels (< 4x)

## 🔧 Bug Investigation Process

1. **Reproduce** - Confirm bug exists
2. **Isolate** - Find minimal conditions 
3. **Fix** - Implement solution
4. **Test** - Verify fix works
5. **Document** - Update this file