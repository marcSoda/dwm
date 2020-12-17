#!/bin/bash

# Written by sebastiencs on github

# You can call this script like this:
# $./volume.sh up
# $./volume.sh down
# $./volume.sh mute

function get_volume {
    amixer get Master | grep '%' | head -n 1 | cut -d '[' -f 2 | cut -d '%' -f 1
}

function is_mute {
    amixer get Master | grep '%' | grep -oE '[^ ]+$' | grep off > /dev/null
}

function send_notification {
    volume=`get_volume`
    dunstify -i	/home/marc/suckless/dwm/addons/dunst_scripts/volume.png -r 1701	" $volume%"
}

case $1 in
    up)
	# Set the volume on (if it was muted)
	amixer -D pulse set Master on > /dev/null
	# Up the volume (+ 5%)
	amixer -D pulse sset Master 5%+ > /dev/null
	send_notification
	;;
    down)
	amixer -D pulse set Master on > /dev/null
	amixer -D pulse sset Master 5%- > /dev/null
	send_notification
	;;
    mute)
    	# Toggle mute
	amixer -D pulse set Master 1+ toggle > /dev/null
	#instead of send_notification, force the volume to read 0 when muted because the volume from get_volume() is not technically 0
	dunstify -i	/home/marc/suckless/dwm/addons/dunst_scripts/volume.png -r 1701	" 0%"
	;;
esac
