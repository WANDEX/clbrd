#pragma once

#include "aliases.hpp"

namespace wndx::clbrd::cfg {

inline constexpr addr_t addr{"127.0.0.1"};  // i.e. localhost
inline constexpr port_t port{12345};        // u16 max!

inline constexpr int interval{5};  // seconds

// default (client UID / device MAC) unique to the client/device.
inline constexpr sv_t def_uid{"f000::f000:f000:f000:f000"};

}  // namespace wndx::clbrd::cfg
