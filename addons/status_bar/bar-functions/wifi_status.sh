#!/bin/sh

wifi_status() {
    STATUS=$(ip a s wlp2s0 | grep state | cut -d ' ' -f 9)

    printf "%s" "$SEP1"
    if [ "$STATUS" = "UP" ]; then
	printf ""
    else
	printf ""
    fi
    printf "%s" "$SEP2"
}

wifi_status
