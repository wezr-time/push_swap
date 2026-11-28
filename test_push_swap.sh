#!/usr/bin/env bash
# ============================================================================
#  test_push_swap.sh  -  full tester for ./push_swap and ./checker (42)
#
#  Put this file in the same folder as ./push_swap and ./checker and run:
#       chmod +x test_push_swap.sh && ./test_push_swap.sh
#
#  Options:
#     -f, --full        long run (more permutations, more random tests)
#     -n N              number of random tests per size   (default 5, full 25)
#     -s, --seed N      seed for reproducible random tests (default 42)
#     -t, --timeout S   timeout per program run in seconds (default 10)
#     -v, --valgrind    run every program under valgrind (leaks / invalid access)
#     -q, --quiet       only print FAILED / WARN lines
#     --only a,b,c      run only some sections:
#                       pre ps perm shapes bench random integ ck diff
#     --no-norm         skip norminette
#     --no-make         skip the Makefile checks
#     -h, --help
#
#  Legend:
#     SUCCESS  test passed
#     FAILED   test failed (reason printed under it, details in test_failures.log)
#     WARN     behaviour is not defined by the subject (informative only)
#
#  The sorting result of push_swap is verified by an INDEPENDENT simulator
#  written in awk (not by your checker), so a bug in one of your programs
#  cannot hide a bug in the other.
# ============================================================================

set -f
export LC_ALL=C

PS=./push_swap
CK=./checker
TIMEOUT=10
MODE=quick
ITER=""
SEED=42
QUIET=0
USE_VG=false
RUN_NORM=1
RUN_MAKE=1
ONLY=""

usage() { sed -n '2,30p' "$0" | sed 's/^# \{0,1\}//'; }

while [ $# -gt 0 ]; do
    case $1 in
        -f|--full) MODE=full ;;
        -q|--quiet) QUIET=1 ;;
        -v|--valgrind) USE_VG=true ;;
        -n) ITER=$2; shift ;;
        -s|--seed) SEED=$2; shift ;;
        -t|--timeout) TIMEOUT=$2; shift ;;
        --only) ONLY=$2; shift ;;
        --no-norm) RUN_NORM=0 ;;
        --no-make) RUN_MAKE=0 ;;
        -h|--help) usage; exit 0 ;;
        *) echo "unknown option: $1"; usage; exit 1 ;;
    esac
    shift
done
if [ -z "$ITER" ]; then
    if [ "$MODE" = full ]; then ITER=25; else ITER=5; fi
fi

want() { [ -z "$ONLY" ] || [[ ",$ONLY," == *",$1,"* ]]; }

# ---------------------------------------------------------------- colours --
if [ -t 1 ]; then
    C_G=$'\033[32m'; C_R=$'\033[31m'; C_Y=$'\033[33m'
    C_B=$'\033[1m';  C_D=$'\033[2m';  C_N=$'\033[0m'
else
    C_G=; C_R=; C_Y=; C_B=; C_D=; C_N=
fi

# -------------------------------------------------------------- workspace --
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
FAILLOG="$PWD/test_failures.log"
: > "$FAILLOG"
START=$(date +%s)

if command -v timeout >/dev/null 2>&1; then TO=timeout
elif command -v gtimeout >/dev/null 2>&1; then TO=gtimeout
else TO=""; fi

# Independent push_swap machine: reads the operations, prints OK / KO / BADOP
cat > "$TMP/sim.awk" <<'AWK'
function size(k) { return T[k] - H[k] }
function sw(k,   t) {
    if (size(k) < 2) return
    t = S[k, H[k]]; S[k, H[k]] = S[k, H[k] + 1]; S[k, H[k] + 1] = t
}
function ro(k,   v) {
    if (size(k) < 2) return
    v = S[k, H[k]]; delete S[k, H[k]]; H[k]++
    S[k, T[k]] = v; T[k]++
}
function rv(k,   v) {
    if (size(k) < 2) return
    T[k]--; v = S[k, T[k]]; delete S[k, T[k]]
    H[k]--; S[k, H[k]] = v
}
function mv(f, t,   v) {
    if (size(f) < 1) return
    v = S[f, H[f]]; delete S[f, H[f]]; H[f]++
    H[t]--; S[t, H[t]] = v
}
BEGIN {
    H["a"] = 0; T["a"] = 0; H["b"] = 0; T["b"] = 0
    n = split(list, nums, " ")
    for (i = 1; i <= n; i++) { S["a", T["a"]] = nums[i] + 0; T["a"]++ }
    isbad = 0
}
{
    if (isbad) next
    if ($0 == "sa") sw("a")
    else if ($0 == "sb") sw("b")
    else if ($0 == "ss") { sw("a"); sw("b") }
    else if ($0 == "pa") mv("b", "a")
    else if ($0 == "pb") mv("a", "b")
    else if ($0 == "ra") ro("a")
    else if ($0 == "rb") ro("b")
    else if ($0 == "rr") { ro("a"); ro("b") }
    else if ($0 == "rra") rv("a")
    else if ($0 == "rrb") rv("b")
    else if ($0 == "rrr") { rv("a"); rv("b") }
    else { isbad = 1; badline = $0; badnr = NR }
}
END {
    if (isbad) { print "BADOP line " badnr " [" badline "]"; exit }
    if (size("b") > 0) { print "KO"; exit }
    ok = 1
    for (i = H["a"]; i < T["a"] - 1; i++)
        if (S["a", i] + 0 > S["a", i + 1] + 0) { ok = 0; break }
    if (ok) print "OK"; else print "KO"
}
AWK

sim() { awk -v list="$1" -f "$TMP/sim.awk" "$2"; }

disorder_of() {
    awk -v list="$1" 'BEGIN {
        n = split(list, v, " "); m = 0; t = 0
        for (i = 1; i <= n; i++) for (j = i + 1; j <= n; j++) {
            t++; if (v[i] + 0 > v[j] + 0) m++ }
        printf "%.2f", (t ? 100 * m / t : 0) }'
}

