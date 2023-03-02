CC:=gcc
CFLAGS:=-Wall -Wextra -Werror --std=c11

all: rebuild

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c) $(wildcard ../common/*.c)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: $(EXEC)
debug: CFLAGS+=-g -DDEBUG
debug: rebuild

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o

_run_test: $(EXEC)
	python3 test/$(EXEC).py

.PHONY: test
test: _run_test clean

.PHONY: verter
verter:
	cd ../../materials/build/ && ./run.sh

.PHONY: format
format:
	clang-format --style=Google -i ../**/*.h ../**/*.c
