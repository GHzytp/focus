############################################################################
# A 2dx CMakeLists.txt                                                     #
#                                                                          #
# Author:                                                                  #
# Nikhil Biyani                                                            #
############################################################################


cmake_minimum_required(VERSION 2.8.11)

# Load Self defined CMake Modules ---------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/cmake ${CMAKE_MODULE_PATH})
#------------------------------------------------------------------------------


# Configuration ---------------------------------------------------------------
set(EXETITLE 2dx_gui)           # Application name
set(CMAKE_DEBUG_POSTFIX -dbg)   # Debug options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g") #C++ options
#------------------------------------------------------------------------------


# C++ Compiler ----------------------------------------------------------------
if(CMAKE_CXX_COMPILER STREQUAL "/opt/intel/composer_xe_2013.2.146/bin/intel64/icpc")
	#set(CMAKE_CXX_FLAGS "-openmp -O3 -xhost -no-prec-div -opt-prefetch -unroll-aggressive -m64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp -O3 -xhost")
	#set(CMAKE_CXX_FLAGS "-openmp -O3 -xhost -ipo -fast -xavx -no-prec-div -unroll")
	add_definitions( -DUSE_CILK )
else(CMAKE_CXX_COMPILER STREQUAL "/opt/intel/composer_xe_2013.2.146/bin/intel64/icpc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -funroll-loops -W -Waddress -Wchar-subscripts -Wcomment -Wformat -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized  -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wvolatile-register-var -Wno-long-long -Wextra")
endif()
#------------------------------------------------------------------------------


# Libraries to use ------------------------------------------------------------

# -- QT5 --
FIND_PACKAGE(Qt5 COMPONENTS Widgets WebKitWidgets Network Script OpenGL Xml REQUIRED)

IF(Qt5_FOUND)
    MESSAGE(STATUS "@EXETITLE@: Found QT5 Widgets (Version: ${Qt5Widgets_VERSION_STRING})")
    MESSAGE(STATUS "@EXETITLE@: Found QT5 WebKitWidgets (Version: ${Qt5WebKitWidgets_VERSION_STRING})")
    MESSAGE(STATUS "@EXETITLE@: Found QT5 Network (Version: ${Qt5Network_VERSION_STRING})")
    MESSAGE(STATUS "@EXETITLE@: Found QT5 Script (Version: ${Qt5Script_VERSION_STRING})")
    MESSAGE(STATUS "@EXETITLE@: Found QT5 OpenGL (Version: ${Qt5OpenGL_VERSION_STRING})")
    MESSAGE(STATUS "@EXETITLE@: Found QT5 Xml (Version: ${Qt5Xml_VERSION_STRING})")
    INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5WebKitWidgets_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5Network_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5Script_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5OpenGL_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5Xml_INCLUDE_DIRS})
    ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
    ADD_DEFINITIONS(${Qt5WebKitWidgets_DEFINITIONS})
    ADD_DEFINITIONS(${Qt5Network_DEFINITIONS})
    ADD_DEFINITIONS(${Qt5Script_DEFINITIONS})
    ADD_DEFINITIONS(${Qt5OepnGL_DEFINITIONS})
    ADD_DEFINITIONS(${Qt5Xml_DEFINITIONS})
ELSE()
    MESSAGE(STATUS "@EXETITLE@: QT5 not Found!")
ENDIF()

SET(2DX_LIBRARIES ${2DX_LIBRARIES} Qt5::Widgets Qt5::WebKitWidgets Qt5::Network Qt5::Script Qt5::OpenGL Qt5::Xml)

find_package(OpenGL)
if(OPENGL_FOUND)
        message(STATUS "Found OpenGL at ${OPENGL_LIBRARIES}")
        INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
        SET(2DX_LIBRARIES ${2DX_LIBRARIES} ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)
#------------------------------------------------------------------------------


# Header files ----------------------------------------------------------------
if(NOT DEFINED 2DX_INCLUDE_DIR)
        set(2DX_INCLUDE_DIR ../include CACHE INTERNAL "the 2dx include dir")
        message(STATUS "2DX_INCLUDE_DIR is not set. Setting it to: ${2DX_INCLUDE_DIR}" )
