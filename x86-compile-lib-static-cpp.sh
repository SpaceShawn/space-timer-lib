#!/bin/bash
make buildBinCpp
ar rcs lib/libtimer.a lib/timer.o
