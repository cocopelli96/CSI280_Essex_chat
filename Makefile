CLIENTDIR=client
SERVERDIR=server
DEPSDIR=deps

TARGETS =  $(DEPSDIR) $(CLIENTDIR) $(SERVERDIR)

all: $(TARGETS)

.PHONY: $(TARGETS)
$(TARGETS):
	$(MAKE) -C $@

.PHONY: deps
deps:
	$(MAKE) -C $(DEPSDIR)

.PHONY: cleandeps
cleandeps:
	$(MAKE) -C $(DEPSDIR) clean

.PHONY: clean
clean: 
	$(MAKE) -C $(CLIENTDIR) clean
	$(MAKE) -C $(SERVERDIR) clean
	$(MAKE) -C $(DEPSDIR) clean

.PHONY: install
install: all
	$(MAKE) -C $(CLIENTDIR) install
	$(MAKE) -C $(SERVERDIR) install
