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

test -e "${HOME}/Miniconda/etc/profile.d/conda.sh" && source "${HOME}/Miniconda/etc/profile.d/conda.sh"
test -e "${HOME}/miniconda/etc/profile.d/conda.sh" && source "${HOME}/miniconda/etc/profile.d/conda.sh"

log.info "Activating shift conda environment..."
conda activate shift

log.info "Preparing environment variables..."
case ${OSTYPE} in
    linux* )  # Linux
		bld_path="${CONDA_PREFIX}/conda-bld/linux-64"
        ;;
    darwin* ) # macOS
		bld_path="${CONDA_PREFIX}/conda-bld/osx-64"
        ;;
esac
log.plain "    USER (user name): ${USER}"
log.plain "    bld_path (conda pkg build path): ${bld_path}"

log.info "Cleaning previous builds and installs..."
rm -rf ${bld_path}/quickfix* >/dev/null 2>&1
rm -rf ${bld_path}/shift* >/dev/null 2>&1
conda build purge
conda remove -y -q quickfix >/dev/null 2>&1
conda remove -y -q shift-miscutils >/dev/null 2>&1
conda remove -y -q shift-coreclient >/dev/null 2>&1
conda remove -y -q shift-python >/dev/null 2>&1

sleep 2

# $1 dir name
# $2 pkg name
function install() {
	log.info "Building $2..."
	if ${CONDA_PREFIX}/bin/conda-build $1 ;
	then
		log.info "Built $2."
	else
		log.err "Failed to build $2."
		exit
	fi

	log.info "Installing $2..."
	if conda install ${bld_path}/$1* ;
	then
		log.info "Installed $2."
	else
		log.err "Failed to install $2."
		exit
	fi
}

install quickfix QuickFIX
install shift-miscutils SHIFT-MiscUtils
install shift-coreclient SHIFT-CoreClient
install shift-python SHIFT-Python
