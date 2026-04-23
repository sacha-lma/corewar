# Structure Policy (file and function creation)

## Scope
- Applies only to how files and functions are structured (not syntax/style rules).
- Applies to every new file placed under `src/` and every new function added.

## Core principles
- One function = one clear action; if more is needed, create another function.
- Functions in modules are `static` only; nothing exported out of `src/`.
- No file-scope or global variables (including `static` globals); pass state explicitly.
- Do not mix responsibilities in one function; split into small, focused helpers.

## File organization
- All code files live under `src/`.
- Create explicit, unambiguous subfolders by domain (e.g., `src/core/`, `src/utils/`, `src/io/`, `src/render/`).
- A file should group functions serving the same functional unit only.
- Avoid catch-all files; split as soon as multiple business concerns appear.

### Example layout
```
src/
  core/
    init_app.c
  io/
    parse_config.c
  metrics/
    update_stats.c
```

## Naming
- Name folders by their functional role, not vague terms.
- Name files after the main action they implement (e.g., `update_stats.c`, `parse_config.c`).
- Name `static` functions after the action performed; avoid generic names like `process()` or `handle()`.

## Dependencies
- Prefer dependency injection via parameters over shared state.
- If shared state is unavoidable, encapsulate it in a struct passed explicitly rather than declaring globals.

### Example code (no globals, static helpers)
```c
static void load_defaults(app_config_t *cfg) {
    // ... load default values ...
}

static void apply_overrides(app_config_t *cfg, const char *path) {
    // ... read file and override fields ...
}

static int init_config(app_config_t *cfg, const char *path) {
    load_defaults(cfg);
    apply_overrides(cfg, path);
    return SUCCESS;
}
```

## Creation checklist
1) Pick or create the appropriate `src/` subfolder with a clear domain name.
2) Name the file after its primary action.
3) Declare only `static` functions, each doing a single action.
4) Do not declare file-scope or global variables; pass state through parameters or structs.
5) Split into more files if multiple responsibilities emerge.

## Quick examples
- Good folders: `src/io/`, `src/metrics/`, `src/render/`; avoid `src/misc/`.
- Good files: `parse_env.c`, `collect_cpu_stats.c`; avoid `helpers.c`, `stuff.c`.
- Good functions: `static int parse_line(...)`, `static void push_sample(...)`; avoid `static void do_it(...)`.
