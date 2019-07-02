###############################################################################
################################### GEANT4 ####################################
###############################################################################

# check if GEANT4 is installed
ifeq ($(shell geant4-config && echo go),go)
ADDITIONAL_INCLUDES += $(shell geant4-config --cflags)
#ADDITIONAL_CPPFLAGS += -DGSL_ENABLED
ADDITIONAL_LIBS += $(shell geant4-config --libs)
endif
