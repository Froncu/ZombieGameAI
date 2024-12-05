#ifndef ROUNDED_VECTOR_COMPARATOR_HPP
#define ROUNDED_VECTOR_COMPARATOR_HPP

#include "pch.hpp"

namespace ai
{
   struct RoundedVectorComparator final
   {
      [[nodiscard]] bool operator()(Elite::Vector2 house_corner1, Elite::Vector2 house_corner2) const
      {
         house_corner1.x = std::round(house_corner1.x);
         house_corner1.y = std::round(house_corner1.y);

         house_corner2.x = std::round(house_corner2.x);
         house_corner2.y = std::round(house_corner2.y);

         return house_corner1 == house_corner2;
      }
   };
}

#endif