# ClipSecret
A way for copy/pasting a secret (like some long password) protected using a shorter secret or pin

# Building

```
$ make
g++    -c -o obfuscator.o obfuscator.cpp
g++ -o obfuscator obfuscator.o
./obfuscator "1234" "hello world"
g++    -c -o clips.o clips.cpp
g++ -o clips clips.cpp -lcurses
```

Now run it a first time

```
./clips
```

Enter 1234 and then you see you can paste "hello world"
which will be erased again after 9 sec.

Install to ~/bin and enter a new pin (or passw) and a longer secret string by running make install:

```
make install
```

Use this little thing at your own risk you'll notice the binary does not contain any of your original strings so someone would need some asm skills
to get to your secrets. It's better than a plain text file and way worse 
than any password manager like KeepassXC or an actual AnyKey (https://www.anykey.shop) or some encrypted file. It is however handy in some cases
(For instance re-entering my vpn password that disconnects frequently).

It's also way better than taking a short/easy password on your vpn because you need to reenter it a lot. Now you can just run ./clips and enter a short pw which results in the longer one on the clipboard and paste it where needed. (The clipboard is also auto cleared again). So for a remote attack the vpn is still secured with a longer pass and if laptop is compromised its better than some plaintext file...

