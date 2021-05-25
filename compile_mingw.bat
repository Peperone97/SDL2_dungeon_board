ECHO OFF
ECHO compiling source

set DLLS=%CD%\src\SDL2\bin
set LIBSDIR=%CD%\src\SDL2\lib
set LIBS=-lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_image
set SOURCES=%CD%\src\baseWindow.cpp %CD%\src\button.cpp %CD%\src\core.cpp %CD%\src\cross.cpp %CD%\src\cursor.cpp %CD%\src\dropdownMenu.cpp %CD%\src\entity.cpp %CD%\src\errorWindow.cpp %CD%\src\inputWindow.cpp %CD%\src\main.cpp %CD%\src\map.cpp %CD%\src\monster.cpp %CD%\src\movementArrow.cpp %CD%\src\phrase.cpp %CD%\src\texture.cpp %CD%\src\timer.cpp %CD%\src\window.cpp
set RES=program

g++ -std=c++0x %SOURCES% -L%LIBSDIR% %LIBS% -o %RES%

copy %DLLS%\*

ECHO compiling completed