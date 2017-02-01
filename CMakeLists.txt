cmake_minimum_required(VERSION 3.6)
project(pooker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Card.cpp Card.h
        CardDeck.cpp CardDeck.h
        Hand.cpp Hand.h
        GameRound.cpp GameRound.h
        Player.cpp Player.h utils.h BotPlayer.cpp BotPlayer.h Game.cpp Game.h)

add_executable(pooker ${SOURCE_FILES})

set(TEST_FILES
        tests.cpp
        Card.cpp Card.h
        CardDeck.cpp CardDeck.h
        Hand.cpp Hand.h
        GameRound.cpp GameRound.h
        Player.cpp Player.h BotPlayer.cpp BotPlayer.h Game.cpp Game.h)
add_executable(tests ${TEST_FILES})