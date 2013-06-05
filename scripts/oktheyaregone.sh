#!/bin/bash
wmctrl -k off
pactl -- set-sink-volume 0 10%
notify-send -t 500 "Ok they are gone"
