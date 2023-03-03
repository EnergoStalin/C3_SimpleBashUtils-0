CC:=gcc
CFLAGS:=-Wall -Wextra -Werror --std=c11

all: rebuild

.PHONY: $(EXEC)
$(EXEC): $(wildcard *.c) $(wildcard ../common/*.c)
	$(CC) $(CFLAGS) $^ -o $@
	chmod +x $(EXEC)

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: $(EXEC)
debug: CFLAGS+=-g -DDEBUG
debug: rebuild

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o

.PHONY: _test_prebuild
_test_prebuild:
	python3 test/$(EXEC).py

.PHONY: test
test: $(EXEC) _test_prebuild clean

.PHONY: docker
docker:
	cd ../common && docker compose up --build $(ARGS)

.PHONY: verter
verter:
	cd ../../materials/build/ && ./run.sh

.PHONY: format
format:
	clang-format --style=Google -i ../**/*.h ../**/*.c
