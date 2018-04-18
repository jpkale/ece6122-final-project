cmake_minimum_required (VERSION 2.6)

# All executables
project (BankingAppClient)
project (BankingAppServer)

add_executable (BankingAppClient client/client.cpp)
add_executable (BankingAppServer server/server.cpp server/encryption.cpp)
