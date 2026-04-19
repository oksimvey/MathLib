#!/usr/bin/env bash
set -e

echo "=== BUILD ==="

g++ main/init.cpp glad/src/glad.c \
  -Iinclude \
  -Imain \
  -I/mingw64/include \
  -L/mingw64/lib \
  -lglfw3 -lopengl32 -lgdi32 \
  -o init.exe 2>&1 | tee build.log

echo "=== RUN ==="

./init.exe 2>&1 | tee run.log

read -p "pressiona enter pra fechar"