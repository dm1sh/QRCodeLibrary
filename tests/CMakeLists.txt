find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(
  gtest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
  URL_HASH SHA1=9ffb7b5923f4a8fcdabf2f42c6540cce299f44c0
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
"IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/googletest/include")

# Tests build

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testQRCode ${SRCS})

TARGET_LINK_LIBRARIES(testQRCode
  QRCodeLibrary
  libgtest
)

add_test(NAME testQRCode
         COMMAND testQRCode)