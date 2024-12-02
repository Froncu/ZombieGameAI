cmake_minimum_required(VERSION 3.29)
project(ZombieGameAI)

set(PLUGIN_NAME "GPP_Plugin")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
   set(PLUGIN_NAME ${PLUGIN_NAME}_d)
endif()

add_library(${PLUGIN_NAME} SHARED
   project/SurvivalAgentPlugin.cpp)

set_target_properties(${PLUGIN_NAME} PROPERTIES
   CXX_STANDARD 20
   CXX_STANDARD_REQUIRED ON)

target_precompile_headers(${PLUGIN_NAME} PRIVATE
   project/stdafx.h)

target_include_directories(${PLUGIN_NAME} PRIVATE
   source
   inc)

set(PLUGIN_BASE_NAME "GPP_PluginBase")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
   set(PLUGIN_BASE_NAME ${PLUGIN_BASE_NAME}_d)
endif()

target_link_libraries(${PLUGIN_NAME} PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PLUGIN_BASE_NAME}.lib
   $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/lib/vld.lib>)