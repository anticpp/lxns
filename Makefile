
TARGETS=pid network uts

all: $(TARGETS)

pid: pid.c
	gcc $^ -o $@

network: network.c
	gcc $^ -o $@

uts: uts.c
	gcc $^ -o $@

clean:
	rm -f $(TARGETS)
