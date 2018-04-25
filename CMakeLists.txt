cmake_minimum_required (VERSION 2.6)

# All executables
project (BankingAppClient)
project (BankingAppServer)

add_executable (BankingAppClient client/client.cpp account.h accountHolder.h account.cpp accountHolder.cpp)
add_executable (BankingAppServer server/server.cpp account.h account.cpp accountHolder.cpp)
