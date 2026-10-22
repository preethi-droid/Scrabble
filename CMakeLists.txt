cmake_minimum_required(VERSION 3.22)
project(ScrabbleGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-VC/SFML-3.1.0/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

include_directories(include)

# Rules library owned by Preethi
add_library(rules 
    src/Dictionary.cpp 
    src/ScoreCalculator.cpp 
    src/HighScoreManager.cpp
)
target_link_libraries(rules PRIVATE SFML::Graphics SFML::Window SFML::System)

# Views library owned by Preethi & Mirudhulaa
add_library(views 
    src/Theme.cpp 
    src/SidePanel.cpp 
    src/SetupScreen.cpp
)
target_link_libraries(views PRIVATE rules SFML::Graphics SFML::Window SFML::System)

# Copy data/ and assets/ folders into build folder on compile
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})