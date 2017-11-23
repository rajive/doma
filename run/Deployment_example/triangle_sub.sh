#!/bin/bash
# Compose a component from the following services:
#      Triangle -> Sub
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

# Service: Triangle
export BASE_NAME_Triangle_Root="Root_Library::Root"
export BASE_NAME_Triangle_Pub="Triangle_Library::Triangle_Root"
export BASE_NAME_Triangle_Sub="Triangle_Library::Triangle_Root"

# Component
export BASE_NAME_Component="Triangle_Library::Triangle_Sub"
export NAME_Component="triangle_sub"
export DOMAIN_ID_Component=0

# QoS Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/services/Triangle.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/res/qos/components/Deployment_example.xml;"

# XML App Configurations
NDDS_QOS_PROFILES+="${MY_HOME}/if/Triangle.xml;"
NDDS_QOS_PROFILES+="${MY_HOME}/if/component/final.xml"

# ---------------------------------------------------------------------
echo NDDS_QOS_PROFILES=${NDDS_QOS_PROFILES}

# -- Running Component Implementation Variants --

rtiddsprototyper -cfgName Component_Library::Component -luaFile ${MY_HOME}/src/lua/Endpoints.lua

#rtiddsprototyper -participantName $NAME_Component 
#                 -cfgName Component_Library::Component
#			     -luaFile ${MY_HOME}/src/lua/shapes/ShapesSubscriber.lua 
#			     -luaOnData false

# ${MY_HOME}/src/c++11/shapes/objs/x64Darwin16clang8.0/Component_triangle_sub