endif(NOT DEFINED 2DX_INCLUDE_DIR)
include_directories(${2DX_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
if(APPLE)
	include_directories(/opt/local/include)
endif(APPLE)
#------------------------------------------------------------------------------



# Source files ----------------------------------------------------------------
file(GLOB_RECURSE 2DX_SRC *.cpp)
#------------------------------------------------------------------------------

# MOC Object creation ---------------------------------------------------------
# these are all the headers containing Q_OBJECT
# TODO: glob these files with a cmake module
set(MOC_HDRS
        main_window.hpp
        conf/user_preferences.hpp
        dialogs/parameters.hpp
        dialogs/preferences.hpp
        windows/library_window.hpp
        windows/merge_window.hpp
        windows/process_window.hpp
        widgets/browser_widget.hpp
        widgets/combo_input_widget.hpp
        widgets/edit_set_widget.hpp
        widgets/graphical_button.hpp
        widgets/library_widget.hpp
        widgets/parameter_input.hpp
        widgets/parameter_section.hpp
        widgets/parameters_widget.hpp
        widgets/yesno_widget.hpp
        wizards/import_execute_page.hpp
        wizards/import_images_wizard.hpp
        wizards/import_options_page.hpp
        wizards/label_wizard_page.hpp
   )

# Create the Sources from the MOC headers
QT5_WRAP_CPP(MOC_SRCS ${MOC_HDRS})

#------------------------------------------------------------------------------


# CREATING EXECUTABLES --------------------------------------------------------
message(STATUS "Creating: ${EXETITLE}")

IF( APPLE )
    # Define some settings for the Bundle
    set(MACOSX_BUNDLE_INFO_STRING "www.2dx.org")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.cina.2dx.${EXETITLE}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${EXETITLE} Version ${2dx_VERSION_MAJOR}.${2dx_VERSION_MINOR}.${2dx_VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_NAME "${EXETITLE}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${2dx_VERSION_MAJOR}.${2dx_VERSION_MINOR}.${2dx_VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${2dx_VERSION_MAJOR}.${2dx_VERSION_MINOR}.${2dx_VERSION_PATCH}")
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright C-CINA, 2016. All Rights Reserved.")
    set(MACOSX_BUNDLE_ICON_FILE  icon.icns )
  
    # create a bundle with an icon too!
    ADD_EXECUTABLE(${EXETITLE} MACOSX_BUNDLE ${2DX_SRC} ${MOC_SRCS})
    
    # Allows for bundle re-creation just by running "make". Also installs bundle icon
    add_custom_command(TARGET ${EXETITLE} POST_BUILD
                        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/${EXETITLE}.app/Contents/Resources
                        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/${EXETITLE}.app/Contents/MacOS
                        COMMAND cp ARGS ${CMAKE_CURRENT_SOURCE_DIR}/resource/${MACOSX_BUNDLE_ICON_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/${EXETITLE}.app/Contents/Resources/${MACOSX_BUNDLE_ICON_FILE}
                      )
ELSE()
    add_executable(${EXETITLE} ${2DX_SRC} ${MOC_SRCS})
ENDIF()

qt5_use_modules(${EXETITLE} Widgets WebKitWidgets Network Script OpenGL Xml)

include_directories(${CMAKE_BINARY_DIR}/include)
target_link_libraries(${EXETITLE} ${2DX_LIBRARIES})
#------------------------------------------------------------------------------
 

# INSTALLATION ----------------------------------------------------------------
SET(plugin_dest_dir ${EXETITLE}/plugins)
SET(qtconf_dest_dir ${EXETITLE}/resources)
SET(APPS "\${CMAKE_INSTALL_PREFIX}/${EXETITLE}/${EXETITLE}")

IF(APPLE)
    SET(plugin_dest_dir ${EXETITLE}/${EXETITLE}.app/Contents/PlugIns)
    SET(qtconf_dest_dir ${EXETITLE}/${EXETITLE}.app/Contents/Resources)
    SET(APPS "\${CMAKE_INSTALL_PREFIX}/${EXETITLE}/${EXETITLE}.app/Contents/MacOS/${EXETITLE}")
ENDIF()

install(TARGETS ${EXETITLE} DESTINATION ${EXETITLE})

# Copy the icons
file(GLOB ICONS "resource/icons/*.png")
install(FILES ${ICONS} DESTINATION "Resource/icons")

# Copy config files
file(GLOB CONFIG "resource/config/*")
install(FILES ${CONFIG} DESTINATION "Resource/config")


# Install needed Qt plugins by copying directories from the qt installation
# One can cull what gets copied by using 'REGEX "..." EXCLUDE'
INSTALL(DIRECTORY "${Qt5_PLUGINS_DIR}/imageformats" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)
IF(APPLE)
	#for  cocoa qt in Mac OS X
	INSTALL(DIRECTORY "${Qt5_PLUGINS_DIR}/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)
ENDIF(APPLE)

# install a qt.conf file
# this inserts some cmake code into the install script to write the file
INSTALL(CODE "file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"[Paths]\nPlugins = PlugIns\")" 
        COMPONENT Runtime)

# Use BundleUtilities to get all other dependencies for the application to work.
# It takes a bundle or executable along with possible plugins and inspects it
# for dependencies.  If they are not system dependencies, they are copied.

# directories to look for dependencies
SET(DIRS ${Qt5_LIB_DIR})

file(GLOB Qt5Libs ${DIRS}/libQt5Gui*)
install(FILES ${Qt5Libs} DESTINATION lib)

# Now the work of copying dependencies into the bundle/package
# The quotes are escaped and variables to use at install time have their $ escaped
# An alternative is the do a configure_file() on a script and use install(SCRIPT  ...).
# Note that the image plugins depend on QtSvg and QtXml, and it got those copied
# over.
if(APPLE_BUNDLE)
	INSTALL(CODE "
	    file(GLOB_RECURSE QTPLUGINS
		       \"${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
	    include(InstallRequiredSystemLibraries)    
	    include(BundleUtilities)
	    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"\${DIRS}\" \"\")
	    verify_app(\"${APPS}\")" 
            COMPONENT Runtime)
endif(APPLE_BUNDLE)

# To Create a package, one can run "cpack -G DragNDrop CPackConfig.cmake" on Mac OS X
# where CPackConfig.cmake is created by including CPack
# And then there's ways to customize this as well
#set(CPACK_BINARY_DRAGNDROP ON)
#include(CPack)
#------------------------------------------------------------------------------
