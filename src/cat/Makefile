CC=gcc
CFLAGS=-Wall -Wextra -Werror --std=c11
BUILDDIR=../../build

all: s21_cat

$(BUILDDIR):
	mkdir -p $@

.PHONY: s21_cat
s21_cat: $(wildcard *.c) | $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $(BUILDDIR)/$@

.PHONY: rebuild
rebuild: clean all

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	rm -rf *.o