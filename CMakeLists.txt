cmake_minimum_required(VERSION 3.16)

project(Graph_ImagingUI VERSION 0.1 LANGUAGES CXX)

# Set Required Compiler Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate Locally installed Qt Required Libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Establish path to CMake deployment script
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

qt_standard_project_setup()

# Include Qt deployment functions held in CMake deployment script
include(deploy_app)

# Establish source file locations
set( TARGET ${PROJECT_NAME} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/includes" )

file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
# Establish executable with project name and targets for compilation
qt_add_executable( ${TARGET}
        MANUAL_FINALIZATION
        src/mainwindow.ui
        ${HPPS}
        ${CPPS}
)

# Ensure path for headers in 'includes' directory is recognized
target_include_directories( ${TARGET} PUBLIC ${INCLUDE_PATH} )

# Link Qt Widgets library required for application
target_link_libraries( ${TARGET} PRIVATE Qt${QT_MAJOR_VERSION}::Widgets)

# Have CMake send different definitions to compiler based on its build type value/configuration
# These are used in determining where resources are located and whether to deploy application
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:RelWithDebInfo>:RELDEBUG>
)

else()
    if(ANDROID)
        add_library( ${TARGET} SHARED
            ${HPPS}
            ${CPPS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${TARGET}
            ${HPPS}
            ${CPPS}
        )
    endif()
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Graph_ImagingUI)
endif()
set_target_properties(${TARGET} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# Install built application based on set build directory path
include(GNUInstallDirs)
install(TARGETS ${TARGET}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${TARGET})
endif()

# FOR APPLICATION DEPLOYMENT ONLY - SET BUILD TYPE TO 'RELEASE'
# Call appropriate function from deployment script to place all resources, runtime dependencies
# and Qt dependencies within same directory as generated .exe file
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (WIN32)
        #use function to call windeployqt for Windows
        windeployqt(${PROJECT_NAME})
    else()
        if(APPLE)
            # use function to call macdeployqt for MacOS
            macdeployqt(${PROJECT_NAME})
        endif()
    # Currently linux is not supported for deployment with this yet
    endif()
endif()
