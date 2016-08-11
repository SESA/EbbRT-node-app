MYDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

CD ?= cd
CP ?= cp
CMAKE ?= cmake
MAKE ?= make
MKDIR ?= mkdir
OBJCOPY ?= objcopy
RM ?= rm
STRIP ?= strip

BUILD_DIR ?= $(MYDIR)/build
NATIVE_DIR := $(BUILD_DIR)/bm

NODE_DIR := $(MYDIR)/node
NODE_CONFIG_FLAGS ?=

ifndef EBBRT_SYSROOT
$(error EBBRT_SYSROOT is undefined)
endif

all: hosted native

clean:
	-$(RM) -r $(BUILD_DIR)
	$(MAKE) -C $(NODE_DIR) distclean

hosted: $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR)

native: $(NATIVE_DIR)/node.elf32

linux:
	$(CD) $(NODE_DIR) && ./configure --dest-os=linux --without-ssl \
        --without-npm --without-snapshot --dest-cpu=x64 \
        $(NODE_CONFIG_FLAGS) && $(MAKE)
$(BUILD_DIR)/Makefile: | $(BUILD_DIR)
	$(CD) $(BUILD_DIR) && $(CMAKE) -DCMAKE_AR=gcc-ar \
	-DCMAKE_RANLIB=gcc-ranlib -DCMAKE_BUILD_TYPE=Release $(MYDIR)

$(BUILD_DIR):
	$(MKDIR) $@

$(NATIVE_DIR): | $(BUILD_DIR)
	$(MKDIR) $@

$(NODE_DIR)/node:
	$(CD) $(NODE_DIR) && CC=$(EBBRT_SYSROOT)/usr/bin/x86_64-pc-ebbrt-gcc \
	CXX=$(EBBRT_SYSROOT)/usr/bin/x86_64-pc-ebbrt-g++ ./configure \
	--dest-os=ebbrt --without-ssl --without-npm --without-snapshot \
	--dest-cpu=x64 $(NODE_CONFIG_FLAGS) && $(MAKE)

$(NATIVE_DIR)/node.elf: $(NODE_DIR)/node | $(NATIVE_DIR)
	$(CP) $< $@

%.elf.stripped: %.elf
	$(STRIP) -s $< -o $@

%.elf32: %.elf.stripped
	$(OBJCOPY) -O elf32-i386 $< $@

.PHONY: all clean hosted native
