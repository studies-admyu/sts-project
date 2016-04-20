cmake_minimum_required(VERSION 2.8)

project(sts)

set (sts_SRC_ROOT_DIR src)

set (sts_HEADERS "${sts_SRC_ROOT_DIR}/sts.hpp")
set (sts_SOURCES
	"${sts_SRC_ROOT_DIR}/sts_main.cpp"
	"${sts_SRC_ROOT_DIR}/sts_resources.cpp"
)
 
include_directories(
	${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Overlay_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

if (WIN32)
	add_executable(sts ${sts_HEADERS} ${sts_SOURCES})
#	ToDo: solve linking problem here
#	set_target_properties (sts PROPERTIES WIN32_EXECUTABLE TRUE)
endif (WIN32)

target_link_libraries(sts ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
 
# ToDo: add post build commands for MSVC_IDE

if (WIN32)
	install (TARGETS sts RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Release)
	# ToDo: do something with that
	install (FILES config/plugins.cfg config/ogre.cfg DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Release)
	
	install (FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/Plugin_CgProgramManager.dll
		${OGRE_PLUGIN_DIR_REL}/Plugin_OctreeSceneManager.dll
		${OGRE_PLUGIN_DIR_REL}/Plugin_ParticleFX.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/OIS.dll
		DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Release
	)
	
	if (INSTALL_DEBUG_BINARIES)
		install (TARGETS sts RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Debug)
		# ToDo: do something with that
		install (FILES config/debug/plugins.cfg config/ogre.cfg DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Debug)
		
		install (FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
			${OGRE_PLUGIN_DIR_DBG}/Plugin_CgProgramManager_d.dll
			${OGRE_PLUGIN_DIR_DBG}/Plugin_OctreeSceneManager_d.dll
			${OGRE_PLUGIN_DIR_DBG}/Plugin_ParticleFX_d.dll
			${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
			${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
			${OGRE_PLUGIN_DIR_DBG}/OIS_d.dll
			DESTINATION ${CMAKE_INSTALL_PREFIX} CONFIGURATIONS Debug
		)
	endif (INSTALL_DEBUG_BINARIES)
	
	install (DIRECTORY data/ DESTINATION data)
endif (WIN32)

if (UNIX)
	install (TARGETS sts RUNTIME DESTINATION bin CONFIGURATIONS Release)
	# ToDo: do something with that
	install (FILES config/plugins.cfg config/ogre.cfg DESTINATION bin CONFIGURATIONS Release)
	
	if (INSTALL_DEBUG_BINARIES)
		install (TARGETS sts RUNTIME DESTINATION bin CONFIGURATIONS Debug)
		# ToDo: do something with that
		install (FILES config/plugins.cfg config/ogre.cfg DESTINATION bin CONFIGURATIONS Debug)
	endif (INSTALL_DEBUG_BINARIES)

	install (DIRECTORY data/ DESTINATION data)
endif (UNIX)
