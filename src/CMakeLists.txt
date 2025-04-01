add_library(Logger STATIC)
add_library(DebugTools::Logger ALIAS Logger)

target_compile_features(Logger PRIVATE cxx_std_14)
target_sources(Logger PRIVATE Logger.cpp)
target_include_directories(Logger PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

## Installing
include(CMakePackageConfigHelpers)

install(
  TARGETS Logger 
  EXPORT LoggerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)

install(
  EXPORT LoggerTargets
  FILE LoggerTargets.cmake
  NAMESPACE DebugTools::
  DESTINATION lib/cmake/Logger
)
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/Logger 
  DESTINATION include
)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Logger
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    LoggerConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake"
  DESTINATION lib/cmake/Logger
)
