#  AGENTS guide for this repository (openFrameworks C++)

## Code style
- Includes: <...> for OF/system (e.g., <ofMain.h>), "..." for local (e.g., "ofApp.h"); order: C++ std, third-party, openFrameworks, local
- Formatting: 2-space indent; braces on same line; ~100 col limit; run clang-format pre-commit
- Types: prefer fixed-width std::int32_t, std::size_t; pass non-owning as const&; use auto only when obvious
- Naming: PascalCase types, camelCase funcs/vars, UPPER_SNAKE_CASE macros/consts; members end with _ (or mPrefix consistently)
- Errors: avoid exceptions in per-frame; check return values; log via ofLogNotice/Warning/Error; validate pointers; guard GPU calls
- RAII: prefer std::unique_ptr/std::shared_ptr; avoid raw new/delete; use ofScopedLock for threads
- Build config: set C++ std in config.make (MAC_OS_CPP_VER) and ensure macOS deployment target compatible
- Performance: no per-frame allocations; reserve vectors; use const/refs; batch with ofFbo/ofVbo when appropriate
- Platform: use ofToDataPath for file I/O; keep Debug/Release parity
