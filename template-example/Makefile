
CLANG_FLAGS = -std=c++17 -Wall -g

GTEST_FLAGS = -lpthread -lgtest_main -lgtest

# determine Python version, need at least 3.7
PYTHON=python3
ifneq (, $(shell which python3.7))
	PYTHON=python3.7
endif
ifneq (, $(shell which python3.8))
	PYTHON=python3.8
endif

build: product_test product_timing

test: product_test
	./product_test

grade: grade.py product_test
	${PYTHON} grade.py

product_test:  product.hpp product_test.cpp
	clang++ ${CLANG_FLAGS} ${GTEST_FLAGS} product_test.cpp -o product_test

product_timing: timer.hpp product.hpp product_timing.cpp
	clang++ ${CLANG_FLAGS} product_timing.cpp -o product_timing

clean:
	rm -f gtest.xml results.json product_test product_timing
