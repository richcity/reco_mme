cmake_minimum_required(VERSION 2.6)


PROJECT(reco_mme)

# -DUNIX -DLINUX -DLITTLE_ENDIAN -DENABLE_LOG -DMM_MON_ENABLE -DMM_DEB_ENABLE --> for libut


SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -DUNIX -DLINUX -DLITTLE_ENDIAN -DENABLE_LOG")

FILE(GLOB fwk_srcs ${reco_mme_SOURCE_DIR}/fwk/*.cpp)

FILE(GLOB sys_srcs ${reco_mme_SOURCE_DIR}/sys/*.cpp)

FILE(GLOB s1_srcs ${reco_mme_SOURCE_DIR}/s1/*.cpp)

FILE(GLOB nas_srcs ${reco_mme_SOURCE_DIR}/nas/*.cpp)

#set_source_files_properties(... COMPILE_FLAGS ... ) 


INCLUDE_DIRECTORIES (${reco_mme_SOURCE_DIR}/pblc
                     ${reco_mme_SOURCE_DIR}/inc
                     ${reco_mme_SOURCE_DIR}/fwk )

LINK_DIRECTORIES (${reco_mme_SOURCE_DIR}/lib)

#ADD_LIBRARY(lfds SHARED ${lfds_srcs})

#add_library( liblfds611.a SHARED IMPORTED )
#set_target_properties( liblfds611.a PROPERTIES IMPORTED_LOCATION (${reco_mme_SOURCE_DIR}/lib) )



ADD_EXECUTABLE(reco_mme ${sys_srcs} 
                   ${fwk_srcs}
                   ${s1_srcs}
                   ${nas_srcs} )

#find_package(netfilter_queue)
#include_directories(${libnetfilter_queue_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(reco_mme liblfds611.a m pthread rt)

#pthread is for libut
