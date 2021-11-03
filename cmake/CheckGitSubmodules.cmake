
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  add_custom_target(
    git-submodules ALL
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Updating git submodules... set CHECK_SUBMODULES to OFF to disable this."
  )
  add_dependencies(tpl git_submodules)
else()
  message(WARNING "Git could not be found, I can't check your git submodules!")
endif()
