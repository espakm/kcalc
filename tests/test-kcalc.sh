#!/bin/bash

set -e

fail() {
    echo "Test failed."
    exit 1
}

trap fail ERR

source_dir="$(dirname ${BASH_SOURCE[0]})/.."
build_dir="${source_dir}/build"
kcalc_binary="${build_dir}/apps/kcalc"

prefix_input=$(cat << EOF
3
+ 1 2
+ 1 * 2 3
+ * 1 2 3
- / 10 + 1 1 * 1 2
- 0 3
/ 3 2
EOF
)

expected_prefix_output=$(cat << EOF
3
3
7
5
3
-3
1.5
EOF
)

prefix_output=$(${kcalc_binary} --prefix <<< "${prefix_input}")

[[ "${prefix_output}" == "${expected_prefix_output}" ]] || fail

infix_input=$(cat << EOF
( 1 + 2 )
( 1 + ( 2 * 3 ) )
( ( 1 * 2 ) + 3 )
( ( ( 1 + 1 ) / 10 ) - ( 1 * 2 ) )
EOF
)

expected_infix_output=$(cat << EOF
3
7
5
-1.8
EOF
)

infix_output=$(${kcalc_binary} --infix <<< "${infix_input}")

[[ "${infix_output}" == "${expected_infix_output}" ]] || fail

infix_output=$(${kcalc_binary} <<< "${infix_input}")

[[ "${infix_output}" == "${expected_infix_output}" ]] || fail

echo "Test passed."
