/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "user.hpp"

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_set>

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
            throw std::overflow_error{"Capacity overflow for given user"};

        _resources.insert(resource);
        ++_size;
    }
}

void User::removeResource(const std::string& resource)
{
    if (!_resources.count(resource))
        throw std::invalid_argument({"No such resource: " + resource});

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
