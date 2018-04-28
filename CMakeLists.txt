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
find_package (Curses REQUIRED)
set (ADDITIONAL_LIBRARIES menu form)
include_directories (${CURSES_INCLUDE_DIR})
target_link_libraries (BankingAppClient ${CURSES_LIBRARIES} ${ADDITIONAL_LIBRARIES})
