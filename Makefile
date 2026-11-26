CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

PROGRAMS = Lab_10_1 Lab_10_2 Lab_10_3
TESTS = tests/UnitTest_10_1 tests/UnitTest_10_2 tests/UnitTest_10_3

.PHONY: all programs tests test check clean help

all: programs tests

programs: $(PROGRAMS)

Lab_10_1: PR_10.1/Lab_10_1.cpp
	$(CXX) $(CXXFLAGS) -IPR_10.1 PR_10.1/Lab_10_1.cpp -o $@

Lab_10_2: PR_10.2/Lab_10_2.cpp
	$(CXX) $(CXXFLAGS) -IPR_10.2 PR_10.2/Lab_10_2.cpp -o $@

Lab_10_3: PR_10.3/Lab_10_3.cpp
	$(CXX) $(CXXFLAGS) -IPR_10.3 PR_10.3/Lab_10_3.cpp -o $@

tests: $(TESTS)

tests/UnitTest_10_1: tests/UnitTest_10_1.cpp PR_10.1/Lab_10_1.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.1 -Itests tests/UnitTest_10_1.cpp -o $@

tests/UnitTest_10_2: tests/UnitTest_10_2.cpp PR_10.2/Lab_10_2.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.2 -Itests tests/UnitTest_10_2.cpp -o $@

tests/UnitTest_10_3: tests/UnitTest_10_3.cpp PR_10.3/Lab_10_3.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.3 -Itests tests/UnitTest_10_3.cpp -o $@

test: check
check: tests
	@echo "=================================================="
	@echo "Running all Unit Tests for Lab 10..."
	@echo "=================================================="
	@./tests/UnitTest_10_1
	@./tests/UnitTest_10_2
	@./tests/UnitTest_10_3
	@echo "=================================================="
	@echo "ALL TESTS PASSED SUCCESSFULLY!"
	@echo "=================================================="

clean:
	rm -rf $(PROGRAMS) $(TESTS) *.dSYM tests/*.dSYM PR_10.1/*.dSYM PR_10.2/*.dSYM PR_10.3/*.dSYM
