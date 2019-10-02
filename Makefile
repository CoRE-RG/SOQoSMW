#Try to detect INET if variable is not set
ifndef INET_PROJ
    ifneq ($(wildcard ../inet),)
        INET_PROJ=../../inet
    else
        $(error "Cannot find INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif
#Try to detect CoRE4INET if variable is not set
ifndef CORE4INET_PROJ
    ifneq ($(wildcard ../CoRE4INET),)
        CORE4INET_PROJ=../../CoRE4INET
    else
        $(error "Cannot find CoRE4INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif
#Try to detect FiCo4OMNeT if variable is not set
ifndef FICO4OMNET_PROJ
    ifneq ($(wildcard ../FiCo4OMNeT),)
        FICO4OMNET_PROJ=../../FiCo4OMNeT
    else
        $(error "Cannot find FiCo4OMNeT framework in the usual location. You have to set the PATH to FiCo4OMNeT in the FICO4OMNET_PROJ variable")
    endif
endif
#Try to detect INET if variable is not set
ifndef SIGNALSANDGATEWAYS_PROJ
    ifneq ($(wildcard ../SignalsAndGateways),)
        SIGNALSANDGATEWAYS_PROJ=../../SignalsAndGateways
    else
        $(error "Cannot find SignalsAndGateways framework in the usual location. You have to set the PATH to SignalsAndGateways in the SIGNALSANDGATEWAYS_PROJ variable")
    endif
endif

all: checkmakefiles
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile
	
ifeq ($(MODE), debug)
    DBG_SUFFIX=_dbg
else
    DBG_SUFFIX=
endif

MAKEMAKE_OPTIONS := -f --deep --no-deep-includes -O out -KINET_PROJ=$(INET_PROJ) -KCORE4INET_PROJ=$(CORE4INET_PROJ) -KFICO4OMNET_PROJ=$(FICO4OMNET_PROJ) -KSIGNALSANDGATEWAYS_PROJ=$(SIGNALSANDGATEWAYS_PROJ) -I. -I$(INET_PROJ)/src/ -I$(CORE4INET_PROJ)/src/ -I$(FICO4OMNET_PROJ)/src/ -L$(INET_PROJ)/src -L$(CORE4INET_PROJ)/src -L$(FICO4OMNET_PROJ)/src -L$(SIGNALSANDGATEWAYS_PROJ)/src -lCoRE4INET$(DBG_SUFFIX) -lINET$(DBG_SUFFIX) -lSignalsAndGateways$(DBG_SUFFIX) -lFiCo4OMNeT$(DBG_SUFFIX)

makefiles: makefiles-so

makefiles-so:
	@cd src && opp_makemake --make-so $(MAKEMAKE_OPTIONS)

makefiles-lib:
	@cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS)

makefiles-exe:
	@cd src && opp_makemake $(MAKEMAKE_OPTIONS)

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
	

doxy:
	doxygen doxy.cfg
	
