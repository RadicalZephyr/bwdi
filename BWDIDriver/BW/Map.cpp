#include "Map.h"
#include "TileSet.h"
#include "TileType.h"
#include "MiniTileFlags.h"

#include "Offsets.h"
#include <Util\Exceptions.h>

namespace BW
{
  namespace Map
  {
    BW::ActiveTile &getActiveTile(int x, int y)
    {
      if(!BW::BWDATA_ActiveTileArray)
        throw GeneralException(__FUNCTION__ ": BWDATA_ActiveTileArray not initialized");

      BW::ActiveTile *bwMap = BW::BWDATA_ActiveTileArray;
      return bwMap[BW::BWDATA_MapSize->x * y + x];
    }

    u16 getMiniTile(int x, int y)
    {
      if(!BW::BWDATA_MiniTileFlags)
        return 0;

      int tx = x / 4;
      int ty = y / 4;
      int mx = x % 4;
      int my = y % 4;

      // get the tile type ID
      BW::TileID tileTypeID = BW::BWDATA_MapTileArray[tx + ty * Map::getWidth()];

      // TileID consists of a tile type and mini tile ID.
      // each tile type has 16 mini tiles

      // get tile type
      BW::TileType* tileType = BW::TileSet::getTileType(tileTypeID);

      if(!tileType)
        return 0;

      // get mini tile type. there 16 mini tiles of a certain mini tile type
      u16 miniTileBlockID = tileType->miniTile[tileTypeID & 0xF];

      return BW::BWDATA_MiniTileFlags->tile[miniTileBlockID].miniTile[mx + my*4];
    }

    bool isVisible(int x, int y, int playerID)
    {
      return !(getActiveTile(x, y).bVisibilityFlags & (1 << playerID));
    }

    bool isExplored(int x, int y, int playerID)
    {
      return !(getActiveTile(x, y).bExploredFlags & (1 << playerID));
    }

    bool isBuildable(int x, int y)
    {
      return getActiveTile(x, y).bAlwaysUnbuildable == 0;
    }

    bool hasCreep(int x, int y)
    {
      return getActiveTile(x, y).bTemporaryCreep != 0;
    }

    bool isWalkable(int x, int y)
    {
      return getMiniTile(x, y) & BW::MiniTileFlags::Walkable;
    }

    int groundHeight(int x, int y)
    {
      return getActiveTile(x, y).bGroundHeight;
    }

    int getWidth()
    {
      return BW::BWDATA_MapSize->x;
    }

    int getHeight()
    {
      return BW::BWDATA_MapSize->y;
    }

    int getHash()
    {
      /*
      unsigned char hash[20];
      char hexstring[42];
      std::string filename = Map::getPathName();

      // Open File
      HANDLE hFile = NULL;
      if ( !SFileOpenFileEx(NULL, filename.c_str(), SFILE_FROM_ABSOLUTE, &hFile) || !hFile)
      {
        char szPath[MAX_PATH];
        SStrCopy(szPath, filename.c_str(), MAX_PATH);
        SStrNCat(szPath, "\\staredit\\scenario.chk", MAX_PATH);
        if ( !SFileOpenFileEx(NULL, szPath, SFILE_FROM_MPQ, &hFile) || !hFile)
          return std::string("Error_map_cannot_be_opened");
      }

      // Obtain file size
      DWORD dwFileSize = SFileGetFileSize(hFile, 0);

      // Allocate memory
      void *pBuffer = SMAlloc(dwFileSize);
      if ( !pBuffer )
      {
        SFileCloseFile(hFile);
        return std::string("Error_could_not_allocate_memory");
      }

      // Read file
      DWORD dwBytesRead = 0;
      SFileReadFile(hFile, pBuffer, dwFileSize, &dwBytesRead, 0);

      // Calculate hash
      sha1::calc(pBuffer, dwBytesRead, hash);
      sha1::toHexString(hash, hexstring);

      // Free memory and return
      SMFree(pBuffer);
      SFileCloseFile(hFile);
      return string(hexstring);
      */
      return 0;
    }
  };
};
