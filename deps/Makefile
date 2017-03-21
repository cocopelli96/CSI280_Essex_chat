SHELL = bash
CMAKE := $(shell command -v cmake)
MKDIR = mkdir
RM = rm -rf
all: deps

.PHONY: deps
deps:
ifeq ($(strip $(CMAKE)),)
	($(error cmake must be installed in order to compile these dependencies))
else
	$(MKDIR) ./tacopie/build
	cd tacopie/build && \
	$(CMAKE) .. && \
	$(MAKE) && \
	cd ../../colorizer/ && \
	$(MAKE)
endif

.PHONY: clean
clean:
	$(RM) ./tacopie/build
