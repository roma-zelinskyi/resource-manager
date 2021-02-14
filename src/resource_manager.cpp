/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "resource_manager.hpp"

#include <cstdint>
#include <forward_list>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "allocator.hpp"
#include "user.hpp"

namespace rm {

class ResourceManager::Impl
{
public:
    Impl(const std::uint32_t capacity)
        : _capacity{capacity}
        , _size{0}
        , _users{}
        , _usersLookup{}
        , _allocator{}
    {
    }

    void attachUser(const std::string& user, const std::uint32_t userCapacity)
    {
        _users.emplace(user, userCapacity);
    }

    void detachUser(const std::string& user)
    {
        _users.erase(user);
    }

    std::string allocate(const std::string& userName)
    {
        if (_size == _capacity)
            throw std::overflow_error{"Resource manger capacity overflow"};

        auto& resourceUser = _users.at(userName);

        if (resourceUser.availableCapacity() == 0)
            throw std::overflow_error{{"Capacity overflow for user: " + userName}};

        const auto resourceId = _allocator.allocate();
        resourceUser.addResource(resourceId);
        _usersLookup[resourceId] = userName;

        ++_size;

        return resourceId;
    }

    void deallocate(const std::string& resourceId)
    {
        const auto userName = _usersLookup.at(resourceId);
        auto& resourceUser = _users.at(userName);
        resourceUser.removeResource(resourceId);
        _usersLookup.erase(resourceId);
        --_size;
    }

    const std::unordered_set<std::string>& listUserResources(const std::string& userName) const
        noexcept
    {
        return _users.at(userName).resources();
    }

    std::forward_list<std::pair<std::string, std::string>> listResources()
    {
        auto resourceList = std::forward_list<std::pair<std::string, std::string>>{};

        for (const auto& [userName, user] : _users)
            for (const auto& resource : user.resources())
                resourceList.emplace_front(userName, resource);

        return resourceList;
    }

    bool hasCapacity() const noexcept
    {
        return _size != _capacity;
    }

    bool hasUserCapacity(const std::string& userName) const noexcept
    {
        return _users.at(userName).availableCapacity() > 0;
    }

private:
    std::uint32_t _capacity;
    std::uint32_t _size;
    std::unordered_map<std::string, User> _users;
    std::unordered_map<std::string, std::string> _usersLookup;
    Allocator _allocator;
};

ResourceManager::ResourceManager(std::uint32_t capacity)
    : _impl{std::make_unique<Impl>(capacity)}
{
}

ResourceManager::ResourceManager(ResourceManager&&) = default;
ResourceManager& ResourceManager::operator=(ResourceManager&&) = default;

ResourceManager::~ResourceManager() noexcept = default;

void ResourceManager::attachUser(const std::string& user, const std::uint32_t userCapacity)
{
    _impl->attachUser(user, userCapacity);
}

void ResourceManager::detachUser(const std::string& user)
{
    _impl->detachUser(user);
}

std::string ResourceManager::allocate(const std::string& userName)
{
    return _impl->allocate(userName);
}

void ResourceManager::deallocate(const std::string& resourceId)
{
    _impl->deallocate(resourceId);
}

const std::unordered_set<std::string>&
ResourceManager::listUserResources(const std::string& userName) const noexcept
{
    return _impl->listUserResources(userName);
}

std::forward_list<std::pair<std::string, std::string>> ResourceManager::listResources()
{
    return _impl->listResources();
}

[[nodiscard]] bool ResourceManager::hasCapacity() const noexcept
{
    return _impl->hasCapacity();
}

[[nodiscard]] bool ResourceManager::hasUserCapacity(const std::string& userName) const noexcept
{
    return _impl->hasUserCapacity(userName);
}

} // namespace rm

