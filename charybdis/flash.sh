#!/bin/bash

echo "Flashing Hawkbane's Charybdis keymap in 2 seconds..."

sleep 2s

# Test out the per-side build configation
qmk flash -kb bastardkb/charybdis/3x5/ -km hawkbane -bl uf2-split-left 
# qmk flash -kb bastardkb/charybdis/3x5 -km hawkbane
