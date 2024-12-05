#ifndef ROUNDED_VECTOR_COMPARATOR_HPP
#define ROUNDED_VECTOR_COMPARATOR_HPP

#include "pch.hpp"

namespace ai
{
   struct RoundedVectorComparator final
   {
      [[nodiscard]] bool operator()(Elite::Vector2 vector1, Elite::Vector2 vector2) const
      {
         vector1.x = std::round(vector1.x);
         vector1.y = std::round(vector1.y);

         vector2.x = std::round(vector2.x);
         vector2.y = std::round(vector2.y);

         return vector1 == vector2;
      }
   };
}

#endif