MYDIR := $(dir $(lastword $(MAKEFILE_LIST)))

NODE_PATH := $(MYDIR)/../../node

ifeq ($(NODE_BENCH),1)
#EBBRT_TARGET := $(shell echo $(NODE_SCRIPT) | tr '[:upper:]' '[:lower:]') )
EBBRT_TARGET := $(NODE_SCRIPT)
EBBRT_APP_OBJECTS := Node.o CmdLineArgs.o FileSystem.o $(NODE_SCRIPT).o
$(info NODE_BENCH set to $(NODE_BENCH) NODE_SCRIPT set to $(NODE_SCRIPT) : EBBRT_TARGET now set to $(EBBRT_TARGET) : EBBRT_APP_OBJECTS now set to $(EBBRT_APP_OBJECTS) )
EBBRT_CONFIG := $(abspath $(MYDIR)../ebbrtbenchcfg.h)
EBBRT_APP_INCLUDES := -DBM_ONLY 
else
EBBRT_TARGET := node
EBBRT_APP_OBJECTS := Node.o CmdLineArgs.o FileSystem.o
EBBRT_CONFIG := $(abspath $(MYDIR)../ebbrtcfg.h)
endif

EBBRT_APP_CAPNPS := CmdLineArgs.capnp FileSystem.capnp
EBBRT_APP_DEPS := build-node
EBBRT_APP_VPATH := $(abspath $(MYDIR)):$(abspath $(MYDIR)../):$(abspath $(MYDIR)../../)

EBBRT_PHONY := build-node

EBBRT_APP_LINK := \
	-Wl,--start-group \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libchrome_zlib.a \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libhttp_parser.a \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libnode.a \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libuv.a \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libv8_base.a \
	$(NODE_PATH)/out/$(EBBRT_BUILDTYPE)/libv8_nosnapshot.a \
	-Wl,--end-group


include $(abspath $(EBBRT_SRCDIR)/apps/ebbrtbaremetal.mk)

build-node:
	cd $(NODE_PATH); CXX=${EBBRT_SRCDIR}/baremetal/ext/toolchain/bin/x86_64-pc-ebbrt-g++ CC=${EBBRT_SRCDIR}/baremetal/ext/toolchain/bin/x86_64-pc-ebbrt-gcc ./configure --without-npm --without-ssl --without-snapshot --dest-cpu=x64 --dest-os=ebbrt
	$(MAKE) -C $(NODE_PATH)/out BUILDTYPE=$(EBBRT_BUILDTYPE)
