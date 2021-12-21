
message(STATUS "Configuring cxbqn tools")
configure_file(cxbqn-config.in
  ${PROJECT_BINARY_DIR}/cxbqn-config
  )
configure_file(vars.bqn.in
  ${PROJECT_BINARY_DIR}/vars.bqn
  )

install(FILES ${PROJECT_BINARY_DIR}/cxbqn-config DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
install(FILES ${PROJECT_BINARY_DIR}/vars.bqn DESTINATION share/bqn/cxbqn)
