#!/bin/bash

# Compile all source files and link them into the final executable
g++ main.cpp window_renderer.cpp text_renderer.cpp table_renderer.cpp -o prog -lSDL2 -lSDL2_ttf
