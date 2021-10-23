add_subdirectory(catch)

if(NOT TARGET spdlog::spdlog)
  message(STATUS "Cant find external spdlog, building it as a subproject")
  add_subdirectory(spdlog)
endif()
