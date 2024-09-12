# Target for the final binaries
all: measure_system_call measure_context_switch

# Rule for measure_system_call binary
measure_system_call: measure_system_call.c
	clang -o measure_system_call measure_system_call.c

# Rule for measure_context_switch binary
measure_context_switch: measure_context_switch.c
	clang -o measure_context_switch measure_context_switch.c -pthread -std=c99 -D_GNU_SOURCE

# Clean rule (optional, to remove binaries)
clean:
	rm -f measure_system_call measure_context_switch
