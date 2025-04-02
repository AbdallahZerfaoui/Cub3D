#!/bin/bash

# Install the required packages
echo "Installing required packages for Linux"
apt-get update
apt-get install -y cmake libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libasound2-dev libglfw3-dev
