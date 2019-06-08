cmake_minimum_required(VERSION 3.13)
project(mockcity)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")

find_package(SFML 2 COMPONENTS graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

file(GLOB MOCKCITY_SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(mockcity ${MOCKCITY_SRC})

target_link_libraries(mockcity ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

install(TARGETS mockcity
        RUNTIME DESTINATION .)

install(DIRECTORY media/
        DESTINATION media/)
