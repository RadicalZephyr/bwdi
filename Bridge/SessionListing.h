#pragma once

#include <BWDI.h>
#include <set>

namespace SessionListing
{
  // --------------------------------- TYPEDEFS --------------------------------------------------
  const int entryCount = 31;
  typedef union
  {
    struct
    {
      bool32 busy;
      u32 guid;
      BWDI::SessionInfo sessionInfo;
    };
    u8  _reserved[128];
  } EntryData;
  typedef struct
  {
    u32 guidCounter;
    EntryData entries[entryCount];
  } GlobalData;

  // --------------------------------- FUNCTIONS -------------------------------------------------
  void init();
  void query(std::set<EntryData> &out);

  class Entry
  {
  public:
    Entry();
    ~Entry();
    void registerSession(EntryData &entryData);
    void unregister();
    int getGUID() const;
  private:
    int sessionID;
    int sessionGUID;
  };
}
