[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

# SHIFT Python Setup Guide

## Supported Platforms
- macOS (Ventura or newer)
- Ubuntu 20.04+
- Windows 10/11 (via WSL2)


## Setup on Different Operating Systems

### Ubuntu:

- **Environment Installation:**
    - Open the Terminal and run the following command: `curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/refactor/scripts/setup-linux-x86.sh | bash`
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
    - Open **PowerShell** as Administrator and run: `wsl --install`
    - Restart your computer when prompted.
    - Once restarted, a terminal will open to finish the Ubuntu installation. Create your username and password.
- **Environment Installation:**
    - Open your **Ubuntu** terminal and run the following command:
      `curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/refactor/scripts/setup-linux-x86.sh | bash`
    - The script will install Miniconda and create the `shift` environment.
- **Interpreter Configuration:**
    - If using an IDE (like PyCharm or VS Code), use the **WSL Interpreter** setting.
    - The path should be: `\\wsl$\Ubuntu\home\USERNAME\miniconda3\envs\shift\bin\python`
- **Validation:**
    - Run `conda activate shift` to begin.
    - You can verify the setup by running `python3 -c "import shift; print('Success')"`. It should return **Success**.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)


### macOS (Apple Silicon: M1, M2, M3, M4):

- **System Requirement:** Ensure your Mac is updated to **macOS Ventura (13.0)** or newer.
- **Virtualization Setup:**
    - Download and install [UTM](https://getutm.app/).
    - Download the **Ubuntu Desktop ARM64** ISO (Important: do not use the AMD64/Intel version).
    - In UTM, go to **Settings > Sharing**, click the **+** icon, and select **Rosetta**. Ensure the VirtioFS tag is named `rosetta`.
- **Environment Installation:**
    - Start the Ubuntu VM and open the Terminal (`Ctrl + Alt + T`).
    - Run the following command: `curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/refactor/scripts/setup-mac-arm.sh | bash`
    - The script will automatically configure the Rosetta bridge and create the `shift` environment.
- **Interpreter Configuration:**
    - If using an IDE (like PyCharm) inside the VM, the *Interpreter* path should be `/home/USERNAME/miniconda3/envs/shift/bin/python`.
- **Validation:**
    - Run `conda activate shift` to begin.
    - You can verify the setup by running `python3 -c "import shift; print('Success')"`. It should return **Success**.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)


### macOS (Intel-based):

- **System Requirement:** Ensure you are running **macOS Big Sur (11.0)** or newer.
- **Virtualization Setup:**
    - Download and install [UTM](https://getutm.app/).
    - Download the **Ubuntu Desktop AMD64** ISO (this is the standard x86_64 version).
    - When creating the VM, select **Virtualize**. Since your Mac is Intel-based, you do not need to enable Rosetta sharing.
- **Environment Installation:**
    - Start your Ubuntu VM and open the Terminal (`Ctrl + Alt + T`).
    - Run the following command to install the environment:
      `curl -sSL https://raw.githubusercontent.com/hanlonlab/shift-python/refs/heads/refactor/scripts/setup-linux-x86.sh | bash`
- **Interpreter Configuration:**
    - If using an IDE (like PyCharm) inside the VM, the *Interpreter* path should be `/home/USERNAME/miniconda3/envs/shift/bin/python`.
- **Validation:**
    - Run `conda activate shift` to begin.
    - You can verify the setup by running `python3 -c "import shift; print('Success')"`. It should return **Success**.
- You are good to go! (You may also get started with [Command Line](#get-started-with-command-line).)


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
