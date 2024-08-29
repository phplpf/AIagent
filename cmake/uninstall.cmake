# -------------------------
#  uninstall target, for 'make uninstall'
# -------------------------

configure_file(
    "${PROJECT_SOURCE_DIR}/pack/templates/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    @ONLY
)

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

if(ENABLE_SOLUTION_FOLDERS)
    set_target_properties(uninstall PROPERTIES FOLDER "CMakeTargets")
endif()
