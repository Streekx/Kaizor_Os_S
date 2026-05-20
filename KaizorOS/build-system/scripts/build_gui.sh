#!/bin/sh
set -e

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"

echo "[Kaizor] Build started..."
echo "[Kaizor] Root: $ROOT_DIR"

BUILD_OUT="$ROOT_DIR/build-system/work/gui-build"
BIN_OUT="$ROOT_DIR/build-system/work/gui-bin"

mkdir -p "$BUILD_OUT"
mkdir -p "$BIN_OUT"

build_project() {
    NAME="$1"
    DIR="$2"

    echo ""
    echo "[Kaizor] Building: $NAME"
    echo "[Kaizor] Path: $DIR"

    mkdir -p "$DIR/build"
    cd "$DIR/build"

    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(sysctl -n hw.ncpu)

    cp "$NAME" "$BIN_OUT/"
}

# Build compositor
build_project "kaizor-compositor" "$ROOT_DIR/gui/compositor"

# Build panel
build_project "kaizor-panel" "$ROOT_DIR/gui/panel"

# Build launcher
build_project "kaizor-launcher" "$ROOT_DIR/gui/launcher"

echo ""
echo "[Kaizor] GUI build finished."
echo "[Kaizor] Binaries stored in: $BIN_OUT"
