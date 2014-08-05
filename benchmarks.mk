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
clean: 
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
