find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
  gtest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  # Disable install step
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
"IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
"IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testQRCode ${SRCS})

TARGET_LINK_LIBRARIES(testQRCode
  QRCodeLibrary
  libgtest
  libgmock
)

add_test(NAME testQRCode
         COMMAND testQRCode)