# TextTypoOrganic02

> [!NOTE]  
> **WIP / EXPERIMENTAL**  
>  
> **AI-Assisted Development Project** - This project serves as a real-world test case for AI coding assistants (GitHub Copilot, Cline, Gemini, etc.) workflows and documentation patterns. Built upon original sketch from [colormotor](https://github.com/colormotor).

An enhanced **openFrameworks** (aka OF) desktop application that creates organic, animated visualizations from text using customizable shapes, colors, and animations.

*Enhanced version based on original code from [PFAD/examples/week_5/organicTypographyWorked](https://github.com/colormotor/PFAD/tree/main/examples/week_5/organicTypographyWorked)*

![](Capture-v0.1.PNG)

## ✨ For Users

**New to TextTypoOrganic02?** → Start with [docs\User\QUICK-START.md](docs\User\QUICK-START.md) for an app usage introduction

## 🤖 For AI Assistants & Coding Agents

**Are you an AI Assistant Agent?** → Read and deep think into **[AI-AGENTS-GUIDE.md](AI-AGENTS-GUIDE.md)** (Explore also the [docs\AI-Assistant](docs\AI-Assistant) folder.)

## 👨‍💻 For Developers

- **[docs\Developer](docs\Developer)** - Folder with developer notes, ideas, future roadmap and C++ concepts

### Future
- **[docs\Developer\Future\FUTURE-FEATURES.md](docs\Developer\Future\FUTURE-FEATURES.md)** - A long-term roadmap and ideas for evaluating the implementation or rejection of these ideas.
- **[docs\Developer\Future\FUTURE-ROADMAP.md](docs\Developer\Future\FUTURE-ROADMAP.md)** - Possible strategies and priorities for implementing these future ideas

## 📋 Project Management

### Status
- **[docs\AI-Assistant\Status\TODO.md](docs\AI-Assistant\Status\TODO.md)** ⭐ The following tasks must be completed immediately. The AI Code Agent will initiate the session by reading and familiarizing itself with the project context. Subsequently, the AI Agent is required to initiate the execution of the instructions now! Go!.
- **[docs\AI-Assistant\Status\CURRENT-TASKS.md](docs\AI-Assistant\Status\CURRENT-TASKS.md)** - A list of recent, completed and next planned tasks
- **[docs\AI-Assistant\Status\KNOWN-BUGS.md](docs\AI-Assistant\Status\KNOWN-BUGS.md)** - Bugs and known issues that we will need to resolve at some point

### Changelog
- **[docs\CHANGELOG.md](docs\CHANGELOG.md)** - Project history, major milestones and current ptoject status

### File Structure
```
TextTypoOrganic02/
├── docs/
│   ├── AI-Assistant/
│   │   ├── AGENTS.md
│   │   ├── CURRENT-STATE.md
│   │   ├── PROJECT-CONTEXT.md
│   │   └── RULES.md
│   ├── Developer/
│   │   ├── Future/
│   │   │   ├── FUTURE-FEATURES.md
│   │   │   └── FUTURE-ROADMAP.md
│   │   └── Learning/
│   │       ├── CPP-CONCEPTS.md
│   │       └── SHADER-CONVERSION-STRATEGY.md
│   ├── Status/
│   │   ├── CURRENT-TASKS.md
│   │   ├── KNOWN-BUGS.md
│   │   └── TODO.md
│   ├── User/
│   │   └── QUICK-START.md
│   └── CHANGELOG.md
├── src/
│   ├── main.cpp
│   ├── ofApp.cpp
│   ├── ofApp.h
│   ├── organicText.cpp
│   └── organicText.h
├── AI-AGENTS-GUIDE.md
├── Capture-v0.1.PNG
├── FILE-STRUCTURE.md
├── README.md
├── addons.make
├── generate-FILE-STRUCTURE.py
```
## 💻 Tested Systems

- **Windows** (openFrameworks 0.12.1, Visual Studio)
- **macOS** (openFrameworks 0.12.1, Xcode)

*Built with openFrameworks C++ - Creative Coding Toolkit*
