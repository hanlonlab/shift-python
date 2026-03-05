#!/bin/bash

GRN='\033[0;32m'
YLW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GRN}Starting SHIFT Setup (ARM + Rosetta)...${NC}"
echo -e "${YLW}Please enter your password if prompted.${NC}"

sudo apt-get update -qq
sudo apt-get install -y -qq wget unzip binfmt-support qemu-user-static

if [ ! -d "/mnt/rosetta" ]; then
    sudo mkdir -p /mnt/rosetta
    sudo mount -t virtiofs rosetta /mnt/rosetta 2>/dev/null
fi

if [ ! -f "/mnt/rosetta/rosetta" ]; then
    echo -e "${RED}ERROR: Rosetta mount failed.${NC}"
    echo -e "1. Shut down the VM."
    echo -e "2. Go to UTM Settings > Sharing."
    echo -e "3. Ensure 'Enable Rosetta' is checked."
    echo -e "4. Ensure the VirtioFS Tag is named 'rosetta'."
    exit 1
fi

sudo /usr/sbin/update-binfmts --install rosetta /mnt/rosetta/rosetta \
    --magic "\x7fELF\x02\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x3e\x00" \
    --mask "\xff\xff\xff\xff\xff\xfe\xfe\x00\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff" \
    --credentials yes --preserve no --fixed yes 2>/dev/null

CONDA_DIR="$HOME/miniconda3"
if [ ! -d "$CONDA_DIR" ]; then
    wget -q "https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-aarch64.sh" -O ~/miniconda.sh
    bash ~/miniconda.sh -b -u -p "$CONDA_DIR"
    rm ~/miniconda.sh
fi

source "$CONDA_DIR/etc/profile.d/conda.sh"
"$CONDA_DIR/bin/conda" init bash
eval "$(conda shell.bash hook)"

conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main || true
conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r || true

conda env remove -n shift -y > /dev/null 2>&1
CONDA_SUBDIR=linux-64 conda create -n shift python=3.11 -y || exit 1
conda activate shift
conda config --env --set subdir linux-64

mkdir -p temp_shift && cd temp_shift || exit
ZIP_FILE="beta_shift_python-2.0.1-conda_linux_py311.zip"
URL="https://github.com/hanlonlab/shift-python/releases/download/v2.0.1/$ZIP_FILE"

if wget -q --show-progress "$URL"; then
    unzip -q -j "$ZIP_FILE"
    conda install *.bz2 -y
    conda clean --all -y
fi

cd .. && rm -rf temp_shift

echo -e "\n${GRN}SETUP COMPLETE!${NC}"
echo -e "1. Run: ${YLW}source ~/.bashrc${NC}"
echo -e "2. Run: ${YLW}conda activate shift${NC}"