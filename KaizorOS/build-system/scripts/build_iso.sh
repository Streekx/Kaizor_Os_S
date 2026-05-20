#!/bin/sh
set -e

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"

WORK_DIR="$ROOT_DIR/build-system/work"
ROOTFS_DIR="$WORK_DIR/rootfs"
OUTPUT_DIR="$ROOT_DIR/build-system/output"

echo "[Kaizor] ISO build started..."
echo "[Kaizor] Root: $ROOT_DIR"

if [ ! -d "$ROOTFS_DIR" ]; then
  echo "[Kaizor] ERROR: rootfs not found."
  echo "[Kaizor] Run build_rootfs.sh first."
  exit 1
fi

mkdir -p "$OUTPUT_DIR"

ISO_NAME="KaizorOS-v0.1.iso"
ISO_PATH="$OUTPUT_DIR/$ISO_NAME"

echo "[Kaizor] Preparing ISO output..."

# Placeholder ISO (v0.1 pipeline base)
# Real FreeBSD bootable ISO build will be added in v0.2 using makefs/mkimg.

echo "Kaizor OS ISO placeholder" > "$ISO_PATH"
echo "RootFS path: $ROOTFS_DIR" >> "$ISO_PATH"
echo "Build time: $(date)" >> "$ISO_PATH"

echo "[Kaizor] ISO build completed:"
echo "         $ISO_PATH"
