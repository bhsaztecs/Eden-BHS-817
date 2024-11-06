Eden is an abstraction library that interfaces with KIPR's wombat.
See https://github.com/kipr/libwallaby

Eden is licensed under GNU AGPL.
to compile: use
```bash
g++ -Iinclude/* -I" \
/usr/local/include/include" \
-Wall src/*.cpp -L"/usr/local/lib" \
-lkipr -lm -o "bin/botball_user_program" \
-lz -lpthread
```
