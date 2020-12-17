#!/bin/bash

# You can call this script like this:
# $./brightness.sh up
# $./brightness.sh down

function get_brightness {
    brightnessctl | grep % | cut -d '(' -f 2 | cut -d '%' -f 1
}

function send_notification {
    brightness=`get_brightness`
    dunstify -i	/home/marc/suckless/dwm/addons/dunst_scripts/brightness.png -r 1701	" $brightness%"
}

case $1 in
    up)
	brightnessctl --save s 1%+
	send_notification
	;;
    down)
	brightnessctl --save s 1%-
	send_notification
	;;
esac
