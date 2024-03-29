.PHONY: all clean skyline

NAME 			:= $(shell basename $(CURDIR))
NAME_LOWER		:= $(shell echo $(NAME) | tr A-Z a-z)

BUILD_DIR 		:= build

MAKE_NSO		:= nso.mk

all: skyline

skyline:
	$(MAKE) all -f $(MAKE_NSO) MAKE_NSO=$(MAKE_NSO) BUILD=$(BUILD_DIR) TARGET=$(NAME)
	mkdir -p 010005F00E036000/exefs
	cp subsdk9 010005F00E036000/exefs/subsdk9
	cp main.npdm 010005F00E036000/exefs/main.npdm

clean:
	$(MAKE) clean -f $(MAKE_NSO)
