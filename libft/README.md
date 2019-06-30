# 42Libc [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)[![freetime](https://i.imgur.com/8IcDLkc.png)](i.imgur.com/8IcDLkc.png)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/72deeb1e890b4bd490676de2ccd1cc91)](https://www.codacy.com/app/Ant0wan/42Libc?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/42Libc&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.com/Ant0wan/42Libc.svg?branch=master)](https://travis-ci.com/Ant0wan/42Libc)

An cross-platform implementation of some of the standard functions in C [a 42 side-project].

This project aims to learn basics of C and open-source project contribution methods.

---

## Makefile

The library contains a makefile, with the following options:

| Command | Usage |
| --- | --- |
| `make` | creates .o files for each function as well as the main library file, libft.a |
| `make libft.a` | same as make |
| `make clean` | removes the .o files used to create the library |
| `make fclean` | removes the .o files used to create the library, as well as the libft.a library file |
| `make re` | removes all compilation files and remakes them |
| `make objects` | build objects files and dependences |
| `make lib` | same as make but does not display usage and built done message |

---

## Using this Library

- Copy of the repository:

```shell=
git clone https://github.com/Ant0wan/42Libc.git && cd 42Libc
```

- Compiling 42Libc:

```shell=
make && make clean
```

- After libft.a file has been created, it can be included in many of C project adding the following header in .c or .h files.

```shell=
include "libft.h"
```

- When compiling entire project, specify the path to libft.a in compiler command line

```shell=
compiler some_c_file.c -L<path_to_library_file> -lft
```

The makefile defines CC as default compiler.

Note that -L takes the path to your library and -l takes the set of characters that come after lib in your library name.
