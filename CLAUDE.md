# TWW Decompilation – Rules for Claude Code

You are assisting with the Wind Waker (TWW) decompilation project (https://github.com/zeldaret/tww).
Your role is strictly technical: produce matching C++ code that compiles to identical assembly, byte-for-byte.

## Scope discipline
- Work ONLY on the function(s) explicitly requested. Do not touch unrelated functions, headers, or files.
- If you notice something that looks wrong elsewhere, report it as a comment but do NOT modify it.
- One task = one clearly defined scope. Ask for clarification if the scope is ambiguous.

## C++ conventions
- Always use member functions (`ClassName::methodName`) — never free functions with `this` as a parameter.
- Match the class structure defined in the existing project headers exactly. Do not invent new members or restructure existing ones.
- Respect the project's existing namespaces, symbol names, and file organization.
- Do not introduce new includes unless strictly necessary and verified to be already used in the project.

## Symbol and struct naming
- Use ONLY symbol names that are either:
  - Already defined in the project's existing headers/source files, OR
  - Directly readable from the assembly (joint names, string literals, etc.)
- Never guess or invent symbol names that could originate from a source leak. If uncertain, use a descriptive placeholder (e.g., `field_0x1C`) and flag it explicitly.

## Matching discipline
- Your output must be written to match 100% with objdiff. Prioritize correctness over readability.
- If a construct looks ugly but matches (specific cast, forced inline, operation order), keep it and add a short comment explaining why.
- If you cannot achieve a clean match, say so explicitly and show what delta remains rather than submitting a partial match silently.
- Never submit a "close enough" solution. 100% or flag it.

## Comments
- No obvious comments (do not describe what the code visibly does).
- Only comment when the intent or reason behind the code is non-obvious from reading it.
- No speculative comments about game logic, level usage, or actor behavior unless it is directly readable from the code (string literals, enum values, etc.).
- No doxygen blocks on functions whose purpose is not certain.

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
