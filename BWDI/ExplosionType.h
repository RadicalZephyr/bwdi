#pragma once

#include <Util\StaticString.h>

namespace BWDI
{
  struct ExplosionType
  {
    int id;
    Util::StaticString<32> name;
  };
}
