[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python

## Requirements

- Upgrade your operating system to the latest version. The installation instructions have been tested on the following systems:
    - macOS: macOS 11 Big Sur
    - Ubuntu: Ubuntu 20.04 LTS Focal Fossa
    - Windows: Windows 10

## Installation
- Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/) or [Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/main).
- Follow the instructions in [SHIFT Python API](#shift-python-api) to create a new environment and install all SHIFT packages.

### macOS:
- If you installed Anaconda with default settings, the *Interpreter* path should look something like `/Users/USERNAME/anaconda3/envs/shift/bin/python`.

### Ubuntu:
- If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.

### Windows:

- Install the Ubuntu subsystem using the [Windows Subsystem for Linux Installation Guide for Windows 10](https://docs.microsoft.com/en-us/windows/wsl/install-win10). After installation, you will find an Ubuntu icon in the Start menu. You can open an Ubuntu terminal by simply running this app.
- For installing Miniconda or Anaconda, please make sure you choose the Linux distribution.
- You can browse files stored in Windows in the Ubuntu app under the `/mnt` folder. Thus, if you downloaded the Anaconda installation file to your desktop (`C:/Users/USERNAME/Desktop`), you will be able to find it in Ubuntu under `/mnt/c/Users/USERNAME/Desktop`.
- Install Anaconda by opening the Ubuntu app and executing:
```bash
cd /mnt/c/Users/USERNAME/Desktop
./Anaconda3-yyyy.xx-Linux-x86_64.sh
```
- Follow the instructions in [SHIFT Python API](#shift-python-api) to create a new environment and install all SHIFT packages:
    - The last step ("In the Terminal") must also be run from the Ubuntu app.
If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.

## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.

## SHIFT Python API

### Installation:

- Download our latest release from our [GitHub Releases Page](https://github.com/hanlonlab/shift-python/releases):
    - macOS: shift_python-x.x.x-conda_macos.zip
    - Ubuntu (including Windows Subsystem for Linux): shift_python-x.x.x-conda_linux.zip

- Unzip the downloaded file to somewhere you like.

- (For ARM Mac users) If you use Mac/Macbook with M1/M2 chips (ARM arch), do the following before moving to the next step:
```bash
conda config --env --set subdir osx-64
```
This step makes conda to use x86_64 architecture channel(s).

- In the Terminal:

```bash
cd [directory-you-unzipped-the-package]
conda create -n shift python=3.7 anaconda -y # might need to change version
conda activate shift
conda update --all -y
conda install *.tar.bz2
conda clean --all -y
```

### Module:

```python
import shift
```

# SHIFT Python Developer Guide

## Ubuntu and macOS

### Required Libraries

**Please refer to the other required libraries in the SHIFT Developer Guide.**

#### SHIFT Core Client

Use the installer in the root folder of the SHIFT project:

In shift-main:
- In the Terminal: `sudo ./install.sh -m LC`

#### pybind11:

Choose a location to keep the pybind11 source files (for debugging purposes), e.g. a "C++" folder in your home directory, and then:

```sh
git submodule update --init --recursive

# setup environment
uv venv --python python3.13
source .venv/bin/activate
uv pip install setuptools
uv pip install ./pybind11

# now make the build dir and build
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=Release -DPYBIND11_PYTHON_VERSION=3.13 ..
make
cd ..

# Choice:
# 1) install into current environment
python setup.py install

# 2) build the package as a wheel
python setup.py bdist_wheel
```

---

### SHIFT Python Installation

**Depending on how python was installed in your system, you may need to use `sudo` in the commands below.**

If you run into any errors, make sure that `pybind11` is installed in the `shift` env:
```bash
pip install pybind11
```

To build SHIFT Python:

- In the Terminal: `# python3 setup.py build`

To install SHIFT Python:

- In the Terminal: `# python3 setup.py install`

To uninstall SHIFT Python:

- In the Terminal: `# pip3 uninstall shift`

To clean the build directories:

- In the Terminal: `# python3 setup.py clean`

---

## Windows

### [TODO] Required Libraries

---

### [TODO] SHIFT Python Installation

---

## 2023 Update
# Installing local changes:

```
python3 setup.py clean
python3 setup.py install
```

You can now see your local changes (in shift-python):

```
python3 import shift
```
....

# Installing to conda environment
python3 setup.py bdist_wheel
pip install dist/shift-2.0.1-py3.7-*.whl

You can now see these changes globally when conda env is active