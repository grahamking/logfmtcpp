GTEST_DIR=/home/graham/src/gtest-1.7.0/

all: logfmt.cpp
	clang++ logfmt.cpp -Ofast -Wall -std=c++14 -o logfmt

gtest:
	clang++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	rm gtest-all.o

build_tests: logfmt.cpp logfmt_test.cpp
	clang++ logfmt.cpp logfmt_test.cpp libgtest.a -isystem ${GTEST_DIR}/include  -Wall -std=c++14 -pthread -o logfmt_test -Ofast

test: build_tests
	./logfmt_test

clean:
	rm logfmt logfmt_test

