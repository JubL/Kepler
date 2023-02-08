SHELL := /bin/bash
MAKEFLAGS += --no-print-directory

all: ./bld/Makefile
	@ $(MAKE) -j -C bld

debug: ./bld_dbg/Makefile
	@ $(MAKE) -j -C bld_dbg

./bld/Makefile:
	@  mkdir -p bld
	@  cd bld && cmake -DCMAKE_BUILD_TYPE=Release ../src/

./bld_dbg/Makefile:
	@  mkdir -p bld_dbg
	@  cd bld_dbg && cmake -DCMAKE_BUILD_TYPE=Debug ../src/
