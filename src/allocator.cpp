/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "allocator.hpp"

#include <cstdint>
#include <string>

using namespace std::string_literals;

namespace rm {

std::string Allocator::allocate()
{
    const auto resourcePrefix = "rs"s;
    const auto resourceId = resourcePrefix + std::to_string(_id);
    ++_id;

    return resourceId;
}

} // namespace rm

