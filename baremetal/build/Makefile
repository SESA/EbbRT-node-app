%::
	$(MAKE) -C Debug $@
	$(MAKE) -C Release $@

all:
	$(MAKE) -C Debug
	$(MAKE) -C Release


bench.dtb: bench.dts
	dtc -I dts -O dtb -o bench.dtb ../bench.dts

bench: bench.dtb
	NODE_BENCH=1 $(MAKE) -C Debug
	NODE_BENCH=1 $(MAKE) -C Release

clean::
	-$(RM) $(wildcard bench.dtb)
