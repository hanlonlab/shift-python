/c/Win-builds/bin/c++.exe -O2 -Wall -shared -std=c++11 -fPIC \
-IC:/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/Shared/Python37_64/include \
-IC:/pybind11/include \
-I../LibCoreClient/include -I./include \
-L../LibCoreClient/build/Release \
-lshift_coreclient \
src/SHIFT.cpp src/Trader.cpp \
-o build/shift.dll
