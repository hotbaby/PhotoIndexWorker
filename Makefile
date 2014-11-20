CC = gcc
CFLAGS = -Werror
LDFLAGS =
GEARMAN_LDFLAGS = -lgearman
TARGET = gearman_worker_lib
TARGET += photoindex_lib

all:$(TARGET)

gearman_worker_lib:
	$(CC) worker.c $(CFLAGS) $(LDFLAGS) $(GEARMAN_LDFLAGS) -fPIC -shared -o worker.so

test_lib:
	$(CC) test.c $(CFLAGS) $(LDFLAGS) -fPIC -shared -o libtest.so

photoindex_lib:
	$(CC) libphotoindex.c $(CFLAGS) $(LDFLAGS) -ltest -fPIC -shared -o libphotoindex.so

install:
	sudo cp libtest.so /lib/

clean:
	rm worker.so
	rm libphotoindex.so
	rm libtest.so
