## client

add_executable(clbrd_client)

target_sources(clbrd_client
  PRIVATE
    client_cmd.cpp
    client.cpp
)

target_link_libraries(clbrd_client PRIVATE clbrd_src)

