#!/bin/bash

echo "making client"
gcc -std=c++11 -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lstdc++ -o openwideworlds_client  src/window.cpp src/button.cpp src/draw.cpp src/client.cpp src/timer.cpp src/mysql.cpp src/image.cpp src/font.cpp src/game.cpp `mysql_config --cflags --libs`
echo "client ready"

echo "making server"
gcc -std=c++11 -lSDL -lstdc++ -o openwideworlds_server src/server.cpp src/timer.cpp src/mysql.cpp src/game.cpp `mysql_config --cflags --libs`
echo "server ready"