# gen N SEED [RANGE]   -> N unique random ints in [-RANGE, RANGE]
gen() {
    awk -v n="$1" -v seed="$2" -v r="${3:-0}" 'BEGIN {
        if (r < n) r = n; if (r < 1000) r = 1000
        srand(seed); m = 2 * r + 1
        for (i = 0; i < n; i++) {
            j = i + int(rand() * (m - i))
            vi = (i in p) ? p[i] : i; vj = (j in p) ? p[j] : j
            p[i] = vj; p[j] = vi
            printf "%s%d", (i ? " " : ""), p[i] - r
        }
        print "" }'
}

# shape N KIND SEED  (sorted reverse rotated pipe sw:<fraction>)
shape() {
    awk -v n="$1" -v kind="$2" -v seed="$3" 'BEGIN {
        srand(seed)
        for (i = 1; i <= n; i++) v[i] = i * 3 - int(n * 1.5)
        if (kind == "reverse") {
            for (i = 1; i <= n; i++) w[i] = v[n + 1 - i]
            for (i = 1; i <= n; i++) v[i] = w[i]
        } else if (kind == "rotated") {
            s = int(n / 3)
            for (i = 1; i <= n; i++) w[i] = v[((i - 1 + s) % n) + 1]
            for (i = 1; i <= n; i++) v[i] = w[i]
        } else if (kind == "pipe") {
            h = int(n / 2)
            for (i = 1; i <= n; i++) w[i] = (i <= h) ? v[2 * i - 1 > n ? n : 2 * i - 1] : 0
            k = 0; for (i = 1; i <= n; i += 2) w[++k] = v[i]
            for (i = (n % 2 ? n - 1 : n); i >= 2; i -= 2) w[++k] = v[i]
            for (i = 1; i <= n; i++) v[i] = w[i]
        } else if (kind ~ /^sw:/) {
            f = substr(kind, 4) + 0; k = int(f * n + 0.5); if (k < 1) k = 1
            for (s = 0; s < k; s++) {
                i = 1 + int(rand() * n); j = 1 + int(rand() * n)
                t = v[i]; v[i] = v[j]; v[j] = t }
        }
        for (i = 1; i <= n; i++) printf "%s%d", (i > 1 ? " " : ""), v[i]
        print "" }'
}

perms() {   # perms N "v1 v2 .. vN"  (values ascending) -> every permutation
    awk -v n="$1" -v vals="$2" '
    function p(k,   i, t, s) {
        if (k > n) {
            s = ""
            for (i = 1; i <= n; i++) s = s (i > 1 ? " " : "") V[a[i]]
            print s; return }
        for (i = k; i <= n; i++) {
            t = a[k]; a[k] = a[i]; a[i] = t
            p(k + 1)
            t = a[k]; a[k] = a[i]; a[i] = t }
    }
    BEGIN { split(vals, V, " "); for (i = 1; i <= n; i++) a[i] = i; p(1) }'
}

sel_vals() {   # n ascending values that include INT_MIN and INT_MAX
    local P=(-2147483648 -7 0 3 15 99 2147483647) n=$1 out="" i
    for ((i = 0; i < n - 1; i++)); do out+="${P[i]} "; done
    echo "$out${P[6]}"
}

