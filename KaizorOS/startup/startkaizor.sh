#!/bin/bash

export DISPLAY=:0

echo "Starting Kaizor OS..."

sleep 1

# Wallpaper
~/Kaizor_Os_S/KaizorOS/gui/wallpaper/build/kaizor-wallpaper &

sleep 1

# Topbar
~/Kaizor_Os_S/KaizorOS/gui/topbar/build/kaizor-topbar &

sleep 1

# Dock
~/Kaizor_Os_S/KaizorOS/gui/dock/build/kaizor-dock &

sleep 1

# Search
~/Kaizor_Os_S/KaizorOS/gui/search/build/kaizor-search &

sleep 1

# Notifications
~/Kaizor_Os_S/KaizorOS/gui/notifications/build/kaizor-notifications &

sleep 1

# Power Menu
~/Kaizor_Os_S/KaizorOS/gui/powermenu/build/kaizor-powermenu &

sleep 1

# Settings
~/Kaizor_Os_S/KaizorOS/gui/settings/build/kaizor-settings &

echo "Kaizor OS V1 Started"
