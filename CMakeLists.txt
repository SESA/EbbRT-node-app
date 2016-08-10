cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project("ebbrt-node" C CXX)

set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g3")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -flto -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g3")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(EbbRT REQUIRED)
find_package(Boost 1.53.0 REQUIRED COMPONENTS
  filesystem system coroutine context )
find_package(Capnp REQUIRED)
find_package(TBB REQUIRED)
find_package(Threads REQUIRED)
find_package(EbbRTCmdLine REQUIRED)
find_package(EbbRTFilesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Wall -Werror")
include_directories(${EBBRT_INCLUDE_DIRS})
add_executable(node Node.cc)
target_link_libraries(node ${EBBRT-CMDLINE_LIBRARIES}
  ${EBBRT-FILESYSTEM_LIBRARIES} ${EBBRT_LIBRARIES}
  ${CAPNP_LIBRARIES_LITE} ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES} ${TBB_LIBRARIES}
)
