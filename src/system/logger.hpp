#pragma once

#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#define LOGGER_INFO(...) spdlog::info(__VA_ARGS__)
#define LOGGER_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOGGER_WARN(...) spdlog::warn(__VA_ARGS__)
