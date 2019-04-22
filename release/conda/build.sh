#!/bin/bash

# verbose
if [ "$1" == "-v" ]; 
then
VERBOSE_OPTION=""
else
VERBOSE_OPTION=" > /dev/null 2>&1"
fi

# colors
CLR='\033[0m'
RED='\033[1;31m'
YEL='\033[1;33m'
GRN='\033[1;32m'
WTE='\033[1;37m'

# prints
function log.plain() {
	echo -e "${WTE}$1${CLR}"
}

function log.info() {
	echo -e "${GRN}SHIFT: $1${CLR}"
}

function log.warn() {
	echo -e "${YEL}SHIFT: $1${CLR}"
}

function log.err() {
	echo -e "${RED}SHIFT: $1${CLR}"
}

# utilities
function util.absPath(){
 	cd "$(dirname "$1")"
	printf "%s/%s\n" "$(pwd)" "$(basename "$1")"
	cd "$OLDPWD"
}

# activate conda environment
log.info "activating conda environment..."
source /home/han/anaconda3/bin/activate shift36

# prepare environment variables
log.info "preparing environment variables..."
bld_path=$(util.absPath "${CONDA_PREFIX}/../../conda-bld/linux-64")
log.plain "    conda pkg build path: ${bld_path}"

# clean previous builds and installs
conda remove -y -q quickfix > /dev/null 2>&1
conda remove -y -q shift-miscutils > /dev/null 2>&1
conda remove -y -q shift-coreclient > /dev/null 2>&1
conda remove -y -q shift-python > /dev/null 2>&1

sleep 2

log.info "building quickfix..."
if /home/han/anaconda3/bin/conda-build quickfix ;  
then
	log.info "built QuickFIX"
else
	log.err "fail to build QuickFIX"
	exit
fi

log.info "installing quickfix..."
if conda install ${bld_path}/quickfix* ; 
then
	log.info "installed QuickFIX"
else
	log.err "fail to build QuickFIX"
	exit
fi





