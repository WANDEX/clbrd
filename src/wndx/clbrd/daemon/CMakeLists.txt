## daemon

add_executable(clbrd_daemon)

target_sources(clbrd_daemon
  PRIVATE
    daemon_cmd.cpp
    daemon.cpp
)

target_link_libraries(clbrd_daemon PRIVATE clbrd_src)

add_subdirectory(gui) # XXX
