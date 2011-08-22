#pragma once

#include <Util\MemoryFrame.h>
#include <Util\Types.h>
#include "..\..\BWDIDriver\BW\storm.h"

//
// The Network interface separates the Storm stuff from pure networking
//

namespace SNP
{
  const int PACKET_SIZE = 500;

  struct NetworkInfo
  {
    char          *pszName;
    DWORD         dwIdentifier;
    char          *pszDescription;
    CAPS          caps;
  };

  typedef ::BinPeerID BinPeerID;

  extern void passAdvertisement(const BinPeerID& host, Util::MemoryFrame ad);
  extern void removeAdvertisement(const BinPeerID& host);
  extern void passPacket(const BinPeerID& host, Util::MemoryFrame packet);

  template<typename PEERID>
  class Network
  {
  public:
    Network()
    {
    }
    virtual ~Network()
    {
    }

    BinPeerID makeBin(const PEERID& src)
    {
      BinPeerID retval;
      memcpy_s(&retval, sizeof(BinPeerID), &src, sizeof(PEERID));
      memset(((BYTE*)&retval)+sizeof(PEERID), 0, sizeof(BinPeerID) - sizeof(PEERID));
      return retval;
    }

    // callback functions that take network specific arguments and cast them away
    void passAdvertisement(const PEERID& host, Util::MemoryFrame ad)
    {
      SNP::passAdvertisement(makeBin(host), ad);
    }
    void removeAdvertisement(const PEERID& host)
    {
      SNP::removeAdvertisement(makeBin(host));
    }
    void passPacket(const PEERID& host, Util::MemoryFrame packet)
    {
      SNP::passPacket(makeBin(host), packet);
    }

    // network plug functions
    virtual void initialize() = 0;
    virtual void destroy() = 0;
    virtual void requestAds() = 0;
    virtual void sendAsyn(const PEERID& to, Util::MemoryFrame packet) = 0;
    virtual void receive() = 0;
    virtual void startAdvertising(Util::MemoryFrame ad) = 0;
    virtual void stopAdvertising() = 0;
  };

  typedef Network<BinPeerID> BinNetwork;
}
