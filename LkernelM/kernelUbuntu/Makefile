obj-m := mod_hello.o

all:	
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules
