@echo off
echo Uninstalling Aegis Driver...
sc stop AegisDriver
sc delete AegisDriver
pause
