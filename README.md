# SHIFT PythonClient Guide


[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc README.md -c ../shift-main/Templates/github.css -o README.html -s --self-contained"

## Ubuntu and macOS

### Required Libraries

**Please refer to the other required libraries in the SHIFT Developer Guide.**

#### SHIFT Core Client

Use the installer in the root folder of the SHIFT project:

- In the Terminal: `sudo ./install -m LC`

#### pybind11:

Choose a location to keep the pybind11 source files (for debugging purposes), e.g. a "C++" folder in your home directory, and then:

``` bash
git clone https://github.com/pybind/pybind11.git
cd pybind11
git checkout stable
mkdir build
cd build
cmake ..
sudo make install
```

---

### SHIFT PythonClient Installation

**Depending on how python was installed in your system, you may need to use `sudo` in the commands below.**

To install the PythonClient:

- In the Terminal: `# python3 setup.py install`

To uninstall the PythonClient:

- In the Terminal: `# pip3 uninstall shift`

To clean the build directories:

- In the Terminal: `# python3 setup.py install`

---

## Windows

### [TODO] Required Libraries

---

### [TODO] SHIFT PythonClient Installation

---
