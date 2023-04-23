target := bsnes
binary := application
build := performance
openmp := true
local := true
flags += -I. -I..

# in order for this to work, obj/lzma.o must be omitted or bsnes will hang on startup.
# further, only the X-Video driver works reliably. OpenGL 3.2, OpenGL 2.0, and XShm crash bsnes.
ifeq ($(profile),true)
  flags += -pg
  options += -pg
endif

# binaries built with this flag are faster, but are not portable to multiple machines.
ifeq ($(local),true)
  flags += -march=native
endif

nall.path := ../nall
include $(nall.path)/GNUmakefile

ifeq ($(platform),windows)
  ifeq ($(binary),application)
    options += -luuid -lkernel32 -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lshell32
    options += -Wl,-enable-auto-import
    options += -Wl,-enable-runtime-pseudo-reloc
  else ifeq ($(binary),library)
    options += -shared
  endif
else ifeq ($(platform),macos)
  ifeq ($(binary),application)
  else ifeq ($(binary),library)
    flags += -fPIC
    options += -dynamiclib
  endif
else ifneq ($(filter $(platform),linux bsd),)
  ifeq ($(binary),application)
    options += -Wl,-export-dynamic
    options += -lX11 -lXext
  else ifeq ($(binary),library)
    flags += -fPIC
    options += -shared
  endif
endif

objects := libco emulator filter lzma

#flags += $(shell python3-config --cflags)
flags += -I/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11 -I/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11 -fno-common -dynamic -DNDEBUG -g -fwrapv -O3 -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX13.sdk

obj/libco.o: ../libco/libco.c
obj/emulator.o: emulator/emulator.cpp
obj/filter.o: filter/filter.cpp
obj/lzma.o: lzma/lzma.cpp

include sfc/GNUmakefile
include gb/GNUmakefile
include processor/GNUmakefile

ui := target-$(target)
include $(ui)/GNUmakefile
-include obj/*.d

clean:
	$(call delete,obj/*)
	$(call delete,out/*)
