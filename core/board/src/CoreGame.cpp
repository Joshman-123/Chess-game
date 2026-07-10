#include <CoreGame.hpp>
#include <iostream>
namespace core
{
    CoreGame::CoreGame()
    {
    }
    CoreGame::~CoreGame()
    {
    }
    CoreRetType CoreGame::Run()
    {
        std::cout<<"Starting Main Loop\n";
        return CoreRetType::SUCESS;
    }
}