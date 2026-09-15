cmake_minimum_required(VERSION 3.11)

project(AutoPSX)

# From apollo-psp, which is from vita shell CMakeLists - credits TheFlow


file(GLOB res_files RELATIVE
 ${CMAKE_SOURCE_DIR}
  assets/**
)

include_directories(src/ src/menus/)
add_executable(${PROJECT_NAME} ${res} src/main.c src/render.c src/menus/m_opening.c src/game_detection.c)


find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_mixer REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    pspdebug
)

if (PSP) 
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
endif()

foreach(fil IN LISTS res_files)
configure_file(${fil} ${CMAKE_CURRENT_BINARY_DIR}/${fil} COPYONLY)
endforeach()

