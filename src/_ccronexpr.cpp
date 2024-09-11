#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
#include <chrono>

#include "ccronexpr.h"

namespace py = pybind11;

std::chrono::system_clock::time_point wrap_cron_next(const std::string &expr, const std::chrono::system_clock::time_point  &date) {
    cron_expr cron;
    const char *error;
    cron_parse_expr(expr.c_str(), &cron, &error);
    if (error) {
        throw std::invalid_argument(std::string("Error parsing cron expression: ") + error);
    }
    time_t next = cron_next(&cron, std::chrono::system_clock::to_time_t(date));
    if (next == CRON_INVALID_INSTANT) {
        throw std::runtime_error("Error calculating next fire date");
    }
    return std::chrono::system_clock::from_time_t(next);
}

std::chrono::system_clock::time_point wrap_cron_prev(const std::string &expr, const std::chrono::system_clock::time_point  &date) {
    cron_expr cron;
    const char *error;
    cron_parse_expr(expr.c_str(), &cron, &error);
    if (error) {
        throw std::invalid_argument(std::string("Error parsing cron expression: ") + error);
    }
    time_t prev = cron_prev(&cron, std::chrono::system_clock::to_time_t(date));
    if (prev == CRON_INVALID_INSTANT) {
        throw std::runtime_error("Error calculating previous fire date");
    }
    return std::chrono::system_clock::from_time_t(prev);
}

PYBIND11_MODULE(_ccronexpr, m) {
    m.def("cron_next", &wrap_cron_next);
    m.def("cron_prev", &wrap_cron_prev);
}
