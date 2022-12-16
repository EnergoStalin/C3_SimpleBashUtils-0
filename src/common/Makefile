CC=gcc
CFLAGS=-Wall -Wextra -Werror --std=c11 --pedantic

all: rebuild

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c) $(wildcard ../common/*.c)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: $(EXEC)
debug: CFLAGS+=-g -DDEBUG
debug: rebuild

.PHONY: test
test: $(EXEC)
	chmod +x test/$(EXEC).py
	cp $(EXEC) test/
	chmod +x test/$(EXEC)
	cd test && ./$(EXEC).py
	rm test/$(EXEC)

.PHONY: test-ci
test-ci:
	chmod +x test/$(EXEC).py
	chmod +x test/$(EXEC)
	cd test && ./$(EXEC).py

.PHONY: clean
clean:
	rm -rf $(EXEC)
	rm -rf *.o
