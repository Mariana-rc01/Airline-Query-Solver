# LI3

## Grade: 19/20 :star:

![Interactive mode](trabalho-pratico/Relatorio/2ª%20Fase/Images/settings.png)

![Interactive mode](trabalho-pratico/Relatorio/2ª%20Fase/Images/result.png)

## Building

### Dependencies

 - GNU Make (build-time)
 - GCC (build-time)
 - Doxygen (optional, build-time)
 - Ncurses (run-time)
 - GLib (run-time)


### Building

A release build is achieved with:

``` console
$ cd trabalho-pratico
$ make
```

To perform a debug build (no optimizations, debug symbols enabled):

``` console
$ DEBUG=1 make
```

To generate documentation (Doxygen is required):

``` console
$ make docs
```

To remove files generated by a build, run:

``` console
$ make clean
```

To run the project in interactive mode, run:

``` console
$ ./programa-principal <dataset-path> <inputs-path>
```

To run a few tests, run:

``` console
$ ./programa-testes <dataset-path> <inputs-path> <outputs-path>
```
