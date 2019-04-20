#!/bin/bash
#*****************************************************************************
#*     (c) 2005-2018 Copyright, Real-Time Innovations, All rights reserved.  *
#*                                                                           *
#*         Permission to modify and use for internal purposes granted.       *
#* This software is provided "as is", without warranty, express or implied.  *
#*                                                                           *
#*****************************************************************************
# Compose a component from the following services:
#      final                ->  Square_Sub
#      Square_Sub           ->  Square_Pub
#      Square_Pub           ->  root
#
# Use this script to launch the component as follows:
#
#  	<this>.sh [<domain_id> [<path_to_executable_or_lua_script>] [project_dir]]
#
# ---------------------------------------------------------------------
# Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2018.

# ---------------------------------------------------------------------
#                   --- Service Composition ---
# ---------------------------------------------------------------------

# final: Component Parameters
NAME_Component="square_pub_sub"


# --- Service composition ---

# final -> Square_Sub
BASE_NAME_Component="SquareIfLib::Square_Sub"

# Square_Sub -> Square_Pub
BASE_NAME_Square_Sub="SquareIfLib::Square_Pub"

# Square_Pub -> root
BASE_NAME_Square_Pub="SquareIfLib::Square_Root"
BASE_NAME_Square_Root="Root_Library::Root"

# ---------------------------------------------------------------------
#                   --- Directories ---
# ---------------------------------------------------------------------

# Project Directory
# Use the third argument, $3, if specified
# Default: one level up (..) from the location of this script
MY_HOME=${3:-$(cd $(dirname "$0")/..; pwd -P)}

# Locations
export TYPES_DIR=${TYPES_DIR:=${MY_HOME}/res/types}

# ---------------------------------------------------------------------
#                   --- Common ---
# ---------------------------------------------------------------------

# DDS-XML files
export NDDS_QOS_PROFILES= #empty

# QoS - Common
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/factory_qos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/participant_qos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/endpoint_qos.xml;"

# ---------------------------------------------------------------------
#                   --- Interface Defaults ---
# ---------------------------------------------------------------------

# root
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/root.xml;"


# Square
export BASE_NAME_Square_Pub=${BASE_NAME_Square_Pub:="SquareIfLib::Square_Root"}
export BASE_NAME_Square_Sub=${BASE_NAME_Square_Sub:="SquareIfLib::Square_Root"}
export BASE_NAME_Square_Root=${BASE_NAME_Square_Root:="Root_Library::Root"}
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/Square_qos.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/Square.xml;"


# final
export BASE_NAME_Component=${BASE_NAME_Component:="Root_Library::Root"}
export NAME_Component=${NAME_Component:="MyComponent"}
export DOMAIN_ID_Component=${1:-0} # Use the first argument, $1, if specified
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/components/deployment_qos.xml;"
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
echo "$0 [<domain_id> [<path_to_executable_or_lua_script>] [project_dir]]"
echo

echo DOMAIN_ID=${DOMAIN_ID_Component}
echo MY_HOME=${MY_HOME}
echo NDDS_QOS_PROFILES=${NDDS_QOS_PROFILES}
echo EXEC=${EXEC}

exec ${EXEC}
			     
# ---------------------------------------------------------------------
