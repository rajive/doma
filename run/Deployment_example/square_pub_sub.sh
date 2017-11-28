#!/bin/bash
#*****************************************************************************
#*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  *
#*                                                                           *
#*         Permission to modify and use for internal purposes granted.       *
#* This software is provided "as is", without warranty, express or implied.  *
#*                                                                           *
#*****************************************************************************
# Compose a component from the following services:
#      Square -> Pub
#      Square -> Sub
# ---------------------------------------------------------------------
# Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.

export MY_HOME=../..
export TYPES_DIR=${MY_HOME}/res/types
# ---------------------------------------------------------------------
# Common Framework

export NDDS_QOS_PROFILES= #empty

# Common - QoS Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/factory.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/participant.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/endpoint.xml;"

# Common - XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/root.xml;"

# ---------------------------------------------------------------------
# Service Composition into a Component

# Service: Square
export BASE_NAME_Square_Root="Root_Library::Root"
export BASE_NAME_Square_Pub="Square_Library::Square_Root"
export BASE_NAME_Square_Sub="Square_Library::Square_Pub"

# Component
export BASE_NAME_Component="Square_Library::Square_Sub"
export NAME_Component="square_pub_sub"
export DOMAIN_ID_Component=0

# QoS Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/Square.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/components/Deployment_example.xml;"

# XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/Square.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/final.xml"

# ---------------------------------------------------------------------
echo NDDS_QOS_PROFILES=${NDDS_QOS_PROFILES}

# -- Running Component Implementation Variants --

rtiddsprototyper -cfgName Component_Library::Component -luaFile ${MY_HOME}/src/lua/Endpoints.lua

#rtiddsprototyper -participantName $NAME_Component 
#                 -cfgName Component_Library::Component
#			     -luaFile ${MY_HOME}/src/lua/shapes/ShapesPublisher.lua 
#			     -luaOnData false

#rtiddsprototyper -participantName $NAME_Component 
#                 -cfgName Component_Library::Component
#			     -luaFile ${MY_HOME}/src/lua/shapes/ShapesSubscriber.lua 
#			     -luaOnData false

# ${MY_HOME}/src/c++11/shapes/objs/x64Darwin16clang8.0/Component_square_pubsub
# ${MY_HOME}/src/c++11/shapes/objs/x64Darwin16clang8.0/Component_square_pub
# ${MY_HOME}/src/c++11/shapes/objs/x64Darwin16clang8.0/Component_square_sub
