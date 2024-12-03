#ifndef HOUSE_CORNER_HASHER_HPP
#define HOUSE_CORNER_HASHER_HPP

#include "pch.hpp"

namespace ai
{
   struct HouseCornerHasher final
   {
      std::size_t operator()(Elite::Vector2 const house_corner) const
      {
         std::hash<float> constexpr hasher{};
         std::size_t const hash_x{ hasher(std::round(house_corner.x)) };
         std::size_t const hash_y{ hasher(std::round(house_corner.y)) };

         return hash_x ^ (hash_y << 1);
      }
   };
}

#endif