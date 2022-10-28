CC=gcc
CFLAGS=-Wall -Wextra -Werror
BUILDDIR=../../build

all: s21_cat

$(BUILDDIR):
	mkdir -p $@

%.o: $.c
	$(CC) $(CFLAGS) -c $@ -o $<

s21_cat: main.o | $(BUILDDIR)
	$(CC) $^ -o $(BUILDDIR)/$@

rebuild: clean all

clean:
	rm -rf $(BUILDDIR)
	rm -rf *.o