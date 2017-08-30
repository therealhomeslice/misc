obj-m += signalex.o
all:
	make -C /lib/modules/\$(shell uname -r)/build M=$(PWD) modules
	gcc -o siguser siguser.c
clean:
	make -C /lib/modules/\$(shell uname -r)/build M=$(PWD) clean
	rm -f siguser
