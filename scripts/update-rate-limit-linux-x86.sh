#!/bin/bash

GRN='\033[0;32m'
YLW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GRN}Starting SHIFT Linux / WSL / UTM (Intel) Update...${NC}"

# Source conda from all common locations (dynamic first, then fallbacks)
CONDA_PATH=$(conda info --base 2>/dev/null)
[ -n "$CONDA_PATH" ] && source "$CONDA_PATH/etc/profile.d/conda.sh"
test -e "${HOME}/Miniconda/etc/profile.d/conda.sh"  && source "${HOME}/Miniconda/etc/profile.d/conda.sh"
test -e "${HOME}/miniconda/etc/profile.d/conda.sh"  && source "${HOME}/miniconda/etc/profile.d/conda.sh"
test -e "${HOME}/miniconda3/etc/profile.d/conda.sh" && source "${HOME}/miniconda3/etc/profile.d/conda.sh"
test -e "${HOME}/anaconda/etc/profile.d/conda.sh"   && source "${HOME}/anaconda/etc/profile.d/conda.sh"
test -e "${HOME}/anaconda3/etc/profile.d/conda.sh"  && source "${HOME}/anaconda3/etc/profile.d/conda.sh"

if ! conda info --envs | grep -qE "^\s*shift(\s|$)"; then
    echo -e "${RED}FAILURE: Conda environment 'shift' not found.${NC}"
    exit 1
fi

conda activate shift

conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main 2>/dev/null || true
conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r    2>/dev/null || true

echo -e "${GRN}Updating 'shift' environment packages...${NC}"
conda remove -y -q quickfix shift-miscutils shift-coreclient shift-python 2>/dev/null || true

mkdir -p temp_shift && cd temp_shift || exit

ZIP_FILE="beta_shift_python-2.1.0-conda_linux_py311.zip"
URL="https://github.com/hanlonlab/shift-python/releases/download/v2.0.1/$ZIP_FILE"

if wget -q --show-progress "$URL"; then
    unzip -q -j "$ZIP_FILE"
    conda install *.conda -y
    conda clean --all -y
else
    echo -e "${RED}Update download failed.${NC}"
    cd .. && rm -rf temp_shift
    exit 1
fi

cd .. && rm -rf temp_shift

echo -e "\n${GRN}UPDATE COMPLETE!${NC}"
echo -e "1. Run: ${YLW}source ~/.bashrc${NC}"
echo -e "2. Run: ${YLW}conda activate shift${NC}"