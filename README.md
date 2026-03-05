[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python Setup Guide

## Supported Platforms
- macOS (Ventura or newer)
- Ubuntu 20.04+
- Windows 10/11 (via WSL2)


## Setup on Different Operating Systems

### Ubuntu:

- **Prerequisite: Install curl**
    - Ensure `curl` is installed by running:
      ```bash
      sudo apt update && sudo apt install -y curl
      ```
- **Environment Installation:**
    - Open the Terminal and run the following command: 
      ```bash
      curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/master/scripts/setup-linux-x86.sh | bash
      ```
    - The script will automatically configure the Rosetta bridge and create the `shift` environment.
- **Interpreter Configuration:**
    - If using an IDE (like PyCharm) inside the VM, the *Interpreter* path should be `/home/USERNAME/miniconda3/envs/shift/bin/python`.
- **Validation:**
    - Run `conda activate shift` to begin.
    - You can verify the setup by running `python3 -c "import shift; print('Success')"`. It should return **Success**.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)


### Windows:

- **System Requirement:** Ensure you are running **Windows 10 (Version 2004+)** or **Windows 11**.
- **WSL Setup:**
    1. Open **PowerShell** as Administrator and run: `wsl --install`
    2. **Restart your computer** when prompted. 
    3. After restarting, a terminal will automatically open to finish the Ubuntu installation. 
    4. **Create a Linux Username & Password:** You will be prompted to enter a new username and password. 
       * *Note: This does not have to match your Windows login. Remember this password; you will need it for `sudo` commands.*
- **Environment Installation:**
    - Open your **Ubuntu** terminal and install `curl`:
      ```bash
      sudo apt update && sudo apt install -y curl
      ```
    - Then, run the following command:
      ```{bash}
      curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/master/scripts/setup-linux-x86.sh | bash
      ```
    - The script will install Miniconda and create the `shift` environment.
- **Interpreter Configuration:**
    - If using an IDE (like PyCharm or VS Code), use the **WSL Interpreter** setting.
    - The path should be: `\\wsl$\Ubuntu\home\USERNAME\miniconda3\envs\shift\bin\python`
- **Validation:**
    - Run `conda activate shift` to begin.
    - You can verify the setup by running `python3 -c "import shift; print('Success')"`. It should return **Success**.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)


### macOS (Intel & Apple Silicon):

- **System Requirement:** macOS Ventura (13.0) or newer.
- **Virtualization Setup:**
    - Download and install **OrbStack** (Free for personal use) from [orbstack.dev](https://orbstack.dev/).
    - **Create a New Machine:** 1. Open OrbStack and go to the **Machines** tab.
        2. Click the **+** icon to create a new machine.
        3. Select **Ubuntu** as the image.
        4. **Important for Apple Silicon (M1/M2/M3/M4):** Change the **Architecture** setting to **x86_64**. This allows you to use the standard Linux setup script via Rosetta emulation.
        5. Click **Create**.
- **Environment Installation:**
    - Open the OrbStack terminal for your Ubuntu x86_64 machine (double-click the machine name in OrbStack).
    - Install `curl` within the machine:
      ```bash
      sudo apt update && sudo apt install -y curl
      ```
    - Run the Linux installation command:
      ```{bash}
      curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/master/scripts/setup-linux-x86.sh | bash
      ```
- **Interpreter Configuration:**
    - Use the **SSH** or **OrbStack** interpreter setting in your IDE (PyCharm Pro or VS Code).
    - Path: `/home/USERNAME/miniconda3/envs/shift/bin/python`
- **Validation:**
    - Run `conda activate shift` to begin.
    - Verify by running `python3 -c "import shift; print('Success')"`. It should return **Success**.

---

## Next Steps
Once you have the `shift` environment activated, you can begin exploring the API.

- **[Explore the SHIFT-Python API Wiki](../../wiki)**: Detailed documentation on classes and methods.


## Python Module Importing:

```python
import shift
```


## Get Started with Command Line

- Run `conda activate shift` to get into the `shift` environment. You need to do this every time you open a new shell (or you can add this command onto your `.bashrc` or `.bash_profile` file).
- If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
- Don't forget to `import shift` when you use Python with SHIFT.


### (Deprecated) Docker Image:

- Step 01:
    - If you are using Windows 10, upgrade to Windows 10 Pro or Windows 10 Education:
        - Use your Stevens email address to login [here](https://aka.ms/devtoolsforteaching) (IT confirms you should all have an account) or request an account from [Stevens IT Helpdesk](https://sit.teamdynamix.com/TDClient/Requests/ServiceDet?ID=19685).

- Step 02:
    - Install [Docker](https://www.docker.com/products/docker-desktop). When you install Docker, make sure to choose **Linux Containers** and not **Windows Containers**:
        - For macOS, [Docker for macOS](https://store.docker.com/editions/community/docker-ce-desktop-mac).
        - For Windows, [Docker for Windows](https://store.docker.com/editions/community/docker-ce-desktop-windows).
    - For Windows, if you store your file in a different drive location from **C:/**, then you will need to access the Docker preferences to add other Shared Folder locations, such as **D:/** or whatever.
    - Follow the online Docker installation instructions carefully and make sure to test the Docker installation.
    - NOTE: In some cases, you may need to enable virtualization on your computers.

- Step 03:
    - Download `shift_python-x.x.x-docker.zip`, the Docker Compose package from our [GitHub Release Page](https://github.com/hanlonlab/shift-python/releases).
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
