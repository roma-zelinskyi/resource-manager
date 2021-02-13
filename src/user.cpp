/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "user.hpp"

#include <cstdint>
#include <limits>
#include <string>
#include <unordered_set>

#include "error.hpp"

namespace rm {

User::User(const std::uint32_t capacity)
    : _capacity{capacity}
    , _resources{}
{
}

void User::addResource(const std::string& resource)
{
    if (_capacity == std::numeric_limits<std::uint32_t>::infinity())
        _resources.insert(resource);
    else {
        if (_capacity == 0)
            throw Error{"No capacity left for given user", ErrorCode::NoUserCapacity};

        _resources.insert(resource);
        --_capacity;
    }
}

void User::removeResource(const std::string& resource)
{
    _resources.erase(resource);

    if (_capacity == std::numeric_limits<std::uint32_t>::infinity())
        return;

    ++_capacity;
}

std::uint32_t User::capacity() const noexcept
{
    return _capacity;
}

const std::unordered_set<std::string>& User::resources() const noexcept
{
    return _resources;
}

} // namespace rm
