#!/bin/bash
##
## EPITECH PROJECT, 2026
## corewar
## File description:
## Functional tests — run the corewar binary end-to-end
##

BINARY=./corewar
COR=tests/tests_files
PASS=0
FAIL=0

# ── helpers ───────────────────────────────────────────────────────────────────

run_check() {
    local desc="$1" expected_exit="$2" mode="$3" pattern="$4"
    shift 4
    local tmpfile actual last

    tmpfile=$(mktemp)
    "$@" >"$tmpfile" 2>&1
    actual=$?

    if [ "$actual" -ne "$expected_exit" ]; then
        printf "[FAIL] %s\n       exit %d (expected %d)\n" \
            "$desc" "$actual" "$expected_exit"
        FAIL=$((FAIL + 1))
        rm -f "$tmpfile"
        return
    fi

    case "$mode" in
        contains)
            if ! grep -q -- "$pattern" "$tmpfile"; then
                printf "[FAIL] %s\n       output missing pattern: '%s'\n" \
                    "$desc" "$pattern"
                FAIL=$((FAIL + 1))
                rm -f "$tmpfile"
                return
            fi
            ;;
        lastline)
            last=$(tail -1 "$tmpfile")
            if ! echo "$last" | grep -q -- "$pattern"; then
                printf "[FAIL] %s\n       last line: '%s'\n       expected pattern: '%s'\n" \
                    "$desc" "$last" "$pattern"
                FAIL=$((FAIL + 1))
                rm -f "$tmpfile"
                return
            fi
            ;;
    esac

    printf "[PASS] %s\n" "$desc"
    PASS=$((PASS + 1))
    rm -f "$tmpfile"
}

chk_exit() { run_check "$1" "$2" "" "" "${@:3}"; }
chk_out()  { run_check "$1" "$2" "contains" "$3" "${@:4}"; }
chk_last() { run_check "$1" "$2" "lastline"  "$3" "${@:4}"; }

# ── argument errors (exit 84) ─────────────────────────────────────────────────

echo "--- Argument errors ---"

chk_exit "non-existent .cor file"         84  $BINARY no_such_file.cor
chk_exit "wrong file extension (.c)"      84  $BINARY "$COR/abel.cor" Makefile
chk_exit "non-.cor extension only"        84  $BINARY Makefile
chk_exit "-dump missing argument"         84  $BINARY -dump
chk_exit "-n missing argument"            84  $BINARY -n
chk_exit "-a missing argument"            84  $BINARY -a
chk_exit "-dump value is zero"            84  $BINARY -dump 0 "$COR/abel.cor"
chk_exit "-dump negative value"           84  $BINARY -dump -1 "$COR/abel.cor"
chk_exit "-dump non-numeric value"        84  $BINARY -dump abc "$COR/abel.cor"
chk_exit "-n value is zero"               84  $BINARY -n 0 "$COR/abel.cor"
chk_exit "-n non-numeric value"           84  $BINARY -n abc "$COR/abel.cor"
chk_exit "-a non-numeric value"           84  $BINARY -a xyz "$COR/abel.cor"

# ── help flags (exit 0) ───────────────────────────────────────────────────────

echo "--- Help flags ---"

chk_out  "-h prints USAGE"                0 "USAGE"       $BINARY -h
chk_out  "-help prints USAGE"             0 "USAGE"       $BINARY -help
chk_out  "-h prints DESCRIPTION"          0 "DESCRIPTION" $BINARY -h
chk_out  "-h prints -dump description"    0 "-dump"       $BINARY -h
chk_out  "-h prints -n description"       0 "-n"          $BINARY -h
chk_out  "-h prints -a description"       0 "-a"          $BINARY -h

# ── single champion ───────────────────────────────────────────────────────────

echo "--- Single champion ---"

chk_exit "single champion exits 0"        0   $BINARY "$COR/abel.cor"
chk_last "abel wins alone"                0   "The player 1(Abel)has won\."    $BINARY "$COR/abel.cor"
chk_last "pdd wins alone"                 0   "The player 1(pdd)has won\."     $BINARY "$COR/pdd.cor"
chk_last "tyron wins alone"               0   "The player 1(Tyron)has won\."   $BINARY "$COR/tyron.cor"
chk_exit "bill alone exits 0"             0   $BINARY "$COR/bill.cor"

# ── -n flag overrides champion number ────────────────────────────────────────

echo "--- -n flag ---"

chk_last "-n 6 abel gets prog_nb 6"       0   "The player 6(Abel)has won\."    $BINARY -n 6 "$COR/abel.cor"
chk_exit "-n 3 bill exits 0"              0   $BINARY -n 3 "$COR/bill.cor"

# ── -a flag (load address) ────────────────────────────────────────────────────

echo "--- -a flag ---"

chk_exit "-a 0 is valid"                  0   $BINARY -a 0 "$COR/abel.cor"
chk_exit "-a negative is valid"           0   $BINARY -a -100 "$COR/abel.cor"
chk_exit "-a large value is valid"        0   $BINARY -a 4000 "$COR/abel.cor"
chk_last "-a 0 abel still wins"           0   "has won\."    $BINARY -a 0 "$COR/abel.cor" "$COR/bill.cor"

# ── two-champion battles ──────────────────────────────────────────────────────

echo "--- Two-champion battles ---"

chk_exit "abel vs bill exits 0"           0   $BINARY "$COR/abel.cor" "$COR/bill.cor"
chk_last "abel wins vs bill"              0   "The player 1(Abel)has won\."    $BINARY "$COR/abel.cor" "$COR/bill.cor"
chk_last "abel wins vs tyron"             0   "has won\."    $BINARY "$COR/abel.cor" "$COR/tyron.cor"
chk_last "bill wins vs pdd"               0   "has won\."    $BINARY "$COR/bill.cor" "$COR/pdd.cor"

# ── four-champion battle ──────────────────────────────────────────────────────

echo "--- Four-champion battle ---"

chk_exit "four-way battle exits 0"        0   \
    $BINARY "$COR/abel.cor" "$COR/bill.cor" "$COR/pdd.cor" "$COR/tyron.cor"
chk_last "bill wins four-way (prog_nb 2)"  0   "The player 2(Bill)has won\." \
    $BINARY "$COR/abel.cor" "$COR/bill.cor" "$COR/pdd.cor" "$COR/tyron.cor"
chk_last "-n 6 abel: bill wins (prog_nb 1)" 0  "The player 1(Bill)has won\." \
    $BINARY -n 6 "$COR/abel.cor" "$COR/bill.cor" "$COR/pdd.cor" "$COR/tyron.cor"

# ── champion ordering ─────────────────────────────────────────────────────────

echo "--- Champion ordering ---"

chk_last "reversed order: same bill winner" 0 "The player 2(Bill)has won\." \
    $BINARY -n 1 "$COR/tyron.cor" -n 2 "$COR/bill.cor" "$COR/abel.cor" "$COR/pdd.cor"

# ── output content ────────────────────────────────────────────────────────────

echo "--- Output content ---"

chk_out  "alive message contains champion name"  0  "is alive" \
    $BINARY "$COR/abel.cor"
chk_out  "output contains winner line"           0  "has won\." \
    $BINARY "$COR/abel.cor" "$COR/bill.cor"

# ── summary ───────────────────────────────────────────────────────────────────

echo ""
echo "Results: $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
