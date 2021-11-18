cmake_minimum_required(VERSION 3.19)
project(blackjack)

set(CMAKE_CXX_STANDARD 14)

add_executable(blackjack blackjack.cpp deck.cpp player.cpp hand.cpp)