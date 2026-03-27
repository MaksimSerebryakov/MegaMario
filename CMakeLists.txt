cmake_minimum_required(VERSION 3.28)
project(Assigment3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(app src/main.cpp
                   src/Entity.cpp
                   src/Vec2.cpp
                   src/EntityManager.cpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE SFML::Graphics)