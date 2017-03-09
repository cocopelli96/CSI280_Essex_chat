CC=g++
LD=g++
CFLAGS=-Wall --std=c++11
LDFLAGS=-L../deps/tacopie/build/lib/ -ltacopie

OBJDIR=obj
OBJFILES = $(addprefix $(OBJDIR)/, client.o)

INCDIR=$(addprefix -I, ../deps/tacopie/includes)

BINDIR=bin
BINNAME=chatter_client

SRCDIR=src

MKDIR = mkdir -p

INSTALL=install

.PHONY: directories

all: directories $(BINNAME)

directories:
	$(MKDIR) $(OBJDIR) $(BINDIR)

$(BINNAME): $(OBJFILES)
	 $(LD) $(LDFLAGS) -o $(BINDIR)/$(BINNAME) $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $< $(INCDIR)

.PHONY: clean
clean:
	rm -rf obj/ bin/

.PHONY: install
install: all
	$(INSTALL) $(BINDIR)/$(BINNAME)