bench.dtb: ../bench.dts
	dtc -I dts -O dtb -o bench.dtb ../bench.dts

### Individual benchmarks -- derived from commenting out appropriate
### lines from fullbench.js
crypto.cc: ../../crypto.js
	xxd -i ../../crypto.js | sed 's/_*crypto_js/node_script/g' > crypto.cc

crypto: bench.dtb crypto.cc
	NODE_BENCH=1 NODE_SCRIPT="crypto" $(MAKE) -C Release

.PHONY: cryptodbg
cryptodbg: bench.dtb crypto.cc
	NODE_BENCH=1 NODE_SCRIPT="crypto" $(MAKE) -C Debug
deltablue.cc: ../../deltablue.js
	xxd -i ../../deltablue.js | sed 's/_*deltablue_js/node_script/g' > deltablue.cc

deltablue: bench.dtb deltablue.cc
	NODE_BENCH=1 NODE_SCRIPT="deltablue" $(MAKE) -C Release

.PHONY: deltabluedbg
deltabluedbg: bench.dtb deltablue.cc
	NODE_BENCH=1 NODE_SCRIPT="deltablue" $(MAKE) -C Debug
earleyboyer.cc: ../../earleyboyer.js
	xxd -i ../../earleyboyer.js | sed 's/_*earleyboyer_js/node_script/g' > earleyboyer.cc

earleyboyer: bench.dtb earleyboyer.cc
	NODE_BENCH=1 NODE_SCRIPT="earleyboyer" $(MAKE) -C Release

.PHONY: earleyboyerdbg
earleyboyerdbg: bench.dtb earleyboyer.cc
	NODE_BENCH=1 NODE_SCRIPT="earleyboyer" $(MAKE) -C Debug
navierstokes.cc: ../../navierstokes.js
	xxd -i ../../navierstokes.js | sed 's/_*navierstokes_js/node_script/g' > navierstokes.cc

navierstokes: bench.dtb navierstokes.cc
	NODE_BENCH=1 NODE_SCRIPT="navierstokes" $(MAKE) -C Release

.PHONY: navierstokesdbg
navierstokesdbg: bench.dtb navierstokes.cc
	NODE_BENCH=1 NODE_SCRIPT="navierstokes" $(MAKE) -C Debug
raytrace.cc: ../../raytrace.js
	xxd -i ../../raytrace.js | sed 's/_*raytrace_js/node_script/g' > raytrace.cc

raytrace: bench.dtb raytrace.cc
	NODE_BENCH=1 NODE_SCRIPT="raytrace" $(MAKE) -C Release

.PHONY: raytracedbg
raytracedbg: bench.dtb raytrace.cc
	NODE_BENCH=1 NODE_SCRIPT="raytrace" $(MAKE) -C Debug
regexp.cc: ../../regexp.js
	xxd -i ../../regexp.js | sed 's/_*regexp_js/node_script/g' > regexp.cc

regexp: bench.dtb regexp.cc
	NODE_BENCH=1 NODE_SCRIPT="regexp" $(MAKE) -C Release

.PHONY: regexpdbg
regexpdbg: bench.dtb regexp.cc
	NODE_BENCH=1 NODE_SCRIPT="regexp" $(MAKE) -C Debug
richards.cc: ../../richards.js
	xxd -i ../../richards.js | sed 's/_*richards_js/node_script/g' > richards.cc

richards: bench.dtb richards.cc
	NODE_BENCH=1 NODE_SCRIPT="richards" $(MAKE) -C Release

.PHONY: richardsdbg
richardsdbg: bench.dtb richards.cc
	NODE_BENCH=1 NODE_SCRIPT="richards" $(MAKE) -C Debug
splay.cc: ../../splay.js
	xxd -i ../../splay.js | sed 's/_*splay_js/node_script/g' > splay.cc

splay: bench.dtb splay.cc
	NODE_BENCH=1 NODE_SCRIPT="splay" $(MAKE) -C Release

.PHONY: splaydbg
splaydbg: bench.dtb splay.cc
	NODE_BENCH=1 NODE_SCRIPT="splay" $(MAKE) -C Debug

