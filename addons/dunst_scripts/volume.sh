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
    dunstify -i	/home/marc/working/environment/dwm/addons/dunst_scripts/volume.png -r 1701	" $volume%"
}

case $1 in
    up)
	# Set the volume on (if it was muted)
	amixer -D pulse set Master on > /dev/null
	# Up the volume (+ 5%)
	if [ `get_volume` -lt  150 ] ; then
	    # for SINK in `pacmd list-sinks | grep 'index:' | cut -b12-`
	    for SINK in `pacmd list-sinks | grep "name: " | cut -d '<' -f 2 | cut -d '>' -f 1`
	    do
		# printf "%s\n" $SINK
		if [ $SINK == `pacmd stat | grep 'Default sink name: ' | cut -d ' ' -f 4` ] ; then
		    pactl set-sink-volume $SINK +5%
		fi
	    done
	fi
	send_notification
	;;
    down)
	amixer -D pulse set Master on > /dev/null
	for SINK in `pacmd list-sinks | grep 'index:' | cut -b12-`
	do
	pactl set-sink-volume $SINK -5%
	done
	send_notification
	;;
    mute)
# Toggle mute
	amixer -D pulse set Master 1+ toggle > /dev/null
	if is_mute ; then
	    dunstify -i /home/marc/working/environment/dwm/addons/dunst_scripts/volume.png -r 1701 -u normal "Mute"
	else
	    send_notification
	fi
esac
