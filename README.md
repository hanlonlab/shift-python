[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python

## Requirements

- Upgrade your operating system to the latest version. The installation instructions have been tested on the following systems:
    - macOS: macOS 11 Big Sur
    - Ubuntu: Ubuntu 20.04 LTS Focal Fossa
    - Windows: Windows 10

- Install [PyCharm Pro](https://www.jetbrains.com/pycharm). Use your Stevens email address to request a free student license (https://www.jetbrains.com/student).

## Installation

### macOS:

- Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/).
- Follow the instructions in [SHIFT Python API](https://github.com/hanlonlab/shift-python/wiki/SHIFT-Python-API) to create a new environment and install all SHIFT packages.
- Create a new project in PyCharm Pro:
    - Click **PyCharm** -> **Preferences...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **Conda Environment**.
    - Select **Existing environment**. If you installed Anaconda with default settings, the *Interpreter* path should look something like `/Users/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)

### Ubuntu:

- Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/).
- Follow the instructions in [SHIFT Python API](https://github.com/hanlonlab/shift-python/wiki/SHIFT-Python-API) to create a new environment and install all SHIFT packages.
- Create a new project in PyCharm Pro:
    - Click **File** -> **Settings...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **Conda Environment**.
    - Select **Existing environment**. If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)

### Windows:

- Install the Ubuntu subsystem using the [Windows Subsystem for Linux Installation Guide for Windows 10](https://docs.microsoft.com/en-us/windows/wsl/install-win10). After installation, you will find an Ubuntu icon in the Start menu. You can open an Ubuntu terminal by simply running this app.
- Download and install the latest version of [Anaconda](https://www.anaconda.com/distribution/):
    - Please make sure you choose the Linux distribution.
    - You can browse files stored in Windows in the Ubuntu app under the `/mnt` folder. Thus, if you downloaded the Anaconda installation file to your desktop (`C:/Users/USERNAME/Desktop`), you will be able to find it in Ubuntu under `/mnt/c/Users/USERNAME/Desktop`.
    - Install Anaconda by opening the Ubuntu app and executing:
```bash
cd /mnt/c/Users/USERNAME/Desktop
./Anaconda3-yyyy.xx-Linux-x86_64.sh
```
- Follow the instructions in [SHIFT Python API](https://github.com/hanlonlab/shift-python/wiki/SHIFT-Python-API) to create a new environment and install all SHIFT packages:
    - The last step ("In the Terminal") must also be run from the Ubuntu app.
- Create a new project in PyCharm Pro:
    - Click **File** -> **Settings...** -> **Project: *Project Name*** -> **Project Interpreter**.
    - Click in the **Project Interpreter** bar and select **Show All** -> ***Plus Icon* (+)** -> **WSL**.
    - If you installed Anaconda with default settings, the *Interpreter* path should look something like `/home/USERNAME/anaconda3/envs/shift/bin/python`.
- You are good to go!

## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.
