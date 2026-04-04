/// client command line (cmd)

#include "wndx/clbrd/aliases.hpp"

#include "wndx/clbrd/config.hpp"
#include "wndx/clbrd/file.hpp"

#include <cxxopts.hpp>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// clang-format off
/// catch all possible exceptions (like Pokemon's)
/// to not suppress core dumps etc -> should be disabled => 0
#ifndef CLBRD_CATCH_THEM_ALL
#define CLBRD_CATCH_THEM_ALL 1 // NOLINT(*-macro-usage)
#endif//CLBRD_CATCH_THEM_ALL
// clang-format on

namespace wndx::clbrd {

/// \brief parse command line options.
///
/// catches every possible exception & signifies about that:
/// with an error message printed to std::cerr.
/// and with the return code / exit code.
///
/// \param  argc - as in the usual main() entry point.
/// \param  argv - as in the usual main() entry point.
/// \return error code.
// NOLINTNEXTLINE(*-avoid-c-arrays)
[[nodiscard]] rc cmd_opts(int argc, char const* argv[]) {
  try {
    // clang-format off
    cxxopts::Options options("clbrd_client",
      "Transfer file(s) over TCP/IP to the server running the clbrd_daemon.");
    options.custom_help("[OPTIONS]");
    options.set_width(80); // NOLINT(*-magic-numbers) - standard TERM width
    options.add_options()
      ("a,addr", "Server IP address with the clbrd_daemon. "
                 "(default: " + std::string{clbrd::cfg::addr} + ')',
       cxxopts::value<cmd_opt_t>())

      ("p,port", "Port number of the daemon on the server. "
                 "(default: " + fmt::to_string<port_t>(clbrd::cfg::port) + ')',
       cxxopts::value<port_t>())

      ("h,help", "Show usage help.")
      ("i,interval", "seconds between connection attempts."
                     "(default: " + std::string{clbrd::cfg::interval} + ')',
       cxxopts::value<int>())
      ("u,urge", "Log urgency level. (All messages </> Only critical)",
       cxxopts::value<int>(), "1-7");
    /// clang-format on

    /// initialize cmd options variable
    cxxopts::ParseResult cmd_opts{ options.parse(argc, argv) };

    /// initialize logger with the specific log file.
    log_g = Logger{ "/tmp/wndx/clbrd/logs/client.log"sv };

    if (cmd_opts.count("help")) {
      std::cout << options.help() << '\n';
      return rc::SUCCESS;
    }

    if (cmd_opts.count("urge")) { // force specific log urgency level
      const LL urgency{ cmd_opts["urge"].as<int>() };
      log_g.set_urgency(urgency);
    }

    rc rc{ rc::INIT }; // reusable variable for the return codes

    /// server address with the running clbrd daemon.
    addr_t const addr{ cmd_opts.count("addr") ? cmd_opts["addr"].as<cmd_opt_t>()
                                              : clbrd::cfg::addr };

    /// port number of the daemon on the server. (daemon instance)
    port_t const port{ cmd_opts.count("port") ? cmd_opts["port"].as<port_t>()
                                              : clbrd::cfg::port };

    // for (;;) {
    //   // TODO: send connection request
    //   // TODO: sleep interval if connection unsuccessful
    // }

  } catch (cxxopts::exceptions::exception const& err) {
    WNDX_LOG(LL::ERRO, "{}:\n{}\n", rc::ERRO_CMD_OPT, err.what());
    return rc::ERRO_CMD_OPT;
  } catch (std::exception const& err) {
    WNDX_LOG(LL::CRIT, "{} was caught:\n{}\n", rc::CRIT_EX_UNHANDLED,
             err.what());
    return rc::CRIT_EX_UNHANDLED;
#if CLBRD_CATCH_THEM_ALL
  } catch (...) {
    WNDX_LOG(LL::CRIT, "{} occurred but was caught!\n{}\n",
             rc::CRIT_EX_ANONYMOUS, "THIS IS VERY BAD!");
    return rc::CRIT_EX_ANONYMOUS;
#endif // CLBRD_CATCH_THEM_ALL
  }
  return rc::SUCCESS;
}

} // namespace wndx::clbrd
