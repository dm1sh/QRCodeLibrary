file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(QRCodeLibrary_SRCS ${SOURCES})

# Declare the library
add_library(QRCodeLibrary STATIC
  ${QRCodeLibrary_SRCS}
)
set_target_properties(QRCodeLibrary PROPERTIES PUBLIC_HEADER "BitArray.hpp;DataBlocks.hpp;Encoder.hpp;Method.hpp;QRCode.hpp;QRMatrix.hpp;Tables.hpp;TritMatrix.hpp")

# Specify here the include directories exported
# by this library
target_include_directories(QRCodeLibrary PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS QRCodeLibrary
        LIBRARY DESTINATION /usr/lib
        PUBLIC_HEADER DESTINATION include/QRCodeLibrary)