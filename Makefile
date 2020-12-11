	obj-m := sample.o

	KERN_SRC = /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN_SRC) M=$(PWD) modules
install:
	$(MAKE) -C $(KERN_SRC) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERN_SRC) M=$(PWD) clean

