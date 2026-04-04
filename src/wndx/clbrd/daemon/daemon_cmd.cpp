/// daemon command line (cmd)

#include "wndx/clbrd/aliases.hpp"

#include "wndx/clbrd/config.hpp"
#include "wndx/clbrd/file.hpp"  // IWYU pragma: keep

#include <cxxopts.hpp>

#include <filesystem>
#include <iostream>
#include <string>

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
    cxxopts::Options options("clbrd_daemon",
        "Accept file(s) over TCP/IP from the clients running the clbrd_client.");
    options.set_width(80); // NOLINT(*-magic-numbers) - standard TERM width
    options.add_options()
      ("d,dir", "Path to the storage dir, else default storage under cwd.",
       cxxopts::value<cmd_opt_t>()->default_value("./clbrd_storage"))

      ("p,port", "Use port number as identity of the daemon on the server. "
                 "(default: " + fmt::to_string<port_t>(clbrd::cfg::port) + ')',
       cxxopts::value<port_t>())

      ("h,help", "Show usage help.")
      ("u,urge", "Log urgency level. (All messages </> Only critical)",
       cxxopts::value<int>(), "1-7");
    // clang-format on
    /// initialize cmd options variable
    cxxopts::ParseResult cmd_opts{options.parse(argc, argv)};

    /// initialize logger with the specific log file.
    log_g = Logger{"/tmp/wndx/clbrd/logs/daemon.log"sv};

    if (cmd_opts.count("help")) {
      std::cout << options.help() << '\n';
      return rc::SUCCESS;
    }

    if (cmd_opts.count("urge")) {  // force specific log urgency level
      const LL urgency{cmd_opts["urge"].as<int>()};
      log_g.set_urgency(urgency);
    }

    rc rc{rc::INIT};  // reusable variable for the return codes

    /// path to the storage dir. (storage for incoming files)
    fs::path const storage_dir{
        wndx::sane::path::sanitize(cmd_opts["dir"].as<cmd_opt_t>())};

    std::error_code ec{};
    if (fs::is_directory(storage_dir, ec)) {
      WNDX_LOG(LL::NTFY,
               "Directory exist, and will be used as the storage dir\n");
    } else {
      WNDX_LOG(LL::DBUG, "storage_dir: {}\n", storage_dir);
      /// make dir for the storage with permissions for owner only.
      rc = file::mkdir(storage_dir, fs::perms::owner_all);
      if (rc != rc::SUCCESS) {
        return rc;
      }
    }

    /// use port number as identity on the server. (cmd option overrides value
    /// from config)
    port_t const port{cmd_opts.count("port") ? cmd_opts["port"].as<port_t>()
                                             : clbrd::cfg::port};

    // for (;;) {
    //   // TODO: accept incoming connection
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
#endif  // CLBRD_CATCH_THEM_ALL
  }
  return rc::SUCCESS;
}

}  // namespace wndx::clbrd
