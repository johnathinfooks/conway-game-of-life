#!/usr/bin/env bash
#
# thank opus 4.7 for writing this <3 i am not writing all that
# ============================================================
#  Configuration — edit these to customize the build
# ============================================================
PROJECT_NAME="Conway's Game of Life"
BINARY_NAME="bin"
COMPILER="gcc"
SRC_EXT="c"
CFLAGS="-lraylib -lm"
SRC_DIR="src"
BIN_DIR="build"
# ============================================================

set -u

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[1;33m'
BLUE=$'\033[0;34m'
DIM=$'\033[2m'
BOLD=$'\033[1m'
NC=$'\033[0m'

# Nanosecond timer with graceful fallback (e.g. macOS BSD date).
now_ms() {
    local t
    t=$(date +%s%N 2>/dev/null)
    if [[ "$t" == *N ]]; then
        echo $(( $(date +%s) * 1000 ))
    else
        echo $(( t / 1000000 ))
    fi
}

start_ms=$(now_ms)

echo "${BOLD}${BLUE}==> Building ${PROJECT_NAME}${NC}"
echo

if [ ! -d "$SRC_DIR" ]; then
    echo "${RED}${BOLD}Error:${NC} source directory '${SRC_DIR}' not found"
    exit 1
fi

mapfile -t sources < <(find "$SRC_DIR" -type f -name "*.${SRC_EXT}" | sort)

if [ "${#sources[@]}" -eq 0 ]; then
    echo "${RED}${BOLD}Error:${NC} no .${SRC_EXT} files found in ${SRC_DIR}/"
    exit 1
fi

mkdir -p "$BIN_DIR"
output_path="${BIN_DIR}/${BINARY_NAME}"

echo "${BOLD}Compile command:${NC}"
echo "  ${DIM}${COMPILER} ${CFLAGS} ${sources[*]} -o ${output_path}${NC}"
echo
echo "${BOLD}Compiling...${NC}"

compile_output=$("$COMPILER" "${sources[@]}" -o "$output_path" $CFLAGS 2>&1)
compile_status=$?

end_ms=$(now_ms)
elapsed_ms=$(( end_ms - start_ms ))
elapsed_sec=$(awk "BEGIN {printf \"%.3f\", ${elapsed_ms}/1000}")

echo
echo "${BOLD}=========================================${NC}"
echo "${BOLD}  Build Review${NC}"
echo "${BOLD}=========================================${NC}"
echo "  Project:       ${PROJECT_NAME}"
echo "  Compiler:      ${COMPILER}"
echo "  Output binary: ${output_path}"
echo "  Source files:  ${#sources[@]}"
for src in "${sources[@]}"; do
    echo "    - ${src}"
done
echo "  Elapsed time:  ${elapsed_sec}s"

if [ "$compile_status" -ne 0 ]; then
    echo "  Status:        ${RED}${BOLD}FAILED${NC}"
    echo "${BOLD}=========================================${NC}"
    echo
    echo "${RED}${BOLD}Compile errors:${NC}"
    echo "${compile_output}"
    exit "$compile_status"
fi

echo "  Status:        ${GREEN}${BOLD}SUCCESS${NC}"
echo "${BOLD}=========================================${NC}"

if [ -n "$compile_output" ]; then
    echo
    echo "${YELLOW}${BOLD}Compiler warnings:${NC}"
    echo "${compile_output}"
fi
