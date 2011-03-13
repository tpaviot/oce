srcdir = @srcdir@

SUBDIRS = adm/make

VPATH = @srcdir@ \
@top_srcdir@/make: \
@top_srcdir@/adm/make:

FoundationClasses_PKGS = OS 
FoundationClasses_DIRS = $(FoundationClasses_PKGS)


FoundationClasses:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) FoundationClasses

ModelingData_PKGS = 
if ENABLE_MODEL
  ModelingData_DIRS = $(ModelingData_PKGS)
else
  ModelingData_DIRS = 
endif


ModelingData:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) ModelingData

ModelingAlgorithms_PKGS = 
if ENABLE_MODEL
  ModelingAlgorithms_DIRS = $(ModelingAlgorithms_PKGS)
else
  ModelingAlgorithms_DIRS = 
endif


ModelingAlgorithms:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) ModelingAlgorithms

Visualization_PKGS = FontMFT Textures 
if ENABLE_VIS
  Visualization_DIRS = $(Visualization_PKGS)
else
  Visualization_DIRS = 
endif


Visualization:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) Visualization

ApplicationFramework_PKGS = StdResource XmlOcafResource 
if ENABLE_OCAF
  ApplicationFramework_DIRS = $(ApplicationFramework_PKGS)
else
  ApplicationFramework_DIRS = 
endif


ApplicationFramework:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) ApplicationFramework

DataExchange_PKGS = SHMessage XSMessage XSTEPResource 
if ENABLE_DE
  DataExchange_DIRS = $(DataExchange_PKGS)
else
  DataExchange_DIRS = 
endif


DataExchange:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) DataExchange

Draw_PKGS = DrawResources 
if ENABLE_DRAW
  Draw_DIRS = $(Draw_PKGS)
else
  Draw_DIRS = 
endif


Draw:
	cd $(top_builddir)/adm/make && $(MAKE) $(AM_MAKEFLAGS) Draw

CP_Linux=L
CP_SunOS=

dir_Linux=lin
dir_SunOS=sun

install-exec-local:
	$(INSTALL) -d $(prefix)/$(platform)
	if [ -e $(prefix)/bin -a ! -e $(prefix)/$(platform)/bin ]; then \
		cd $(prefix)/$(platform) && ln -s ../bin bin; \
	fi
	if [ -e $(prefix)/lib -a ! -e $(prefix)/$(platform)/lib ]; then \
		cd $(prefix)/$(platform) && ln -s ../lib lib; \
	fi
	$(INSTALL) -d $(prefix)/$(dir_$(platform))
	if [ -e $(prefix)/bin -a ! -e $(prefix)/$(dir_$(platform))/bin ]; then \
		cd $(prefix)/$(dir_$(platform)) && ln -s ../bin bin; \
	fi
	if [ -e $(prefix)/lib -a ! -e $(prefix)/$(dir_$(platform))/lib ]; then \
		cd $(prefix)/$(dir_$(platform)) && ln -s ../lib lib; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		$(INSTALL) -d $(prefix)/inc; \
		cp -fr$(CP_$(platform)) $(top_srcdir)/inc $(prefix); \
	fi; \
	if [ "$$pd" != "$$bd" ]; then \
		cp -fr$(CP_$(platform)) $$bd/config.h $(prefix); \
	fi
	if [ -e $(prefix)/inc/config.h ]; then \
		unlink $(prefix)/inc/config.h; \
	fi
	cd $(prefix)/inc && ln -s ../config.h config.h 
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" -a -d $(top_srcdir)/src/UnitsAPI ]; then \
		$(INSTALL) -d $(prefix)/src; \
		$(INSTALL) -d $(prefix)/src/UnitsAPI; \
		cp -fr$(CP_$(platform)) $(top_srcdir)/src/UnitsAPI $(prefix)/src; \
		cp -f$(CP_$(platform)) $(top_srcdir)/env_DRAW.sh $(prefix); \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(FoundationClasses_DIRS)"; \
		if test "x$(FoundationClasses_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(ModelingData_DIRS)"; \
		if test "x$(ModelingData_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(ModelingAlgorithms_DIRS)"; \
		if test "x$(ModelingAlgorithms_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(Visualization_DIRS)"; \
		if test "x$(Visualization_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(ApplicationFramework_DIRS)"; \
		if test "x$(ApplicationFramework_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(DataExchange_DIRS)"; \
		if test "x$(DataExchange_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi
	bd=`pwd`; cd $(top_srcdir); sd=`pwd`; cd $(prefix); pd=`pwd`; cd $$bd; \
	if [ "$$pd" != "$$sd" ]; then \
		inst_dirs="$(Draw_DIRS)"; \
		if test "x$(Draw_DIRS)" != "x"; then \
			for d in $$inst_dirs; do \
				$(INSTALL) -d $(prefix)/src/$$d; \
				cp -fr$(CP_$(platform)) $(top_srcdir)/src/$$d $(prefix)/src; \
			done; \
		fi; \
	fi

.PHONY: FoundationClasses ModelingData ModelingAlgorithms Visualization ApplicationFramework DataExchange Draw
