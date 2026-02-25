[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python Setup Guide

<!-- ## Requirements

- Upgrade your operating system to the latest version. The installation instructions have been tested on the following systems:
    - macOS: macOS 11 Big Sur
    - Ubuntu: Ubuntu 20.04 LTS Focal Fossa
    - Windows: Windows 10 -->

## Supported Platforms
- macOS (Big Sur or newer)
- Ubuntu 20.04+
- Windows 10/11 (via WSL)

<!-- - Install [PyCharm Pro](https://www.jetbrains.com/pycharm). Use your Stevens email address to request a free student license (https://www.jetbrains.com/student). -->

## Install Conda

- Install either:
    - [Anaconda](https://www.anaconda.com/distribution/)
    - [Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/install) (same thing but lighter)

## Accept Conda Terms of Service (if prompted)

- Before using conda, you may need to accept the terms of service. You can do that by running:

```bash
conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main

conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r
```

## Setup on Different Operating Systems

### macOS:

<!-- - Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/). -->
- Follow the instructions in [SHIFT Python API](#shift-python-api) to create a new environment and install all SHIFT packages.
<!-- - Create a new project in PyCharm Pro:
    - Click **PyCharm** -> **Preferences...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **Conda Environment**.
    - Select **Existing environment**. -->
- If you installed Anaconda with default settings, the *Interpreter* path should look something like `/Users/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)

### Ubuntu:

<!-- - Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/). -->
- Follow the instructions in [SHIFT Python API](#shift-python-api) to create a new environment and install all SHIFT packages.
<!-- - Create a new project in PyCharm Pro:
    - Click **File** -> **Settings...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **Conda Environment**.
    - Select **Existing environment**.  -->
- If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)

### Windows (WSL required):

- For Windows, you **must use WSL**
- Install the Ubuntu subsystem using the [Windows Subsystem for Linux Installation Guide for Windows 10](https://docs.microsoft.com/en-us/windows/wsl/install-win10). After installation, you will find an Ubuntu icon in the Start menu. You can open an Ubuntu terminal by simply running this app.
- For installing Anaconda/Miniconda:
    - Please make sure you choose the Linux distribution.
    - You can browse files stored in Windows in the Ubuntu app under the `/mnt` folder. Thus, if you downloaded the Anaconda installation file to your desktop (`C:/Users/USERNAME/Desktop`), you will be able to find it in Ubuntu under `/mnt/c/Users/USERNAME/Desktop`.
    - Install Anaconda by opening the Ubuntu app and executing:

```bash
cd /mnt/c/Users/USERNAME/Desktop
./Anaconda3-yyyy.xx-Linux-x86_64.sh
```
- Follow the instructions in [SHIFT Python API](#shift-python-api) to create a new environment and install all SHIFT packages:
    - The last step ("In the Terminal") must also be run from the Ubuntu app.
- Create a new project in PyCharm Pro:
    - Click **File** -> **Settings...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **WSL**.
    - If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go!

<!-- # SHIFT Python API -->

<!-- ## 2023 Update -->
<!-- # Installing local changes:
python3 setup.py clean
python3 setup.py install

You can now see your local changes (in shift-python):
python3
import shift
....

# Installing to conda environment
python3 setup.py bdist_wheel
pip install dist/shift-2.0.1-py3.7-*.whl

You can now see these changes globally when conda env is active -->

<!-- ## Installation: -->

## SHIFT Python API

- Download our latest release from our [GitHub Releases Page](https://github.com/hanlonlab/shift-python/releases):
    - macOS: `shift_python-x.x.x-conda_macos.zip`
    - Ubuntu (including Windows Subsystem for Linux): `shift_python-x.x.x-conda_linux.zip`

- Unzip the downloaded file to somewhere you like.

- (For ARM Mac users) If you use Mac/Macbook with M1/M2 chips (ARM arch), do the following before moving to the next step:
```bash
conda config --env --set subdir osx-64
```
This step makes conda to use x86_64 architecture channel(s).

- In the Terminal:

```bash
cd [directory-you-unzipped-the-package]
conda create -n shift python=3.11 anaconda -y
conda activate shift
conda update --all -y
conda install *.tar.bz2
conda clean --all -y
```

## Module:

```python
import shift
```



## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.

<!-- [header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc DeveloperGuide.md -c ../shift-main/Templates/github.css -o DeveloperGuide.html -s --self-contained" -->

### SHIFT Python Installation

**Depending on how python was installed in your system, you may need to use `sudo` in the commands below.**

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

