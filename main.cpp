#include <boost/program_options.hpp>

#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <chrono>
#include <thread>
#include "GameObjects/Snake.h"
#include "Engine/InputRouter.h"
#include "GameObjects/Food.h"
#include <random>
#include <time.h>
#include "Engine/Engine.h"
#include "GameObjects/GameRunner.h"
#include "Engine/AudioEngine.h"
#include <memory>

#define MINIMUM_Y_NEEDED 40
#define MINIMUM_X_NEEDED 80

namespace po = boost::program_options;
boost::log::sources::severity_logger< boost::log::trivial::severity_level > lg;


/**
 * Set up the ncurses screen.
 */
void setup_screen()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);
    start_color();
}

/**
 * Initialize logging to the disk.
 *
 * @param filename The file to log to. This can be set on the command line.
 */
void setup_logging(std::string filename)
{
    /**
     * Set up the system-wide logger.
     */
    boost::log::add_common_attributes();
    boost::log::add_file_log(boost::log::keywords::file_name=filename, boost::log::keywords::format="[%TimeStamp%]: %Message%");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

/**
 * A helper function for simply getting the command line parameters.
 *
 * @param argc Number of arguments as passed to main.
 * @param argv The arguments as passed to main.
 * @param desc The description object passed as a reference
 * @param vm THe variable map that will store our variable values.
 */
void get_args(int argc, char* argv[], po::options_description& desc, po::variables_map& vm)
{

    desc.add_options()
            ("help", "Show help message")
            ("logfile", po::value<std::string>()->default_value("/tmp/engine.log"), "Set engine log file location and name.");

    po::store(po::parse_command_line(argc, argv, desc), vm);

    po::notify(vm);
}

int main(int argc, char* argv[])
{
    std::string enginelogfile = "./engine.log";

    po::options_description desc("Snek Command Line Options");
    po::variables_map vm;
    get_args(argc, argv, desc, vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("logfile"))
    {
        enginelogfile = vm["logfile"].as<std::string>();
    }


    setup_logging(enginelogfile);

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "I'm alive!";

    // after this point stdscr is now available as well as
    setup_screen();

    // Check that stdscr is the minimum size.
    if (getmaxy(stdscr) <= MINIMUM_Y_NEEDED || getmaxx(stdscr) <= MINIMUM_X_NEEDED)
    {
        endwin();
        std::cout << "Your terminal size is only " << getmaxx(stdscr) << " columns wide and "
        << getmaxy(stdscr) << " rows high. You need a minimum of " << MINIMUM_X_NEEDED << " columns and " << MINIMUM_Y_NEEDED
        << " lines hight." << std::endl;

        return 0;
    }

    gameEngine = std::make_shared<Engine>(0);

    gameEngine->MainLoop();

    endwin();
    return 0;
}