fmt()   { printf '%q ' "$@"; }
short() { local s="$*"; if [ ${#s} -gt 110 ]; then s="${s:0:110}..."; fi; printf '%s' "$s"; }

# --------------------------------------------------------------- reporting --
N_PASS=0; N_FAIL=0; N_WARN=0

section() { printf '\n%s==== %s ====%s\n' "$C_B" "$1" "$C_N"; }
note()    { [ "$QUIET" = 1 ] || printf '             %s%s%s\n' "$C_D" "$1" "$C_N"; }

t_pass() {
    N_PASS=$((N_PASS + 1))
    [ "$QUIET" = 1 ] || printf '%s[ SUCCESS ]%s %s\n' "$C_G" "$C_N" "$1"
}
t_fail() {
    N_FAIL=$((N_FAIL + 1))
    printf '%s[ FAILED  ]%s %s\n' "$C_R" "$C_N" "$1"
    [ -n "$2" ] && printf '             %s-> %s%s\n' "$C_R" "$2" "$C_N"
    [ -n "$3" ] && printf '             %scmd: %s%s\n' "$C_D" "$(short "$3")" "$C_N"
    { printf 'FAILED: %s\n  reason: %s\n  cmd: %s\n\n' "$1" "$2" "$3"; } >> "$FAILLOG"
}
t_warn() {
    N_WARN=$((N_WARN + 1))
    printf '%s[  WARN   ]%s %s\n' "$C_Y" "$C_N" "$1"
    [ -n "$2" ] && printf '             %s-> %s%s\n' "$C_Y" "$2" "$C_N"
    [ -n "$3" ] && printf '             %scmd: %s%s\n' "$C_D" "$(short "$3")" "$C_N"
}
verdict() {   # name why cmd [info]
    if [ -z "$2" ]; then t_pass "$1"
    elif [ "$4" = info ]; then t_warn "$1" "$2" "$3"
    else t_fail "$1" "$2" "$3"; fi
}

bulk_begin() { B_NAME=$1; B_SEV=${2:-strict}; B_TOT=0; B_BAD=0; B_MSGS=""; }
bulk_add() {   # why cmd label
    B_TOT=$((B_TOT + 1))
    if [ -n "$1" ]; then
        B_BAD=$((B_BAD + 1))
        if [ "$B_BAD" -le 5 ]; then
            B_MSGS+="[$(short "$3")] $1"$'\n'
        fi
        { printf 'FAILED (bulk): %s\n  case: %s\n  reason: %s\n  cmd: %s\n\n' \
            "$B_NAME" "$3" "$1" "$2"; } >> "$FAILLOG"
    fi
}
bulk_end() {
    if [ "$B_BAD" -eq 0 ]; then
        t_pass "$B_NAME ($B_TOT cases)"
    else
        if [ "$B_SEV" = info ]; then t_warn "$B_NAME ($B_BAD/$B_TOT differ)" "" ""
        else t_fail "$B_NAME ($B_BAD/$B_TOT failed)" "" ""; fi
        printf '%s' "$B_MSGS" | sed "s/^/             ${C_R}-> /; s/\$/${C_N}/"
        if [ "$B_BAD" -gt 5 ]; then printf '             ... and %d more (see test_failures.log)\n' $((B_BAD - 5)); fi
    fi
}

# ------------------------------------------------------------ run wrapper --
R_RC=0; R_FAULT=""; R_WHY=""; R_OPS=0

fault() {
    R_FAULT=""
    if [ "$R_RC" -eq 124 ]; then
        R_FAULT="TIMEOUT (more than ${TIMEOUT}s)"
    elif $USE_VG && [ "$R_RC" -eq 42 ]; then
        R_FAULT="valgrind found memory errors/leaks: $(grep -m2 -E 'Invalid|definitely lost|uninitialised|ERROR SUMMARY' "$TMP/vg.log" | tr '\n' ' ')"
    elif [ "$R_RC" -ge 128 ]; then
        R_FAULT="CRASH: killed by signal $((R_RC - 128)) ($(kill -l $((R_RC - 128)) 2>/dev/null))"
    fi
}

run() {   # stdin_file cmd args...   -> $TMP/out $TMP/err R_RC R_FAULT
    local in=$1; shift
    local vg=()
    if $USE_VG; then
        vg=(valgrind -q --leak-check=full --errors-for-leak-kinds=definite
            --error-exitcode=42 --log-file="$TMP/vg.log")
        rm -f "$TMP/vg.log"
    fi
    ${TO:+"$TO" "$TIMEOUT"} "${vg[@]}" "$@" < "$in" > "$TMP/out" 2> "$TMP/err"
    R_RC=$?
    fault
}

err_ok() {
    [ "$(cat "$TMP/err")" = "Error" ] && [ $(( $(wc -c < "$TMP/err") )) -eq 6 ]
}
peek() { head -c 70 "$1" | tr '\n' ' '; }

# error_check PROG args...  -> must print nothing on stdout and "Error\n" on stderr
error_check() {
    local prog=$1; shift
    run /dev/null "$prog" "$@"
    R_WHY=""
    if [ -n "$R_FAULT" ]; then R_WHY=$R_FAULT
    elif [ -s "$TMP/out" ]; then
        R_WHY="stdout must stay empty on error, got: '$(peek "$TMP/out")'"
    elif ! err_ok; then
        R_WHY="stderr must be exactly 'Error' + newline, got: '$(peek "$TMP/err")'"
    fi
    [ -z "$R_WHY" ]
}

# silent_check args... -> push_swap must print nothing at all
silent_check() {
    run /dev/null "$PS" "$@"
    R_WHY=""
    if [ -n "$R_FAULT" ]; then R_WHY=$R_FAULT
    elif [ -s "$TMP/out" ] || [ -s "$TMP/err" ]; then
        R_WHY="must print nothing, got stdout='$(peek "$TMP/out")' stderr='$(peek "$TMP/err")'"
    fi
    [ -z "$R_WHY" ]
}

# ps_sorted_check "numbers" [flags...]  -> output must sort the stack
ps_sorted_check() {
    local nums=$1; shift
    local f bench=0
    for f in "$@"; do [ "$f" = --bench ] && bench=1; done
    run /dev/null "$PS" "$@" $nums
    R_WHY=""; R_OPS=0
    if [ -n "$R_FAULT" ]; then R_WHY=$R_FAULT; return 1; fi
    if [ "$bench" = 0 ] && [ -s "$TMP/err" ]; then
        R_WHY="unexpected stderr output: '$(peek "$TMP/err")'"; return 1
    fi
    if [ -n "$(tail -c1 "$TMP/out")" ]; then
        R_WHY="last operation is not terminated by a newline"; return 1
    fi
    R_OPS=$(( $(wc -l < "$TMP/out") ))
    local res; res=$(sim "$nums" "$TMP/out")
    if [ "$res" != OK ]; then
        case $res in
            BADOP*) R_WHY="invalid output -> $res (only sa sb ss pa pb ra rb rr rra rrb rrr, one per line)" ;;
            *)      R_WHY="stack is NOT sorted after executing the $R_OPS operations printed" ;;
        esac
        return 1
    fi
    return 0
}

FLAGS=("" --simple --medium --complex --adaptive)

# ============================================================== PREFLIGHT ==
HAVE_PS=0; HAVE_CK=0
sec_pre() {
    section "Preflight"
    if [ -x "$PS" ]; then t_pass "$PS exists and is executable"; HAVE_PS=1
    else t_fail "$PS exists and is executable" "not found (run make)" ""; fi
    if [ -x "$CK" ]; then t_pass "$CK exists and is executable"; HAVE_CK=1
    else t_warn "$CK exists and is executable" "not found (run make bonus) - checker tests skipped" ""; fi
    command -v awk >/dev/null || t_fail "awk available" "awk is required by this script" ""
    if [ -z "$TO" ]; then t_warn "timeout command available" "no timeout/gtimeout: infinite loops will hang this script" ""; fi
    if $USE_VG && ! command -v valgrind >/dev/null; then
        t_warn "valgrind available" "valgrind not installed, running without it" ""; USE_VG=false
    fi

    if [ "$RUN_MAKE" = 1 ] && [ -f Makefile ]; then
        local r bad=""
        for r in all clean fclean re; do
            grep -qE "^$r[[:space:]]*:" Makefile || bad+="$r "
        done
        grep -qE '^\$\(NAME\)[[:space:]]*:' Makefile || bad+='$(NAME) '
        verdict "Makefile has rules \$(NAME) all clean fclean re" \
            "${bad:+missing rule(s): $bad}" "grep Makefile"
        grep -qE -- '-Wall' Makefile && grep -qE -- '-Wextra' Makefile && grep -qE -- '-Werror' Makefile
        verdict "Makefile uses -Wall -Wextra -Werror" \
            "$([ $? -eq 0 ] || echo 'one of the flags is missing')" "grep Makefile"
        grep -qE '\*\.(c|o)|wildcard' Makefile
        verdict "Makefile names sources explicitly (no *.c / wildcard)" \
            "$([ $? -ne 0 ] || echo 'wildcard / *.c found')" "grep Makefile"
        local mk; mk=$(make -n 2>&1)
        if printf '%s' "$mk" | grep -qE '(^|[[:space:]])(cc|gcc|clang)[[:space:]]'; then
            t_fail "Makefile does not relink" "'make -n' still wants to compile (relink, or binaries older than sources)" "make -n"
        else t_pass "Makefile does not relink"; fi
    fi

    if [ "$RUN_NORM" = 1 ] && command -v norminette >/dev/null; then
        local nr; nr=$(norminette 2>&1 | grep -v ': OK!')
        if [ -z "$nr" ]; then t_pass "norminette"
        else t_fail "norminette" "$(printf '%s' "$nr" | head -3 | tr '\n' ' ')" "norminette"; fi
    fi
}

# ================================================= push_swap: basic / errors =
INVALID=(
    # not integers
    "abc" "1 2 a" "a 1 2" "0 one 2 3" "1.5 2" "1,5 2" "-" "+" "--" "1-2" "--5"
    "++5" "5-" "0x10 1" "1e3 2" "1 2 3x" "x1" "1 -" "- 1" "1_000 2" "-0- 1"
    "+-1" "-+1" "1 2 3 4 five"
    # empty arguments
    "<E>" "1 <E>" "<E> 1" "1 2 3 <E> 4"
    # above INT_MAX / below INT_MIN
    "2147483648" "-2147483649" "2147483648 1" "1 2147483648" "1 2147483648 3"
    "-2147483649 5" "5 -2147483649" "10000000000" "99999999999999999999"
    "-99999999999999999999" "4294967296 1" "4294967297 2" "-4294967296"
    "9223372036854775807" "9223372036854775808" "-9223372036854775808"
    "-9223372036854775809" "18446744073709551616" "18446744073709551617 5"
    "99999999999999999999999999999999999999999999999999"
    "00000000000000000000002147483648" "-00000000000000000000002147483649"
    "1 2 3 4 5 6 7 8 9 2147483648"
    # duplicates
    "1 1" "3 2 3" "1 2 3 4 5 1" "-1 -1" "2147483647 2147483647"
    "-2147483648 -2147483648" "0 0" "5 4 3 2 1 5" "1 2 3 2" "7 7 7"
    "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 1"
)

expand_case() {
    CASE_ARGS=(); local tok
    for tok in $1; do
        case $tok in
            "<E>") CASE_ARGS+=("") ;;
            "<S>") CASE_ARGS+=(" ") ;;
            *)     CASE_ARGS+=("$tok") ;;
        esac
    done
}

