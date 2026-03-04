@echo off

REM Change this path if your MSYS2 is installed somewhere else
set MSYS2_PATH=C:\msys64

REM Delete old build directory
IF EXIST build (
    rmdir /s /q build
)

REM Run the MSYS2 MinGW64 shell and execute build commands
set "PROJECT_ROOT=%~dp0"
"%MSYS2_PATH%\usr\bin\bash.exe" -lc "
cd \"$(cygpath -u \"$PROJECT_ROOT\")\"
cmake -S . -B build -G Ninja
cmake --build build
"

REM Run the executable after build
echo Running ChessGame...
build\ChessGame.exe

pause
