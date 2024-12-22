# CXX=g++
# CXXFLAGS=-std=c++17 -O2

# all: a3

# clean:
# 	rm -rf a3


NVCC = nvcc
NVCCFLAGS = --std=c++17 -O2

all: a3

a3: a3.cpp gkernel.cu
	$(NVCC) $(NVCCFLAGS) -x cu a3.cpp gkernel.cu -o a3

clean:
	rm -f a3_program
