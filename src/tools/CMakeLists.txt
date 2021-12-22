
message(STATUS "Configuring cxbqn tools")
configure_file(cxbqn-config.in
  ${PROJECT_BINARY_DIR}/cxbqn-config
  )
configure_file(vars.bqn.in
  ${PROJECT_BINARY_DIR}/vars.bqn
  )

install(FILES ${PROJECT_BINARY_DIR}/cxbqn-config DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
install(FILES ${PROJECT_BINARY_DIR}/vars.bqn DESTINATION share/bqn/cxbqn)

add_executable(bqn-format bqn_format.cpp)
target_link_libraries(bqn-format PRIVATE cxbqn::tpl)
target_include_directories(bqn-format PRIVATE ${PROJECT_SOURCE_DIR}/ext/spirit-1.78.0/include)
install(TARGETS bqn-format DESTINATION bin)
