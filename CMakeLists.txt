cmake_minimum_required (VERSION 2.6)

# All executables
project (BankingAppClient)
project (BankingAppServer)

file (GLOB CLIENT_MAIN client/client.cpp)
file (GLOB CLIENT_HEADERS client/*/*.h)
file (GLOB CLIENT_SOURCES client/*/*.cpp)
add_executable (BankingAppClient ${CLIENT_MAIN} ${CLIENT_HEADERS} ${CLIENT_SOURCES} Sockets/CreateClient/ClientFunc.cpp Sockets/CreateClient/ClientFunc.h Sockets/Serialization/Serialize.cpp Sockets/Serialization/Serialize.h)

file (GLOB SERVER_MAIN server/server.cpp)
file (GLOB SERVER_HEADERS server/*/.h)
file (GLOB SERVER_SOURCES server/*/*.cpp)
add_executable (BankingAppServer ${SERVER_MAIN} ${SERVER_HEADERS} ${SERVER_SOURCES} Sockets/CreateServer/ServerFunc.cpp Sockets/CreateServer/ServerFunc.h Sockets/Serialization/Serialize.cpp Sockets/Serialization/Serialize.h)

# Dependencies

# Curses
find_package (Curses QUIET)

if (Curses_NOTFOUND)
    message(SEND_ERROR "Curses was not found!")
    if (WIN32)
        message(FATAL_ERROR "Install ncurses in cygwin and run from cygwin terminal")
    elseif (APPLE)
        message(FATAL_ERROR "Install with 'brew install ncurses'")
    elseif (UNIX)
        message(FATAL_ERROR "Install with 'apt install ncurses-base'")
    endif(WIN32)
    message(FATAL_ERROR "Can't determine how to install ncurses on your system")
endif(!Curses_NOTFOUND)

set (ADDITIONAL_LIBRARIES menu form)
include_directories (${CURSES_INCLUDE_DIR})
target_link_libraries (BankingAppClient ${CURSES_LIBRARIES} ${ADDITIONAL_LIBRARIES})
