CLIENTDIR=client
SERVERDIR=server
DEPSDIR=deps
GENDIR=generic

TARGETS =  $(DEPSDIR) $(GENDIR) $(CLIENTDIR) $(SERVERDIR)

all: $(TARGETS)

.PHONY: $(TARGETS)
$(TARGETS):
	$(MAKE) -C $@

.PHONY: deps
deps:
	$(MAKE) -C $(GENDIR)
	$(MAKE) -C $(DEPSDIR)

.PHONY: cleandeps
cleandeps:
	$(MAKE) -C $(GENDIR) clean
	$(MAKE) -C $(DEPSDIR) clean

.PHONY: clean
clean:
	$(MAKE) -C $(CLIENTDIR) clean
	$(MAKE) -C $(SERVERDIR) clean
	$(MAKE) -C $(GENDIR) clean
	$(MAKE) -C $(DEPSDIR) clean

.PHONY: install
install: all
	$(MAKE) -C $(CLIENTDIR) install
	$(MAKE) -C $(SERVERDIR) install
