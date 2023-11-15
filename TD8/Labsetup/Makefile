
all: bn_sample bn_operations

bn_sample: bn_sample.c
	gcc bn_sample.c -o bn_sample -lcrypto

bn_operations: bn_operations.c
	gcc bn_operations.c -o bn_operations -lcrypto
clean:
	rm -f bn_sample bn_operations *.o
