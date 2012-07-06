
all: dirent_counter

clean:
	rm -f dirent_counter

CFLAGS+=-Wall

run: dirent_counter
	sudo ./dirent_counter /var | sort -nr | grep -v jail


t: dirent_counter
	./dirent_counter ~/src

