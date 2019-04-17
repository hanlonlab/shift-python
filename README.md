[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python

## Installation

### Docker Image Installation (recommended)

- Step 01:
    - Install or upgrade your operating system to latest version:
        - For macOS, Mojave.
        - For Windows, Windows 10 Pro (https://aka.ms/devtoolsforteaching). Use your Stevens email address to either login (IT confirms you should all have an account) or request an account from:
            - [Stevens IT Helpdesk](https://sit.teamdynamix.com/TDClient/Requests/ServiceDet?ID=19685)

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

- Installation finished! Get started with [PyCharm Pro](#get-started-with-pycharm-pro).

### Anaconda Packages Installation (linux only)

**Note: This is for Linux users only. Windows and macOS are not yet supported.**

- Run the following to create a new `shift` environment and install SHIFT Python:

```bash
conda create -y -n shift python=3.6 anaconda
conda activate shift
wget -qO- https://github.com/hanlonlab/shift-python/releases/download/v1.2.0/shift-python_1.2.0_conda_linux64.zip | bsdtar -xvf-
cd shift*
conda install *.tar.bz2
```

- Installation finished! Get started with [Command Line](#get-started-with-command-line).

## Get Started with PyCharm Pro

- Install [PyCharm Pro](https://www.jetbrains.com/pycharm). Use your Stevens email address to request a free student license (https://www.jetbrains.com/student).
- Configuring Docker as a remote interpreter:
    - For Windows, follow the extra instructions in the `Prerequisites` session of this [guide](https://www.jetbrains.com/help/pycharm/using-docker-as-a-remote-interpreter.html).
    - Open an existing project, or create a completely new Python project in Pycharm Pro.
    - Follow the steps in the `Configuring Docker as a remote interpreter` session of this [guide](https://www.jetbrains.com/help/pycharm/using-docker-as-a-remote-interpreter.html).

## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.
