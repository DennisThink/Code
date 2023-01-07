project(sqlite)
include_directories(./include/)
link_directories(./lib/)
aux_source_directory(./src/ SQLITE_SOURCE)
link_libraries(gdbm)
add_executable(sqlite ${SQLITE_SOURCE})

add_custom_command(
        TARGET  sqlite  PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/../thirdparty/gdbm/include/
                ${PROJECT_SOURCE_DIR}/include/)
