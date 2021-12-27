#include "Core.h"

bool ACore::CoreInit()
{
    return true;
}
bool ACore::GameRun()
{
    CoreInit();
    while(WinRun())
    {
        CoreFrame();
        CoreRender();
    }
    CoreRelease();
    return true;
}
bool ACore::CoreFrame()
{
    return true;
}
bool ACore::CoreRender()
{
    return true;
}
bool ACore::CoreRelease()
{
    return true;
}
