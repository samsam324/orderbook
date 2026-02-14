# Owner: Integration (Role 3 lead)
cmake_minimum_required(VERSION 3.20)
project(md_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

option(MD_WITH_PCAP "Enable libpcap support" ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_library(md STATIC
  src/core/time.cpp

  src/io/pcap_reader.cpp
  src/io/pcap_writer.cpp
  src/io/udp_receiver.cpp
  src/io/udp_sender.cpp
  src/io/itch_binfile_reader.cpp

  src/protocols/moldudp64.cpp
  src/protocols/itch_decoder.cpp

  src/transport/mutex_queue.cpp
  src/transport/spsc_ring.cpp

  src/book/l3_order_book.cpp
  src/book/book_snapshot.cpp
  src/book/analytics.cpp

  src/metrics/reporter.cpp

  src/api/json_schema.cpp
  src/api/ws_server.cpp

  src/app/modes.cpp
  src/app/engine.cpp
)

target_include_directories(md PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(md PUBLIC
  Boost::system
  Threads::Threads
)

if(MD_WITH_PCAP)
  find_package(PCAP)
  if(PCAP_FOUND)
    target_link_libraries(md PUBLIC PCAP::pcap)
    target_compile_definitions(md PUBLIC MD_WITH_PCAP=1)
  else()
    message(STATUS "PCAP not found; building skeleton without libpcap linkage")
  endif()
endif()

add_executable(md_engine
  src/app/main.cpp
)
target_link_libraries(md_engine PRIVATE md)

enable_testing()

add_executable(test_moldudp64 tests/test_moldudp64.cpp)
target_link_libraries(test_moldudp64 PRIVATE md)
add_test(NAME test_moldudp64 COMMAND test_moldudp64)

add_executable(test_itch_decoder tests/test_itch_decoder.cpp)
target_link_libraries(test_itch_decoder PRIVATE md)
add_test(NAME test_itch_decoder COMMAND test_itch_decoder)

add_executable(test_l3_book tests/test_l3_book.cpp)
target_link_libraries(test_l3_book PRIVATE md)
add_test(NAME test_l3_book COMMAND test_l3_book)

add_executable(test_end_to_end_replay tests/test_end_to_end_replay.cpp)
target_link_libraries(test_end_to_end_replay PRIVATE md)
add_test(NAME test_end_to_end_replay COMMAND test_end_to_end_replay)

