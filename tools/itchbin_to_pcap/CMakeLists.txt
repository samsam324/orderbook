# Owner: ROLE 1 (IO/Networking/PCAP) + ROLE 2 (Protocols)

cmake_minimum_required(VERSION 3.20)
project(itchbin_to_pcap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(itchbin_to_pcap
  main.cpp
)

target_compile_features(itchbin_to_pcap PRIVATE cxx_std_20)

# Intentionally keep dependencies minimal in skeleton
# Later will reuse backend PCAP writer + MoldUDP64 encoder

