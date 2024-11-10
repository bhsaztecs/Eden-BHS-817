# Eden is an abstraction library that interfaces with KIPR's wombat.
## See https://github.com/kipr/libwallaby

## Eden is licensed under GNU AGPL.

to compile on a wombat: use
```bash
sudo g++ -Iinclude/* -I" \
/usr/local/include/include" \
-Wall src/*.cpp -L"/usr/local/lib" \
-lkipr -lm -o "bin/botball_user_program" \
-lz -lpthread
```
to compile on ubuntu: use
```bash
aarch64-linux-gnu-g++ -Iinclude/* -I" \
/usr/local/include/include" \
-Wall src/*.cpp -L"/usr/local/lib" \
-lkipr -lm -o "bin/botball_user_program" \
-lz -lpthread
```
then, copy the files to the wombat using
```bash
scp -r * kipr@192.168.125.1:~/Documents/KISS/[username]/[projectname]
# to run the program, via ssh, run:
./bin/botball_user_program
```
