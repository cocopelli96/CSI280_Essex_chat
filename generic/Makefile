CC=g++
LD=ar
CFLAGS=-Wall --std=gnu++11
LDFLAGS=rcs

OBJDIR=obj
OBJFILES = $(addprefix $(OBJDIR)/, command_names.o message.o message_handler.o)

INCDIR=$(addprefix -I, ./include)

BINDIR=lib
BINNAME=libessexgeneric.a

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
	rm -rf obj/ lib/

.PHONY: install
install: all
	$(INSTALL) $(BINDIR)/$(BINNAME)
