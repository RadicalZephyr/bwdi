#include "SessionListing.h"

#include <Util\Types.h>
#include <Util\Mutex.h>
#include <Util\SharedStructure.h>
#include <Util\Exceptions.h>

namespace SessionListing
{
  // --------------------------------- OBJECTS ---------------------------------------------------
  Util::Mutex globalMutex("Global\\BWDI_SessionListingMutex");
  Util::SharedStructure<GlobalData> globalStructure;

  bool isInitialized = 0;

  // --------------------------------- FUNCTIONS -------------------------------------------------
  void init()
  {
    if(isInitialized)
      return;
    { // interlocked
      Util::Mutex::Lock listingLock(globalMutex);

      bool alreadyExisted = !globalStructure.create("Global\\BWDI_SessionListingData");
      if(!alreadyExisted)
      {
        // we were the first to create it, initialize it
        for(int i = 0; i < entryCount; i++)
        {
          globalStructure.get().entries[i].busy = false;
        }
        globalStructure.get().guidCounter = GetTickCount();
      }
    } // interlocked
    isInitialized = true;
  }

  void query(std::set<EntryData> &out)
  {
    out.clear();
    if(!isInitialized)
      throw GeneralException(__FUNCTION__ ": SessionListing not initialized");
    { // interlocked
      Util::Mutex::Lock listingLock(globalMutex);
      // check each entry if it's still valid
      // copy the entries
    }
  }

  // --------------------------------- ENTRY CLASS -----------------------------------------------
  Entry::Entry()
    : sessionGUID(0), sessionID(0)
  {
  }

  Entry::~Entry()
  {
    unregister();
  }

  void Entry::unregister()
  {
    if(!sessionGUID)
      return;
  }

  void Entry::registerSession(EntryData &entryData)
  {
    if(!isInitialized)
      throw GeneralException("session listing not initialized");
  }

  int Entry::getGUID() const
  {
    return sessionGUID;
  }
}
