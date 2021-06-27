#!/bin/bash

#call with brightness.sh <device> <up/down>

function send_notification {
    new_brightness=$( echo "($new_brightness * 100) / 1" | bc -l | cut -d. -f1)
    dunstify -i	/home/marc/working/environment/dwm/addons/dunst_scripts/brightness.png -r 1701	" $new_brightness%"
}

inc=.05
brightness=$(xrandr --verbose | grep -w -A 5 $1 | grep Brightness | awk '{print $2}')
if [ $2 = "up" ]; then
    if (( $(echo "$brightness >= 1.0" | bc -l) )); then
        new_brightness=1
        send_notification
        exit 0
    fi
    new_brightness=$(echo $brightness + $inc | bc )
elif [ $2 = "down" ]; then
    if (( $(echo "$brightness <= 0.0" | bc -l) )); then
        new_brightness=0
        send_notification
        exit 0
    fi
    new_brightness=$(echo $brightness - $inc | bc )
fi
xrandr --output $1 --brightness $new_brightness
send_notification
