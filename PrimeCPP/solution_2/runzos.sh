#!/bin/sh
xlc -o PrimeCPP31 -O3 -Wl,xplink -Wc,xplink,-qlanglvl=extended0x PrimeCPP.cpp
./PrimeCPP31

