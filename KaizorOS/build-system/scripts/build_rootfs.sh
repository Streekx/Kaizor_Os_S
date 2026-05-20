#!/bin/sh
set -e

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"

WORK_DIR="$ROOT_DIR/build-system/work"
ROOTFS_DIR="$WORK_DIR/rootfs"
BIN_DIR="$WORK_DIR/gui-bin"
OVERLAY_DIR="$ROOT_DIR/build-system/overlay"

echo "[Kaizor] Building root filesystem..."
echo "[Kaizor] Root: $ROOT_DIR"

mkdir -p "$ROOTFS_DIR"
mkdir -p "$ROOTFS_DIR/usr/local/bin"
mkdir -p "$ROOTFS_DIR/etc"

echo "[Kaizor] Cleaning old rootfs..."
rm -rf "$ROOTFS_DIR"/*
mkdir -p "$ROOTFS_DIR/usr/local/bin"
mkdir -p "$ROOTFS_DIR/etc"

echo "[Kaizor] Copying overlay files..."
cp -R "$OVERLAY_DIR/"* "$ROOTFS_DIR/"

echo "[Kaizor] Installing GUI binaries..."
if [ ! -f "$BIN_DIR/kaizor-compositor" ]; then
  echo "[Kaizor] ERROR: kaizor-compositor not found. Run build_gui.sh first."
  exit 1
fi

cp "$BIN_DIR/kaizor-compositor" "$ROOTFS_DIR/usr/local/bin/"
cp "$BIN_DIR/kaizor-panel" "$ROOTFS_DIR/usr/local/bin/"
cp "$BIN_DIR/kaizor-launcher" "$ROOTFS_DIR/usr/local/bin/"

chmod +x "$ROOTFS_DIR/usr/local/bin/kaizor-compositor"
chmod +x "$ROOTFS_DIR/usr/local/bin/kaizor-panel"
chmod +x "$ROOTFS_DIR/usr/local/bin/kaizor-launcher"
chmod +x "$ROOTFS_DIR/usr/local/bin/start-kaizor"

echo "[Kaizor] Root filesystem prepared at:"
echo "         $ROOTFS_DIR"
