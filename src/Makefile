#
# OMNeT++/OMNEST Makefile for $(LIB_PREFIX)soqosmw
#
# This file was generated with the command:
#  opp_makemake --make-so -f --deep -S -KCORE4INET_PROJ=../../CoRE4INET -KINET_PROJ=../../inet -KFICO4OMNET_PROJ=../../FiCo4OMNeT -KSIGNALSANDGATEWAYS_PROJ=../../SignalsAndGateways -I. -Isoqosmw -I$$\(CORE4INET_PROJ\)/src -I$$\(CORE4INET_PROJ\)/src/core4inet/api/AS6802/tte_api -I$$\(INET_PROJ\)/src -I$$\(FICO4OMNET_PROJ\)/src -I$$\(SIGNALSANDGATEWAYS_PROJ\)/src -L$$\(CORE4INET_PROJ\)/out/$$\(CONFIGNAME\)/src -L$$\(FICO4OMNET_PROJ\)/out/$$\(CONFIGNAME\)/src -L$$\(INET_PROJ\)/out/$$\(CONFIGNAME\)/src -L$$\(SIGNALSANDGATEWAYS_PROJ\)/out/$$\(CONFIGNAME\)/src -lCoRE4INET -lFiCo4OMNeT -lINET -lSignalsAndGateways
#

# Name of target to be created (-o option)
TARGET = $(LIB_PREFIX)soqosmw$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Isoqosmw \
    -I$(CORE4INET_PROJ)/src \
    -I$(CORE4INET_PROJ)/src/core4inet/api/AS6802/tte_api \
    -I$(INET_PROJ)/src \
    -I$(FICO4OMNET_PROJ)/src \
    -I$(SIGNALSANDGATEWAYS_PROJ)/src

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = $(LDFLAG_LIBPATH)$(CORE4INET_PROJ)/out/$(CONFIGNAME)/src $(LDFLAG_LIBPATH)$(FICO4OMNET_PROJ)/out/$(CONFIGNAME)/src $(LDFLAG_LIBPATH)$(INET_PROJ)/out/$(CONFIGNAME)/src $(LDFLAG_LIBPATH)$(SIGNALSANDGATEWAYS_PROJ)/out/$(CONFIGNAME)/src  -lCoRE4INET -lFiCo4OMNeT -lINET -lSignalsAndGateways

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/soqosmw/applications/base/SOQoSMWApplicationBase.o \
    $O/soqosmw/applications/publisherapp/base/PublisherAppBase.o \
    $O/soqosmw/applications/publisherapp/gateway/GatewayPublisherApp.o \
    $O/soqosmw/applications/subscriberapp/base/SubscriberAppBase.o \
    $O/soqosmw/applications/subscriberapp/gateway/GatewaySubscriberApp.o \
    $O/soqosmw/connector/base/ConnectorBase.o \
    $O/soqosmw/connector/pubsub/reader/SubscriberConnector.o \
    $O/soqosmw/connector/pubsub/writer/PublisherConnector.o \
    $O/soqosmw/discovery/base/IServiceDiscovery.o \
    $O/soqosmw/discovery/static/StaticServiceDiscovery.o \
    $O/soqosmw/endpoints/base/EndpointBase.o \
    $O/soqosmw/endpoints/publisher/base/PublisherEndpointBase.o \
    $O/soqosmw/endpoints/publisher/realtime/avb/AVBPublisherEndpoint.o \
    $O/soqosmw/endpoints/publisher/realtime/base/RTPublisherEndpointBase.o \
    $O/soqosmw/endpoints/publisher/standard/base/STDPublisherEndpointBase.o \
    $O/soqosmw/endpoints/publisher/standard/tcp/TCPPublisherEndpoint.o \
    $O/soqosmw/endpoints/publisher/standard/udp/UDPPublisherEndpoint.o \
    $O/soqosmw/endpoints/subscriber/base/SubscriberEndpointBase.o \
    $O/soqosmw/endpoints/subscriber/realtime/avb/AVBSubscriberEndpoint.o \
    $O/soqosmw/endpoints/subscriber/realtime/base/RTSubscriberEndpointBase.o \
    $O/soqosmw/endpoints/subscriber/standard/base/STDSubscriberEndpointBase.o \
    $O/soqosmw/endpoints/subscriber/standard/tcp/TCPSubscriberEndpoint.o \
    $O/soqosmw/endpoints/subscriber/standard/udp/UDPSubscriberEndpoint.o \
    $O/soqosmw/qosmanagement/negotiation/QoSNegotiationProtocol.o \
    $O/soqosmw/qosmanagement/negotiation/broker/QoSBroker.o \
    $O/soqosmw/qospolicy/base/IQoSPolicy.o \
    $O/soqosmw/qospolicy/base/qospolicy.o \
    $O/soqosmw/servicemanager/LocalServiceManager.o \
    $O/soqosmw/test/discovery/static/StaticServiceDiscoveryTest.o \
    $O/soqosmw/utility/processing/ProcessingTimeSimulation.o \
    $O/soqosmw/messages/Envelope_m.o \
    $O/soqosmw/messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.o \
    $O/soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.o

# Message files
MSGFILES = \
    soqosmw/messages/Envelope.msg \
    soqosmw/messages/QoSNegotiationProtocol/ConnectionSpecificInformation.msg \
    soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol.msg

# SM files
SMFILES =

# Other makefile variables (-K)
CORE4INET_PROJ=../../CoRE4INET
INET_PROJ=../../inet
FICO4OMNET_PROJ=../../FiCo4OMNeT
SIGNALSANDGATEWAYS_PROJ=../../SignalsAndGateways

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)
ifneq ($(TOOLCHAIN_NAME),clangc2)
LIBS += -Wl,-rpath,$(abspath $(CORE4INET_PROJ)/out/$(CONFIGNAME)/src) -Wl,-rpath,$(abspath $(FICO4OMNET_PROJ)/out/$(CONFIGNAME)/src) -Wl,-rpath,$(abspath $(INET_PROJ)/out/$(CONFIGNAME)/src) -Wl,-rpath,$(abspath $(SIGNALSANDGATEWAYS_PROJ)/out/$(CONFIGNAME)/src)
endif

COPTS = $(CFLAGS) $(IMPORT_DEFINES)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%.o=%.d)