sec_ps() {
    section "push_swap: trivial inputs"
    silent_check;                           verdict "no arguments -> prints nothing" "$R_WHY" "$PS"
    local c
    for c in "5" "-5" "0" "2147483647" "-2147483648" "1 2" "1 2 3" "-3 -2 -1 0 1" \
             "1 2 3 4 5 6 7 8 9 10" "-2147483648 2147483647" "-2147483648 0 2147483647" \
             "10 20 30 40 50 60 70 80 90 100 110 120"; do
        silent_check $c; verdict "already sorted / single value, prints nothing: $c" "$R_WHY" "$PS $c"
    done
    for f in --simple --medium --complex --adaptive; do
        silent_check $f 1 2 3 4 5; verdict "already sorted with $f prints nothing" "$R_WHY" "$PS $f 1 2 3 4 5"
    done

    section "push_swap: invalid input must print 'Error' on stderr"
    local case
    for case in "${INVALID[@]}"; do
        expand_case "$case"
        error_check "$PS" "${CASE_ARGS[@]}"
        verdict "Error: $(fmt "${CASE_ARGS[@]}")" "$R_WHY" "$PS $(fmt "${CASE_ARGS[@]}")"
    done
    local flag
    for flag in --simple --medium --complex --adaptive --bench; do
        bulk_begin "all invalid inputs combined with $flag"
        for case in "${INVALID[@]}"; do
            expand_case "$case"
            error_check "$PS" $flag "${CASE_ARGS[@]}"
            bulk_add "$R_WHY" "$PS $flag $(fmt "${CASE_ARGS[@]}")" "$flag $(fmt "${CASE_ARGS[@]}")"
        done
        bulk_end
    done
    error_check "$PS" --simple;  verdict "'--simple' alone must not crash (nothing or Error)" \
        "$([ -n "$R_FAULT" ] && echo "$R_FAULT")" "$PS --simple"
    run /dev/null "$PS" --bench; verdict "'--bench' alone must not crash" "$R_FAULT" "$PS --bench"

    section "push_swap: valid boundary values"
    local nums
    for nums in "2147483647 -2147483648" "-2147483648 2147483647" "2147483647 0 -2147483648" \
                "0 -1 1" "-1 0" "2 1" "1 3 2" "3 2 1" "2147483646 2147483647 -2147483647 -2147483648" \
                "-1 -2 -3 -4 -5" "5 4 3 2 1" "1 5 2 4 3" "100 -100 50 -50 0" \
                "2147483647 2147483646 2147483645" "-2147483648 -2147483647 -2147483646 0 1"; do
        ps_sorted_check "$nums"; verdict "sorts: $nums" "$R_WHY" "$PS $nums"
    done

    section "push_swap: strategy flags & ambiguous formats (WARN = not defined by subject)"
    for flag in --simple --medium --complex --adaptive; do
        bulk_begin "flag $flag on small/medium inputs"
        for nums in "2 1" "3 1 2" "5 4 3 2 1" "$(gen 10 7)" "$(gen 50 8)" "-2147483648 2147483647 0"; do
            ps_sorted_check "$nums" $flag; bulk_add "$R_WHY" "$PS $flag $nums" "$flag $nums"
        done
        bulk_end
    done
    ps_sorted_check "3 2 1" --bench --simple;  verdict "--bench --simple (order 1)" "$R_WHY" "$PS --bench --simple 3 2 1"
    ps_sorted_check "3 2 1" --simple --bench;  verdict "--simple --bench (order 2)" "$R_WHY" "$PS --simple --bench 3 2 1"

    ps_sorted_check "+5 3 -2";   verdict "'+5' accepted as an integer" "$R_WHY" "$PS +5 3 -2" info
    ps_sorted_check "007 3 01";  verdict "leading zeros accepted ('007')" "$R_WHY" "$PS 007 3 01" info
    error_check "$PS" +1 1;      verdict "'+1 1' treated as duplicate" "$R_WHY" "$PS +1 1" info
    error_check "$PS" 0 -0;      verdict "'0 -0' treated as duplicate" "$R_WHY" "$PS 0 -0" info
    error_check "$PS" 01 1;      verdict "'01 1' treated as duplicate" "$R_WHY" "$PS 01 1" info
    error_check "$PS" --foo 1 2; verdict "unknown option '--foo' -> Error" "$R_WHY" "$PS --foo 1 2" info
    error_check "$PS" 3 2 1 --simple; verdict "flag AFTER the numbers -> Error" "$R_WHY" "$PS 3 2 1 --simple" info
    ps_sorted_check "3 2 1" --simple --complex; verdict "two strategy flags together are accepted" "$R_WHY" "$PS --simple --complex 3 2 1" info
    run /dev/null "$PS" "3 2 1"
    local one=""
    if [ -n "$R_FAULT" ]; then one=$R_FAULT
    elif [ "$(sim "3 2 1" "$TMP/out")" != OK ]; then one="a single quoted argument \"3 2 1\" is not split"; fi
    verdict "single quoted argument \"3 2 1\" is split into numbers" "$one" "$PS \"3 2 1\"" info
}

