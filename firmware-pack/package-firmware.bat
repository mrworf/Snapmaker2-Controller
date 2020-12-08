@ECHO OFF
CLS

SET FW_SOURCE="%1"

ECHO.
ECHO Snapmaker 2.0 Firmware Builder

REM Check arg and path 3exists
IF %FW_SOURCE%=="" GOTO :no_arg
IF NOT EXIST %FW_SOURCE% GOTO :path_invalid

REM Get build version
ECHO. 
ECHO What is the build version? Ex: 3.2.2_1
SET /P BUILD_VERSION=" > "

IF "%BUILD_VERSION%"=="" GOTO :exit

REM Get folder name
ECHO. 
ECHO What is the build name? Ex: Feature Test
SET /P BUILD_NAME=" > "

IF "%BUILD_NAME%"=="" GOTO :exit
SET BUILD_FOLDER=%~dp0V%BUILD_VERSION% %BUILD_NAME%

REM Create build folders
MKDIR "%BUILD_FOLDER%"
MKDIR "%BUILD_FOLDER%\obj"

REM Copy firmware into folder
COPY %FW_SOURCE% "%BUILD_FOLDER%\obj"

REM Package firmware
%~dp0package --flag controller Snapmaker_V%BUILD_VERSION% 0 20 < "%BUILD_FOLDER%\obj\firmware.bin" > "%BUILD_FOLDER%\obj\controller_new.bin.packet"

%~dp0update --force Snapmaker2_V%BUILD_VERSION% "%BUILD_FOLDER%\obj\controller_new.bin.packet" > "%BUILD_FOLDER%\Snapmaker_FW.bin"

EXIT /B

:no_arg
ECHO.
ECHO Usage: package-firmware.bat ^<firmware.bin path^>
EXIT /B

:path_invalid
ECHO.
ECHO Firmware bin %FW_SOURCE% not found.
EXIT /B

:exit
EXIT /B