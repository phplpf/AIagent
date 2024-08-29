# -----------------------
#  generate service file
# -----------------------

set(SYSTEMCTL_EXECSTART ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME})
configure_file(
    "${PROJECT_SOURCE_DIR}/pack/templates/systemd.service.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service"
    @ONLY
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service DESTINATION /usr/lib/systemd/system/)
