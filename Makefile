
TARGETS=pid network user

all: $(TARGETS)

pidns: pid.c
	gcc $^ -o $@

nwns: network.c
	gcc $^ -o $@

mntns: user.c
	gcc $^ -o $@

clean:
	rm -f $(TARGETS)
