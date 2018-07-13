#!/bin/bash
#*****************************************************************************
#*     (c) 2005-2018 Copyright, Real-Time Innovations, All rights reserved.  *
#*                                                                           *
#*         Permission to modify and use for internal purposes granted.       *
#* This software is provided "as is", without warranty, express or implied.  *
#*                                                                           *
#*****************************************************************************
# Compose a component from the following services:
#      final				->	MyServiceN_InterfaceX
#	   ServiceN_InterfaceX	->	MyServiceM_InterfaceY
#	   ServiceM_InterfaceY	->	root
#
# Use this script to launch the component as follows:
#     <this_script>.sh [<domain_id> [<path_to_executable_or_lua_script>]]
#
# ---------------------------------------------------------------------
# Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2018.

# ---------------------------------------------------------------------
#                   --- Service Composition ---
# ---------------------------------------------------------------------

# Project Directory
MY_HOME=..

# final: Component Parameters
NAME_Component="MyComponent"


# --- Service composition ---

# final -> ServiceN_InterfaceX
BASE_NAME_Component="MyService_Library::MyServiceN_InterfaceX"

# ServiceN_InterfaceX -> ServiceM_InterfaceY
BASE_NAME_MyServiceN_InterfaceX="MyServiceN_Library::MyService_Root"
BASE_NAME_MyServiceN_Root="MyServiceM_Library::MyServiceM_InterfaceY"

# ServiceM_InterfaceY -> root
BASE_NAME_MyServiceM_InterfaceY="MyServiceM_Library::MyServiceM_Root"
BASE_NAME_MyServiceN_Root="Root_Library::Root"


# ---------------------------------------------------------------------
#                   --- Directories ---
# ---------------------------------------------------------------------

# Locations
export MY_HOME=${MY_HOME:=..}
export TYPES_DIR=${TYPES_DIR:=${MY_HOME}/res/types}

# ---------------------------------------------------------------------
#                   --- Common ---
# ---------------------------------------------------------------------

# DDS-XML files
export NDDS_QOS_PROFILES= #empty

# QoS - Common
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/factory.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/participant.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/endpoint.xml;"

# ---------------------------------------------------------------------
#                   --- Interface Defaults ---
# ---------------------------------------------------------------------

# root
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/root.xml;"


# ServiceM
export BASE_NAME_MyServiceM_InterfaceX=${BASE_NAME_MyServiceM_InterfaceX:="MyServiceM_Library::MyService_Root"}
export BASE_NAME_MyServiceM_InterfaceY=${BASE_NAME_MyServiceM_InterfaceY:="MyServiceM_Library::MyService_Root"}
export BASE_NAME_MyServiceM_InterfaceZ=${BASE_NAME_MyServiceM_InterfaceZ:="MyServiceM_Library::MyService_Root"}
export BASE_NAME_MyServiceM_Root=${BASE_NAME_MyServiceM_Root:="Root_Library::Root"}
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/MyServiceMQos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/MyServiceM.xml;"


# ServiceN
export BASE_NAME_MyServiceN_InterfaceX=${BASE_NAME_MyServiceN_InterfaceX:="MyServiceN_Library::MyService_Root"}
export BASE_NAME_MyServiceN_InterfaceY=${BASE_NAME_MyServiceN_InterfaceY:="MyServiceN_Library::MyService_Root"}
export BASE_NAME_MyServiceN_InterfaceZ=${BASE_NAME_MyServiceN_InterfaceZ:="MyServiceN_Library::MyService_Root"}
export BASE_NAME_MyServiceN_Root=${BASE_NAME_MyServiceN_Root:="Root_Library::Root"}
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/MyServiceNQos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/MyServiceN.xml;"


# final
export BASE_NAME_Component=${BASE_NAME_Component:="Root_Library::Root"}
export NAME_Component=${NAME_Component:="MyComponent"}
export DOMAIN_ID_Component=${1:-0} # Use the first argument, $1, if specified

NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/components/MyComponentQos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/final.xml"

# ---------------------------------------------------------------------
#                   --- Executable ---
# ---------------------------------------------------------------------

# Get executable from the second argument, $2, if any:
# Default: lua script that enumerates the component (service composition) 
#          inputs & outputs
EXEC_PATH=${2:-${MY_HOME}/src/lua/Endpoints.lua}

# if executable is a lua file, run it with the rtiddsprototyper
case ${EXEC_PATH} in
*.lua) 
	EXEC="rtiddsprototyper -cfgName Component_Library::Component -luaFile ${EXEC_PATH}"
	;;
*)	EXEC=${EXEC_PATH}
	;;
esac

# ---------------------------------------------------------------------
#                   --- Run ---
# ---------------------------------------------------------------------

echo "Usage: "
echo "$0 [<domain_id> [<path_to_executable_or_lua_script>]]"
echo

echo DOMAIN_ID=${DOMAIN_ID_Component}
echo NDDS_QOS_PROFILES=${NDDS_QOS_PROFILES}
echo EXEC=${EXEC}

exec ${EXEC}
			     
# ---------------------------------------------------------------------