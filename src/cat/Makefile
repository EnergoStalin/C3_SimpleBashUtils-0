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
	chmod +x test/cat.py
	cp $(EXEC) test/
	chmod +x test/$(EXEC)
	cd test && ./cat.py
	rm test/$(EXEC)


.PHONY: clean
clean:
	rm -rf $(EXEC)
	rm -rf *.o
