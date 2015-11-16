# MIHT

C implementation of [Multi-Index Hybrid Trie
(MIHT)](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6585242&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6585242) for efficient forwarding of IPv4 datagrams.

## Building

This project has some dependencies configured as git submodules. In order to
download these dependencies, you can clone this repository recursively:
```
git clone --recursive git@bitbucket.org:alexandrelucchesi/bloomfwd.git
```

Alternatively, after cloning this repository, you may run:
```
git submodule update --init --recursive
```

Then, run:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

This will generate a **Debug** build by default, with all the optimization
flags on. In order to generate a **Release** build, run `cmake
-DCMAKE_BUILD_TYPE=Debug ..` instead. The compilation process can be followed in
detail by running `make VERBOSE=1`. The binaries will be put in the `bin/`
directory under the project root.

### Intel(R) Xeon(tm) Phi

When building for MIC architecture, it is necessary to add some compiler flags
to set the compiler and the target. The easiest way is to set the following
environment variables (using `export` or `setenv` depending on your shell),
before running `cmake` (explained previously):

```
export CC=icc
export CFLAGS="-mmic -qopt-report[=n] -qopt-report-phase[=list]"
```

The first option is mandatory whilst the last two are optional (used for
generating compiler optimization reports). This only needs be done once, as the
settings are cached by CMake (can be edited with `make edit_cache`).

## Collaborators

- [Alexandre Lucchesi](http://lattes.cnpq.br/6373192328475976)
- [George Teodoro](http://lattes.cnpq.br/6732940162423405)

