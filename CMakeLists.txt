cmake_minimum_required(VERSION 2.8)

project(sts)

if (APPLE)
	message (FATAL_ERROR "Sorry, project building with CMake on Apple is not supported.")
endif ()

if (MSVC)
	message (FATAL_ERROR "Sorry, project building with Microsoft Visual Studio is not supported due to compatibility issues.")
endif ()

if (MSVC_IDE)
	set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
	unset (CMAKE_BUILD_TYPE CACHE)
else (MSVC_IDE)
	unset (CMAKE_CONFIGURATION_TYPES CACHE)
endif (MSVC_IDE)

option (INSTALL_DEVELOPER_FILES "Install include headers, libs & debug symbols (Visual Studio only)" ON)

if (INSTALL_DEVELOPER_FILES)
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		option (INSTALL_DEBUG_EXECUTABLES "Install debug versions of executables." ON)
		if (MSVC AND INSTALL_DEBUG_EXECUTABLES)
			# ToDo: add *.pdb installation code
			#option (INSTALL_DEBUG_BINARIES_PDB "Install PDB files for debug versions of binaries." OFF)
		endif (MSVC AND INSTALL_DEBUG_EXECUTABLES)
	endif (CMAKE_BUILD_TYPE MATCHES Debug)
endif (INSTALL_DEVELOPER_FILES)

# Additional options for G++ like comilers
if (${CMAKE_COMPILER_IS_GNUCXX})
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (${CMAKE_COMPILER_IS_GNUCXX})

# Ogre dependency, searched by cmake module
if (WIN32)
	# Replace backslash with slash to avoid parsing errors
	string (REPLACE "\\" "/" CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
elseif (UNIX)
	if (EXISTS "/usr/share/OGRE/cmake/modules")
		set (CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules;${CMAKE_MODULE_PATH}")
	elseif (EXISTS "/usr/local/lib/OGRE/cmake")
		set (CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	elseif (EXISTS "/usr/lib/OGRE/cmake")
		set (CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	else (EXISTS "/usr/local/lib/OGRE/cmake")
		message (SEND_ERROR "Failed to find OGRE module path.")
	endif (EXISTS "/usr/share/OGRE/cmake/modules")
endif (WIN32)

find_package (OGRE REQUIRED)

# OIS dependency
find_package (OIS REQUIRED)

if (NOT OIS_FOUND)
	message (SEND_ERROR "Failed to find OIS.")
endif ()

# Boost dependency
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set (Boost_USE_MULTITHREADED ON)
		set (Boost_USE_STATIC_LIBS ON)
		set (Boost_USE_STATIC_RUNTIME OFF)
	else (WIN32 OR APPLE)
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set (Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif (WIN32 OR APPLE)

	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set (CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()

	# Set component variables
	set (OGRE_BOOST_COMPONENTS thread date_time)
	set (EXTRA_BOOST_COMPONENTS filesystem)

	set (ALL_BOOST_COMPONENTS ${OGRE_BOOST_COMPONENTS} ${EXTRA_BOOST_COMPONENTS})

	find_package (Boost COMPONENTS ${ALL_BOOST_COMPONENTS} REQUIRED)

	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set (Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package (Boost COMPONENTS ${ALL_BOOST_COMPONENTS} REQUIRED)
	endif ()

	find_package (Boost COMPONENTS ${ALL_BOOST_COMPONENTS} REQUIRED)

	add_definitions ("-DBOOST_ALL_NO_LIB")
	if (WIN32)
		# Boost.Asio _WIN32_WINNT
		#add_definitions("-D_WIN32_WINNT=0x0501")
	endif ()
endif()

# SDL dependencies
find_package (SDL REQUIRED)

if (NOT SDL_FOUND)
	message (SEND_ERROR "Failed to find SDL.")
endif ()

find_package (SDL_mixer REQUIRED)

if (NOT SDL_MIXER_FOUND)
	message (SEND_ERROR "Failed to find SDL_Mixer.")
endif ()

# STS
add_subdirectory (sts)
