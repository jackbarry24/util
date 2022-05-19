#!/bin/sh

# Globals

STATE=Indiana
CITY=
CITYBOOL=0
URL=https://www.zipcodestogo.com/

# Functions

usage() {
    cat 1>&2 <<EOF
    
Usage: zipcode.sh
-c      CITY    Which city to search
-s      STATE   Which state to search (Indiana)

If no CITY is specified, then all the zip codes for the STATE are displayed.
EOF
    exit $1
}

get_zipcodes() {

    if [ $CITYBOOL -eq 1 ]; then
        if [ -z "$CITY" ]; then
            curl -s $URL"$STATE"/ | grep -E "zipcodestogo.com" | grep -Eo '[[:digit:]]{5}' | uniq
        else
            curl -s $URL"$STATE"/ | grep -E "zipcodestogo.com" | grep "/$CITY/" | grep -Eo '[[:digit:]]{5}' | uniq
        fi
    else  
        curl -s $URL"$STATE"/ | grep -E "zipcodestogo.com" | grep -Eo '[[:digit:]]{5}' | uniq
    fi
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
    -h) usage 0;;
    -s) STATE=$(echo "$2" | sed 's/\s/%20/');;
    -c) CITYBOOL=1; CITY="$2";
    # *) usage 1;;
    esac
    shift
done

# Filter Pipeline(s)

get_zipcodes
