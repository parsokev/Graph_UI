cmake_minimum_required(VERSION 3.16)

project(Graph_ImagingUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Set path to CMake deployment script
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

qt_standard_project_setup()

# Include Qt deployment functions held in CMake deployment script
include(windeployqt)

set( TARGET ${PROJECT_NAME} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/includes" )


file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

qt_add_executable( ${TARGET}
        MANUAL_FINALIZATION
        ${HPPS}
        ${CPPS}
)

target_include_directories( ${TARGET} PUBLIC ${INCLUDE_PATH} )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Graph_ImagingUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
target_link_libraries( ${TARGET} PRIVATE Qt${QT_MAJOR_VERSION}::Widgets)

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

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${TARGET})
endif()

# Call appropriate function from deployment script to place all resources, runtime dependencies
# and Qt dependencies within same directory as generated .exe file
if (WIN32)
    windeployqt(${PROJECT_NAME})
else()
    if(APPLE)
        macdeployqt(${PROJECT_NAME})
    endif()
endif()
