cmake_minimum_required(VERSION 3.6)
project(pooker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Card.cpp Card.h CardDeck.cpp CardDeck.h Hand.cpp Hand.h)
#        Presenter.cpp Presenter.h GameRound.cpp GameRound.h Player.cpp Player.h )
add_executable(pooker ${SOURCE_FILES})