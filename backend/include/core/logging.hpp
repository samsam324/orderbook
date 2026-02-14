// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <iostream>

// Currently just skeleton logging helpers
// Later replace with spdlog or a structured logger; include thread ids, timestamps, etc...

#define MD_LOG_INFO(msg)  (std::cerr << "[INFO] " << msg << "\n")
#define MD_LOG_WARN(msg)  (std::cerr << "[WARN] " << msg << "\n")
#define MD_LOG_ERROR(msg) (std::cerr << "[ERROR] " << msg << "\n")

