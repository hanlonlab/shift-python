# Set the base image using anaconda3
FROM continuumio/anaconda3:latest

# shift-python maintainer
MAINTAINER Han Zheng (zhenghanecho@gmail.com)

# Update all conda packages
RUN conda update --all -y

# Install extra packages for the algorithmic trading competition
# RUN conda install joblib && \
#     conda install tensorflow==1.9.0

# Install shift-python
RUN wget -qO- https://github.com/hanlonlab/shift-python/releases/download/0.0.1/shift-python_0.0.1_conda_linux64_py37.zip | bsdtar -xvf- && \
    cd shift* && \
    conda install *.tar.bz2

# Clean conda packages cache
RUN conda clean --all -y

# Set working directory 
WORKDIR /home/notebooks

# Run shell command for notebook on start 
CMD jupyter notebook --port=8888 --no-browser --ip=0.0.0.0 --allow-root
