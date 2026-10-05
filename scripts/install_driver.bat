@echo off
echo Installing Aegis Driver...
sc create AegisDriver type= kernel binPath= C:\Path\To\AegisDriver.sys
sc start AegisDriver
pause
