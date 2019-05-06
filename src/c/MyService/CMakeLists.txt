#******************************************************************************
#   Copyright 2019 Rajive Joshi, Real-Time Innovations Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#******************************************************************************

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

message("RTIMEHOME = ${RTIMEHOME}") # >>><<<

ADD_DEFINITIONS()
LINK_DIRECTORIES()
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
PROJECT(doma)
SET(SOURCE_EXTENSION c)

SET(RTIDDSGEN ${RTIMEHOME}/rtiddsgen/scripts/rtiddsgen)
SET(RTIDDSMAG ${RTIMEHOME}/rtiddsmag/scripts/rtiddsmag)
SET_PROPERTY(GLOBAL PROPERTY RULE_MESSAGES OFF)

set(IF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../if)
set(IDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../res/types)
set(QOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../res/qos)

SET(IDL_SOURCE_C ${IDL_DIR}/MyService.idl) # >>><<<
SET(IDL_GEN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/gen) # >>><<<

# >>><<<
SET(APP_CFG_IF  ${IF_DIR}/MyService.xml) 
SET(APP_CFG_REF ${QOS_DIR}/builtin/BuiltinProfiles.xml
                ${QOS_DIR}/services/MyService_qos.xml)
SET(APP_CFG_TYPES MyService.idl)
SET(APP_GEN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/gen)
# >>><<<

SET(COMMON_C_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Databus.${SOURCE_EXTENSION} 
                     ${CMAKE_CURRENT_SOURCE_DIR}/App.${SOURCE_EXTENSION}
) 


SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${RTIME_TARGET_NAME})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${RTIME_TARGET_NAME})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/objs/${RTIME_TARGET_NAME})

IF (NOT EXISTS gen)
    file(MAKE_DIRECTORY gen)
ENDIF()

SET(RTI_LIB_PREFIX rti_me)
SET(RTI_LIB_SUFFIX)

IF (NOT (DEFINED RTI_SHARED_LIB))
    IF (${CMAKE_BUILD_TYPE} MATCHES "[Rr]elease")
        SET(RTI_LIB_SUFFIX "z")
        SET(RTI_DEBUG_BUILD FALSE)
        ADD_DEFINITIONS(-DNDEBUG)
    ELSE()
        SET(RTI_LIB_SUFFIX "zd")
        SET(RTI_DEBUG_BUILD TRUE)
    ENDIF()
ELSE()
    IF (${CMAKE_BUILD_TYPE} MATCHES "[Rr]elease")
        SET(RTI_LIB_SUFFIX "")
        SET(RTI_DEBUG_BUILD FALSE)
        ADD_DEFINITIONS(-DNDEBUG)
    ELSE()
        SET(RTI_LIB_SUFFIX "d")
        SET(RTI_DEBUG_BUILD TRUE)
    ENDIF()
ENDIF()

SET(MICRO_C_LIBS rti_me_appgen${RTI_LIB_SUFFIX}
                 rti_me_rhsm${RTI_LIB_SUFFIX} 
                 rti_me_whsm${RTI_LIB_SUFFIX} 
                 rti_me_discdpse${RTI_LIB_SUFFIX} 
                 rti_me_discdpde${RTI_LIB_SUFFIX} 
                 rti_me${RTI_LIB_SUFFIX}
)

MESSAGE("RTIME_TARGET_NAME = ${RTIME_TARGET_NAME}")
INCLUDE_DIRECTORIES(gen/ ${RTIMEHOME}/include ${RTIMEHOME}/include/rti_me)
LINK_DIRECTORIES(${RTIMEHOME}/lib/${RTIME_TARGET_NAME})

FOREACH(idl ${IDL_SOURCE_C})
    GET_FILENAME_COMPONENT(filename ${idl} NAME)
    STRING(REGEX REPLACE "\\.idl" "" basename ${filename})
    LIST(APPEND IDL_GEN_C ${IDL_GEN_ROOT}/${basename}.${SOURCE_EXTENSION}
                          ${IDL_GEN_ROOT}/${basename}Plugin.${SOURCE_EXTENSION}
                          ${IDL_GEN_ROOT}/${basename}Support.${SOURCE_EXTENSION})
                          
    LIST(APPEND IDL_GEN_H ${IDL_GEN_ROOT}/${basename}.h
                          ${IDL_GEN_ROOT}/${basename}Plugin.h  
                          ${IDL_GEN_ROOT}/${basename}Support.h)
                          
    ADD_CUSTOM_COMMAND(OUTPUT ${IDL_GEN_C} ${IDL_GEN_H} 
                       COMMAND ${RTIDDSGEN} -verbosity 1 -language C -micro 
                               -update typefiles 
                               -d ${IDL_GEN_ROOT} ${idl}
                       DEPENDS ${idl}
                       COMMENT "Regeneration type support plugin from ${idl}"
   	)                        
ENDFOREACH()
SET_SOURCE_FILES_PROPERTIES(${IDL_GEN_C} ${IDL_GEN_H} PROPERTIES GENERATED 1)  

FOREACH(xml ${APP_CFG_IF}) # >>><<<
    GET_FILENAME_COMPONENT(filename ${xml} NAME)
    STRING(REGEX REPLACE "\\.xml" "" basename ${filename})
    LIST(APPEND APP_GEN_C ${APP_GEN_ROOT}/${basename}Appgen.c)  
                          
    LIST(APPEND APP_GEN_H ${APP_GEN_ROOT}/${basename}Appgen.h)  
    LIST(JOIN APP_CFG_REF " -referencedFile " APP_GEN_XML)

    ADD_CUSTOM_COMMAND(OUTPUT ${APP_GEN_C} ${APP_GEN_H} 
                       COMMAND ${RTIDDSMAG} -verbosity 1 -language C 
                               -replace  
                               -d ${APP_GEN_ROOT} ${xml} 
                               -idlFile ${APP_CFG_TYPES} 
                               -referencedFile ${APP_GEN_XML}
                       DEPENDS ${xml} ${APP_CFG_REF}
                       COMMENT "Regeneration of application support from ${xml}"
   	)             	              
ENDFOREACH()
SET_SOURCE_FILES_PROPERTIES(${APP_GEN_C} ${APP_GEN_H} PROPERTIES GENERATED 1)    


ADD_EXECUTABLE(Publisher
               ${CMAKE_CURRENT_SOURCE_DIR}/Publisher.${SOURCE_EXTENSION}
               ${CMAKE_CURRENT_SOURCE_DIR}/Writers.${SOURCE_EXTENSION}
               ${COMMON_C_SOURCES}
                                             ${IDL_GEN_C} ${IDL_GEN_H}
                                             ${APP_GEN_C} ${APP_GEN_H})

ADD_EXECUTABLE(Subscriber 
               ${CMAKE_CURRENT_SOURCE_DIR}/Subscriber.${SOURCE_EXTENSION}
               ${CMAKE_CURRENT_SOURCE_DIR}/Readers.${SOURCE_EXTENSION}
               ${COMMON_C_SOURCES}
               ${CMAKE_CURRENT_SOURCE_DIR}/Filters.c
                                             ${IDL_GEN_C} ${IDL_GEN_H}
                                             ${APP_GEN_C} ${APP_GEN_H})

message("MICRO_C_LIBS = ${MICRO_C_LIBS}")

TARGET_LINK_LIBRARIES(Publisher  ${MICRO_C_LIBS} ${PLATFORM_LIBS})
TARGET_LINK_LIBRARIES(Subscriber ${MICRO_C_LIBS} ${PLATFORM_LIBS})