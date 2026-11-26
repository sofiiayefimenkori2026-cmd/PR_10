CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

PROGRAMS = Lab_10_1_A Lab_10_1_B Lab_10_2_A Lab_10_2_B
TESTS = tests/UnitTest_10_1_A tests/UnitTest_10_1_B tests/UnitTest_10_2_A tests/UnitTest_10_2_B

.PHONY: all programs tests test check clean

all: programs tests

programs: $(PROGRAMS)

Lab_10_1_A: PR_10.1_A/Lab_10_1_A.cpp
	$(CXX) $(CXXFLAGS) PR_10.1_A/Lab_10_1_A.cpp -o $@

Lab_10_1_B: PR_10.1_B/Lab_10_1_B.cpp
	$(CXX) $(CXXFLAGS) PR_10.1_B/Lab_10_1_B.cpp -o $@

Lab_10_2_A: PR_10.2_A/Lab_10_2_A.cpp
	$(CXX) $(CXXFLAGS) PR_10.2_A/Lab_10_2_A.cpp -o $@

Lab_10_2_B: PR_10.2_B/Lab_10_2_B.cpp
	$(CXX) $(CXXFLAGS) PR_10.2_B/Lab_10_2_B.cpp -o $@

tests: $(TESTS)

tests/UnitTest_10_1_A: PR_10.1_A/UnitTest_10_1_A.cpp PR_10.1_A/Lab_10_1_A.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_A -Itests PR_10.1_A/UnitTest_10_1_A.cpp -o $@

tests/UnitTest_10_1_B: PR_10.1_B/UnitTest_10_1_B.cpp PR_10.1_B/Lab_10_1_B.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.1_B -Itests PR_10.1_B/UnitTest_10_1_B.cpp -o $@

tests/UnitTest_10_2_A: PR_10.2_A/UnitTest_10_2_A.cpp PR_10.2_A/Lab_10_2_A.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_A -Itests PR_10.2_A/UnitTest_10_2_A.cpp -o $@

tests/UnitTest_10_2_B: PR_10.2_B/UnitTest_10_2_B.cpp PR_10.2_B/Lab_10_2_B.cpp tests/doctest.h
	$(CXX) $(CXXFLAGS) -IPR_10.2_B -Itests PR_10.2_B/UnitTest_10_2_B.cpp -o $@

test: check
check: tests
	@echo "=================================================="
	@echo "Running all Unit Tests for Lab 10 (A & B)..."
	@echo "=================================================="
	@./tests/UnitTest_10_1_A
	@./tests/UnitTest_10_1_B
	@./tests/UnitTest_10_2_A
	@./tests/UnitTest_10_2_B
	@echo "=================================================="
	@echo "ALL TESTS PASSED SUCCESSFULLY!"
	@echo "=================================================="

clean:
	rm -rf $(PROGRAMS) $(TESTS) *.dSYM tests/*.dSYM PR_10.*/*.dSYM
