#!/bin/sh
# HOLEXA Test Runner
# Code like a Dragon. Think like a Human.

GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m'

HLXC="../compiler/hlxc"
PASSED=0
FAILED=0

echo ""
echo "════════════════════════════════"
echo "   HOLEXA Test Suite v1.0.0"
echo "════════════════════════════════"
echo ""

run_test() {
    FILE="$1"
    NAME="$2"
    echo "${CYAN}Testing: $NAME${NC}"
    $HLXC run "$FILE" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "${GREEN}  ✓ PASS: $NAME${NC}"
        PASSED=$((PASSED + 1))
    else
        echo "${RED}  ✗ FAIL: $NAME${NC}"
        FAILED=$((FAILED + 1))
    fi
}

echo "── Unit Tests ──"
run_test "unit/test_variables.hlx"  "Variables"
run_test "unit/test_functions.hlx"  "Functions"
run_test "unit/test_loops.hlx"      "Loops"
run_test "unit/test_conditions.hlx" "Conditions"
run_test "unit/test_strings.hlx"    "Strings"

echo ""
echo "── Integration Tests ──"
run_test "integration/test_class.hlx"      "Classes"
run_test "integration/test_error.hlx"      "Error Handling"
run_test "integration/test_algorithms.hlx" "Algorithms"

echo ""
echo "── Real World Tests ──"
run_test "realworld/task_manager.hlx" "Task Manager"

echo ""
echo "════════════════════════════════"
echo "  Results:"
echo "  Passed: $PASSED"
echo "  Failed: $FAILED"
echo "  Total:  $((PASSED + FAILED))"
if [ "$FAILED" -eq 0 ]; then
    echo "${GREEN}  ✓ ALL TESTS PASSED!${NC}"
else
    echo "${RED}  ✗ SOME TESTS FAILED${NC}"
fi
echo "════════════════════════════════"
