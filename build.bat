@echo off
title C++ Build & Run

echo Compiling project...

g++ src\file_management.cpp src\main.cpp src\group_operation.cpp -o main

if %errorlevel% neq 0 (
    echo.
    echo ================================
    echo   Compilation Failed!
    echo ================================
    echo.
    pause
    exit /b
)

echo.
echo ================================
echo   Build Successful!
echo ================================
echo.

echo Running program...
echo --------------------------------
main.exe
echo --------------------------------

echo.
pause
