#!/bin/sh

dir=$1

if [ "$#" -ne 1 ]; then
	dir=.
fi

find -E $dir -iregex '.*\.(s|c|h)$' -exec wc -l {} \;
