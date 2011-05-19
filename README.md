Backtracpp
==========

What is it?
-----------
It is `backtrace(3)` in C++.
Need `backtrace(3)` and `cxxabi.h` (for name demangling).

How to...
---------

### To build
`make` and `libbacktracpp.a` will be generated.

Use `make LIB_DIR=library-output-directory` to specify where to put `libbacktracpp.a`, or current directory if not specified.

### See samples
`make sample` and run `backtrace.out`

### Run test
Have `gtest` installed and `make runtest`

License
-------
Do whatever you want with the codes.
