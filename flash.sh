#!/bin/bash
glasgow run memory-25x -V 2.5 identify
glasgow run memory-25x -V 2.5 erase-chip
glasgow run memory-25x -V 2.5 program 0x0 -P 256 -f ./build/firmware.bin
