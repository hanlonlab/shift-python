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
function util.absPath() {
 	cd "$(dirname "$1")"
	printf "%s/%s\n" "$(pwd)" "$(basename "$1")"
	cd "$OLDPWD"
}

# activate conda environment
log.info "activating conda environment..."
source /Users/$USER/miniconda/bin/activate shift

# prepare environment variables
log.info "preparing environment variables..."
bld_path=$(util.absPath "${CONDA_PREFIX}/../../conda-bld/osx-64")
log.plain "    USER (user name): ${USER}"
log.plain "    bld_path (conda pkg build path): ${bld_path}"

# clean previous builds and installs
log.info "cleaning previous builds and installs..."
rm -rf /Users/$USER/miniconda/conda-bld/osx-64/quickfix* >/dev/null 2>&1
rm -rf /Users/$USER/miniconda/conda-bld/osx-64/shift* >/dev/null 2>&1
conda build purge
conda remove -y -q quickfix >/dev/null 2>&1
conda remove -y -q shift-miscutils >/dev/null 2>&1
conda remove -y -q shift-coreclient >/dev/null 2>&1
conda remove -y -q shift-python >/dev/null 2>&1

sleep 2

# $1 dir name
# $2 pkg name
function install() {
	log.info "building $2..."
	if /Users/$USER/miniconda/bin/conda-build $1 ;  
	then
		log.info "built $2"
	else
		log.err "fail to build $2"
		exit
	fi
	
	log.info "installing $2..."
	if conda install ${bld_path}/$1* ; 
	then
		log.info "installed $2"
	else
		log.err "fail to install $@"
		exit
	fi
}

install quickfix QuickFIX
install shift-miscutils SHIFT-MiscUtils
install shift-coreclient SHIFT-CoreClient
install shift-python SHIFT-Python
