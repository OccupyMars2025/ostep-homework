# Makefile for TLB program and testing script

all: tlb test_tlb

# Compile the C program tlb.c
tlb: tlb.c
	gcc -O0 -o tlb tlb.c -lpthread

# Run the Python test script
test_tlb: tlb test_tlb.py
	python3 ./test_tlb.py

# Clean up generated files
clean:
	rm -f tlb

# Help target for usage information
help:
	@echo "Makefile targets:"
	@echo "  all       - Compile tlb.c and run test_tlb.py"
	@echo "  tlb       - Compile tlb.c"
	@echo "  test_tlb  - Run the test_tlb.py script"
	@echo "  clean     - Remove the tlb executable"
