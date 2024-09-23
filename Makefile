CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -I./include
LDFLAGS = -L./lib
SRC = ./src/*.c
OUT = ./bin/albatross
TEST = ./test/*.c
TESTOUT = ./bin/test

$(OUT):$(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(OUT)

$(TESTOUT):$(TEST)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST) -o $(TESTOUT)

test: $(TESTOUT)

clean:
	rm -f $(OUT)

cleanall:
	rm -f $(OUT) $(TESTOUT)

cleantest:
	rm -f $(TESTOUT)

.PHONY: all clean
