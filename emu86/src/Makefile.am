SUBDIRS = cpu hardware mem

bin_PROGRAMS = emu86
emu86_SOURCES = emu86.c timer.c log.c

emu86_LDADD = cpu/libcpu.a hardware/libhardware.a mem/libmem.a
