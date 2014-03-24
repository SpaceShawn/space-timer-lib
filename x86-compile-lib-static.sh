#!/bin/bash
make buildBin
ar rcs lib/libtimer.a lib/timer.o
