find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Editor ${SOURCES})
target_link_libraries(Editor PRIVATE compile_flags Engine Qt5::Core Qt5::Widgets Qt5::OpenGL)
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(Editor PRIVATE cxx_std_17)
target_compile_options(Editor PRIVATE "/Zc:__cplusplus")
set_property(TARGET Editor PROPERTY AUTOMOC TRUE)

add_custom_command(
    TARGET Editor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:Editor>/assets
    COMMENT "Creating symbolic link for assets for the editor")

add_custom_command(
    TARGET Editor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:Editor>/../assets
    COMMENT "Creating symbolic link for assets for the editor (for starting the editor from the visual studio)")