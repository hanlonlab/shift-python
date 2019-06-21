[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python

## Requirements

- Upgrade your operating system to the latest version:
    - macOS: macOS Mojave 10.14
    - Ubuntu: Ubuntu 18.04 LTS Bionic Beaver
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

### (Deprecated) Docker Image:

- Step 01:
    - If you are using Windows 10, upgrade to Windows 10 Pro or Windows 10 Education (https://aka.ms/devtoolsforteaching):
        - Use your Stevens email address to login (IT confirms you should all have an account) or request an account from [Stevens IT Helpdesk](https://sit.teamdynamix.com/TDClient/Requests/ServiceDet?ID=19685)

- Step 02:
    - Install [Docker](https://www.docker.com/products/docker-desktop). When you install Docker, make sure to choose **Linux Containers** and not **Windows Containers**:
        - For macOS, [Docker for macOS](https://store.docker.com/editions/community/docker-ce-desktop-mac).
        - For Windows, [Docker for Windows](https://store.docker.com/editions/community/docker-ce-desktop-windows).
    - For Windows, if you store your file in a different drive location from **C:/**, then you will need to access the Docker preferences to add other Shared Folder locations, such as **D:/** or whatever.
    - Follow the online Docker installation instructions carefully and make sure to test the Docker installation.
    - NOTE: In some cases, you may need to enable virtualization on your computers.

- Step 03:
    - Download `shift-python_x.x.x_docker.zip`, the Docker Compose package from our [GitHub Release Page](https://github.com/hanlonlab/shift-python/releases).
    - Unzip the downloaded file to somewhere you like.
    - Access a terminal window on your computer. You may require admin privileges:
        - For macOS, Terminal.app.
        - For Windows, Powershell (run as administrator). NOTE: do not use PowerShell ISE.

```bash
cd [directory-you-unzipped-the-package]
docker-compose build
```

- If successful, you should see the Docker image named `shift-python_xxx_docker_anaconda3` by running:

```bash
docker images
```

- Now you should be able to run the SHIFT Python Docker image by running:

```bash
docker-compose up
```

- Configure Docker as a remote interpreter in PyCharm Pro:
    - For Windows, follow the extra instructions in the `Prerequisites` session of this [guide](https://www.jetbrains.com/help/pycharm/using-docker-as-a-remote-interpreter.html).
    - Open an existing project, or create a completely new Python project in Pycharm Pro.
    - Follow the steps in the `Configuring Docker as a remote interpreter` session of this [guide](https://www.jetbrains.com/help/pycharm/using-docker-as-a-remote-interpreter.html).

- Installation finished!

## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.
