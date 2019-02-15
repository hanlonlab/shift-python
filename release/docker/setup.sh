conda create -y -n shift python=3.7
source /opt/conda/etc/profile.d/conda.sh
conda activate shift
wget -qO- https://github.com/hanlonlab/shift-python/releases/download/0.0.1/shift-python_0.0.1_conda_linux64_py37.zip | bsdtar -xvf-
cd shift*
conda install *.tar.bz2