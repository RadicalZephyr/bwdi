#pragma once

//
// The binary loader is a buffer with loading and saving capabilities.
// It throws if something goes wrong
//

#include <windows.h>

class BinaryLoader
{
public:
  BinaryLoader();
  ~BinaryLoader();

  void release();
  void loadFromFile(const char* filename);
  void loadFromResource(WORD resourceID);
  void saveToFile(const char* filename);

  BYTE *buffer;
  int bufferSize;

private:
  bool isBufferOwned;
};
