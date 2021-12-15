file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(QRCodeLibrary_SRCS ${SOURCES})

# Declare the library
add_library(QRCodeLibrary STATIC
  ${QRCodeLibrary_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(QRCodeLibrary PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
