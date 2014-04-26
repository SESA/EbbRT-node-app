EBBRT_OPTFLAGS := -O4 -flto -DNDEBUG

FILE_PATH := $(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

EBBRT_APP_VPATH := $(FILE_PATH)/../

EBBRT_CONFIG := $(FILE_PATH)/../config.h

EBBRT_TARGET := nodetest

NODE_PATH := $(FILE_PATH)/../node

EBBRT_APP_OBJECTS := \
	test.o

EBBRT_APP_LINK := \
-Wl,--start-group \
$(NODE_PATH)/out/Release/libchrome_zlib.a \
$(NODE_PATH)/out/Release/libhttp_parser.a \
$(NODE_PATH)/out/Release/libnode.a \
$(NODE_PATH)/out/Release/libuv.a \
$(NODE_PATH)/out/Release/libv8_base.a \
$(NODE_PATH)/out/Release/libv8_nosnapshot.a \
-Wl,--end-group

include ../../EbbRT/baremetal/build.mk
