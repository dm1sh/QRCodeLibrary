set(Demo_SRCS
  main.cpp
)

add_executable(QRCodeLibraryDemo
  ${Demo_SRCS}
)

target_link_libraries(QRCodeLibraryDemo
  QRCodeLibrary
)

install(TARGETS QRCodeLibraryDemo DESTINATION bin)
