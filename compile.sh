##!/bin/bash
# declare STRING variable
MAC="make M"
DEBIAN="make D"
Arch="make A"

echo -e "\nSupported Systems :"
echo -e "1) MacOs (Mavericks, Yosemite, El Capitane, Sierra)"
echo -e "2) Debian-Linux (Ubuntu, Kubuntu, Lubuntu, ..)"
printf "3) Arch-Linux (Manjaro, Antergos, ApricityOs, ..)\n\nYour system : " && read in_system

if [ "$in_system" -eq 1 ]; then
   make M
elif [ "$in_system" -eq 2 ]; then
   make D
elif [ "$in_system" -eq 3 ]; then
   make A
fi