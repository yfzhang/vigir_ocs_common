cmake_minimum_required(VERSION 2.8.3)
project(vigir_ocs_rviz_plugins)

## Find catkin and any catkin packages on which
## this package depends at build time
find_package(catkin REQUIRED COMPONENTS roscpp rospy roslib std_msgs shape_msgs geometry_msgs
  # vigir_interactive_marker_server_custom
  rviz pluginlib class_loader
  cv_bridge)

## This plugin includes Qt widgets, so we must include Qt like so:
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

find_package(OpenGL REQUIRED)

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

catkin_package(
  LIBRARIES
    vigir_ocs_rviz_plugin_image_selection_tool_custom
    vigir_ocs_rviz_plugin_mesh_display_custom
    vigir_ocs_rviz_plugin_map_display_custom
    vigir_ocs_rviz_plugin_interaction_tool_custom
    vigir_ocs_rviz_plugin_image_selection_tool_custom_core
    vigir_ocs_rviz_plugin_mesh_display_custom_core
    vigir_ocs_rviz_plugin_map_display_custom_core
    vigir_ocs_rviz_plugin_interaction_tool_custom_core
    ${OPENGL_LIBRARIES}
  INCLUDE_DIRS
    vigir_ocs_rviz_plugin_image_selection_tool_custom/src
    vigir_ocs_rviz_plugin_mesh_display_custom/src
    vigir_ocs_rviz_plugin_map_display_custom/src
    vigir_ocs_rviz_plugin_interaction_tool_custom/src
    ${OPENGL_INCLUDE_DIR}
  CATKIN_DEPENDS
    roscpp 
    rospy
    roslib
    std_msgs
    shape_msgs
    geometry_msgs 
    rviz 
    pluginlib 
    class_loader
    cv_bridge
)

include_directories(
        vigir_ocs_rviz_plugin_image_selection_tool_custom/src
        vigir_ocs_rviz_plugin_interaction_tool_custom/src
        vigir_ocs_rviz_plugin_map_display_custom/src
        vigir_ocs_rviz_plugin_mesh_display_custom/src
	${catkin_INCLUDE_DIRS})

include_directories(SYSTEM
                    ${OPENGL_INCLUDE_DIR}
                    ${QT_INCLUDE_DIR})

link_directories(${catkin_LIBRARY_DIRS})


add_subdirectory(vigir_ocs_rviz_plugin_image_selection_tool_custom)
add_subdirectory(vigir_ocs_rviz_plugin_interaction_tool_custom)
add_subdirectory(vigir_ocs_rviz_plugin_map_display_custom)
add_subdirectory(vigir_ocs_rviz_plugin_mesh_display_custom)

install(FILES
  camera_display_custom_plugin_description.xml
  image_selection_tool_custom_plugin_description.xml
  interaction_tool_custom_plugin_description.xml
  map_display_custom_plugin_description.xml
  mesh_display_custom_plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

#install(DIRECTORY icons DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
