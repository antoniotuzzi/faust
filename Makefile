version := 0.9.67

DESTDIR ?= 
PREFIX ?= /usr/local
CROSS=i586-mingw32msvc-

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

all :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix)
	$(MAKE) -C architecture/osclib
	

httpd :
	$(MAKE) -C architecture/httpdlib/src

win32 :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix) CXX=$(CROSS)g++
	$(MAKE) -C architecture/osclib CXX=$(CROSS)g++ system=Win32

sound2faust: 

	$(MAKE) -C tools/sound2faust

.PHONY: clean depend install ininstall dist parser help

help :
	@echo "Usage : 'make; sudo make install'"
	@echo "For http support : 'make httpd; make; sudo make install' (requires GNU libmicrohttpd)"
	@echo "make or make all : compile the faust compiler"
	@echo "make httpd : compile httpdlib (requires GNU libmicrohttpd)"
	@echo "make sound2faust : compile sound to DSP file converter"
	@echo "make parser : generate the parser from the lex and yacc files"
	@echo "make clean : remove all object files"
	@echo "make doc : generate the documentation using doxygen"
	@echo "make install : install the compiler, tools and the architecture files in $(prefix)/bin $(prefix)/lib/faust $(prefix)/include/faust"
	@echo "make uninstall : undo what install did"
	@echo "make dist : make a Faust distribution as a .zip file"
	@echo "make log : make a changelog file"

parser :
	$(MAKE) -C compiler -f $(MAKEFILE) parser

clean :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	$(MAKE) -C architecture/osclib clean
	$(MAKE) -C architecture/httpdlib/src clean

depend :
	$(MAKE) -C compiler -f $(MAKEFILE) depend
	$(MAKE) -C architecture/osclib depend
	$(MAKE) -C architecture/httpdlib/src depend


doc :
	$(MAKE) -C compiler -f $(MAKEFILE) doc


install :
	# install faust itself
	mkdir -p $(prefix)/bin/
	mkdir -p $(prefix)/include/
	mkdir -p $(prefix)/include/faust/
	mkdir -p $(prefix)/include/faust/osc/
	install compiler/faust $(prefix)/bin/
	# install architecture and faust library files
	mkdir -p $(prefix)/lib/faust
	cp architecture/*.cpp $(prefix)/lib/faust/
	cp architecture/*.lib $(prefix)/lib/faust/
	# install iOS
	rm -rf $(prefix)/lib/faust/iOS
	cp -r architecture/iOS $(prefix)/lib/faust/
	rm -rf $(prefix)/lib/faust/iOS/DerivedData/
	# install AU
	rm -rf $(prefix)/lib/faust/AU/
	cp -r architecture/AU $(prefix)/lib/faust/
	cp -r architecture/android $(prefix)/lib/faust/
	# install math documentation files
	cp architecture/mathdoctexts-*.txt $(prefix)/lib/faust/
	cp architecture/latexheader.tex $(prefix)/lib/faust/
	# install additional binary libraries (osc, http,...)
	([ -e architecture/httpdlib/libHTTPDFaust.a ] && cp architecture/httpdlib/libHTTPDFaust.a $(prefix)/lib/faust/) || echo libHTTPDFaust not available	
	cp architecture/osclib/*.a $(prefix)/lib/faust/
	cp -r architecture/httpdlib/html/js $(prefix)/lib/faust/js
	([ -e architecture/httpdlib/src/hexa/stylesheet ] && cp architecture/httpdlib/src/hexa/stylesheet $(prefix)/lib/faust/js/stylesheet.js) || echo stylesheet not available
	([ -e architecture/httpdlib/src/hexa/jsscripts ] && cp architecture/httpdlib/src/hexa/jsscripts $(prefix)/lib/faust/js/jsscripts.js) || echo jsscripts not available
	# install includes files for architectures
	cp -r architecture/faust $(prefix)/include/
	# install additional includes files for binary libraries  (osc, http,...)
	cp architecture/osclib/faust/faust/OSCControler.h $(prefix)/include/faust/gui/
	cp architecture/osclib/faust/faust/osc/*.h $(prefix)/include/faust/osc/
	cp architecture/httpdlib/src/include/*.h $(prefix)/include/faust/gui/
	# install faust2xxx tools
	make -C tools/faust2appls install
	# install sound2faust converter
	[ -e tools/sound2faust/sound2faust ] && make -C tools/sound2faust install || echo sound2faust not compiled
	# install webaudio
	cp -r architecture/webaudio $(prefix)/lib/faust/


uninstall :
	rm -rf $(prefix)/lib/faust/
	rm -rf $(prefix)/include/faust/
	rm -f $(prefix)/bin/faust
	make -C tools/faust2appls uninstall

# make a faust distribution .zip file
dist :
	git archive -o faust-$(version).zip --prefix=faust-$(version)/ HEAD


log :
	git log --oneline --date-order --reverse --after={2011-01-07} master >log-$(version)
	
# DO NOT DELETE
