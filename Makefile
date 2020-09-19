obj-m += clearup.o
all:
	make --directory /lib/modules/$(shell /usr/bin/uname --kernel-release)/build M=$(PWD) modules

clean:
	make --directory /lib/modules/$(shell /usr/bin/uname --kernel-release)/build M=$(PWD) clean
