# Troubleshooting - TextTypoOrganic02

## Quick Fixes

### Application Won't Start
1. **Check openFrameworks installation**
   - Ensure OF 0.12.1 is properly installed
   - Verify all required libraries are present
2. **Font file missing**
   - Ensure `NotoSansMono-Regular.ttf` is in `bin/data/` folder
   - Download from Google Fonts if missing
3. **Visual C++ Runtime**
   - Install latest Visual C++ Redistributable
   - Restart system after installation

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

#### Slow Startup
**Symptoms**: Long loading time
**Solutions**:
- Check font file exists in correct location
- Verify hard drive has free space
- Disable antivirus temporarily during startup
- Run as administrator if needed

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

### GUI/Interface Issues

#### GUI Not Responding
**Symptoms**: Can't click GUI elements
**Solutions**:
- Click in main window first to focus it
- Try keyboard shortcuts instead
- Check window isn't covered by other apps
- Restart application

#### GUI Panels Missing/Closed
**Symptoms**: Parameter panels disappeared
**Solutions**:
- Look for minimize buttons on GUI panels
- Restart application (GUI auto-restores)
- Check if window is too small
- Try fullscreen mode

#### Settings Won't Save
**Symptoms**: Ctrl+S doesn't work, settings lost
**Solutions**:
- Check file permissions in application folder
- Run as administrator
- Verify disk isn't full
- Check antivirus isn't blocking file writes

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

### System-Specific Issues

#### Windows 10/11 Compatibility
- Install latest Windows updates
- Update graphics drivers
- Check Windows Defender exclusions

#### High DPI Displays
- Try different display scaling settings
- Update graphics drivers
- Use compatibility mode if needed

#### Multiple Monitors
- Try moving window to primary monitor
- Check display scaling on each monitor
- Ensure graphics drivers support multi-monitor

## Error Messages

### "Font could not be loaded"
**Cause**: Missing or corrupted font file
**Solution**: 
1. Download `NotoSansMono-Regular.ttf` from Google Fonts
2. Place in `bin/data/` folder
3. Restart application

### "Failed to initialize graphics"
**Cause**: Graphics driver or OpenGL issues
**Solution**:
1. Update graphics drivers
2. Check OpenGL support (version 3.0+ required)
3. Try different graphics settings
4. Restart system

### "Settings file corrupted"
**Cause**: Invalid JSON in settings file
**Solution**:
1. Delete settings file in application folder
2. Restart application (creates new settings)
3. Reconfigure parameters as needed

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

### Contact Information
For technical support:
- Check GitHub repository for updates
- Review developer documentation
- Search existing issues before reporting new ones

## Prevention Tips

### Regular Maintenance
- **Restart periodically** during long sessions
- **Keep density reasonable** (< 0.7 for most use)
- **Save good configurations** (Ctrl+S)
- **Update graphics drivers** regularly

### Best Practices
- **Start with presets** rather than random settings
- **Test performance** before using in presentations
- **Have backups** of good configurations
- **Keep font files** in proper location