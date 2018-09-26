#-------------------------------------------------
#
# Project created by SHIFT 2018-07-14T10:07:19
#
#-------------------------------------------------
QT       -= core gui
CONFIG   += c++14
QMAKE_CXXFLAGS = -O3 -Wall -shared -std=c++14
TARGET = shift
TEMPLATE = lib
LIBS += \
    -lshift_coreclient
SOURCES += \
    src/Trader.cpp \
    src/SHIFT.cpp
HEADERS += \
    include/Common.h \
    include/Order.h \
    include/PortfolioItem.h \
    include/PortfolioSummary.h \
    include/Trader.h \
    include/BestPrice.h \
    include/OrderBookEntry.h
INCLUDEPATH += \
    include/ \
    ./pybind11/build/mock_install/include
unix {
    target.path = ./
    INSTALLS += target
    # pkg-config
    CONFIG += link_pkgconfig
    # LibCoreClient
    CONFIG(debug, debug | release): PKGCONFIG += libshift_coreclient-d
    CONFIG(release, debug | release): PKGCONFIG += libshift_coreclient
    # PyBind11
    INCLUDEPATH += /usr/include/python3.6m \
        /usr/local/include/python3.6 \
        /home/han/.local/include/python3.6m
}

win32 {
    # Python
    INCLUDEPATH += "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python36_64/include"

    # cURL
    Debug:DEPENDPATH += $$(CURL_LIB)/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/include/curl
    Debug:INCLUDEPATH += $$(CURL_LIB)/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/include/curl

    Debug:LIBS += -L$$(CURL_LIB)/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/lib/ -llibcurl_a_debug
    Debug:PRE_TARGETDEPS += $$(CURL_LIB)/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/lib/libcurl_a_debug.lib

    Release:DEPENDPATH += $$(CURL_LIB)/libcurl-vc17-x86-release-static-ipv6-sspi-winssl/include/curl
    Release:INCLUDEPATH += $$(CURL_LIB)/libcurl-vc17-x86-release -static-ipv6-sspi-winssl/include/curl

    Release:LIBS += -L$$(CURL_LIB)/libcurl-vc17-x86-release-static-ipv6-sspi-winssl/lib/ -llibcurl_a
    Release:PRE_TARGETDEPS += $$(CURL_LIB)/libcurl-vc17-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a.lib

    # QuickFIX
    DEPENDPATH += $$(QuickFIX_VS2017)/include
    INCLUDEPATH += $$(QuickFIX_VS2017)/include

    Debug:LIBS += -L$$(QuickFIX_VS2017)/lib/debug -lquickfix
    Debug:PRE_TARGETDEPS += $$(QuickFIX_VS2017)/lib/debug/quickfix.lib

    Release:LIBS += -L$$(QuickFIX_VS2017)/lib -lquickfix
    Release:PRE_TARGETDEPS += $$(QuickFIX_VS2017)/lib/quickfix.lib

    # LibCoreClient
    DEPENDPATH += $$PWD/../shift-main/LibCoreClient/include
    INCLUDEPATH += $$PWD/../shift-main/LibCoreClient/include

    Debug:LIBS += -L$$PWD/../shift-main/LibCoreClient/build/Debug/ -lshift_coreclient-d
    Debug:PRE_TARGETDEPS += $$PWD/../shift-main/LibCoreClient/build/Debug/shift_coreclient-d.lib

    Release:LIBS += -L$$PWD/../shift-main/LibCoreClient/build/Release/ -lshift_coreclient
    Release:PRE_TARGETDEPS += $$PWD/../shift-main/LibCoreClient/build/Release/shift_coreclient.lib

    # LibMiscUtils
    DEPENDPATH += $$PWD/../shift-main/LibMiscUtils/include
    INCLUDEPATH += $$PWD/../shift-main/LibMiscUtils/include

    Debug:LIBS += -L$$PWD/../shift-main/LibMiscUtils/build/Debug/ -lshift_miscutils-d
    Debug:PRE_TARGETDEPS += $$PWD/../shift-main/LibMiscUtils/build/Debug/shift_miscutils-d.lib

    Release:LIBS += -L$$PWD/../shift-main/LibMiscUtils/build/Release/ -lshift_miscutils
    Release:PRE_TARGETDEPS += $$PWD/../shift-main/LibMiscUtils/build/Release/shift_miscutils.lib

}
