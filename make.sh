#!/bin/bash

echo "making client"
g++ -std=c++11 -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lstdc++ -o openwideworlds_client  src/event.cpp src/inputbox.cpp src/window.cpp src/button.cpp src/draw.cpp src/client.cpp src/timer.cpp src/mysql.cpp src/image.cpp src/font.cpp src/game.cpp `mysql_config --cflags --libs`
echo "client ready"

echo "making server"
gcc -std=c++11 -lSDL -lSDL_image -lstdc++ -lSDL_ttf -o openwideworlds_server src/font.cpp src/event.cpp src/window.cpp src/server.cpp src/timer.cpp src/mysql.cpp src/inputbox.cpp src/button.cpp src/draw.cpp src/game.cpp `mysql_config --cflags --libs`
echo "server ready"

echo ""
find ./src/ -type f | xargs cat | wc -l
echo "zeilen code mit viel scheiß"
