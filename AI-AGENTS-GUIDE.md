# AI-AGENTS-GUIDE.md

> [!INFO]
> Quick reference for AI coding assistants:
> GitHub Copilot, Gemini, Claude, Cline, Cursor, Windsurf and other AI coding assistants in VS Code, Visual Studio 2026, Xcode or similar IDEs.

---

## 📚 AI-ASSISTANT FILE:
- All the related notes for the `AI AGENT` are placed on this folder:
[docs/AI-Assistant](docs/AI-Assistant/)

---

# **SESSION WORKFLOW STEPS**

## **EVERY SESSION START**

1. **READ**:
- [**FILE-STRUCTURE**](FILE-STRUCTURE.md) - Project file map.
- [**PROJECT-CONTEXT.md**](/docs/AI-Assistant/PROJECT-CONTEXT.md) - Full project overview. Read on first session or when lost.

2. **CHECK**:
- [**AGENTS.md**](docs/AI-Assistant/AGENTS.md) - Full onboarding, workflows & best practices for assistants.
- [**RULES.md**](/docs/AI-Assistant/RULES.md) - Automated execution rules and constraints for AI assistants.

3. **REVIEW**:
- [**CURRENT-STATE.md**](docs/AI-Assistant/CURRENT-STATE.md) - Current priorities. Read at every session start.
- [**CURRENT-TASKS.md**](docs/AI-Assistant/Status/CURRENT-TASKS.md) - What to work on now.

## **BEFORE CODING**

1. **REVIEW**:
- **[docs/AI-Assistant/Status/CURRENT-TASKS.md](docs/AI-Assistant/Status/CURRENT-TASKS.md)** - A list of recent, completed and next planned tasks.
2. **CHECK**:
- **[docs\AI-Assistant\Status\KNOWN-BUGS.md](docs\AI-Assistant\Status\KNOWN-BUGS.md)** - Bugs and known issues that we will need to resolve at some point.
3. **PLAN & EXECUTE**:
	⭐ **`START CODING: After reading TODO.md, begin implementation!`**
	- **[docs\AI-Assistant\Status\TODO.md](docs\AI-Assistant\Status\TODO.md)** The following tasks must be completed immediately. The AI Code Agent will initiate the session by reading and familiarizing itself with the project context. Subsequently, the AI Agent is required to initiate the execution of the instructions now! Go!.

## **AFTER CODING**

1. **DOCUMENT**:
   - Summarize what was accomplished this session
   - Update relevant status files

2. **TEST & VALIDATE**:
   - Ask developer to compile the binary project
   - Request testing of new features/fixes

3. **REVIEW STATUS**:
   - Check if persistent problems are resolved
   - Confirm successfully implemented features
   - Perform deep review and summarize current project state

4. **PLAN NEXT**:
   - Update [docs/AI-Assistant/Status/CURRENT-TASKS.md](docs/AI-Assistant/Status/CURRENT-TASKS.md) with next priorities
