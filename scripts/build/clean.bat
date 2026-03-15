@echo off
cd /d "%~dp0..\.."
if exist build rmdir /s /q build
if exist bin rmdir /s /q bin
echo Cleaned build and bin.
