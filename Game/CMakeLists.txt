set(SOURCES "")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Game ${SOURCES})
target_link_libraries(Game PUBLIC compile_flags Engine)

add_custom_command(
    TARGET Game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:Game>/assets
    COMMENT "Creating symbolic link for assets for the game")

add_custom_command(
    TARGET Game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:Game>/../assets
    COMMENT "Creating symbolic link for assets for the game (for starting the game from the visual studio)")