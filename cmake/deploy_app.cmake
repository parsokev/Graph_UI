find_package(Qt6Core REQUIRED)

# Create function for handling Windows deployment script using windeployqt
function(windeployqt target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --verbose 1
                --release
                --no-svg
                --no-opengl
                --no-opengl-sw
                --compiler-runtime
                --no-system-d3d-compiler
                \"$<TARGET_FILE:${target}>\"
        COMMAND ${CMAKE_COMMAND} -E make_directory "dot_graphs" "$<TARGET_FILE_DIR:${target}>"
        COMMAND ${CMAKE_COMMAND} -E make_directory "graph_images" "$<TARGET_FILE_DIR:${target}>"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/sample_graphs"  "$<TARGET_FILE_DIR:${target}>/sample_graphs"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/Graphviz" "$<TARGET_FILE_DIR:${target}>/Graphviz"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/scripts" "$<TARGET_FILE_DIR:${target}>/scripts"
    )
endfunction()

# Create function for handling MacOS deployment script using macdeployqt
function(macdeployqt target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${QT_DIR}/bin/macdeployqt.exe"
                -verbose 1
                -hardened-runtime
                \"$<TARGET_FILE:${target}>\"
        COMMAND ${CMAKE_COMMAND} -E make_directory "dot_graphs" "$<TARGET_FILE_DIR:${target}>"
        COMMAND ${CMAKE_COMMAND} -E make_directory "graph_images" "$<TARGET_FILE_DIR:${target}>"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/sample_graphs"  "$<TARGET_FILE_DIR:${target}>/sample_graphs"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/Graphviz" "$<TARGET_FILE_DIR:${target}>/Graphviz"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/scripts" "$<TARGET_FILE_DIR:${target}>/scripts"
    )
endfunction()
