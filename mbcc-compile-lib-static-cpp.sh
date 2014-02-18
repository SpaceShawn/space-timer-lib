#!/bin/bash
make buildQ6Cpp
ar rcs lib/libtimer-mbcc.a lib/timer-mbcc.o
