---
tags:
    - dev
    - sysadmin
    - post
created: 2016-02-18
updated: 2024-05-06
---
# MySQL Workbench libtool issues

I have been trying to use MySQL Workbench to design some database schemas these days, but it does crash so often that I decided to install it from the source hoping to find a more stable version, however I faced this problem:

```txt
make[4]: Entering directory `/home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src/ext/antlr-runtime'
/bin/bash ./libtool  --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H -I. -I. -Iinclude    -O2  -Wall -MT antlr3baserecognizer.lo -MD -MP -MF .deps/antlr3baser
ecognizer.Tpo -c -o antlr3baserecognizer.lo `test -f 'src/antlr3baserecognizer.c' || echo './'`src/antlr3baserecognizer.c
./libtool: line 865: X--tag=CC: command not found
./libtool: line 898: libtool: ignoring unknown tag : command not found
./libtool: line 865: X--mode=compile: command not found
./libtool: line 1032: *** Warning: inferring the mode of operation is deprecated.: command not found
./libtool: line 1033: *** Future versions of Libtool will require --mode=MODE be specified.: command not found
./libtool: line 1176: Xgcc: command not found
./libtool: line 1176: X-DHAVE_CONFIG_H: command not found
./libtool: line 1176: X-I.: command not found
./libtool: line 1176: X-I.: command not found
./libtool: line 1176: X-Iinclude: command not found
./libtool: line 1176: X-O2: command not found
./libtool: line 1176: X-Wall: command not found
./libtool: line 1176: X-MT: command not found
./libtool: line 1176: Xantlr3baserecognizer.lo: command not found
./libtool: line 1176: X-MD: command not found
./libtool: line 1176: X-MP: command not found
./libtool: line 1176: X-MF: command not found
./libtool: line 1176: X.deps/antlr3baserecognizer.Tpo: No such file or directory
./libtool: line 1176: X-c: command not found
./libtool: line 1229: Xantlr3baserecognizer.lo: command not found
./libtool: line 1234: libtool: compile: cannot determine name of library object from `': command not found
make[4]: *** [antlr3baserecognizer.lo] Error 1
make[4]: Leaving directory `/home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src/ext/antlr-runtime'
make[3]: *** [all] Error 2
make[3]: Leaving directory `/home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src/ext/antlr-runtime'
make[2]: *** [all-recursive] Error 1
make[2]: Leaving directory `/home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src/ext'
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory `/home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src'
make: *** [all] Error 2
```

I found the solution <a href="http://blog.csdn.net/kumu_linux/article/details/7957449" target="_blank" title="Solution">here</a>:

```sh
cp /usr/bin/libtool /home/user/Downloads/workbench/mysql-workbench-gpl-5.2.44-src/ext/antlr-runtime/`
```

I hope it helps!
