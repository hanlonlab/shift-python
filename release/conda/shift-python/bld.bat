"%PYTHON%" setup.py build_ext --prefix=${PREFIX} install --single-version-externally-managed --record=record.txt
if errorlevel 1 exit 1
