
TARGETS=pid network uts runc

all: $(TARGETS)

pid: pid.c
	gcc $^ -o $@

network: network.c
	gcc $^ -o $@

uts: uts.c
	gcc $^ -o $@

runc: runc.c
	gcc $^ -o $@



clean:
	rm -f $(TARGETS)
