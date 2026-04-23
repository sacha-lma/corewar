# COMMIT_POLICY — My_World Project

**Audience:** Humans and automated AI agents alike.  
**Purpose:** Defines how to write commit messages, what to commit, what to avoid, and how to behave before pushing.  
**Authority:** This file is the single source of truth. Always follow it.

---

## 1. Commit Message Format

Every commit message title **MUST** follow this exact format:

```
{SYMBOL}[{SYMBOL}...] <type>: <short description>
```

Rules:
- One or more symbols at the start (no space between symbols if combining).
- A lowercase keyword matching the primary symbol (`add`, `del`, `mod`, `fix`, `major`, `docs`, `tests`).
- A colon and a space after the keyword.
- A short, imperative description (≤ 72 characters total for the title).
- No period at the end of the title.

### Valid Examples

```
{+} add: new linked list helper push_sorted
{-} del: remove unused debug prints in setup.c
{~} mod: refactor event_manager loop for clarity
{#} fix: handle NULL pointer in my_strdup
{!}{+} major add: full CSFML rendering pipeline
{!}{#} major fix: critical memory leak in free_list
{...} docs: add installation section to README
{%} tests: add unit tests for my_strlen
{%}{#} tests fix: update broken tests after list refactor
{~}{+} mod add: improve Makefile and add coverage target
```

---

## 2. Symbol Reference Table

| Symbol  | Keyword  | When to use |
|---------|----------|-------------|
| `{+}`   | `add`    | You **added** something that did not exist before (file, function, feature, test, doc). |
| `{-}`   | `del`    | You **deleted** something (file, function, dead code, unused asset). |
| `{~}`   | `mod`    | You **modified** existing code or docs. No bug was present; this is a refactor, cleanup, or improvement. |
| `{#}`   | `fix`    | You **corrected a bug, wrong behavior, or error**. There was a defect and now it is resolved. |
| `{!}`   | `major`  | The change is **large or critical**. Teammates must be aware and pull quickly. Always combine with another symbol. |
| `{...}` | `docs`   | **Documentation only**. No source code behavior changed (README, policy files, comments). |
| `{%}`   | `tests`  | **Tests only**. New or updated unit/functional tests; no change to production code. |

### Combining Symbols — Decision Rules

- Use `{!}` **in addition** to the primary symbol when the change is a major milestone or breaking change.
- Use two primary symbols only when the commit truly covers two distinct types of change that cannot be separated.
- **Prefer small, focused commits** over large mixed ones.

| Situation | Correct symbols |
|-----------|-----------------|
| Big new feature | `{!}{+}` |
| Critical bug fix | `{!}{#}` |
| New tests that also fix a broken test | `{%}{#}` |
| Code improvement + new helper added | `{~}{+}` |
| Only updating a README | `{...}` |

---

## 3. What TO Commit

Include **only** intentional, meaningful changes:

- **Source code:** `*.c`, `*.h`
- **Build files:** `Makefile`
- **Scripts and configs:** any tool configuration tracked intentionally
- **Tests:** test source files (`*.c`), stable test data files
- **Documentation:** `*.md`, `*.mmd`, policy files

---

## 4. What NOT TO Commit

**Never stage or commit the following:**

| Category | Examples |
|----------|----------|
| Compiled objects | `*.o` |
| Binaries / executables | `my_world`, `a.out`, temp test binaries |
| Rebuilt libraries | `libmy.a`, `*.so`, `*.dylib` |
| Coverage artifacts | `*.gcda`, `*.gcno`, `coverage.html`, `*.css` |
| Log files | `*.log` |
| Editor / OS junk | `*.swp`, `*.swo`, `*~`, `.DS_Store` |

**Rule of thumb:** if `make` or `make -C lib/my` can regenerate it, do **not** version it.

---

## 5. Mandatory Pre-Commit Checklist

An agent or developer **MUST** complete these steps in order before committing or pushing:

### Step 1 — Pull latest changes
```sh
git pull
```
> Use `git pull --rebase` **only in emergencies** (broken local history) and only if you fully understand the consequences.

### Step 2 — Build the project
```sh
# Full project
make

# Library only (if changes are limited to lib/my)
make -C lib/my
```
The build **must succeed with no errors**.

### Step 3 — Run tests (if they exist)
```sh
make tests_run
```
All tests **must pass** before committing.

### Step 4 — Inspect the diff
```sh
git diff --staged
```
Verify:
- No generated files (`*.o`, `libmy.a`, binaries, coverage, logs).
- Only the intended files are staged.
- The commit scope is focused and logical.

### Step 5 — Commit
```sh
git commit -m "{SYMBOL} type: short description"
```

### Step 6 — Push
```sh
git push
```

---

## 6. Rules for Automated Agents

Agents follow the **exact same rules** as humans, plus these explicit constraints:

1. **Symbol format is mandatory.** Every commit title must start with at least one symbol from the table in Section 2.
2. **Never stage generated artifacts.** Check `git status` and `git diff --staged` before committing.
3. **One logical unit per commit.** Do not bundle unrelated changes.
4. **Always build before committing.** Do not commit if `make` fails.
5. **Run tests if available.** Do not commit failing tests unless the explicit task is to record a failing state (in that case, state it clearly in the commit body).
6. **Never force-push** to the main branch.
7. **Never push unfinished work** to the main branch.

### Agent Commit Message Examples

```
{+} add: new malloc helper for file reading
{~} mod: simplify coverage target in Makefile
{#} fix: avoid segfault on empty list in get_front
{!}{+} major add: full printf refactor with new format specifiers
{...} docs: create COMMIT_POLICY for team and agent use
{%} tests: add coverage tests for my_str_to_word_array
{%}{#} tests fix: repair broken list tests after get_at refactor
{-} del: remove obsolete rotate_map stub
{!}{#} major fix: resolve double-free in free_all on error path
```

---

## 7. Branch and Collaboration Rules

- The **main branch** must always be in a **buildable and stable state**.
- Keep commits **small and focused** so teammates and agents can review them easily.
- After resolving a merge conflict, always re-run `make` and `make tests_run`.
- If this policy changes, update this file **immediately** so all humans and agents stay synchronized.

---

## 8. Quick Reference (Machine-Parseable Summary)

```
SYMBOLS:
  {+}   → add      (new content added)
  {-}   → del      (content removed)
  {~}   → mod      (existing content improved, no bug)
  {#}   → fix      (bug or error corrected)
  {!}   → major    (large/critical change, always combined)
  {...} → docs     (documentation only)
  {%}   → tests    (tests only)

FORMAT:
  {SYMBOL}[{SYMBOL}] <keyword>: <description>

DO NOT COMMIT:
  *.o  *.a  *.so  binaries  *.gcda  *.gcno  *.log  *.swp  .DS_Store

PRE-COMMIT ORDER:
  1. git pull
  2. make (or make -C lib/my)
  3. make tests_run
  4. git diff --staged  (check for junk)
  5. git commit -m "..."
  6. git push
```
