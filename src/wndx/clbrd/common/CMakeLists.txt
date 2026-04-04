## common sources to the both targets: client & daemon

target_sources(clbrd_src
  PRIVATE
    file.cpp
    unix_sig.cpp
)

