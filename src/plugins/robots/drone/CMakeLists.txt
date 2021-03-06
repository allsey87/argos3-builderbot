#
# Drone headers
#
# argos3/plugins/robots/drone/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE
  control_interface/ci_drone_cameras_system_sensor.h
  control_interface/ci_drone_flight_system_actuator.h
  control_interface/ci_drone_flight_system_sensor.h
  control_interface/ci_drone_rangefinders_sensor.h
  control_interface/ci_drone_system_sensor.h)
if(ARGOS_BUILD_FOR_SIMULATOR)
  # argos3/plugins/robots/drone/simulator
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR
    simulator/drone_cameras_system_default_sensor.h
    simulator/drone_entity.h
    simulator/drone_flight_system_default_actuator.h
    simulator/drone_flight_system_default_sensor.h
    simulator/drone_flight_system_entity.h
#    simulator/drone_rangefinders_default_sensor.h
    simulator/drone_system_default_sensor.h
    simulator/pointmass3d_drone_model.h)
  if(ARGOS_QTOPENGL_FOUND)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR}
      simulator/qtopengl_drone.h)
  endif(ARGOS_QTOPENGL_FOUND)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # argos3/plugins/robots/drone/hardware
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE
    hardware/drone.h
    hardware/drone_cameras_system_default_sensor.h
    hardware/drone_flight_system_default_actuator.h
    hardware/drone_flight_system_default_sensor.h
    hardware/drone_rangefinders_default_sensor.h
    hardware/drone_system_default_sensor.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Drone sources
#
# argos3/plugins/robots/drone/control_interface
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE}
  control_interface/ci_drone_cameras_system_sensor.cpp
  control_interface/ci_drone_flight_system_actuator.cpp
  control_interface/ci_drone_flight_system_sensor.cpp
  control_interface/ci_drone_rangefinders_sensor.cpp
  control_interface/ci_drone_system_sensor.cpp)
if(ARGOS_BUILD_FOR_SIMULATOR)
  # argos3/plugins/robots/drone/simulator
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR}
    simulator/drone_cameras_system_default_sensor.cpp
    simulator/drone_entity.cpp
    simulator/drone_flight_system_default_actuator.cpp
    simulator/drone_flight_system_default_sensor.cpp
    simulator/drone_flight_system_entity.cpp
#    simulator/drone_rangefinders_default_sensor.cpp
    simulator/drone_system_default_sensor.cpp
    simulator/pointmass3d_drone_model.cpp)
  if(ARGOS_QTOPENGL_FOUND)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
      simulator/qtopengl_drone.cpp)
  endif(ARGOS_QTOPENGL_FOUND)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # argos3/plugins/robots/drone/hardware
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE}
    hardware/drone.cpp
    hardware/drone_cameras_system_default_sensor.cpp
    hardware/drone_flight_system_default_actuator.cpp
    hardware/drone_flight_system_default_sensor.cpp
    hardware/drone_rangefinders_default_sensor.cpp   
    hardware/drone_system_default_sensor.cpp
    hardware/main.cpp)
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR_SIMULATOR)
  # Create a plug-in for the simulator
  add_library(argos3plugin_${ARGOS_BUILD_FOR}_drone SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE})
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_drone
    argos3core_${ARGOS_BUILD_FOR}
    argos3plugin_${ARGOS_BUILD_FOR}_pointmass3d
    argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
    argos3plugin_${ARGOS_BUILD_FOR}_entities
    argos3plugin_${ARGOS_BUILD_FOR}_srocs_genericrobot
    argos3plugin_${ARGOS_BUILD_FOR}_srocs_entities)
  if(ARGOS_QTOPENGL_FOUND)
    target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_drone argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
  endif(ARGOS_QTOPENGL_FOUND)
  install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_drone
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/argos3
    ARCHIVE DESTINATION lib/argos3)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # Create an executable for the robot
  add_executable(argos3 ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE})
  target_link_libraries(argos3 tbb
    argos3core_${ARGOS_BUILD_FOR}
    argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
    argos3plugin_${ARGOS_BUILD_FOR}_srocs_genericrobot
    ${IIO_LIBRARY}
    ${APRILTAG_LIBRARY}
    ${TURBOJPEG_LIBRARY})
  install(TARGETS argos3
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/argos3
    ARCHIVE DESTINATION lib/argos3)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/drone/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR} DESTINATION include/argos3/plugins/robots/drone/simulator)
  if(ARGOS_QTOPENGL_FOUND)
    install(DIRECTORY simulator/models DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl)
  endif(ARGOS_QTOPENGL_FOUND)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE} DESTINATION include/argos3/plugins/robots/drone/hardware)
endif(ARGOS_BUILD_FOR_SIMULATOR)

