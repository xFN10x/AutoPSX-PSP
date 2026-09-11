cmake_minimum_required(VERSION 3.11)

project(AutoPSX)


include_directories(src/ src/menus/)
add_executable(${PROJECT_NAME} src/main.c src/render.c src/menus/m_opening.c)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    SDL3::SDL3
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
