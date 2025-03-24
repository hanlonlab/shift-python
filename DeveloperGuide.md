[header]: # "To generate a html version of this document:"
[pandoc]: # "pandoc DeveloperGuide.md -c ../shift-main/Templates/github.css -o DeveloperGuide.html -s --self-contained"

# SHIFT Python Developer Guide

## Ubuntu and macOS

### Required Libraries

**Please refer to the other required libraries in the SHIFT Developer Guide.**

#### SHIFT Core Client

Use the installer in the root folder of the SHIFT project:

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
python3 setup.py clean
python3 setup.py install

You can now see your local changes (in shift-python):
python3
import shift
....

# Installing to conda environment
python3 setup.py bdist_wheel
pip install dist/shift-2.0.1-py3.7-*.whl

You can now see these changes globally when conda env is active
