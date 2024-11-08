CFLAGS=-g -Wall -O2
all: irsender
irsender: main.o
	gcc -o $@ $^
clean:
	rm -f irsender core *.o common/*.o
zerow: clean
	scp -pr * zerow:src/irsender/
	
backup: clean
	tar -jcf - . | jbackup src.irsender.tar.bz2
