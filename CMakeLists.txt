# CMakeLists files in this project can
# refer to the root source directory of the project as ${HIWONDER_SOURCE_DIR} and
# to the root binary directory of the project as ${HIWONDER_BINARY_DIR}.
cmake_minimum_required (VERSION 3.6.0)
project (HIWONDER)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory (src)
add_subdirectory (test)

# target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)