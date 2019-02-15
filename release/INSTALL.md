## Installation

### Docker Image Installation (recommended)

* Install latest docker from official website.
* Download `shift-python_x.x.x_dockerfile_anaconda3_py37.zip`, the Dockerfile package from [GitHub Release Page](https://github.com/hanlonlab/shift-python/releases/tag/0.0.1).
* Unzip the downloaded files to the same directory somewhere you like.
* Run in terminal/command prompt:

```bash
cd [directory-you-unzipped-the-Dockerfile]
docker build -t "shift-python-conda3:latest" .
```

* If successful, you should see docker image named `shift-python-conda3:latest` by running:

```bash
docker images -a
```

* Now you should be able to run SHIFT Python docker image by running:

```bash
docker run -it shift-python-conda3:latest
```

* Installation finished! Get started with [command line](#get-started-with-command-line) or [PyCharm IDE](#get-started-with -pycharm).

### Anaconda package Installation

**Note: This is for Linux users only. Windows and MacOS is not yet supported.**

* Download `shift-python_x.x.x_dockerfile_anaconda3_py37.zip`, the Dockerfile package from [GitHub Release Page](https://github.com/hanlonlab/shift-python/releases/tag/0.0.1).
* Run `setup.sh`  only.
* Installation finished! Get started with [command line](#get-started-with-command-line) or [PyCharm IDE](#get-started-with -pycharm).

## Get started with command line

* Run `conda activate shift` to get into shift environment. You need to do this every time you log in to docker container shell.
* If you see `(shift)` in the beginning of your command line, that means you are in the right environment to run SHIFT.
* Don't forget to `import shift` when you use Python with SHIFT.

## Get started with PyCharm

* Install PyCharm Pro from the official website. (You need to register pro version with your .edu email).
* Configure your docker and PyCharm accordingly with this [guide](https://www.jetbrains.com/help/pycharm/using-docker-as-a-remote-interpreter.html).