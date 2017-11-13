@echo off

:: Check build directory.
set BUILD_DIR=..\build\vc14-x64-release
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
pushd %BUILD_DIR%

:: Run Conan
echo [*] Installing dependencies...
conan install ^
	--build missing ^
	-s arch="x86_64" ^
	-s os="Windows" ^
	-s build_type="Release" ^
	-s compiler="Visual Studio" ^
	-s compiler.version="14" ^
	-s compiler.runtime="MT" ^
	../..
if errorlevel 1 goto :error

:: Run CMake.
echo [*] CMake is running...
cmake ^
	-G"Visual Studio 14 2015 Win64" ^
	"-DCMAKE_CONFIGURATION_TYPES:STRING=Release" ^
	"-DBUILD_WITH_STATIC_CRT:BOOL=ON" ^
	../..
if errorlevel 1 goto :error

:: Exit
echo [*] Project generation succeeded!
popd
goto :eof

:: Error handling
:error
echo [!] ERROR: Failed to generate project - see above and correct.
popd
exit /b 1
