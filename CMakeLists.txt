cmake_minimum_required(VERSION 3.10)
project(AudioAura)

set(CMAKE_C_STANDARD 99)

find_package(raylib 4.5 QUIET)


if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_MP3 1 CACHE BOOL "Support MP3 file format")
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

FetchContent_Declare(
        nfd
        GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
        GIT_TAG master
)

FetchContent_GetProperties(nfd)
if (NOT nfd_POPULATED)
    FetchContent_Populate(nfd)
    add_library(nfd STATIC ${nfd_SOURCE_DIR}/src/nfd_common.c ${nfd_SOURCE_DIR}/src/nfd_gtk.c)
    target_include_directories(nfd PRIVATE ${nfd_SOURCE_DIR}/src/include ${GTK3_INCLUDE_DIRS})
endif ()

add_executable(AudioAura src/main.c src/ui.c src/playlist.c)
target_include_directories(AudioAura PRIVATE 
    ${raylib_SOURCE_DIR}/src 
    ${nfd_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(AudioAura raylib nfd ${GTK3_LIBRARIES})