# ================================================== exhaustive permutations ==
sec_perm() {
    section "push_swap: exhaustive permutations"
    local maxn=5 n flag sel line fact maxops
    [ "$MODE" = full ] && maxn=6
    for n in $(seq 2 $maxn); do
        sel=$(sel_vals "$n")
        fact=1; for ((i = 2; i <= n; i++)); do fact=$((fact * i)); done
        for flag in "${FLAGS[@]}"; do
            bulk_begin "all $fact permutations of $n values (incl. INT_MIN/INT_MAX) - ${flag:-default}"
            maxops=0
            while IFS= read -r line; do
                if ps_sorted_check "$line" $flag; then
                    [ "$R_OPS" -gt "$maxops" ] && maxops=$R_OPS
                    bulk_add "" "" ""
                else
                    bulk_add "$R_WHY" "$PS $flag $line" "$line"
                fi
            done < <(perms "$n" "$sel")
            bulk_end
            note "max operations used: $maxops"
            if [ "$flag" = "" ] || [ "$flag" = --adaptive ]; then
                [ "$n" = 3 ] && [ "$maxops" -gt 3 ] && t_warn "n=3 could be sorted in <= 3 ops (${flag:-default})" "your max is $maxops" ""
                [ "$n" = 5 ] && [ "$maxops" -gt 12 ] && t_warn "n=5 can be sorted in <= 12 ops (${flag:-default})" "your max is $maxops" ""
            fi
        done
    done
}

# ================================================================== shapes ==
sec_shapes() {
    section "push_swap: structured inputs (sorted, reversed, nearly sorted, ...)"
    local sizes=(2 3 4 7 10 33 100)
    [ "$MODE" = full ] && sizes+=(250 500)
    local kind n flag nums d
    for kind in sorted reverse rotated pipe sw:0.01 sw:0.05 sw:0.2 sw:0.5 sw:1 sw:3; do
        for flag in "${FLAGS[@]}"; do
            bulk_begin "shape '$kind' sizes ${sizes[*]} - ${flag:-default}"
            for n in "${sizes[@]}"; do
                nums=$(shape "$n" "$kind" $((SEED + n)))
                if ps_sorted_check "$nums" $flag; then bulk_add "" "" ""
                else bulk_add "$R_WHY" "$PS $flag $nums" "n=$n"; fi
            done
            bulk_end
        done
    done
    for n in 100 500; do
        for kind in sw:0.02 sw:0.1 sw:0.4 sw:3; do
            nums=$(shape "$n" "$kind" "$SEED")
            note "n=$n $kind -> disorder $(disorder_of "$nums")%"
        done
    done
}

# ================================================================== bench ==
bench_validate() {   # nums flag(with possible empty)
    local nums=$1 flag=$2 why="" e="$TMP/err" d exp kw cx op c real total
    ps_sorted_check "$nums" --bench $flag || { R_WHY=$R_WHY; return 1; }
    d=$(grep -oE '[0-9]+\.[0-9]{2}%' "$e" | head -1)
    if [ -z "$d" ]; then why+="no disorder percentage with 2 decimals (like 12.34%); "
    else
        exp=$(disorder_of "$nums")
        awk -v a="${d%\%}" -v b="$exp" 'BEGIN { x = a - b; if (x < 0) x = -x; exit !(x <= 0.0101) }' \
            || why+="disorder shows $d but expected ${exp}%; "
    fi
    case $flag in
        --simple)  kw=simple;   cx='n\^2|n²|n2|n\*n|\^\{2\}' ;;
        --medium)  kw=medium;   cx='sqrt|√|1\.5|3/2' ;;
        --complex) kw=complex;  cx='log' ;;
        *)         kw=adaptive; cx='O\(' ;;
    esac
    grep -qi "$kw" "$e" || why+="strategy name '$kw' not found in bench output; "
    grep -qiE "$cx" "$e" || why+="complexity class not found in bench output; "
    total=$(grep -i 'total' "$e" | grep -oE '[0-9]+' | head -1)
    if [ -z "$total" ]; then why+="no 'total' operations line; "
    elif [ "$total" -ne "$R_OPS" ]; then why+="total says $total but $R_OPS operations were printed; "; fi
    for op in sa sb ss pa pb ra rb rr rra rrb rrr; do
        c=$(grep -oE "(^|[^a-z])$op[^a-z0-9]*[0-9]+" "$e" | head -1 | grep -oE '[0-9]+$')
        real=$(grep -cx "$op" "$TMP/out")
        if [ -z "$c" ]; then why+="count of $op missing; "
        elif [ "$c" -ne "$real" ]; then why+="$op count says $c but really $real; "; fi
    done
    R_WHY=$why
    [ -z "$why" ]
}

