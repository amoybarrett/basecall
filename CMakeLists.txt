cmake_minimum_required(VERSION 2.8)

SET(ENV{COMPILE_STATIC} "1")

project (test_tile)
#set (result /home/xuweibin/basecall/mine/basecall_module_900/bin) 

#add_definitions(-DCGI_MAX_DNB_BASE_COUNT=${dnb_arch_def})
#find_file (google_tcmalloc libtcmalloc.so.0 PATHS  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/google/lib NO_DEFAULT_PATH )

include_directories(/home/xuweibin/basecall/mine/basecall_module_900)

file (GLOB test_tile_src /home/xuweibin/basecall/mine/basecall_module_900/*.c*)
add_library(commonlib ${test_tile_src})
add_executable (test_tile /home/xuweibin/basecall/mine/basecall_module_900/tile/test_tile.cpp)

LINK_DIRECTORIES(/home/xuweibin/workgroup/CPPLib/boost_1_56_0/boost_1_56_0/lib) #copy library to pwd
target_link_libraries (test_tile commonlib.a opencv_core opencv_imgproc opencv_highgui boost_system boost_thread boost_filesystem boost_date_time tiff -lz -lfftw3)

#add_subdirectory(libdnbcollection) CMakeList.txt

install(FILES test_tile DESTINATION /home/xuweibin/basecall/mine/basecall_module_900/bin)
