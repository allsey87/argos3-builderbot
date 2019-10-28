#
# drone headers
#
# argos3/plugins/robots/drone/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE
  control_interface/ci_drone_cameras_system_sensor.h
  control_interface/ci_drone_wifi_actuator.h
  control_interface/ci_drone_wifi_sensor.h)
if(ARGOS_BUILD_FOR_SIMULATOR)
  # argos3/plugins/robots/drone/simulator
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR
    simulator/drone_cameras_system_default_sensor.h
    simulator/drone_entity.h
#    simulator/drone_flight_system_default_actuator.h
#    simulator/drone_flight_system_default_sensor.h
#    simulator/drone_flight_system_entity.h
#    simulator/drone_system_default_sensor.h
    simulator/drone_wifi_default_actuator.h
    simulator/drone_wifi_default_sensor.h
    simulator/dynamics3d_drone_model.h)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR}
      simulator/qtopengl_drone.h)
  endif(ARGOS_COMPILE_QTOPENGL)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # argos3/plugins/robots/drone/hardware
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE
    hardware/drone.h
    hardware/drone_cameras_system_default_sensor.h
    hardware/drone_wifi_default_actuator.h
    hardware/drone_wifi_default_sensor.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# drone sources
#
# argos3/plugins/robots/drone/control_interface
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE}
  control_interface/ci_drone_cameras_system_sensor.cpp
  control_interface/ci_drone_wifi_actuator.cpp
  control_interface/ci_drone_wifi_sensor.cpp)
if(ARGOS_BUILD_FOR_SIMULATOR)
  # argos3/plugins/robots/drone/simulator
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR}
    simulator/drone_cameras_system_default_sensor.cpp
    simulator/drone_entity.cpp
#    simulator/drone_flight_system_default_actuator.cpp
#    simulator/drone_flight_system_default_sensor.cpp
#    simulator/drone_flight_system_entity.cpp
#    simulator/drone_system_default_sensor.cpp
    simulator/drone_wifi_default_actuator.cpp
    simulator/drone_wifi_default_sensor.cpp
    simulator/dynamics3d_drone_model.cpp)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
      simulator/qtopengl_drone.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # argos3/plugins/robots/drone/hardware
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE}
    hardware/drone.cpp
    hardware/drone_cameras_system_default_sensor.cpp
    hardware/drone_wifi_default_actuator.cpp
    hardware/drone_wifi_default_sensor.cpp
    hardware/main.cpp)
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR_SIMULATOR)
  # Create a plug-in for the simulator
  add_library(argos3srocs_${ARGOS_BUILD_FOR}_drone SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE})
  # Use double precision in Bullet, if ARGoS is using double precision
  if(ARGOS_USE_DOUBLE)
    target_compile_definitions(argos3srocs_${ARGOS_BUILD_FOR}_drone PUBLIC BT_USE_DOUBLE_PRECISION)
  endif(ARGOS_USE_DOUBLE)
  target_link_libraries(argos3srocs_${ARGOS_BUILD_FOR}_drone
    argos3srocs_${ARGOS_BUILD_FOR}_entities
    ${ARGOS_CORE_LIBRARY}
    ${ARGOS_DYNAMICS3D_LIBRARY}
    ${ARGOS_ENTITIES_LIBRARY})
  if(ARGOS_COMPILE_QTOPENGL)
    target_link_libraries(argos3srocs_${ARGOS_BUILD_FOR}_drone ${ARGOS_QTOPENGL_LIBRARY})
  endif(ARGOS_COMPILE_QTOPENGL)
  install(TARGETS argos3srocs_${ARGOS_BUILD_FOR}_drone
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/argos3
    ARCHIVE DESTINATION lib/argos3)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  # Create an executable for the robot
  add_executable(argos3 ${ARGOS3_SOURCES_PLUGINS_ROBOTS_DRONE})
  target_link_libraries(argos3 tbb
    ${ARGOS_CORE_LIBRARY}
    ${LUA_LIBRARIES}
    ${PTHREADS_LIBRARY}
    ${APRILTAG_LIBRARY})
  install(TARGETS argos3
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/argos3
    ARCHIVE DESTINATION lib/argos3)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/drone/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_SIMULATOR} DESTINATION include/argos3/plugins/robots/drone/simulator)
  if(ARGOS_COMPILE_QTOPENGL)
    install(DIRECTORY simulator/models DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl)
  endif(ARGOS_COMPILE_QTOPENGL)
elseif(ARGOS_BUILD_FOR STREQUAL "drone")
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_DRONE_HARDWARE} DESTINATION include/argos3/plugins/robots/drone/hardware)
endif(ARGOS_BUILD_FOR_SIMULATOR)