sec_bench() {
    section "push_swap: --bench output (stderr)"
    local flag nums
    for flag in "${FLAGS[@]}"; do
        bulk_begin "--bench ${flag:-<default>} : disorder, strategy, complexity, totals, per-op counts"
        for nums in "$(gen 5 11)" "$(gen 20 12)" "$(gen 100 13)" "$(shape 30 reverse 1)" \
                    "$(shape 40 sw:0.05 2)" "$(shape 10 sorted 1)" "3 1 2"; do
            bench_validate "$nums" "$flag"
            bulk_add "$R_WHY" "$PS --bench $flag $nums" "$(short "$nums")"
        done
        bulk_end
    done
    run /dev/null "$PS" --bench $(gen 10 5)
    verdict "bench output goes to stderr only (stdout has operations only)" \
        "$([ -n "$R_FAULT" ] && echo "$R_FAULT" || { grep -qE '[^a-z]' <(tr -d '\n' < "$TMP/out") && echo "stdout contains non-operation text"; })" "$PS --bench ..."
    ps_sorted_check "$(gen 10 6)"
    verdict "no stderr output without --bench" "$R_WHY" "$PS ..."
    run /dev/null "$PS" --bench 1 2 3
    verdict "--bench on sorted input still prints the report" \
        "$([ -s "$TMP/err" ] || echo 'stderr is empty')" "$PS --bench 1 2 3"
}

# ================================================== random + benchmarks ==
sec_random() {
    section "push_swap: random inputs (seed $SEED, $ITER runs per size) + subject benchmarks"
    local sizes=(3 5 10 50 100 500)
    [ "$MODE" = full ] && sizes=(3 5 10 20 50 100 200 500 1000)
    local size flag i nums mn mx sum lim_p lim_g lim_e tier
    for size in "${sizes[@]}"; do
        for flag in "${FLAGS[@]}"; do
            bulk_begin "$size random numbers - ${flag:-default}"
            mn=999999999; mx=0; sum=0
            for ((i = 0; i < ITER; i++)); do
                nums=$(gen "$size" $((SEED * 1000 + size * 10 + i)))
                if ps_sorted_check "$nums" $flag; then
                    bulk_add "" "" ""
                    sum=$((sum + R_OPS))
                    [ "$R_OPS" -lt "$mn" ] && mn=$R_OPS
                    [ "$R_OPS" -gt "$mx" ] && mx=$R_OPS
                else
                    bulk_add "$R_WHY" "$PS $flag $nums" "seed index $i"
                fi
            done
            bulk_end
            note "$(printf 'ops  min %-7s avg %-7s max %-7s' "$mn" "$((sum / ITER))" "$mx")"
            if [ "$flag" = "" ] && { [ "$size" = 100 ] || [ "$size" = 500 ]; } && [ "$B_BAD" -eq 0 ]; then
                if [ "$size" = 100 ]; then lim_e=700;  lim_g=1500; lim_p=2000
                else                       lim_e=5500; lim_g=8000; lim_p=12000; fi
                if   [ "$mx" -lt "$lim_e" ]; then tier="EXCELLENT"
                elif [ "$mx" -lt "$lim_g" ]; then tier="GOOD"
                elif [ "$mx" -lt "$lim_p" ]; then tier="PASS (minimum)"
                else tier=""; fi
                if [ -n "$tier" ]; then
                    t_pass "BENCHMARK $size numbers (default): worst of $ITER = $mx ops -> $tier [<$lim_e / <$lim_g / <$lim_p]"
                else
                    t_fail "BENCHMARK $size numbers (default): worst of $ITER = $mx ops" "must be < $lim_p" ""
                fi
            fi
        done
    done
    bulk_begin "100 numbers spread over the whole int range - default"
    for ((i = 0; i < ITER; i++)); do
        nums=$(gen 100 $((SEED + i)) 2147483647)
        ps_sorted_check "$nums"; bulk_add "$R_WHY" "$PS $nums" "wide range #$i"
    done
    bulk_end
    bulk_begin "500 all-negative numbers - default"
    for ((i = 0; i < ITER; i++)); do
        nums=$(gen 500 $((SEED + 77 + i)) | tr ' ' '\n' | awk '{ print ($1 > 0 ? -$1 : $1) - 1 }' | sort -un | tr '\n' ' ')
        ps_sorted_check "$nums"; bulk_add "$R_WHY" "$PS ..." "negative #$i"
    done
    bulk_end
}

