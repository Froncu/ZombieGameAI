#ifndef HOUSE_INFO_HASHER_HPP
#define HOUSE_INFO_HASHER_HPP

#include "pch.hpp"

#include "RoundedVectorHasher.hpp"

namespace ai
{
   struct HouseInfoHasher final
   {
      [[nodiscard]] std::size_t operator()(HouseInfo const house_info) const
      {
         RoundedVectorHasher constexpr hasher{};
         return hasher(house_info.Center);
      }
   };
}

#endif