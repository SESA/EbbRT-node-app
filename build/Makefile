EBBRT_OPTFLAGS := -g3 -O0

FILE_PATH := $(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

EBBRT_APP_VPATH := $(FILE_PATH)/../

EBBRT_CONFIG := $(FILE_PATH)/../config.h

EBBRT_TARGET := nodetest

NODE_PATH := $(FILE_PATH)/../node

EBBRT_APP_OBJECTS := \
	test.o

EBBRT_APP_LINK := \
-Wl,--start-group \
$(NODE_PATH)/out/Debug/libchrome_zlib.a \
$(NODE_PATH)/out/Debug/libhttp_parser.a \
$(NODE_PATH)/out/Debug/libnode.a \
$(NODE_PATH)/out/Debug/libuv.a \
$(NODE_PATH)/out/Debug/libv8_base.a \
$(NODE_PATH)/out/Debug/libv8_nosnapshot.a \
-Wl,--end-group

include ../../EbbRT/baremetal/build.mk
