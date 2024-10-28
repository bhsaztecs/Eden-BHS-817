Eden is an abstraction library that interfaces with KIPR's wombat.
Eden is licensed under GNU AGPL.
to compile: use
```bash
$ g++ code/kipr/*.cpp \
$(ls code/src/*.cpp | grep -v interface.cpp) \
code/src/interface.cpp example.cpp \
-o example_program.o
```
