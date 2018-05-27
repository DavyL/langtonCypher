### CMake file for langton cypher
###
###
###	CMake from Sébastien Druon
###	
###	---Project started in May 2018---
###
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (langtonCypher)
set (memoire_VERSION_MAJOR 0)
set (memoire_VERSION_MINOR 1)

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )

set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )


# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()


### Search for Lib/Headers

#find_package(ICU COMPONENTS i18n io REQUIRED)
#find_package(CURL REQUIRED)
#find_package(LibXml2 REQUIRED)

### Config File


configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		 "${PROJECT_SOURCE_DIR}/src/config.h" )


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
	             "${CMAKE_CURRENT_BINARY_DIR}"
		     #"${ICU_INCLUDE_DIRS}" 
		     #"${LIBXML2_INCLUDE_DIR}" 
		     #"${CURL_INCLUDE_DIRS}" 
		     )

# link_directories( "${VISION_LIBRARY_DIR}" )


### Main Target

file( GLOB src "src/*.c"  )
file( GLOB hdr "src/*.h"  "include/*.h" )

add_executable( "langtonCypher" ${src} ${hdr} ) 

target_link_libraries( "langtonCypher" m	# "${ICU_LIBRARIES}"
				# "${CURL_LIBRARIES}"
				# "${LIBXML2_LIBRARIES}"
			       	)

install( TARGETS "langtonCypher"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

### Test target

##file( GLOB test_src "src/test/*.c"  )
##file( GLOB test_hdr "src/test/*.h"  "include/*.h" )

##add_executable( "test" ${test_src} ${test_hdr} ) 

##target_link_libraries( "test" "${ICU_LIBRARIES}"
##			      "${CURL_LIBRARIES}"
##			      "${LIBXML2_LIBRARIES}" )

##install( TARGETS "test"
##	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
##	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
##            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )


