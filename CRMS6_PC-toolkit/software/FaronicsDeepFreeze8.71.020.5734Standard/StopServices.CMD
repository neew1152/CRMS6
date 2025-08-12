@echo off
net stop "DFServ"
sc config "DFServ" start=disabled