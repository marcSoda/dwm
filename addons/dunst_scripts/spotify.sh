#!/bin/bash
function send_notification {
    artist=`playerctl metadata artist`
    song=`playerctl metadata title`
    album=`playerctl metadata album`
    dunstify -r 1701 "$artist" "$song\n$album"
}

case $1 in
    play-pause)
	playerctl play-pause
	;;
    next)
	playerctl next
	send_notification
	;;
    previous)
	playerctl previous
	send_notification
	;;
esac
