#include <BW\Unit.h>
#include <BW\PlayerID.h>

#include <Util\MemoryFrame.h>
#include <Util\Exceptions.h>

namespace BWDI
{
  namespace Engine
  {
    void onMatchFrame();
    void onMenuFrame();
    void onMatchEnd();
    void onUnitKilled(BW::Unit* unit);
    void onDllLoad();
    void onMessageIntercepted(const char* text);
    void onMatchDrawHigh();
    bool onIssueCommand(Util::MemoryFrame command);
    void onException(const char* text);
  }
}

void BWCLBK_OnGameEnd()
{
  try
  {
    BWDI::Engine::onMatchEnd();
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
};

void BWCLBK_Update()
{
  try
  {
    BWDI::Engine::onMatchFrame();
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
};

void BWCLBK_OnSaveGame(const char* saveFilePath)
{
};

void BWCLBK_OnReceiveText(BW::PlayerID fromPlayer, const char* text)
{
  try
  {
    BWDI::Engine::onMessageIntercepted(text);
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
};

bool BWCLBK_OnMatchDraw()
{
  try
  {
    BWDI::Engine::onMatchDrawHigh();
    return true;
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
  return false;
};

void BWCLBK_OnMenuFrame()
{
  try
  {
    BWDI::Engine::onMenuFrame();
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
};

bool BWCLBK_OnIssueCommand(BYTE *buffer, DWORD length)
{
  try
  {
    return BWDI::Engine::onIssueCommand(Util::MemoryFrame(buffer, length));
  }
  catch(GeneralException &e)
  {
    BWDI::Engine::onException(e.getMessage());
  }
  catch(std::exception &e)
  {
    BWDI::Engine::onException(e.what());
  }
  return true;
}
