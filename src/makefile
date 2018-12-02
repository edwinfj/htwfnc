# default
REL:=1
AVX2:=1
# end default

OBJDIR:=../bin

ifeq ($(REL),1)
	BUILD_TYPE:=Release
	CPPFLAGS+=-DRELEASE
else
	BUILD_TYPE:=Debug
	CPPFLAGS+=-DDEBUG
endif

OBJDIR:=$(abspath $(addsuffix $(BUILD_TYPE)/,$(addsuffix _,$(OBJDIR))))

HEADERS:=kernels.h test.h
SRCS:=kernels.c main.c test.c
LIBS:=m
EXE:=$(addprefix $(OBJDIR)/,main)
OBJS:=$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
TUS:=$(addprefix $(OBJDIR)/,$(SRCS:.c=.i))
ASMS:=$(addprefix $(OBJDIR)/,$(SRCS:.c=.s))

INCLUDE_PATH+=
LIBRARY_PATH+=
LD_LIBRARY_PATH+=

CPPFLAGS+=-Wall
CFLAGS+=-g
LDFLAGS+=$(foreach lib,$(LIBS),-l$(lib))

TARGET_ARCH+=

ifeq ($(AVX2), 1)
	CFLAGS+=-mavx2
else
	CFLAGS+=-mavx    # most processors nowadays has the avx extension
endif

ifeq ($(BUILD_TYPE),Release)
	CFLAGS+=-O3
	ifeq ($(GPROF),1)
		ifeq ($(CC),gcc)
			CLFAGS+=-pg
		else
			ifeq ($(CC), icc)
				CFLAGS+=-p
			endif
		endif
	endif
endif

.PHONY: all clean gen_asm gen_tu dist_clean

all: $(EXE)

gen_asm: $(ASMS)

$(EXE): $(OBJS)
	$(LINK.c) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $< -o $@

$(OBJDIR)/%.i: %.c
ifeq ($(CC), icc)
	$(CC) $(CPPFLAGS) -P -C $< -o $@
else
	$(CC) $(CPPFLAGS) -E -C $< -o $@
endif

$(OBJDIR)/%.s: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -S $< -o $@

$(OBJS) $(ASMS) $(TUS): $(HEADERS) | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(EXE) $(OBJS) $(TUS) $(ASMS) 2> /dev/null

dist_clean:
	rm -f $(EXE) 2> /dev/null