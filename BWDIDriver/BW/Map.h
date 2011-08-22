#pragma once

namespace BW
{
  namespace Map
  {
    bool isVisible(int x, int y, int PlayerID);
    bool isExplored(int x, int y, int PlayerID);
    bool isBuildable(int x, int y);
    bool hasCreep(int x, int y);
    bool isWalkable(int x, int y);
    int groundHeight(int x, int y);
    int getHash();
    int getWidth();
    int getHeight();
  };
};
