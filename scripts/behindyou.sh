#!/bin/bash
wmctrl -k on
pactl -- set-sink-volume 0 0%
notify-send -t 400 "Someone is behind you"

