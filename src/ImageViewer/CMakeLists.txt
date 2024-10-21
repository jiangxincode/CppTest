IF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
    if (GTK3_FOUND)
        add_executable(ImageViewer
                main.c
                fileselect.c
                fileselect.h
                imageviewerutility.c
                imageviewerutility.h
                ImageWindow.c
                ImageWindow.h
                mainwindow.c
                mainwindow.h
                mainwindowhandlers.h)
        target_link_libraries(ImageViewer PkgConfig::GTK3)
        target_compile_options(ImageViewer PRIVATE -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED)
    endif ()
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin")