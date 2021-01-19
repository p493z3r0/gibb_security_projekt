# Install script for directory: /Users/dominicjarmann/CLionProjects/SecModulBackend/include/cpp-jwt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt/cpp-jwtTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt/cpp-jwtTargets.cmake"
         "/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/CMakeFiles/Export/lib/cmake/cpp-jwt/cpp-jwtTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt/cpp-jwtTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt/cpp-jwtTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt" TYPE FILE FILES "/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/CMakeFiles/Export/lib/cmake/cpp-jwt/cpp-jwtTargets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cpp-jwt" TYPE FILE FILES
    "/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/cpp-jwtConfig.cmake"
    "/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/cpp-jwtConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jwt" TYPE DIRECTORY FILES "/Users/dominicjarmann/CLionProjects/SecModulBackend/include/cpp-jwt/include/jwt/detail")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jwt" TYPE DIRECTORY FILES "/Users/dominicjarmann/CLionProjects/SecModulBackend/include/cpp-jwt/include/jwt/impl")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jwt" TYPE DIRECTORY FILES "/Users/dominicjarmann/CLionProjects/SecModulBackend/include/cpp-jwt/include/jwt/json")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jwt" TYPE DIRECTORY FILES "/Users/dominicjarmann/CLionProjects/SecModulBackend/include/cpp-jwt/include/jwt/" FILES_MATCHING REGEX "/[^/]*\\.hpp$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/tests/cmake_install.cmake")
  include("/Users/dominicjarmann/CLionProjects/SecModulBackend/cmake-build-debug/include/cpp-jwt/examples/cmake_install.cmake")

endif()

