AGENTS guide for this repository (openFrameworks C++ on macOS)

Build/lint/test (macOS)
- Makefile: Debug make Debug; Release make Release; Clean make clean; Run ./bin/TextTypoOrganic02.app/Contents/MacOS/TextTypoOrganic02
- Xcode: open TextTypoOrganic02.xcodeproj; use schemes "TextTypoOrganic02 Debug/Release"
- Lint/format: clang-format (LLVM). Check clang-format -n -Werror $(git ls-files "*.{h,hpp,cpp,cxx}"); Fix clang-format -i $(git ls-files "*.{h,hpp,cpp,cxx}")
- Tests: none in repo. If adding gtest: ctest -R <NameRegex>; Catch2: ctest -R <NameRegex>. Prefer single-test runs via ctest -R

Code style
- Includes: <...> for OF/system (e.g., <ofMain.h>), "..." for local (e.g., "ofApp.h"); order: C++ std, third-party, openFrameworks, local
- Formatting: 2-space indent; braces on same line; ~100 col limit; run clang-format pre-commit
- Types: prefer fixed-width std::int32_t, std::size_t; pass non-owning as const&; use auto only when obvious
- Naming: PascalCase types, camelCase funcs/vars, UPPER_SNAKE_CASE macros/consts; members end with _ (or mPrefix consistently)
- Errors: avoid exceptions in per-frame; check return values; log via ofLogNotice/Warning/Error; validate pointers; guard GPU calls
- RAII: prefer std::unique_ptr/std::shared_ptr; avoid raw new/delete; use ofScopedLock for threads
- Build config: set C++ std in config.make (MAC_OS_CPP_VER) and ensure macOS deployment target compatible
- Performance: no per-frame allocations; reserve vectors; use const/refs; batch with ofFbo/ofVbo when appropriate
- Platform: use ofToDataPath for file I/O; keep Debug/Release parity

Cursor/Copilot rules
- No .cursor rules or .github/copilot-instructions.md present at generation time

---

(Modified file originally taken from: https://github.com/smeyfroi/ AGENTS.md.)