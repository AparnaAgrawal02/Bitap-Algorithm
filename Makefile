# -*- Makefile -*-
SRC_DIR = src
HEADERS_DIR = $(SRC_DIR)

INP_DIR = alignment_dataset/medium
# INP_FILE = $(INP_DIR)
CC = g++
CFLAGS = -I$(HEADERS_DIR) -g -std=c++17 -fopenmp -O3 # -fsanitize=thread 

HEADERS_PATHLESS = utils.h
HEADERS = $(patsubst %, $(HEADERS_DIR)/%, $(HEADERS_PATHLESS))

EXECUTABLES = bitap_1D bitap_2D bitap_2D_parallel bitap_1D_1computation_less bitap_approx 
all:bitap_1D bitap_2D bitap_parallel bitap_1D_1computation_less bitap_approx #bitap
# all: $(SRC_DIR)/%.cpp $(HEADERS_DIR)/%.h $(HEADERS_DIR)/%.hpp 
# 	$(CC) $(CFLAGS) $^ -o $@


bitap_1D: $(SRC_DIR)/Bitap_1D.cpp $(HEADERS_DIR)/utils.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap_1D.cpp -o $@

bitap_2D: $(SRC_DIR)/Bitap_2D.cpp $(HEADERS_DIR)/utils.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap_2D.cpp -o $@

bitap_parallel: $(SRC_DIR)/Bitap_parallel.cpp $(HEADERS_DIR)/utils.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap_parallel.cpp -o $@

bitap_1D_1computation_less: $(SRC_DIR)/Bitap_1D_1computation_less.cpp $(HEADERS_DIR)/utils.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap_1D_1computation_less.cpp -o $@

bitap_approx: $(SRC_DIR)/Bitap_approx.cpp $(HEADERS_DIR)/utils.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap_approx.cpp -o $@

# bitap: $(SRC_DIR)/Bitap.cpp $(HEADERS)
# 	$(CC) $(CFLAGS) $(SRC_DIR)/Bitap.cpp -o $@

debug: CFLAGS += -DDEBUG=1 -Wall -Wextra -O2 -Wswitch-default -Wconversion -Wundef -fsanitize=address -fsanitize=undefined -fstack-protector # -Werror
debug: bitap_1D bitap_2D bitap_parallel

dev: CFLAGS += -Wall -Wextra -O2 -Wswitch-default -Wconversion -Wundef -fsanitize=address -fsanitize=undefined -fstack-protector
dev: bitap_1D bitap_2D bitap_parallel bitap_1D_1computation_less

clean:
	rm -f bitap_2D bitap_1D bitap_1D_1computation_less bitap_approx bitap_parallel

# .PHONY: run
# run:
#     ./bitap $(INP_DIR)/1.fasta $(INP_DIR)/2.fasta 