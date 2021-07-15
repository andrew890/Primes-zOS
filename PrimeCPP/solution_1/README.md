# C++ solution by davepl

![Algorithm](https://img.shields.io/badge/Algorithm-base-green)
![Faithfulness](https://img.shields.io/badge/Faithful-yes-green)
![Parallelism](https://img.shields.io/badge/Parallel-no-green)
![Bit count](https://img.shields.io/badge/Bits-1-green)


Modified by Andrew Rowley to compile and run on z/OS.

Changes for z/OS:
- Use gettimeofday() instead of &lt;chrono&gt; functions because I couldn't find &lt;chrono&gt; on z/OS.
- Change initialization of resultsDictionary because the C++ 11 initialization format didn't work on z/OS.
- Add cast to sqrt because it wouldn't accept a long.
- Change vector&lt;bool&gt; back to raw bit array for improved performance. The raw bit implementation was at least 50% faster on z/OS than vector&lt;bool&gt;
- z/OS also required: 
```
#define _XOPEN_SOURCE_EXTENDED 1
```

The gettimeofday() change means that this will not compile under Windows, but will still compile on Unix based systems.

## Running the test

The test runs under the OMVS shell.

Compile and run in 31 bit mode:
```
./runzos.sh 
```
Compile and run in 64 bit mode:
```
./runzos64.sh
```

31 bit seems about 10% faster than 64 bit.

### Compile options

The program is compiled with the command/options:

```
xlc -o PrimeCPP31 -O3 -Wl,xplink -Wc,xplink,-qlanglvl=extended0x PrimeCPP.cpp

xlc -o PrimeCPP64 -O3 -Wl,lp64,xplink -Wc,xplink,-qlanglvl=extended0x PrimeCPP.cpp
```