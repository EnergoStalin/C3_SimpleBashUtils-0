CC=gcc
CFLAGS=-Wall -Wextra -Werror --std=c11 --pedantic
EXEC=s21_cat

all: $(EXEC)

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c) | $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: rebuild
rebuild: clean all

.PHONY: clean
clean:
	rm -rf $(EXEC)
	rm -rf *.o
