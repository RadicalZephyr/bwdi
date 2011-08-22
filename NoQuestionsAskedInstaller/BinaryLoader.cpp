#include "BinaryLoader.h"

#include <stdio.h>
#include <io.h>
#include <stdexcept>

BinaryLoader::BinaryLoader()
  : isBufferOwned(false)
{
}

BinaryLoader::~BinaryLoader()
{
  release();
}

 void BinaryLoader::release()
 {
  if(isBufferOwned)
    free(buffer);
 }

void BinaryLoader::loadFromFile(const char* filename)
{
  release();
  FILE *fileHandle = fopen(filename, "rb");
  if(!fileHandle)
    throw std::runtime_error("could not find file");
  bufferSize = _filelength(_fileno(fileHandle));
  buffer = (BYTE*)calloc(1, bufferSize);
  fread(buffer, bufferSize, 1, fileHandle);
  fclose(fileHandle);
}

void BinaryLoader::loadFromResource(WORD resourceID)
{
  release();
  HRSRC resourceInfo = FindResource(NULL, MAKEINTRESOURCE(resourceID), NULL);
  HGLOBAL resourceHandle = LoadResource(NULL, resourceInfo);
  char* buffer = (char*) LockResource(resourceHandle);
  bufferSize = SizeofResource(NULL, resourceInfo);
}
 
void BinaryLoader::saveToFile(const char* filename)
{
  FILE *fileHandle = fopen(filename, "wb");
  if(!fileHandle)
    throw std::runtime_error("could not save file");
  fwrite(buffer, bufferSize, 1, fileHandle);
  fclose(fileHandle);
}
