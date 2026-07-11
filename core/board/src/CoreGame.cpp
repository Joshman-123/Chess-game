#include <CoreGame.hpp>
#include <iostream>
#include "Logger.hpp"
#include <RenderFactory.hpp>
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
        render::RenderConfig l_renderCfg{};
        l_renderCfg.m_renderType = "OpenGL";
        l_renderCfg.m_windowName = "TEST GAME";
        l_renderCfg.m_height = 864;
        l_renderCfg.m_width = 1024;
        l_renderCfg.m_samples = 4;

        const auto l_infOrErr = render::RenderFactory::create(l_renderCfg);

        if(not l_infOrErr.has_value())
        {
            LOG_ERROR("Error %d\n", l_infOrErr.error());
        }

        l_infOrErr.value()->execute();
        return CoreRetType::SUCESS;
    }
}