obj-m := gpio_rpi.o

all:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules
