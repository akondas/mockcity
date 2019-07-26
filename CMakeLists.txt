cmake_minimum_required(VERSION 3.7)
project(mockcity)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")

find_package(SFML 2 COMPONENTS audio graphics window system)
if(NOT SFML_FOUND)
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.60.0 COMPONENTS system filesystem REQUIRED)

file(GLOB MOCKCITY_SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(mockcity ${MOCKCITY_SRC})

include_directories(${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})
target_link_libraries(mockcity ${Boost_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

install(TARGETS mockcity RUNTIME DESTINATION .)
install(DIRECTORY media/ DESTINATION media/)
