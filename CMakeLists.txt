#cmake_minimum_required(VERSION 3.14)

#project(sqlite_test LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

#add_executable(sqlite_test
#  main.cpp
#  sqlite_orm.h
#  sqlite3.c
#  sqlite3.h
#  sqlite3ext.h
#  sqlorm_xpro_define.h
#  easylogging++.h
#  easylogging++.cc
#  my_easylogging.cpp
#  my_easylogging.h
#  normal_typedef.h
#)
#target_link_libraries(sqlite_test Qt${QT_VERSION_MAJOR}::Core)


#cmake version
cmake_minimum_required ( VERSION 3.10 )

set(CMAKE_CONFIGURATION_TYPES Release)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
endif()

project ( xdevice_project CXX C)
#设置程序编译输出路径

#reset output path
set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_SHARED_LIBRARY_LINK_C_FLAGS )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#QT编译开关
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


#自动获取工程路径
string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})# 获取当前cmakelist文件存放的路径
get_filename_component(CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE} NAME)#获取当前存放cmakelist文件的文件夹名称，用于获取上层路径
#string(REGEX REPLACE "(.*)/${CURRENT_FOLDER}$" "\\1" CMAKE_MY_PROJECT_PATH ${CURRENT_FOLDER_ABSOLUTE})#获取工程路径
# message (STATUS "1111111111111  CURRENT_FOLDER_ABSOLUTE   ==  ${CURRENT_FOLDER_ABSOLUTE}")
# string(REGEX REPLACE ".*/(.*)" "\\1" SECOND_FOLDER ${CMAKE_MY_PROJECT_PATH})#这句会获取路径${CMAKE_MY_PROJECT_PATH}最后一个文件夹的名字
#very important, for find package
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_MY_PROJECT_PATH}/Build)#//好像不生效 QT的路径还是的在项目中修改
set(CMAKE_MY_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_FEATURE_PATH ${CMAKE_MY_PROJECT_PATH}/feature)
set(CMAKE_MY_THIRDPARTY_PATH ${CMAKE_MY_PROJECT_PATH}/thirdparty)
message (STATUS "CMAKE_MY_PROJECT_PATH ==  ${CMAKE_MY_PROJECT_PATH}")
message (STATUS "CMAKE_FEATURE_PATH ==  ${CMAKE_MY_PROJECT_PATH}")
message (STATUS "CMAKE_MY_THIRDPARTY_PATH ==  ${CMAKE_MY_THIRDPARTY_PATH}")


#第三方库的导入
#set(CMAKE_PREFIX_PATH "/opt/qt515")
#find_package(Qt5 COMPONENTS Widgets Core Network Gui Qml Quick PrintSupport Mqtt REQUIRED)
# set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/msvc2019_64;${CMAKE_MY_PROJECT_PATH}/thirdparty/libprotobuf-win;${CMAKE_MY_PROJECT_PATH}/thirdparty/libzmq-win")#设置第三方库的存放路径
#set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/msvc2019_64";${CMAKE_MY_THIRDPARTY_PATH}/libmosquitto_win64_debug)#设置第三方库的存放路径
set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/mingw_64")#设置第三方库的存放路径
find_package(Qt6 COMPONENTS Widgets Core Network Gui Qml Quick PrintSupport Charts REQUIRED)

#set debug
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions (
        -DPRINT_DEBUG_INFO
    )
endif()
add_definitions (
        -DWIN32_LEAN_AND_MEAN
        -DSQLITE_ENABLE_RTREE
        -DSQLITE_ENABLE_COLUMN_METADATA
        -DELPP_FEATURE_CRASH_LOG
        # easylog thread safe, it's very important!!!!!!!!
        -DELPP_THREAD_SAFE
        -DELPP_NO_DEFAULT_LOG_FILE
        -DELPP_FEATURE_ALL
#        -DELPP_OS_UNIX
        # -DSENDCMD_BY_MANNUE #开启后底层协议可以手动输入指令，新的通过数据库方式启动底层模块后，这方法就用不了了。
)


#include_directories ( ${CMAKE_MY_PROJECT_PATH})

#aux_source_directory ( ${CMAKE_MY_PROJECT_PATH} DIR_USR_SOURCE )

set(CMAKE_MY_TARGET_NAME ${CMAKE_PROJECT_NAME})#获取工程名
#generate target
#add_executable ( ${CMAKE_MY_TARGET_NAME} ${DIR_USR_SOURCE} )#执行编译
#add_executable(${CMAKE_MY_TARGET_NAME}
#  main.cpp
#  sqlite_orm.h
#  sqlite3.c
#  sqlite3.h
#  sqlite3ext.h
#  sqlorm_xpro_define.h
#  easylogging++.h
#  easylogging++.cc
#  my_easylogging.cpp
#  my_easylogging.h
#  normal_typedef.h
#)

file(GLOB_RECURSE CPP_PATHS  *.cpp *.h *.cc *.hpp *.c )
foreach(filepath ${CPP_PATHS})
    message("add cpp file:" ${filepath})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath}) #.+/(.+)\\\\..*" "\\\\1
    list(APPEND CPP_FILES ${filename})
endforeach(filepath)
list(REMOVE_DUPLICATES CPP_FILES)

add_executable ( ${CMAKE_MY_TARGET_NAME} ${CPP_FILES} )#执行编译

target_link_libraries(${CMAKE_MY_TARGET_NAME} PRIVATE   Qt::Widgets Qt::Core Qt::Network Qt::Gui Qt::Qml Qt::Quick Qt::PrintSupport Qt::Charts)
