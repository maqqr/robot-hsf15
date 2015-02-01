#!/bin/bash

# Start blender detached from terminal
nohup blender >>/dev/null 2>>/dev/null &

echo "Blender started"

sleep 2

# Start recordscreen.py in new window
nohup x-terminal-emulator -e "recordscreen.py" >>/dev/null 2>>/dev/null &
echo "Recorder started in new terminal"

sleep 2

BLENDERWIN=`xdotool search --class Blender`
# c-up
# p
xdotool windowactivate $BLENDERWIN
sleep 0.2
xdotool mousemove --window $BLENDERWIN 400 300
sleep 0.2
xdotool click 1 ## Not needed for production
sleep 0.2
xdotool key Control+Up
xdotool key Alt+F11
xdotool key p
xdotool mousemove 3000 100


## RECORDING TIME
sleep 4

SEARCHTERM=`xdotool search --name "/bin/zsh"`
ARR=($SEARCHTERM)
xdotool windowactivate ${ARR[0]}


xdotool key Control+c
killall blender
