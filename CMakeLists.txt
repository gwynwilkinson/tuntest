cmake_minimum_required(VERSION 3.13)
project(vpntest C)

set(CMAKE_C_STANDARD 11)

add_executable(vpnclient vpnclient.c)
add_executable(vpnserver vpnserver.c)
