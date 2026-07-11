#pragma once

#include <stdio.h>

/*
 * A simple logging utility.
 * LOG_INFO, LOG_WARN, and LOG_ERROR are always enabled.
 * LOG_DEBUG is only enabled when DEBUG_BUILD is defined.
 * You can define DEBUG_BUILD in your CMakeLists.txt for debug builds, e.g.:
 * add_compile_definitions(DEBUG_BUILD)
 */

#define LOG_INFO(format, ...) printf("[INFO] " format "\n", ##__VA_ARGS__)

#define LOG_WARN(format, ...) printf("[WARN] " format "\n", ##__VA_ARGS__)

#define LOG_ERROR(format, ...) printf("[ERROR] " format "\n", ##__VA_ARGS__)

#ifdef DEBUG_BUILD
#define LOG_DEBUG(format, ...) printf("[DEBUG] " format "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...) (void)0
#endif