CC=gcc
CFLAGS=-Wall -Wextra -Werror --std=c11 --pedantic
EXEC=s21_cat

all: rebuild

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: $(EXEC)
debug: CFLAGS+=-g -DDEBUG
debug: rebuild

.PHONY: test
test: $(EXEC)
	chmod +x test/test.py
	cp $(EXEC) test/
	chmod +x test/s21_cat
	cd test && ./test.py
	rm test/s21_cat


.PHONY: clean
clean:
	rm -rf $(EXEC)
	rm -rf *.o
