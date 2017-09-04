cmake_minimum_required(VERSION 3.0)
project(cereal_optional)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS
        include/cereal_optional/optional_nvp.hpp
        include/cereal_optional/optional_json.hpp
        include/cereal_optional/optional_binary.hpp)
set_source_files_properties(${HEADERS} PROPERTIES LANGUAGE CXX)

add_library(cereal-optional INTERFACE)
target_include_directories(cereal-optional INTERFACE include)
