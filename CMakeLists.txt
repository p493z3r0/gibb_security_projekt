cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

project(main)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix OpenSSL
            RESULT_VARIABLE BREW_OPENSSL
            OUTPUT_VARIABLE BREW_OPENSSL_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_OPENSSL EQUAL 0 AND EXISTS "${BREW_OPENSSL_PREFIX}")
        message(STATUS "Found OpenSSL keg installed by Homebrew at ${BREW_OPENSSL_PREFIX}")
        set(OPENSSL_ROOT_DIR "${BREW_OPENSSL_PREFIX}/")
        set(OPENSSL_INCLUDE_DIR "${BREW_OPENSSL_PREFIX}/include")
        set(OPENSSL_LIBRARIES "${BREW_OPENSSL_PREFIX}/lib")
        set(OPENSSL_CRYPTO_LIBRARY "${BREW_OPENSSL_PREFIX}/lib/libcrypto.dylib")
    endif ()
endif ()


find_library(FWCoreFoundation NAMES CoreFoundation)
message(">>>> find_library(CoreFoundation): ${FWCoreFoundation}")

include_directories(core/include)
include_directories(${CMAKE_SOURCE_DIR}/include/Bcrypt.cpp/include)
include_directories(${CMAKE_SOURCE_DIR}/include/cpp-jwt/include)


find_package(cpprestsdk REQUIRED)
set(libpqxxdir "include/libpqxx")
set(SKIP_BUILD_TEST on)
set(BUILD_SHARED_LIBS OFF)

# Used this instead of FindLibrary.
# Setting PostgresSQL_INCLUDE_DIRS externally.
set(PostgreSQL_FOUND true)
set(PostgresSQL_INCLUDE_DIR ${PostgresSQL_INCLUDE_DIRS})
set(PostgresSQL_TYPE_INCLUDE_DIR ${PostgresSQL_INCLUDE_DIRS})

add_subdirectory(${libpqxxdir})

add_executable(main main.cpp core/core_controller.cpp core/network.cpp core/include/controller.h core/include/core_controller.h core/include/common.h core/include/network.h app/controllers/user/user_controller.cpp app/controllers/user/user_controller.h core/include/interrupt_handler.h core/include/runtime_utils.h app/services/user/user_service.cpp app/services/user/user_service.h app/models/user_model.cpp app/models/user_model.h core/include/logger.h core/logger.cpp)
target_link_libraries(main PRIVATE cpprestsdk::cpprest)
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(main PRIVATE "${FWCoreFoundation}")
endif ()
message(${CMAKE_SOURCE_DIR})
target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/include/Bcrypt.cpp/libbcryptcpp.a)
target_link_libraries(main PRIVATE pqxx)

add_subdirectory(${CMAKE_SOURCE_DIR}/include/cpp-jwt)

target_link_libraries(main PRIVATE cpp-jwt::cpp-jwt)



# I have no clue how to Link on Linux and Windows. Good Luck in adding those libs here :)

# But this does indeed work on MacOS, but you have to create a symlink to the MacOS SDK. Since one library did not change their linking behaviour to comply with the new
# XCode Install Path



