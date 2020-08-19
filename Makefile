CC=gcc
CFLAGS=-I.

ODIR=obj

DEPS = stringToInteger.h
OBJ = main.o stringToInteger.o
TARGET = stringToInteger

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(ODIR)/$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)
