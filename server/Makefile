CC=g++
LD=g++
CFLAGS=-Wall --std=c++11
LDFLAGS=-L../deps/tacopie/build/lib/ -ltacopie -L../deps/colorizer/lib -lcolorizer -pthread

OBJDIR=obj
OBJFILES = $(addprefix $(OBJDIR)/, server.o)

INCDIR=$(addprefix -I, ../deps/tacopie/includes ../deps/colorizer/include)

BINDIR=bin
BINNAME=chatter_server

SRCDIR=src

MKDIR = mkdir -p

INSTALL=install

.PHONY: directories

all: directories $(BINNAME)

directories:
	$(MKDIR) $(OBJDIR) $(BINDIR)

$(BINNAME): $(OBJFILES)
	 $(LD) -o $(BINDIR)/$(BINNAME) $< $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $< $(INCDIR)

.PHONY: clean
clean:
	rm -rf obj/ bin/

.PHONY: install
install: all
	$(INSTALL) $(BINDIR)/$(BINNAME)
