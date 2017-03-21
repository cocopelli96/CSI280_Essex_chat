SHELL = bash
CMAKE := $(shell command -v cmake)
MKDIR = mkdir -p
RM = rm -rf
UNAME_S := $(shell uname -s)
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
ifneq ($(UNAME_S),MSYS_NT-6.1)
	cd ncurses && \
	./configure && \
	$(MAKE)
else
	$(info MSYS user need to install ncurses-devel to compile this suite...)
endif
endif

.PHONY: clean
clean:
	$(RM) ./tacopie/build
