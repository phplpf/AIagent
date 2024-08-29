# -------------------------
# generate deb file
# -------------------------


file(GLOB DEBIAN_IN_FILES_LIST RELATIVE ${PROJECT_SOURCE_DIR}/pack/DEBIAN/ ${PROJECT_SOURCE_DIR}/pack/DEBIAN/*.in)

set(DEBIAN_FILES)

foreach(DEBIAN_IN_FILE ${DEBIAN_IN_FILES_LIST})
    get_filename_component(DEBIAN_FILE "${PROJECT_SOURCE_DIR}/pack/DEBIAN/${DEBIAN_IN_FILE}" NAME_WE)
    list(APPEND DEBIAN_FILES "${PROJECT_BINARY_DIR}/${DEBIAN_FILE}")
    configure_file(
        "${PROJECT_SOURCE_DIR}/pack/DEBIAN/${DEBIAN_IN_FILE}"
        "${PROJECT_BINARY_DIR}/${DEBIAN_FILE}"
        @ONLY
    )
endforeach()

