CC=gcc
CFLAGS=-Wall -Wextra -Werror --std=c11 --pedantic
EXEC=s21_cat

all: rebuild

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: rebuild
rebuild: clean $(EXEC)

debug: CFLAGS+=-g
debug: rebuild

.PHONY: clean
clean:
	rm -rf $(EXEC)
	rm -rf *.o