# =============================================================== checker ==
ck_check() {   # expect opsfile args...
    local expect=$1 in=$2; shift 2
    run "$in" "$CK" "$@"
    R_WHY=""
    if [ -n "$R_FAULT" ]; then R_WHY=$R_FAULT; return 1; fi
    local o e; o=$(cat "$TMP/out"); e=$(cat "$TMP/err")
    case $expect in
        OK|KO)
            if [ "$o" != "$expect" ] || [ $(( $(wc -c < "$TMP/out") )) -ne 3 ]; then
                R_WHY="expected stdout '$expect', got '$(peek "$TMP/out")'"
            elif [ -n "$e" ]; then R_WHY="stderr should be empty, got '$e'"; fi ;;
        Error)
            if [ -n "$o" ]; then R_WHY="stdout must be empty on error, got '$o'"
            elif ! err_ok; then R_WHY="stderr must be exactly 'Error', got '$(peek "$TMP/err")'"; fi ;;
        NOOUT)
            if [ -n "$o$e" ]; then R_WHY="must print nothing, got stdout='$o' stderr='$e'"; fi ;;
    esac
    [ -z "$R_WHY" ]
}
ck_str() { local expect=$1 ops=$2; shift 2; printf '%b' "$ops" > "$TMP/in"; ck_check "$expect" "$TMP/in" "$@"; }
ck_case() {   # severity expect ops args...
    local sev=$1 expect=$2 ops=$3; shift 3
    ck_str "$expect" "$ops" "$@"
    local pretty=${ops//\\n/,}
    verdict "checker -> $expect | ops=[${pretty%,}] args=[$*]" "$R_WHY" "printf '$ops' | $CK $*" "$sev"
}

sec_ck() {
    [ "$HAVE_CK" = 1 ] || return
    section "checker: OK / KO"
    ck_case strict OK  ""                           1 2 3
    ck_case strict OK  ""                           5
    ck_case strict OK  ""                           -2147483648 2147483647
    ck_case strict KO  ""                           3 2 1
    ck_case strict KO  ""                           2147483647 -2147483648
    ck_case strict OK  "rra\npb\nsa\nrra\npa\n"     3 2 1 0
    ck_case strict KO  "sa\nrra\npb\n"              3 2 1 0
    section "checker: each operation"
    ck_case strict OK  "sa\n"                       2 1
    ck_case strict KO  "sa\n"                       1 2
    ck_case strict OK  "sa\n"                       1
    ck_case strict OK  "sa\n"                       2147483647 -2147483648
    ck_case strict OK  "sb\n"                       1 2 3
    ck_case strict OK  "ss\n"                       2 1
    ck_case strict OK  "ra\n"                       2 1
    ck_case strict OK  "ra\n"                       3 1 2
    ck_case strict KO  "ra\n"                       1 2 3
    ck_case strict OK  "rra\n"                      2 3 1
    ck_case strict OK  "rra\n"                      2 1
    ck_case strict KO  "rra\n"                      1 2 3
    ck_case strict OK  "rr\n"                       2 1
    ck_case strict OK  "rrr\n"                      2 1
    ck_case strict OK  "rb\n"                       1 2 3
    ck_case strict OK  "rrb\n"                      1 2 3
    ck_case strict OK  "pa\n"                       1 2 3
    ck_case strict KO  "pb\n"                       1 2 3
    ck_case strict KO  "pb\npb\npb\n"               1 2 3
    ck_case strict OK  "pb\npa\n"                   1 2 3
    ck_case strict KO  "pb\npa\n"                   2 1
    ck_case strict OK  "pb\nrb\npa\n"               1 2 3
    ck_case strict OK  "pb\npb\npa\npa\n"           1 2 3
    ck_case strict OK  "pb\npb\nsb\npa\npa\n"       2 1 3
    ck_case strict OK  "pb\npb\nrb\nrb\npa\npa\n"   1 2 3
    ck_case strict OK  "pb\npb\nrrb\nrrb\npa\npa\n" 1 2 3
    ck_case strict KO  "pb\npb\nrb\npa\npa\n"       1 2 3
    ck_case strict KO  "pb\npb\nrrb\npa\npa\n"      1 2 3

    section "checker: no argument / errors"
    ck_case strict NOOUT ""                         
    ck_case strict NOOUT "sa\nra\n"
    local case flag
    for case in "${INVALID[@]}"; do
        expand_case "$case"
        ck_str Error "" "${CASE_ARGS[@]}"
        verdict "checker Error: $(fmt "${CASE_ARGS[@]}")" "$R_WHY" "$CK $(fmt "${CASE_ARGS[@]}")"
    done
    local bad
    for bad in 'sx\n' 'SA\n' 'sa \n' ' sa\n' 'sa sa\n' 'rrrr\n' 'pc\n' 's\n' 'p\n' 'r\n' \
               'ra\nfoo\n' 'foo\nra\n' 'sa\nxx\nsa\n' 'pa;pb\n' 'rrr1\n' '1\n' 'sa,ra\n' \
               'ra rb\n' '\tsa\n' 'Sa\n' 'sA\n' 'rrs\n' 'ssa\n' 'pbb\n' 'ra\nra\nrx\n' 'RRA\n'; do
        ck_case strict Error "$bad" 1 2 3
    done
    ck_case strict Error 'sa\nbogus\nra\n' 3 2 1
    ck_case strict Error 'foo\n'            2147483647 -2147483648

    section "checker: ambiguous cases (WARN = not defined by subject)"
    ck_case info OK  "sa"           2 1
    ck_case info Error '\n'         1 2 3
    ck_case info Error 'sa\n\nra\n' 3 2 1
    ck_case info Error 'sa\r\n'     2 1
    ck_case info Error ""           "<E>"
    ck_str Error "" " " ; verdict "checker with a blank argument ' '" "$R_WHY" "$CK ' '" info
    ck_str OK "sa\n" "2 1"
    verdict "checker splits one quoted argument \"2 1\"" "$R_WHY" "$CK \"2 1\"" info
}

# ============================================= push_swap | checker pipeline ==
sec_integ() {
    [ "$HAVE_CK" = 1 ] && [ "$HAVE_PS" = 1 ] || return
    section "integration: ./push_swap | ./checker"
    local flag nums size i
    for size in 1 2 3 5 10 100 500; do
        for flag in "${FLAGS[@]}"; do
            bulk_begin "push_swap ${flag:-default} | checker for $size numbers"
            for ((i = 0; i < ITER; i++)); do
                nums=$(gen "$size" $((SEED * 31 + size + i)))
                run /dev/null "$PS" $flag $nums
                if [ -n "$R_FAULT" ]; then bulk_add "$R_FAULT" "$PS $flag $nums" "$i"; continue; fi
                cp "$TMP/out" "$TMP/ops"
                ck_check OK "$TMP/ops" $nums
                bulk_add "$R_WHY" "$PS $flag \$ARG | $CK \$ARG" "ARG #$i"
            done
            bulk_end
        done
    done
    bulk_begin "checker must say KO when a valid solution is tampered with"
    for size in 5 20 100; do
        nums=$(gen "$size" $((SEED + size)))
        "$PS" $nums > "$TMP/ops" 2>/dev/null
        cp "$TMP/ops" "$TMP/ops2"; echo pb >> "$TMP/ops2"
        ck_check KO "$TMP/ops2" $nums; bulk_add "$R_WHY" "solution + extra pb" "n=$size +pb"
        cp "$TMP/ops" "$TMP/ops2"; echo ra >> "$TMP/ops2"
        ck_check KO "$TMP/ops2" $nums; bulk_add "$R_WHY" "solution + extra ra" "n=$size +ra"
        : > "$TMP/ops2"
        ck_check KO "$TMP/ops2" $nums; bulk_add "$R_WHY" "empty solution on unsorted stack" "n=$size empty"
    done
    bulk_end
}

# ============================== checker vs independent simulator (diff test) ==
sec_diff() {
    [ "$HAVE_CK" = 1 ] || return
    section "checker: differential test against the awk simulator"
    local OPS=(sa sb ss pa pb ra rb rr rra rrb rrr)
    local POOL=(-2147483648 -5 -1 0 3 7 2147483647)
    local cnt=400; [ "$MODE" = full ] && cnt=2000
    RANDOM=$SEED
    local c n len k srt nums seq expect nok=0 nko=0 nerr=0
    pick() {
        local m=$1 s=$2 arr=("${POOL[@]}") i j t
        for ((i = ${#arr[@]} - 1; i > 0; i--)); do
            j=$((RANDOM % (i + 1))); t=${arr[i]}; arr[i]=${arr[j]}; arr[j]=$t
        done
        arr=("${arr[@]:0:m}")
        if [ "$s" = 1 ]; then printf '%s\n' "${arr[@]}" | sort -n | tr '\n' ' '
        else echo "${arr[*]}"; fi
    }
    bulk_begin "random stacks + random operation lists ($cnt cases)"
    for ((c = 0; c < cnt; c++)); do
        n=$((RANDOM % 4 + 1)); len=$((RANDOM % 8)); srt=$((RANDOM % 3 == 0))
        nums=$(pick "$n" "$srt")
        seq=()
        for ((k = 0; k < len; k++)); do seq+=("${OPS[RANDOM % 11]}"); done
        if [ $((RANDOM % 12)) -eq 0 ] && [ "$len" -gt 0 ]; then seq[RANDOM % len]="xx"; fi
        if [ "${#seq[@]}" -eq 0 ]; then : > "$TMP/in"; else printf '%s\n' "${seq[@]}" > "$TMP/in"; fi
        expect=$(sim "$nums" "$TMP/in")
        case $expect in BADOP*) expect=Error; nerr=$((nerr + 1)) ;; OK) nok=$((nok + 1)) ;; *) nko=$((nko + 1)) ;; esac
        ck_check "$expect" "$TMP/in" $nums
        bulk_add "$R_WHY" "printf '%s\\n' ${seq[*]} | $CK $nums" "args=[$nums] ops=[${seq[*]}]"
    done
    bulk_end
    note "expected results in this run: OK=$nok KO=$nko Error=$nerr"

    if [ "$MODE" = full ]; then
        local seqs=("") o1 o2 o3 line
        for o1 in "${OPS[@]}"; do seqs+=("$o1")
            for o2 in "${OPS[@]}"; do seqs+=("$o1 $o2")
                for o3 in "${OPS[@]}"; do seqs+=("$o1 $o2 $o3"); done
            done
        done
        bulk_begin "EXHAUSTIVE: every sequence of <=3 ops on every permutation of 3 numbers (${#seqs[@]} x 6)"
        while IFS= read -r line; do
            for seq in "${seqs[@]}"; do
                if [ -z "$seq" ]; then : > "$TMP/in"; else printf '%s\n' $seq > "$TMP/in"; fi
                expect=$(sim "$line" "$TMP/in")
                ck_check "$expect" "$TMP/in" $line
                bulk_add "$R_WHY" "ops=[$seq] args=[$line]" "args=[$line] ops=[$seq]"
            done
        done < <(perms 3 "-5 0 7")
        bulk_end
    fi
}

# ================================================================== main ==
want pre    && sec_pre
if [ "$HAVE_PS" = 0 ] && ! want pre; then [ -x "$PS" ] && HAVE_PS=1; [ -x "$CK" ] && HAVE_CK=1; fi
if [ "$HAVE_PS" = 1 ]; then
    want ps     && sec_ps
    want perm   && sec_perm
    want shapes && sec_shapes
    want bench  && sec_bench
    want random && sec_random
else
    echo "${C_R}push_swap not found: all push_swap tests skipped${C_N}"
fi
want ck     && sec_ck
want integ  && sec_integ
want diff   && sec_diff

ELAPSED=$(( $(date +%s) - START ))
printf '\n%s================ SUMMARY ================%s\n' "$C_B" "$C_N"
printf '  %sSUCCESS: %d%s   %sFAILED: %d%s   %sWARN: %d%s   (%ds)\n' \
    "$C_G" "$N_PASS" "$C_N" "$C_R" "$N_FAIL" "$C_N" "$C_Y" "$N_WARN" "$C_N" "$ELAPSED"
if [ "$N_FAIL" -eq 0 ]; then
    printf '  %sALL TESTS SUCCESS%s\n' "$C_G" "$C_N"
    rm -f "$FAILLOG"
    exit 0
else
    printf '  %sSOME TESTS FAILED%s - full details in %s\n' "$C_R" "$C_N" "$FAILLOG"
    exit 1
fi
