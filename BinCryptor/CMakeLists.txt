add_executable (BinCryptor "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BinCryptor PROPERTY CXX_STANDARD 20)
endif()
