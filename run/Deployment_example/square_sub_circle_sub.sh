#!/bin/bash
#*****************************************************************************
#*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  *
#*                                                                           *
#*         Permission to modify and use for internal purposes granted.       *
#* This software is provided "as is", without warranty, express or implied.  *
#*                                                                           *
#*****************************************************************************
# Compose a component from the following services:
#      Square 	->  Sub
#	   Circle   ->  Sub
# ---------------------------------------------------------------------
# Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.

# ---------------------------------------------------------------------
# Service Composition into a Component

# Component
export NAME_Component="square_sub_circle_sub"
export DOMAIN_ID_Component=0
export BASE_NAME_Component="Circle_Library::Circle_Sub"

# Service: Square -> Sub
export BASE_NAME_Square_Root="Root_Library::Root"
export BASE_NAME_Square_Pub="Square_Library::Square_Root"
export BASE_NAME_Square_Sub="Square_Library::Square_Root"

# Service: Circle -> Sub
export BASE_NAME_Circle_Root="Square_Library::Square_Sub"
export BASE_NAME_Circle_Pub="Circle_Library::Circle_Root"
export BASE_NAME_Circle_Sub="Circle_Library::Circle_Root"

# ---------------------------------------------------------------------
export MY_HOME=../..
export TYPES_DIR=${MY_HOME}/res/types
# ---------------------------------------------------------------------
# NDDS_QOS_PROFILES

export NDDS_QOS_PROFILES= #empty

# Component - XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/root.xml;"

# Common - QoS Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/factory.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/participant.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/common/endpoint.xml;"

# Service - QoS Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/Square.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/Circle.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/components/Deployment_example.xml;"

# Service - XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/Square.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/Circle.xml;"

# Component - XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/final.xml"
# ---------------------------------------------------------------------
echo NDDS_QOS_PROFILES=${NDDS_QOS_PROFILES}

# -- Running Component Implementation Variants --

rtiddsprototyper -cfgName Component_Library::Component -luaFile ${MY_HOME}/src/lua/Endpoints.lua

#rtiddsprototyper -participantName $NAME_Component 
#                 -cfgName Component_Library::Component
#			     -luaFile ${MY_HOME}/src/lua/shapes/ShapesPublisher.lua 
#			     -luaOnData false

# ${MY_HOME}/src/c++11/shapes/objs/x64Darwin16clang8.0/Component_square_sub_circle_sub