#!/bin/bash

GRN='\033[0;32m'
YLW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GRN}Starting SHIFT Linux / WSL / UTM (Intel) Setup...${NC}"

if ! command -v wget &> /dev/null; then
    sudo apt-get update && sudo apt-get install wget unzip -y
fi

if ! command -v conda &> /dev/null; then
    ARCH=$(uname -m)
    INSTALLER="Miniconda3-latest-Linux-${ARCH}.sh"
    wget "https://repo.anaconda.com/miniconda/$INSTALLER" -O ~/miniconda.sh
    bash ~/miniconda.sh -b -u -p "$HOME/miniconda3"
    rm ~/miniconda.sh
    CONDA_PATH="$HOME/miniconda3"
else
    CONDA_PATH=$(conda info --base)
fi

source "$CONDA_PATH/etc/profile.d/conda.sh"
"$CONDA_PATH/bin/conda" init bash

eval "$(conda shell.bash hook)"

conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main || true
conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r || true

echo -e "${GRN}Configuring 'shift' environment...${NC}"
conda env remove -n shift -y > /dev/null 2>&1
conda create -n shift python=3.11 -y || { echo -e "${RED}Setup failed. Check ToS status.${NC}"; exit 1; }
conda activate shift

mkdir -p temp_shift && cd temp_shift || exit
ZIP_FILE="beta_shift_python-2.0.1-conda_linux_py311.zip"
URL="https://github.com/hanlonlab/shift-python/releases/download/v2.0.1/$ZIP_FILE"

if wget --show-progress "$URL"; then
    unzip -j "$ZIP_FILE"
    conda install *.bz2 -y
    conda clean --all -y
fi

cd .. && rm -rf temp_shift

echo -e "\n${GRN}SETUP COMPLETE!${NC}"
echo -e "1. Run: ${YLW}source ~/.bashrc${NC}"
echo -e "2. Run: ${YLW}conda activate shift${NC}"