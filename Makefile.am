srcdir = @srcdir@

SUBDIRS = adm/lin/amk

VPATH = @srcdir@ @top_srcdir@/adm/lin/amk: @top_srcdir@/adm/lin/amk:

FoundationClasses_PKGS = OS UnitsAPI

if ENABLE_FOC
  FoundationClasses_DIRS = $(FoundationClasses_PKGS)
else
  FoundationClasses_DIRS = 
endif

FoundationClasses:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) FoundationClasses

ModelingData_PKGS =

if ENABLE_DATA
  ModelingData_DIRS = $(ModelingData_PKGS)
else
  ModelingData_DIRS = 
endif

ModelingData:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) ModelingData

ModelingAlgorithms_PKGS =

if ENABLE_ALGO
  ModelingAlgorithms_DIRS = $(ModelingAlgorithms_PKGS)
else
  ModelingAlgorithms_DIRS = 
endif

ModelingAlgorithms:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) ModelingAlgorithms

Visualization_PKGS = Textures

if ENABLE_VIS
  Visualization_DIRS = $(Visualization_PKGS)
else
  Visualization_DIRS = 
endif

Visualization:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) Visualization

ApplicationFramework_PKGS = StdResource XmlOcafResource

if ENABLE_CAF
  ApplicationFramework_DIRS = $(ApplicationFramework_PKGS)
else
  ApplicationFramework_DIRS = 
endif

ApplicationFramework:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) ApplicationFramework

DataExchange_PKGS = XSMessage SHMessage XSTEPResource

if ENABLE_DXE
  DataExchange_DIRS = $(DataExchange_PKGS)
else
  DataExchange_DIRS = 
endif

DataExchange:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) DataExchange

Draw_PKGS = DrawResources

if ENABLE_DRAW
  Draw_DIRS = $(Draw_PKGS)
else
  Draw_DIRS = 
endif

Draw:
	cd $(top_builddir)/adm/lin/amk && $(MAKE) $(AM_MAKEFLAGS) Draw

install-exec-local:
	$(INSTALL) -d $(prefix)/$(platform)
	if [ -e $(prefix)/bin -a ! -e $(prefix)/$(platform)/bin ]; then \
		cd $(prefix)/$(platform) && ln -s ../bin bin; \
	fi
	if [ -e $(prefix)/lib -a ! -e $(prefix)/$(platform)/lib ]; then \
		cd $(prefix)/$(platform) && ln -s ../lib lib; \
	fi
	buildd=`pwd`; cd $(top_srcdir); sourced=`pwd`; cd $(prefix); installd=`pwd`; cd $$buildd; \
	if [ "$$installd" != "$$sourced" ]; then \
		$(INSTALL) -d $(prefix)/inc; \
		cp -frL $(top_srcdir)/inc $(prefix); \
		cp -frL $$buildd/config.h $(prefix); \
		for d in  $(FoundationClasses_DIRS) $(ModelingData_DIRS) $(ModelingAlgorithms_DIRS) $(Visualization_DIRS) $(ApplicationFramework_DIRS) $(DataExchange_DIRS) $(Draw_DIRS); do \
			$(INSTALL) -d $(prefix)/src/$$d; \
			cp -frL $(top_srcdir)/src/$$d $(prefix)/src; \
		done; \
	fi
	if [ -e $(prefix)/inc/config.h ]; then \
		rm -f $(prefix)/inc/config.h; \
	fi
	cd $(prefix)/inc && ln -s ../config.h config.h
	cd $(top_srcdir) && cp *.sh $(prefix)

.PHONY: FoundationClasses ModelingData ModelingAlgorithms Visualization ApplicationFramework DataExchange Draw