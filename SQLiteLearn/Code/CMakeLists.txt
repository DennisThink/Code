cmake_minimum_required(VERSION 3.0)
project(SQLiteLearn)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/sqlite/lib)
add_compile_definitions(BUILD_GDBM_STATIC)
add_subdirectory(thirdparty)
add_subdirectory(sqlite)