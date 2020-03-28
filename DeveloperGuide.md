[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc DeveloperGuide.md -c ../shift-main/Templates/github.css -o DeveloperGuide.html -s --self-contained"

# SHIFT Python Developer Guide

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
git checkout tags/v2.2.4 # v2.3.0 has a bug with char enums
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=17 -DPYBIND11_PYTHON_VERSION=3.7 ..
make
sudo make install
```

---

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
