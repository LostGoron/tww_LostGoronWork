# TWW Decompilation – Rules for Claude Code

You are assisting with the Wind Waker (TWW) decompilation project (https://github.com/zeldaret/tww).
Your role is strictly technical: produce matching C++ code that compiles to identical assembly, byte-for-byte.

## Canonical project standards (authoritative — read these first)
The project's own written guides are the source of truth. Defer to them over anything in this file if they ever conflict:
- `docs/decompiling.md` — workflow, Ghidra-isms, switch statements, inlines & debug maps, linking a TU
- `docs/coding_guidelines.md` — naming style, primitive types, offsets/padding, includes, resource enums
- `docs/regalloc.md` — fixing register swaps (declaration order, casts, temp vars, inlines, const)

This file only adds how *you* (the assistant) should operate on top of those guides.

## Scope discipline
- Work ONLY on the function(s) explicitly requested. Do not touch unrelated functions, headers, or files.
- If you notice something that looks wrong elsewhere, report it as a comment but do NOT modify it.
- One task = one clearly defined scope. Ask for clarification if the scope is ambiguous.

## C++ conventions
- Always use member functions (`ClassName::methodName`) — never free functions with `this` as a parameter. (This is the #1 thing the project flags about AI-generated code.)
- Match the class structure defined in the existing project headers exactly. Do not invent new members or restructure existing ones.
- Respect the project's existing namespaces, symbol names, and file organization.
- Do not introduce new includes unless strictly necessary and verified to be already used in the project. Prefer forward declarations in headers; put includes in the .cpp where used.
- Avoid Ghidra-isms: don't pass an object as the first argument to its own method, don't write unnecessary `this->`, use `NULL`/`FALSE` instead of `(Type*)0x0`/`0`.

## Naming & types (per coding_guidelines.md)
- Primitive types: use the Dolphin typedefs (`s8 u8 s16 u16 s32 u32 f32 f64`). **But `int` ≠ `s32` for matching** — there is no typedef for `int`, use it directly when the original did.
- Naming prefixes: function params `i_` (or `o_` for output), lowerCamelCase (`i_this`); local vars no prefix, lower_snake_case (`phase_state`); class members `m`/`mp`, UpperCamelCase (`mpModel`); plain-struct (POD) members no prefix, lower_snake_case (`shape_angle`); function-local statics `l_`; globals `g_`.
- Member variables need `/* 0xNN */` offset comments. Do not write explicit padding fields in the body — but only remove padding-looking fields once the TU is 100% matched (before that, you can't know if it's padding or an undecompiled field).

## Symbol and struct naming
- Use ONLY symbol names that are either:
  - Already defined in the project's existing headers/source files, OR
  - Directly readable from the assembly (joint names, string literals, etc.), OR
  - Revealed by a getter (`getChainCnt()` → `mChainCnt`) or a `JUT_ASSERT` string (use the assert's exact spelling, even if its style is inconsistent).
- Never guess or invent symbol names that could originate from a source leak. A descriptive placeholder (`field_0x1C`, `temp`, `r29`) is always preferable to a name you aren't sure is correct — placeholders get cleaned up in a later documentation pass.
- Resource loads: replace raw file indices with the archive enums — `dComIfG_getObjectRes` uses the `dRes_INDEX_*` enum, `dComIfG_getObjectIDRes` uses the `dRes_ID_*` enum.

## Matching discipline
- Your output must be written to match 100% with objdiff. Prioritize correctness over readability.
- Keep the `/* Nonmatching */` marker on a function until it actually shows 100% in objdiff.
- If a construct looks ugly but matches (specific cast, forced inline, operation order), keep it and add a short comment explaining why.
- If you cannot achieve a clean match, say so explicitly and show what delta remains rather than submitting a partial match silently.
- Never submit a "close enough" solution. 100% or flag it.
- Switches: the compiler builds either a comparison tree or a jump table — don't trust Ghidra's if/else or its case order. Write cases in the order objdiff shows, and add "useless" case labels if the tree needs them. m2c handles switches better than Ghidra.
- if/else vs ternary, and swapped if/else blocks, compile differently — try the other form when the branch optimization is wrong.
- Register swaps (all instructions match but registers are permuted): first confirm the code is functionally equivalent, then apply `docs/regalloc.md` techniques — reorder local declarations, add/change a cast (C-style vs `static_cast` differ), split into temp variables, use the exact inline, or add/remove `const`. Inline *shape* matters: the same final asm via a different inline (e.g. a setter `obj->setX(get())` vs a copy) gives different regalloc.

## Comments
- No obvious comments (do not describe what the code visibly does).
- Only comment when the intent or reason behind the code is non-obvious from reading it.
- No speculative comments about game logic, level usage, or actor behavior unless it is directly readable from the code (string literals, enum values, etc.).
- No doxygen blocks on functions whose purpose is not certain.

## Inlines & the Twilight Princess reference
Inline usage is invisible in the asm but strongly affects codegen/regalloc. To find which inline the original used:
1. The kiosk-demo debug maps (`*D.map`, pinned in the ZeldaRET `tww-decomp` Discord) are the authoritative source for inline names/usage — prefer them.
2. Otherwise, reuse an inline already used by another function in the same object, or by a similar function in another object — TP (/workspace/tp) is the main "other object" reference for this.

TP priority rules (TP is a reference, not an authority):
1. TWW assembly is always ground truth
2. TP names are strong hints, not facts — flag them with a comment if used
3. Never copy TP code directly — always re-derive from TWW assembly
4. If TP and TWW diverge on a struct layout, trust TWW offsets

## What to provide before starting
Before decompiling any function, make sure you have:
1. The target function's assembly or P-code output from Ghidra
2. The existing header for the class being decompiled
3. At least one already-matched function from the same class as a style reference
4. The current objdiff output if a previous attempt exists

## Output format
For each function, provide:
1. The decompiled C++ code
2. A brief note on any non-obvious matching decisions
3. An explicit statement of confidence: "Should match 100%" or "Uncertain about [specific construct] — needs objdiff verification"

## What you must never do
- Do not modify files outside the explicitly requested scope
- Do not invent struct layouts or member names not grounded in the assembly or existing project headers
- Do not produce verbose or speculative prose comments
- Do not silently produce a partial match and present it as complete