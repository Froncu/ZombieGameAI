#ifndef ROUNDED_VECTOR_HASHER_HPP
#define ROUNDED_VECTOR_HASHER_HPP

#include "pch.hpp"

namespace ai
{
   struct RoundedVectorHasher final
   {
      [[nodiscard]] std::size_t operator()(Elite::Vector2 const vector) const
      {
         std::hash<float> constexpr hasher{};
         std::size_t const hash_x{ hasher(std::round(vector.x)) };
         std::size_t const hash_y{ hasher(std::round(vector.y)) };

         return hash_x ^ (hash_y << 1);
      }
   };
}

#endif