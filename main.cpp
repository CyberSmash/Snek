#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
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

#define Y 0
#define X 1

namespace po = boost::program_options;
boost::log::sources::severity_logger< boost::log::trivial::severity_level > lg;
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

void setup_logging(std::string filename)
{
    /**
     * Set up the system-wide logger.
     */
    boost::log::add_common_attributes();
    boost::log::add_file_log(boost::log::keywords::file_name=filename, boost::log::keywords::format="[%TimeStamp%]: %Message%");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

}

int main(int argc, char* argv[])
{
    std::string enginelogfile = "./engine.log";
    po::options_description desc("Snek Command Line Options");
    desc.add_options()
            ("help", "Show help message")
            ("logfile", po::value<std::string>()->default_value("/tmp/engine.log"), "Set engine log file location and name.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    po::notify(vm);

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
    gameEngine = std::make_shared<Engine>(0);

    gameEngine->MainLoop();

    endwin();
    return 0;
}