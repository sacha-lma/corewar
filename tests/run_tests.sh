#!/usr/bin/env bash

set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT_DIR/robot-factory"
LOG_DIR="$ROOT_DIR/Logs/functional_tests"
LATEST_LOG="$LOG_DIR/latest.log"
TMP_DIR="$(mktemp -d)"

PASS_COUNT=0
FAIL_COUNT=0

cleanup()
{
    rm -rf "$TMP_DIR"
}

log()
{
    echo "$1" | tee -a "$LATEST_LOG"
}

assert_exit()
{
    local expected="$1"
    local got="$2"

    if [ "$expected" -ne "$got" ]; then
        return 1
    fi
    return 0
}

run_usage_case()
{
    local out_file err_file status

    out_file="$TMP_DIR/usage.out"
    err_file="$TMP_DIR/usage.err"
    "$BIN" >"$out_file" 2>"$err_file"
    status=$?
    assert_exit 84 "$status" || return 1
    grep -q "Usage" "$err_file" || return 1
    return 0
}

run_missing_file_case()
{
    local out_file err_file status

    out_file="$TMP_DIR/missing.out"
    err_file="$TMP_DIR/missing.err"
    "$BIN" "$TMP_DIR/does_not_exist.s" >"$out_file" 2>"$err_file"
    status=$?
    assert_exit 84 "$status" || return 1
    return 0
}

run_champion_case()
{
    local name src ref_bin ref_champ ref tmp_src tmp_cor status

    name="$1"
    src="$ROOT_DIR/Utilities/G-CPE-200_champions/$name.s"
    ref_bin="$ROOT_DIR/Utilities/G-CPE-200_binaries/$name.cor"
    ref_champ="$ROOT_DIR/Utilities/G-CPE-200_champions/$name.cor"
    tmp_src="$TMP_DIR/$name.s"
    tmp_cor="$TMP_DIR/$name.cor"

    ref="$ref_bin"
    if [ ! -f "$ref" ]; then
        ref="$ref_champ"
    fi
    [ -f "$ref" ] || return 1

    cp "$src" "$tmp_src" || return 1
    "$BIN" "$tmp_src" >/dev/null 2>&1
    status=$?
    assert_exit 0 "$status" || return 1
    [ -s "$tmp_cor" ] || return 1
    cmp -s "$tmp_cor" "$ref" || return 1
    return 0
}

run_case()
{
    local name

    name="$1"
    shift
    if "$@"; then
        PASS_COUNT=$((PASS_COUNT + 1))
        log "[PASS] $name"
    else
        FAIL_COUNT=$((FAIL_COUNT + 1))
        log "[FAIL] $name"
    fi
}

mkdir -p "$LOG_DIR"
: > "$LATEST_LOG"
trap cleanup EXIT

if [ ! -x "$BIN" ]; then
    log "[FAIL] Binary not found: $BIN"
    log "Run 'make' before functional tests."
    exit 1
fi

log "Running Robot Factory functional tests"
run_case "usage_without_arguments" run_usage_case
run_case "missing_input_file" run_missing_file_case
run_case "champion_abel" run_champion_case "abel"
run_case "champion_bill" run_champion_case "bill"
run_case "champion_pdd" run_champion_case "pdd"
run_case "champion_tyron" run_champion_case "tyron"

log ""
log "Passed: $PASS_COUNT"
log "Failed: $FAIL_COUNT"

if [ "$FAIL_COUNT" -eq 0 ]; then
    log "ALL TESTS PASSED"
    exit 0
fi
log "TESTS FAILED"
exit 1


