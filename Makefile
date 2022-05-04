# -*- Makefile -*-
SRC_DIR = src
HEADERS_DIR = $(SRC_DIR)

CC = clang++
CFLAGS = -I$(HEADERS_DIR) -g -std=c++17 # -fsanitize=thread 

HEADERS_PATHLESS = utils.h
HEADERS = $(patsubst %, $(HEADERS_DIR)/%, $(HEADERS_PATHLESS))

EXECUTABLES = bitap
#all:tarjan schmidt #bitap
# all: $(SRC_DIR)/%.cpp $(HEADERS_DIR)/%.h $(HEADERS_DIR)/%.hpp 
# 	$(CC) $(CFLAGS) $^ -o $@


bitap: $(SRC_DIR)/Bitap.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap.cpp -o $@

debug: CFLAGS += -DDEBUG=1 -Wall -Wextra -O2 -Wswitch-default -Wconversion -Wundef -fsanitize=address -fsanitize=undefined -fstack-protector # -Werror
debug: bitap

dev: CFLAGS += -Wall -Wextra -O2 -Wswitch-default -Wconversion -Wundef -fsanitize=address -fsanitize=undefined -fstack-protector
dev: bitap

clean:
	rm -f bitap