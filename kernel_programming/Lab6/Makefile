obj-m += sched_dumper.o
all:
	make -C /lib/modules/\$(shell uname -r)/build M=$(PWD) modules
	gcc -o setsched setsched.c
clean:
	make -C /lib/modules/\$(shell uname -r)/build M=$(PWD) clean
	rm -f setsched.o setsched

