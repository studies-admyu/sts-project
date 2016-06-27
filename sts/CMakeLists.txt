cmake_minimum_required(VERSION 2.8)

project(sts)

set (sts_SRC_ROOT_DIR src)

set (sts_HEADERS
	"${sts_SRC_ROOT_DIR}/sts_cross_platform.hpp"
	"${sts_SRC_ROOT_DIR}/sts_resources.hpp"
	"${sts_SRC_ROOT_DIR}/sts_game_root.hpp"
	"${sts_SRC_ROOT_DIR}/game_data.hpp"
	"${sts_SRC_ROOT_DIR}/game_object.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/sts_unit.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/sts_unit_type.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/motion/sts_motion_behavior.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/motion/sts_motion_state.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_sm_permanent_state.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_sm_state.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_sm_transition.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_unit_state_sequence.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_firing_behavior.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_firing_state.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_bullet.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_bullet_style.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_firing_style.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_weapon.hpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_weapon_state.hpp"
	"${sts_SRC_ROOT_DIR}/input/sts_key.hpp"
	"${sts_SRC_ROOT_DIR}/ois/MyFrameListener.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_attachable.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_renderable.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_model3d.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_model3d_attachable.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_sprite2d.hpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_sprite2d_attachable.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_layer.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_layered_object.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_object_group.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_scene_manager.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_scene_object.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_shared_object.hpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_shared_object_group.hpp"
	"${sts_SRC_ROOT_DIR}/sound/SoundManager.hpp"
)

set (sts_SOURCES
	"${sts_SRC_ROOT_DIR}/sts_main.cpp"
	"${sts_SRC_ROOT_DIR}/sts_resources.cpp"
	"${sts_SRC_ROOT_DIR}/sts_game_root.cpp"
	"${sts_SRC_ROOT_DIR}/game_data.cpp"
	"${sts_SRC_ROOT_DIR}/game_object.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/sts_unit.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/sts_unit_type.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/motion/sts_motion_behavior.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_sm_permanent_state.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_sm_state.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/statemachine/sts_unit_state_sequence.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_firing_behavior.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_bullet.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_bullet_style.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_firing_style.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_weapon.cpp"
	"${sts_SRC_ROOT_DIR}/gameplay/weaponry/sts_weapon_state.cpp"
	"${sts_SRC_ROOT_DIR}/input/sts_key.cpp"
	"${sts_SRC_ROOT_DIR}/ois/MyFrameListener.cpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_renderable.cpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_model3d.cpp"
	"${sts_SRC_ROOT_DIR}/rendering/sts_sprite2d.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_layer.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_layered_object.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_scene_manager.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_scene_object.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_shared_object.cpp"
	"${sts_SRC_ROOT_DIR}/scene/sts_shared_object_group.cpp"
	"${sts_SRC_ROOT_DIR}/sound/SoundManager.cpp"
)

include_directories(
	${Boost_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OIS_INCLUDE_DIRS}
	${SDL_INCLUDE_DIR}
	${sts_SRC_ROOT_DIR}
)

# Do we need to built a binary?
set (sts_BUILD_EXECUTABLE ON)
if (CMAKE_BUILD_TYPE MATCHES "Debug" AND NOT INSTALL_DEBUG_EXECUTABLES)
	set (sts_BUILD_EXECUTABLE OFF)
endif ()

if (sts_BUILD_EXECUTABLE)
	add_executable(sts ${sts_HEADERS} ${sts_SOURCES})

	target_link_libraries(sts ${Boost_LIBRARIES} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${SDL_LIBRARY} ${SDL_MIXER_LIBRARIES})

	if (WIN32)
	#	ToDo: solve linking problem here
	#	set_target_properties (sts PROPERTIES WIN32_EXECUTABLE TRUE)
	endif ()

	# ToDo: add post build commands for MSVC_IDE

	# Folder with binaries. Currently on Windows we install just to INSTALL_PREFIX, on Linux to bin subfoler.
	if (WIN32)
		set (sts_BIN_DIR ${CMAKE_INSTALL_PREFIX})
	else (WIN32)
		# Same for unix and apple systems for now
		set (sts_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
	endif (WIN32)

	# Install the executable itself
	install (TARGETS sts DESTINATION ${sts_BIN_DIR})

	# Install ogre.cfg, necessary if binary is built
	if (NOT EXISTS ${PROJECT_SOURCE_DIR}/config/ogre.cfg)
		message(SEND_ERROR "Failed to find config/ogre.cfg file. Please create one.")
	endif ()
	install (FILES config/ogre.cfg DESTINATION ${sts_BIN_DIR})

	# Install plugins.cfg, optional (release)
	if (EXISTS ${PROJECT_SOURCE_DIR}/config/plugins.cfg)
		install (FILES config/plugins.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Release)
	endif ()

	# Install plugins.cfg, optional (debug)
	if (EXISTS ${PROJECT_SOURCE_DIR}/config/debug/plugins.cfg)
		install (FILES config/debug/plugins.cfg DESTINATION ${sts_BIN_DIR} CONFIGURATIONS Debug)
	endif ()

	# Install plugins for Windows
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
endif ()

# Install all the game data
install (DIRECTORY data/ DESTINATION data)
