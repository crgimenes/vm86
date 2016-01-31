CP = clang

ifndef DEBUG
	CFLAGS := -O3 -fno-rtti -fno-exceptions \
		-fmerge-all-constants \
		-Wall -W -Wshadow -Wpointer-arith \
		-Wcast-qual -Wcast-align -Wwrite-strings \
		-Wconversion -Wwrite-strings -pedantic

else
	CFLAGS := -Wall -W -g -DDEBUG 
endif

LIB_OBJ := r86.c

all: $(LIB_OBJ)
	$(CP) $(CFLAGS) $(LIB_OBJ) -o r86

debug:
	@[ ! -f .debug ] && ($(MAKE) clean ; touch .debug) || true
	$(MAKE) DEBUG=1 all

.SUFFIXES: .c .o
.c.o:
	$(CP) -c $(CFLAGS) $< -o $@

