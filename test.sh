#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
NC=$'\033[0m'

PROG="./cub3d"
INVALID_FILES=(\
	"invalid_el(3sep).cub" \
	"invalid_el(404_asset).cub" \
	"invalid_el(color_format).cub" \
	"invalid_el(color_overflow).cub" \
	"invalid_el(element).cub" \
	"invalid_el(map_order).cub" \
	"invalid_el(dup).cub"
)
	
INVALID_MAP=(\
	"invalid_map(0player).cub" \
	"invalid_map(notclosed).cub" \
	"invalid_map(2player).cub"
)

exe() {
	echo ${RED}"${PROG} $@"${NC} ; ${PROG} $@ ;
}

if [ "$1" = "" ]; then
	echo ${GREEN}"======== Test Elements ========"${NC}
	for str in ${INVALID_FILES[@]}; do
		exe ./maps/${str}
	done
	echo ${GREEN}"======== Test Map ========"${NC}
	for map in ${INVALID_MAP[@]}; do
		exe ./maps/${map}
	done
elif [ "$1" = "default" ]; then
	exe ./maps/default.cub
fi