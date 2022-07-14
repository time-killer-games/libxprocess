#!/bin/sh
cd "${0%/*}"

if [ $(uname) = "Darwin" ]; then
  clang++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -Wno-unused-command-line-argument -DPROCESS_GUIWINDOW_IMPL -framework Cocoa -framework CoreFoundation -framework CoreGraphics -ObjC++ -arch arm64 -arch x86_64 && clang++ gamemaker.o process.o -o libxprocess.dylib -shared -std=c++17 -Wno-unused-command-line-argument -DPROCESS_GUIWINDOW_IMPL -framework CoreFoundation -framework CoreGraphics -framework Cocoa -ObjC++ -arch arm64 -arch x86_64;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "cocoa.o" "process.o";
elif [ $(uname) = "Linux" ]; then
  g++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -static-libgcc -static-libstdc++ -lprocps -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC && g++ gamemaker.o process.o -o  libxprocess.so -shared -std=c++17 -static-libgcc -static-libstdc++ -lprocps -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "process.o";
elif [ $(uname) = "FreeBSD" ]; then
  clang++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lprocstat -lutil -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC && clang++ gamemaker.o process.o -o libxprocess.so -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lprocstat -lutil -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "process.o";
elif [ $(uname) = "DragonFly" ]; then
  g++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -static-libgcc -static-libstdc++ -lkvm -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC && g++ gamemaker.o process.o -o libxprocess.so -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lkvm -lutil -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "process.o";
elif [ $(uname) = "NetBSD" ]; then
  g++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -static-libgcc -static-libstdc++ -lkvm -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC && g++ gamemaker.o process.o -o libxprocess.so -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lkvm -lutil -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "process.o";
elif [ $(uname) = "OpenBSD" ]; then
  clang++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lkvm -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC && clang++ gamemaker.o process.o -o libxprocess.so -shared -std=c++17 -I/usr/local/include -L/usr/local/lib -lkvm -lc -lpthread -DPROCESS_GUIWINDOW_IMPL `pkg-config x11 --cflags --libs` -fPIC;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "gamemaker.o" "process.o";
else
  C:/msys64/msys2_shell.cmd -defterm -mingw32 -no-start -here -lc "g++ apiprocess/process.cpp -o process32.exe -std=c++17 -static-libgcc -static-libstdc++ -static -m32";
  C:/msys64/msys2_shell.cmd -defterm -mingw64 -no-start -here -lc "g++ apiprocess/process.cpp -o process64.exe -std=c++17 -static-libgcc -static-libstdc++ -static -m64";
  xxd -i 'process32' | sed 's/\([0-9a-f]\)$/\0, 0x00/' > 'apiprocess/process32.h';
  xxd -i 'process64' | sed 's/\([0-9a-f]\)$/\0, 0x00/' > 'apiprocess/process64.h';
  rm -f "process32.exe" "process64.exe";
  g++ -c gamemaker.cpp apiprocess/process.cpp -shared -std=c++17 -static-libgcc -static-libstdc++ -static -DPROCESS_WIN32EXE_INCLUDES -DPROCESS_GUIWINDOW_IMPL && g++ gamemaker.o process.o -o  libxprocess.dll -shared -std=c++17 -static-libgcc -static-libstdc++ -static -DPROCESS_WIN32EXE_INCLUDES -DPROCESS_GUIWINDOW_IMPL;
  ar rc libxprocess.a gamemaker.o process.o && rm -f "apiprocess/process32.h" "apiprocess/process64.h" "gamemaker.o" "process.o";
fi
