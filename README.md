Project wxHexView
=================

Build on MacOS:

```sh
$ export WXOSX=$HOME/Workspace/wxWidgets/build-cocoa-debug
$ mkdir build_mac
$ cd build_mac
$ cmake .. -DwxWidgets_CONFIG_EXECUTABLE:FILEPATH=$WXOSX/wx-config -DwxWidgets_wxrc_EXECUTABLE:FILEPATH=$WXOSX/utils/wxrc/wxrc -G Xcode
$ cmake --build . --target wxHewView_test
```

Build on Windows:

```bat
set WXWIN=C:\wxWidgets
mkdir build_win
cd build_win
cmake ..
cmake --build . --target wxHewView_test
set PATH=%PATH%;%WXWIN%\lib\vc_dll 
```

Build wxWidgets
===============

Source:
* https://docs.wxwidgets.org/3.1/plat_osx_install.html
* https://wiki.wxwidgets.org/RunScript

```sh
$ mkdir build-cocoa-debug
$ cd build-cocoa-debug
$ ../configure --enable-debug --enable-cxx11 --with-macosx-version-min=10.9
$ make
$ cd samples; make;cd ..
$ cd demos;   make;cd ..
$ cd utils;   make;cd ..
```
