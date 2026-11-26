CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

PROGRAMS = Lab_10_1_A Lab_10_1_B Lab_10_2_A Lab_10_2_B
TESTS = tests/UnitTest_10_1_A tests/UnitTest_10_1_B tests/UnitTest_10_2_A tests/UnitTest_10_2_B

.PHONY: all programs tests test check clean

all: programs tests

programs: $(PROGRAMS)

Lab_10_1_A: PR_10.1_A/Lab_10_1_A.cpp PR_10.1_A/io.cpp PR_10.1_A/calc.cpp PR_10.1_A/student.h PR_10.1_A/io.h PR_10.1_A/calc.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_A PR_10.1_A/Lab_10_1_A.cpp PR_10.1_A/io.cpp PR_10.1_A/calc.cpp -o $@

Lab_10_1_B: PR_10.1_B/Lab_10_1_B.cpp PR_10.1_B/io.cpp PR_10.1_B/calc.cpp PR_10.1_B/student.h PR_10.1_B/io.h PR_10.1_B/calc.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_B PR_10.1_B/Lab_10_1_B.cpp PR_10.1_B/io.cpp PR_10.1_B/calc.cpp -o $@

Lab_10_2_A: PR_10.2_A/Lab_10_2_A.cpp PR_10.2_A/io.cpp PR_10.2_A/sort_search.cpp PR_10.2_A/student.h PR_10.2_A/io.h PR_10.2_A/sort_search.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_A PR_10.2_A/Lab_10_2_A.cpp PR_10.2_A/io.cpp PR_10.2_A/sort_search.cpp -o $@

Lab_10_2_B: PR_10.2_B/Lab_10_2_B.cpp PR_10.2_B/io.cpp PR_10.2_B/sort_search.cpp PR_10.2_B/student.h PR_10.2_B/io.h PR_10.2_B/sort_search.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_B PR_10.2_B/Lab_10_2_B.cpp PR_10.2_B/io.cpp PR_10.2_B/sort_search.cpp -o $@

tests: $(TESTS)

tests/UnitTest_10_1_A: tests/UnitTest_10_1_A.cpp PR_10.1_A/calc.cpp PR_10.1_A/calc.h PR_10.1_A/student.h tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_A -Itests tests/UnitTest_10_1_A.cpp PR_10.1_A/calc.cpp -o $@

tests/UnitTest_10_1_B: tests/UnitTest_10_1_B.cpp PR_10.1_B/calc.cpp PR_10.1_B/calc.h PR_10.1_B/student.h tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_B -Itests tests/UnitTest_10_1_B.cpp PR_10.1_B/calc.cpp -o $@

tests/UnitTest_10_2_A: tests/UnitTest_10_2_A.cpp PR_10.2_A/sort_search.cpp PR_10.2_A/sort_search.h PR_10.2_A/student.h tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_A -Itests tests/UnitTest_10_2_A.cpp PR_10.2_A/sort_search.cpp -o $@

tests/UnitTest_10_2_B: tests/UnitTest_10_2_B.cpp PR_10.2_B/sort_search.cpp PR_10.2_B/sort_search.h PR_10.2_B/student.h tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_B -Itests tests/UnitTest_10_2_B.cpp PR_10.2_B/sort_search.cpp -o $@

test: check
check: tests
	@echo "=================================================="
	@echo "Running all Unit Tests for Lab 10 (Multi-module)..."
	@echo "=================================================="
	@./tests/UnitTest_10_1_A
	@./tests/UnitTest_10_1_B
	@./tests/UnitTest_10_2_A
	@./tests/UnitTest_10_2_B
	@echo "=================================================="
	@echo "ALL TESTS PASSED SUCCESSFULLY!"
	@echo "=================================================="

clean:
	rm -rf $(PROGRAMS) $(TESTS) *.dSYM tests/*.dSYM PR_10.*/*.dSYM PR_10.1_A/Lab_10_1_A PR_10.1_B/Lab_10_1_B PR_10.2_A/Lab_10_2_A PR_10.2_B/Lab_10_2_B
