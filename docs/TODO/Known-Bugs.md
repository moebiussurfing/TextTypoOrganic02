# Known Bugs - TextTypoOrganic02

## 🐛 Confirmed Bugs (Fix Immediately)

> Currently no critical bugs confirmed. This section will be populated as issues are discovered and verified.

## 🔍 Issues Under Investigation

### Performance Related

#### High Density Performance Drop
- **Symptom**: Frame rate drops significantly when point density > 0.8
- **Impact**: Medium - affects user experience at high settings
- **Cause**: O(n²) connection calculations become expensive
- **Status**: Investigating spatial optimization solutions
- **Workaround**: Keep density < 0.7 for smooth performance
- **Priority**: Medium

#### Memory Growth with Long Trails  
- **Symptom**: Memory usage increases over time with trails enabled
- **Impact**: Low - only affects very long sessions (> 1 hour)
- **Cause**: Possible trail cleanup inefficiency 
- **Status**: Need to profile memory usage patterns
- **Workaround**: Restart application periodically or use shorter trails
- **Priority**: Low

### GUI Related

#### Parameter Refresh Lag
- **Symptom**: Some GUI sliders don't update immediately when presets load
- **Impact**: Low - visual only, values are correct internally
- **Cause**: Parameter listener events may be out of sync
- **Status**: Need to investigate parameter update order
- **Workaround**: Move slider slightly to refresh display
- **Priority**: Low

#### GUI Focus Issues
- **Symptom**: Sometimes GUI doesn't respond until main window is clicked
- **Impact**: Medium - affects usability
- **Cause**: Window focus management
- **Status**: Investigating openFrameworks GUI focus handling
- **Workaround**: Click main window before using GUI
- **Priority**: Medium

### Rendering Related

#### Zoom Edge Cases
- **Symptom**: Very high zoom levels (> 4x) may clip some elements
- **Impact**: Low - extreme zoom levels rarely used
- **Cause**: OpenGL viewport calculations at extreme scales
- **Status**: Need to test zoom bounds more thoroughly
- **Workaround**: Use moderate zoom levels (< 4x)
- **Priority**: Low

## 🧪 Areas Needing Testing

### Stress Testing
- [ ] **High point density** (density > 0.9)
- [ ] **Many connections** (connection distance > 150)
- [ ] **Long trails** (trail length > 80)
- [ ] **Rapid preset switching** (multiple switches per second)
- [ ] **Extended runtime** (> 2 hours continuous)

### Edge Case Testing
- [ ] **Zero/minimal parameter values**
- [ ] **Maximum parameter values**
- [ ] **Very small window sizes**
- [ ] **Large zoom levels** (> 4x)
- [ ] **Missing font file scenarios**
- [ ] **Corrupted settings file**

### Platform Testing
- [ ] **Different Windows versions** (10, 11)
- [ ] **Various screen resolutions** (1080p, 1440p, 4K)
- [ ] **Different graphics drivers** (NVIDIA, AMD, Intel)
- [ ] **Systems with limited RAM** (< 8GB)
- [ ] **High DPI displays**

## 🚫 Confirmed Non-Issues (By Design)

### Expected Behaviors
- **Discrete preset switching**: Presets change instantly by design
- **Limited animation types**: Only 5 modes implemented intentionally  
- **Fixed text content**: "ARB" text is hardcoded by design choice
- **Parameter ranges**: Min/max values chosen for optimal visual results
- **Windows-only build**: Current target platform by design

### Performance Limitations
- **Connection calculation complexity**: O(n²) is expected for current algorithm
- **Higher memory with trails**: Expected behavior for particle trail system
- **Lower performance at high density**: Expected due to increased calculations

## 🔧 Bug Reporting Guidelines

### When You Find a Bug
1. **Check this list first** - see if it's already known
2. **Try to reproduce** - can you make it happen again?
3. **Note your system** - Windows version, hardware specs
4. **Document steps** - exactly what you did to trigger it
5. **Check workarounds** - is there a temporary solution?

### Bug Report Template
```
**Bug Title**: Brief description

**Symptom**: What you observed
**Expected**: What should happen instead  
**Steps to Reproduce**: 
1. Step one
2. Step two
3. etc.

**Frequency**: Always/Sometimes/Rare
**Impact**: High/Medium/Low
**System**: Windows version, graphics card, RAM
**Workaround**: Any temporary solution found

**Additional Notes**: Screenshots, error messages, etc.
```

## 📊 Bug Priority Guidelines

### 🔴 Critical (Fix Immediately)
- Application crashes
- Data loss or corruption
- Complete feature failure
- Security vulnerabilities

### 🟡 High Priority (Fix Soon)  
- Significant performance degradation
- Major usability issues
- Incorrect visual output
- Save/load problems

### 🟢 Medium Priority (Fix When Convenient)
- Minor performance issues
- Cosmetic GUI problems
- Edge case behaviors
- Enhancement requests

### ⚪ Low Priority (Note and Monitor)
- Rare edge cases
- Minor visual inconsistencies  
- Documentation issues
- Feature suggestions

## 🛠️ Bug Investigation Process

### Investigation Steps
1. **Reproduce**: Confirm bug exists and steps to recreate
2. **Isolate**: Find minimal conditions that trigger the issue
3. **Analyze**: Examine code and identify potential root causes
4. **Fix**: Implement solution with minimal side effects
5. **Test**: Verify fix works and doesn't break other features
6. **Document**: Update this file and git commit message

### Debugging Tools Available
- **Visual Studio Debugger**: Step through code execution
- **Console Output**: Use `ofLog()` for runtime debugging
- **Debug Mode**: Built-in debug visualization (press D)
- **Performance Profiler**: Identify performance bottlenecks
- **Memory Monitor**: Track memory usage over time

## 📝 Bug Resolution History

### Recently Fixed (Reference)
*This section will track major bugs that have been resolved*

**Example entry format:**
- **Bug**: Description of the issue
- **Fixed in**: Version or date
- **Solution**: Brief description of the fix
- **Impact**: What changed for users

---

## 📞 Getting Help

### Self-Diagnosis
1. **Try the workarounds** listed above
2. **Reset parameters** (R key) and test again
3. **Try different presets** to isolate the issue
4. **Check system requirements** and update drivers
5. **Restart the application** to clear temporary issues

### Reporting Critical Issues
If you find a critical bug (crashes, data loss):
1. **Stop using the feature** that causes the problem
2. **Document everything** about when it happens
3. **Report immediately** with full details
4. **Use workarounds** until a fix is available

### Community Support
- Check documentation for common solutions
- Search existing issues before reporting new ones
- Provide complete information when asking for help
- Test suggested solutions and report back