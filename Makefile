
TARGETS=pid network mount

all: $(TARGETS)

pidns: pid.c
	gcc $^ -o $@

nwns: network.c
	gcc $^ -o $@

mntns: mount.c
	gcc $^ -o $@

clean:
	rm -f $(TARGETS)
