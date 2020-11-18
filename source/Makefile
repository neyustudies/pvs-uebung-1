GCC_FLAGS = -fopenmp -Wall

.PHONY: build
build: threadID matmult

threadID:
	g++ $(GCC_FLAGS) -o threadID threadID.cpp

matmult:
	g++ $(GCC_FLAGS) -o matmult matmult.cpp

.PHONY: test
test: matmult
	./test.sh

.PHONY: clean
clean:
	rm threadID matmult
