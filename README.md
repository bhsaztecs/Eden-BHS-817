# Eden is an abstraction library that interfaces with KIPR's wombat.

See https://github.com/kipr/libwallaby

Eden is licensed under GNU AGPL.

src/main.cpp is both an example and a test.

to compile on a wombat: use
```bash
sudo g++ -std=c++17 -g \
-Iinclude/* -I" \
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
to compile using docker: use
```bash
mkdir develop
sudo cp -r src include data bin LICENSE.txt project.manifest README.md develop/
sudo docker run -it --rm -v $(pwd)/develop:/root/develop:rw sillyfreak/wombat-cross /bin/sh -c ". /root/develop/data/shfuncs && aarch64-linux-gnu-g++ -std=c++17 -g -Iinclude/* -I /usr/local/include/include -Wall /root/develop/src/*.cpp -L/usr/local/lib -lkipr -lm -o /root/develop/bin/botball_user_program -lz -lpthread"
sudo cp develop/bin/botball_user_program bin/
sudo rm -r develop/
```
then, copy the files to the wombat using
```bash
scp -r * kipr@192.168.125.1:~/Documents/KISS/[username]/[projectname]
ssh kipr@192.168.125.1
./bin/botball_user_program
```
