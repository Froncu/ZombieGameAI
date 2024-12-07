#ifndef HOUSE_INFO_COMPARATOR_HPP
#define HOUSE_INFO_COMPARATOR_HPP

#include "pch.hpp"

#include "RoundedVectorComparator.hpp"

namespace ai
{
   struct HouseInfoComparator final
   {
      [[nodiscard]] bool operator()(HouseInfo const house_info1, HouseInfo const house_info2) const
      {
         RoundedVectorComparator constexpr comparator{};
         return comparator(house_info1.Center, house_info2.Center);
      }
   };
}

#endif