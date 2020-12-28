#!/bin/sh

# A modular status bar for dwm
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Dependencies: xorg-xsetroot

# Store the directory the script is running from
LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

# Change the charachter(s) used to seperate modules. If two are used, they will be placed at the start and end.
export SEP2=" | "

# Import the modules
. "$DIR/bar-functions/battery_status.sh"
. "$DIR/bar-functions/get_date.sh"
. "$DIR/bar-functions/wifi_status.sh"
# Update dwm status bar every second
while true
do
    # Append results of each func one by one to a string
    dispstr=""
    dispstr="$dispstr$(wifi_status)"
    dispstr="$dispstr$(battery_status)"
    dispstr="$dispstr$(get_date)"

    xsetroot -name " | $dispstr"
    sleep 1
done
