CXX := g++
CXXFLAGS := -std=c++14

.PHONY : all

all : page-replacement-simulator

.PHONY : clean

clean :
	rm -rf ./cxxopts ./page-replacement-simulator

page-replacement-simulator : external-cxxopts \
        ../src/frequency_iterative_algorithm.cpp \
        ../src/fifo_iterative_replacement_algorithm.cpp \
        ../src/file_input_retriever.cpp \
        ../src/iterative_replacement_algorithm.cpp \
        ../src/lfu_iterative_replacement_algorithm.cpp \
        ../src/lru_iterative_replacement_algorithm.cpp \
        ../src/mfu_iterative_replacement_algorithm.cpp \
        ../src/optimal_iterative_replacement_algorithm.cpp \
        ../src/main.cpp
	$(CXX) $(CXXFLAGS) \
	      -I../include \
				-I./cxxopts/include \
	      -o $@ \
        ../src/frequency_iterative_algorithm.cpp \
        ../src/fifo_iterative_replacement_algorithm.cpp \
        ../src/file_input_retriever.cpp \
        ../src/iterative_replacement_algorithm.cpp \
        ../src/lfu_iterative_replacement_algorithm.cpp \
        ../src/lru_iterative_replacement_algorithm.cpp \
        ../src/mfu_iterative_replacement_algorithm.cpp \
        ../src/optimal_iterative_replacement_algorithm.cpp \
        ../src/main.cpp

external-cxxopts : 
	[ -d cxxopts ] || git clone https://github.com/jarro2783/cxxopts.git cxxopts
