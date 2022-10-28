CC=gcc
CFLAGS=-Wall -Wextra -Werror
BUILDDIR=../../build

all: s21_grep

$(BUILDDIR):
	mkdir -p $@

%.o: $.c
	$(CC) $(CFLAGS) -c $@ -o $<

s21_grep: main.o | $(BUILDDIR)
	$(CC) $^ -o $(BUILDDIR)/$@

rebuild: clean all

clean:
	rm -rf $(BUILDDIR)
	rm -rf *.o