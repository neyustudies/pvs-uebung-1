.ONESHELL:
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

.PHONY: pvs.pdf
pvs.pdf:
	pandoc tasks.md -o pvs.pdf --from markdown --template /tmp/eisvogel.tex --listings

FILES=Makefile matmult.cpp pvs.pdf tasks.md test.sh threadID.cpp
DIR=pvs-01-gruppeC

.PHONY: pvs-01-gruppeC-piekarski-wichmann-ruckel.tar.gz
pvs-01-gruppeC-piekarski-wichmann-ruckel.tar.gz: pvs.pdf
	mkdir $(DIR)
	for f in $(FILES); do cp $$f $(DIR); done
	tar zcvf pvs-01-gruppeC-piekarski-wichmann-ruckel.tar.gz $(DIR)
	rm -fr $(DIR)
