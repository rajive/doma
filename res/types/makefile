######################################################################
# makefile
#
# This makefile assumes that the build environment is already correctly
# configured. (For example, the correct version of your compiler and
# linker should be on the PATH.)
#
# Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
######################################################################

# Check NDDSHOME:
ifndef NDDSHOME
$(error Please define NDDSHOME)
endif
$(info NDDSHOME=${NDDSHOME})

TYPE_XML_FILES_TO_GENERATE:=ShapeType.xml

# Generate XML from IDL types
${TYPE_XML_FILES_TO_GENERATE}: %.xml: %.idl
	${NDDSHOME}/bin/rtiddsgen  -convertToXml -d . $< 
