#!/bin/sh
set -e

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"

echo "[Kaizor] Cleaning build directories..."

rm -rf "$ROOT_DIR/gui/compositor/build"
rm -rf "$ROOT_DIR/gui/panel/build"
rm -rf "$ROOT_DIR/gui/launcher/build"

rm -rf "$ROOT_DIR/build-system/work"

echo "[Kaizor] Clean complete."
