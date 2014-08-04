%::
	$(MAKE) -C Debug $@
	$(MAKE) -C Release $@

all:
	$(MAKE) -C Debug
	$(MAKE) -C Release


bench.dtb: bench.dts
	dtc -I dts -O dtb -o bench.dtb ../bench.dts


fullbench.cc: fullbench.js
	xxd -i ../../fullbench.js | sed 's/_*fullbench_js/node_script/g' > fullbench.cc

fullbench: bench.dtb fullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Debug
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Release

nullbench.cc: nullbench.js
	xxd -i ../../nullbench.js | sed 's/_*nullbench_js/node_script/g' > nullbench.cc

nullbench: bench.dtb nullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Debug
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Release

goodbench.cc: goodbench.js
	xxd -i ../../goodbench.js | sed 's/_*goodbench_js/node_script/g' > goodbench.cc

goodbench: bench.dtb goodbench.cc
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Debug
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Release

badbench.cc: badbench.js
	xxd -i ../../badbench.js | sed 's/_*badbench_js/node_script/g' > badbench.cc

badbench: bench.dtb badbench.cc
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Debug
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Release

hello.cc: hello_world.js
	xxd -i ../../hello_world.js | sed 's/_*hello_world_js/node_script/g' > hello.cc

hello: bench.dtb hello.cc
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Debug
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Release

clean::
	-$(RM) $(wildcard bench.dtb)  $(wildcard *script.h)  $(wildcard hello.cc fullbench.cc nullbench.cc goodbench.cc badbench.cc) 
	$(MAKE) -C Debug clean
	$(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Release clean
