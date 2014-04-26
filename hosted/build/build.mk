MYDIR := $(dir $(lastword $(MAKEFILE_LIST)))

app_objects := \
	Node.o \
	CmdLineArgs.o

app_capnps := \
	CmdLineArgs.capnp 

target := node

EBBRT_APP_VPATH := $(MYDIR)/..:$(MYDIR)/../..

include $(abspath $(EBBRT_SRCDIR)/apps/ebbrthosted.mk)
