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

User::User()
    : _capacity{std::numeric_limits<std::uint32_t>::infinity()}
    , _size{0}
    , _resources{}
{
}

User::User(const std::uint32_t capacity)
    : _capacity{capacity}
    , _size{0}
    , _resources{}
{
}

void User::addResource(const std::string& resource)
{
    if (_capacity == std::numeric_limits<std::uint32_t>::infinity())
        _resources.insert(resource);
    else {
        if (_size == _capacity)
            throw Error{"No capacity left for given user", ErrorCode::NoUserCapacity};

        _resources.insert(resource);
        ++_size;
    }
}

void User::removeResource(const std::string& resource)
{
    if (!_resources.count(resource))
        throw Error({"No resource with ID: " + resource}, ErrorCode::NoResource);

    _resources.erase(resource);
    --_size;
}

std::uint32_t User::availableCapacity() const noexcept
{
    return _capacity - _size;
}

const std::unordered_set<std::string>& User::resources() const noexcept
{
    return _resources;
}

} // namespace rm
