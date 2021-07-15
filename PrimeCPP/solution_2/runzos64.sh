#!/bin/sh
xlc -o PrimeCPP64 -O3 -Wl,lp64,xplink -Wc,xplink,-qlanglvl=extended0x PrimeCPP.cpp
./PrimeCPP64
