cmake_minimum_required(VERSION 3.19)
project(SearchEngine LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(SearchEngine
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/Indexer.cpp
    src/SearchEngine.cpp
    src/DocxParser.cpp
    src/miniz.c
    src/pugixml.cpp

    include/DocxParser.h
    include/Indexer.h
    include/SearchEngine.h
    include/Tokenizer.h
    include/miniz.h
    include/pugiconfig.hpp
    include/pugixml.hpp

)
set_source_files_properties(src/miniz.c PROPERTIES LANGUAGE CXX)

target_include_directories(SearchEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SearchEngine
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS SearchEngine
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SearchEngine
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})