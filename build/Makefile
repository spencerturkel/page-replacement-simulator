CXX := g++
CXXFLAGS := -std=c++14

page-replacement-simulator : cxxopts-git \
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
				-I cxxopts/include \
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

cxxopts-git : 
	git clone https://github.com/jarro2783/cxxopts.git cxxopts-git
