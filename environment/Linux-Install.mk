#
#
#You are not expected to touch this make file directly as it does not 
#build program but just install simple environment programs
#
#This make file installs the following environments
#
#	simplerepl
#	simplepad
#	modular
#	bake
#	webworker
#

# Macros
VERSION=s0.3.303-debug
CND_PLATFORM=Linux
ENV_DISTDIR=../../$(VERSION)/environment

#ifeq ($(PREFIX),)
#    PREFIX := /usr/local
#endif

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install $(ENV_DISTDIR)/* $(DESTDIR)$(PREFIX)/bin/
	
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/simplerepl
	rm -f $(DESTDIR)$(PREFIX)/bin/simplepad
	rm -f $(DESTDIR)$(PREFIX)/bin/modular
	rm -f $(DESTDIR)$(PREFIX)/bin/bake
	rm -f $(DESTDIR)$(PREFIX)/bin/webworker

#If this make file does not work on your Windows PC or you use 
#alternative compiler e.g Visual Studio, Cygwin e.t.c feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/modules . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Linux-{Compiler}-{WindowsVersion}.mk
#
#e.g Makefile-Linux-cygwin-Windows8.mk
#
#looking forward to your contribution
#Thank You

