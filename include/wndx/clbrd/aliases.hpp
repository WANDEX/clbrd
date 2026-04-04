#pragma once
/// project-wide type aliases

#include "wndx/sane/aliases.hpp"

#include <string_view>
#include <vector>

namespace wndx::clbrd {

using namespace wndx::sane;

#if 1
using ch_t = char;
using str_t = std::string;
using str_v = std::string_view;
#else
using ch_t = char8_t;
using str_t = std::u8string;
using str_v = std::u8string_view;
#endif
using vec_str_t = std::vector<str_t>;
using vec_s32_t = std::vector<s32>;

using addr_t = sv_t;
using port_t = u16;

/// cxxopts default_value() accepts std::string.
/// Any other type make working with the cxxopts unnecessarily harder.
/// => Common type for the command line options.
using cmd_opt_t = std::string;

}  // namespace wndx::clbrd
