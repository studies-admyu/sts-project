cmake_minimum_required(VERSION 2.8)

project(sts)

set (sts_SRC_ROOT_DIR src)

set (sts_HEADERS
	"${sts_SRC_ROOT_DIR}/sts.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_attachable.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_renderable.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_model3d.hpp"
)
set (sts_SOURCES
	"${sts_SRC_ROOT_DIR}/sts_main.cpp"
	"${sts_SRC_ROOT_DIR}/sts_resources.cpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_model3d.cpp"
)

include_directories(
	${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Overlay_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

add_executable(sts ${sts_HEADERS} ${sts_SOURCES})

if (WIN32)
#	ToDo: solve linking problem here
#	set_target_properties (sts PROPERTIES WIN32_EXECUTABLE TRUE)
endif (WIN32)

target_link_libraries(sts ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES})

# ToDo: add post build commands for MSVC_IDE

# Folder with binaries. Currently on Windows we install just to INSTALL_PREFIX, on Linux to bin subfoler.
set (sts_BIN_DIR ${CMAKE_INSTALL_PREFIX})
if (UNIX)
	set (sts_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif (UNIX)

# do we need to built a binary?
set (sts_IS_BINARY_BUILT False)
if ((CMAKE_BUILD_TYPE MATCHES "Release") OR (CMAKE_BUILD_TYPE MATCHES "Debug" AND INSTALL_DEBUG_BINARIES))
	set (sts_IS_BINARY_BUILT TRUE)
endif ((CMAKE_BUILD_TYPE MATCHES "Release") OR (CMAKE_BUILD_TYPE MATCHES "Debug" AND INSTALL_DEBUG_BINARIES))

# install the binary
if (sts_IS_BINARY_BUILT)
	# install the binary itself
    install (TARGETS sts DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Release)
	install (TARGETS sts DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Debug)

	# install ogre.cfg, necessary if binary is built
	if (NOT EXISTS ${PROJECT_SOURCE_DIR}/config/ogre.cfg)
		message(SEND_ERROR "Failed to find config/ogre.cfg file")
	endif (NOT EXISTS ${PROJECT_SOURCE_DIR}/config/ogre.cfg)
	install (FILES config/ogre.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Release)
	install (FILES config/ogre.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Debug)

	# install plugins.cfg, optional
	if (EXISTS ${PROJECT_SOURCE_DIR}/config/plugins.cfg)
		install (FILES config/plugins.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Release)
		install (FILES config/plugins.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Debug)
	endif (EXISTS ${PROJECT_SOURCE_DIR}/config/plugins.cfg)

	# install data such as models
	install (DIRECTORY data/ DESTINATION data)

	if (WIN32)
		install (FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
				${OGRE_PLUGIN_DIR_REL}/Plugin_CgProgramManager.dll
				${OGRE_PLUGIN_DIR_REL}/Plugin_OctreeSceneManager.dll
				${OGRE_PLUGIN_DIR_REL}/Plugin_ParticleFX.dll
				${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
				${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
				${OGRE_PLUGIN_DIR_REL}/OIS.dll
				DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Release
				)

		install (FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
				${OGRE_PLUGIN_DIR_DBG}/Plugin_CgProgramManager_d.dll
				${OGRE_PLUGIN_DIR_DBG}/Plugin_OctreeSceneManager_d.dll
				${OGRE_PLUGIN_DIR_DBG}/Plugin_ParticleFX_d.dll
				${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
				${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
				${OGRE_PLUGIN_DIR_DBG}/OIS_d.dll
				DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Debug
				)
	endif (WIN32)
endif (sts_IS_BINARY_BUILT)