#### combinations of  benchmarks

octane2.cc: ../../octane2.js
	xxd -i ../../octane2.js | sed 's/_*octane2_js/node_script/g' > octane2.cc

octane2: bench.dtb octane2.cc
	NODE_BENCH=1 NODE_SCRIPT="octane2" $(MAKE) -C Release

.PHONY: octane2dbg
octane2dbg: bench.dtb octane2.cc
	NODE_BENCH=1 NODE_SCRIPT="octane2" $(MAKE) -C Debug

fullbench.cc: ../../fullbench.js
	xxd -i ../../fullbench.js | sed 's/_*fullbench_js/node_script/g' > fullbench.cc

fullbench: bench.dtb fullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Release

.PHONY: fullbenchdbg
fullbenchdbg: bench.dtb fullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Debug

fullbench-quiet.cc: ../../fullbench-quiet.js
	xxd -i ../../fullbench-quiet.js | sed 's/_*fullbench_quiet_js/node_script/g' > fullbench-quiet.cc

fullbench-quiet: bench.dtb fullbench-quiet.cc
	NODE_BENCH=1 NODE_SCRIPT="fullbench-quiet" $(MAKE) -C Release

.PHONY: fullbench-quietdbg
fullbench-quietdbg: bench.dtb fullbench-quiet.cc
	NODE_BENCH=1 NODE_SCRIPT="fullbench-quiet" $(MAKE) -C Debug

nullbench.cc: ../../nullbench.js
	xxd -i ../../nullbench.js | sed 's/_*nullbench_js/node_script/g' > nullbench.cc

nullbench: bench.dtb nullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Release

.PHONY: nullbenchdbg

nullbenchdbg: bench.dtb nullbench.cc
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Debug

goodbench.cc: ../../goodbench.js
	xxd -i ../../goodbench.js | sed 's/_*goodbench_js/node_script/g' > goodbench.cc

goodbench: bench.dtb goodbench.cc
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Release

.PHONY: goodbenchdbg
goodbenchdbg: bench.dtb goodbench.cc
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Debug

badbench.cc: ../../badbench.js
	xxd -i ../../badbench.js | sed 's/_*badbench_js/node_script/g' > badbench.cc

badbench: bench.dtb badbench.cc
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Release

.PHONY: badbenchdbg
badbenchdbg: bench.dtb badbench.cc
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Debug

hello.cc: ../../hello_world.js
	xxd -i ../../hello_world.js | sed 's/_*hello_world_js/node_script/g' > hello.cc

hello: bench.dtb hello.cc
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Release

.PHONY: hellodbg
hellodbg: bench.dtb hello.cc
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Debug

hello_http.cc: ../../hello_http.js
	xxd -i ../../hello_http.js | sed 's/_*hello_http_js/node_script/g' > hello_http.cc

hello_http: bench.dtb hello_http.cc
	NODE_BENCH=1 NODE_NET_CFG=1 NODE_SCRIPT="hello_http" $(MAKE) -C Release

.PHONY: hello_httpdbg
hello_httpdbg: bench.dtb hello_http.cc
	NODE_BENCH=1 NODE_NET_CFG=1 NODE_SCRIPT="hello_http" $(MAKE) -C Debug

clean::
	-$(RM) $(wildcard bench.dtb)  $(wildcard *script.h)  $(wildcard hello.cc hello_http.cc fullbench.cc nullbench.cc goodbench.cc badbench.cc octane2.cc) 
	$(MAKE) -C Debug clean
	$(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="crypto" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="crypto" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="deltablue" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="deltablue" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="earleyboyer" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="earleyboyer" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="navierstokes" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="navierstokes" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="raytrace" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="raytrace" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="regexp" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="regexp" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="richards" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="richards" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="splay" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="splay" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="nullbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench-quiet" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="fullbench-quiet" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="hello_http" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="hello_http" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="octane2" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="octane2" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="badbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="goodbench" $(MAKE) -C Release clean
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Debug clean
	NODE_BENCH=1 NODE_SCRIPT="hello" $(MAKE) -C Release clean
