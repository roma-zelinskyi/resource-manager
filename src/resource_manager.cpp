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
#include <utility>

namespace rm {

class ResourceManager::Impl
{
public:
    Impl(const std::uint32_t capacity)
        : _capacity{capacity}
        , _size{0}
    {
    }

    void attachUser(
        [[maybe_unused]] const std::string& user, [[maybe_unused]] const std::uint32_t userCapacity)
    {
    }

    void detachUser([[maybe_unused]] const std::string& user)
    {
    }

    std::string allocate([[maybe_unused]] const std::string& userName)
    {
        return {};
    }

    void deallocate([[maybe_unused]] const std::string& resourceId)
    {
    }

    std::forward_list<std::string> listUserResources([[maybe_unused]] const std::string& userName)
    {
        return {};
    }

    std::forward_list<std::pair<std::string, std::string>> listResources()
    {
        return {};
    }

    bool hasCapacity() const noexcept
    {
        return {};
    }

    bool hasUserCapacity([[maybe_unused]] const std::string& userName) const noexcept
    {
        return {};
    }

private:
    std::uint32_t _capacity;
    std::uint32_t _size;
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

std::forward_list<std::string> ResourceManager::listUserResources(const std::string& userName)
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

