# Troubleshooting - TextTypoOrganic02

## Quick Fixes

### Performance Issues

#### Low Frame Rate / Stuttering
**Symptoms**: Animation is choppy, low FPS
**Solutions**:
- Reduce **Point Density** to 0.3-0.5
- Decrease **Connection Distance** or disable connections (L key)
- Shorten **Trail Length** or disable trails (T key)
- Lower **Animation Speed**
- Close other applications

#### High Memory Usage
**Symptoms**: System slows down over time
**Solutions**:
- Reduce **Trail Length** to < 20
- Disable trails if not needed (T key)
- Restart application periodically
- Check for memory leaks in Task Manager

### Visual Problems

#### Black/Empty Screen
**Symptoms**: Nothing appears on screen
**Solutions**:
- Press **R** to reset all parameters
- Try different presets (0-9 keys)
- Check that **Point Density** > 0
- Ensure **Shape Type** is selected
- Verify window isn't minimized

#### No Animation
**Symptoms**: Everything is static
**Solutions**:
- Check **Animation Mode** isn't set to "None"
- Increase **Animation Speed** 
- Try pressing **A** to cycle animation modes
- Reset animation parameters

#### Weird Colors/No Color
**Symptoms**: Strange colors or all gray
**Solutions**:
- Try different **Color Mode** (C key to cycle)
- Check **Global Colors** aren't all black/gray
- Reset color parameters
- Try a preset that's known to work

#### Shapes Look Wrong
**Symptoms**: Shapes are too big/small/wrong type
**Solutions**:
- Adjust **Shape Size/Radius**
- Try different **Shape Type** (Shift+1-5)
- Check **Triangle Ratio** for triangles
- Reset shape parameters

### Preset Problems

#### Presets Don't Load
**Symptoms**: Number keys don't change anything
**Solutions**:
- Make sure main window has focus (click it first)
- Try different presets (0-9)
- Check if custom settings are overriding
- Press R to reset, then try presets

#### Preset Looks Different Than Expected
**Symptoms**: Preset doesn't match description
**Solutions**:
- Some presets need higher density to look good
- Check animation is enabled and running
- Try adjusting zoom level (←/→ keys)
- Reset parameters first, then load preset

## Getting Help

### Self-Diagnosis Steps
1. **Try presets first** - If presets work, issue is with custom settings
2. **Reset parameters** - Press R to see if that fixes the issue
3. **Check basics** - Font file exists, window has focus, etc.
4. **Test performance** - Try lower density settings
5. **Restart application** - Sometimes fixes temporary issues

### Information to Collect
If you need to report an issue:
- **System specs**: Windows version, graphics card, RAM
- **Symptoms**: Exact description of what happens
- **Steps to reproduce**: How to trigger the problem
- **Error messages**: Any text that appears
- **Screenshots**: Visual evidence of the problem

## Prevention Tips

### Best Practices
- **Start with presets** rather than random settings
- **Test performance** before using in presentations
- **Have backups** of good configurations
- **Keep font files** in proper location