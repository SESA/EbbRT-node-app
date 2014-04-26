MYDIR := $(dir $(lastword $(MAKEFILE_LIST)))

NODE_PATH := $(MYDIR)/../../node

EBBRT_TARGET := node
EBBRT_APP_CAPNPS := CmdLineArgs.capnp
EBBRT_APP_OBJECTS := Node.o CmdLineArgs.o
#EBBRT_APP_DEPS := build-node
EBBRT_APP_VPATH := $(abspath $(MYDIR)../):$(abspath $(MYDIR)../../)
EBBRT_CONFIG := $(abspath $(MYDIR)../ebbrtcfg.h)

#build-node:
#	$(MAKE) -C $(NODE_PATH)/out BUILDTYPE=$(EBBRT_BUILDTYPE)

#EBBRT_PHONY := build-node

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
