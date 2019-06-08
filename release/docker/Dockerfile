# Set the base image using anaconda3
FROM continuumio/anaconda3:5.2.0

# shift-python maintainer
MAINTAINER Han Zheng (zhenghanecho@gmail.com)

# Set correct time zone
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update all conda packages
RUN conda update --all -y

# Install extra packages for the algorithmic trading competition
RUN conda install joblib && \
    conda install keras && \
    conda install tensorflow
RUN pip install pymdptoolbox

# Install shift-python
RUN wget -qO- https://github.com/hanlonlab/shift-python/releases/download/v1.2.5/shift-python_1.2.5_conda_linux.zip | bsdtar -xvf- && \
    cd shift* && \
    conda install *.tar.bz2

# Clean conda packages cache
RUN conda clean --all -y

# Generate a notebook server config
RUN jupyter notebook --generate-config

# Set working directory 
WORKDIR /home/notebooks

# Run shell command for notebook on start 
CMD jupyter notebook --port=8888 --no-browser --ip=0.0.0.0 --allow-root
