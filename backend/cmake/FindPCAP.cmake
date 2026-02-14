# Owner: ROLE 1 (IO/Networking/PCAP)
# Minimal FindPCAP.cmake for libpcap.
# - Provides imported target: PCAP::pcap
# - Sets: PCAP_FOUND, PCAP_INCLUDE_DIRS, PCAP_LIBRARIES

find_path(PCAP_INCLUDE_DIR
  NAMES pcap/pcap.h pcap.h
)

find_library(PCAP_LIBRARY
  NAMES pcap
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PCAP
  REQUIRED_VARS PCAP_INCLUDE_DIR PCAP_LIBRARY
)

if(PCAP_FOUND)
  set(PCAP_INCLUDE_DIRS "${PCAP_INCLUDE_DIR}")
  set(PCAP_LIBRARIES "${PCAP_LIBRARY}")

  if(NOT TARGET PCAP::pcap)
    add_library(PCAP::pcap UNKNOWN IMPORTED)
    set_target_properties(PCAP::pcap PROPERTIES
      IMPORTED_LOCATION "${PCAP_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${PCAP_INCLUDE_DIR}"
    )
  endif()
endif()

