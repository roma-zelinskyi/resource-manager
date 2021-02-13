/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <cstdint>
#include <forward_list>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace rm {

class ResourceManager
{
public:
    /*!
     * Creates an object with maximum capacity of resources.
     */
    explicit ResourceManager(std::uint32_t capacity);

    ResourceManager(const ResourceManager& rhs) = delete;
    ResourceManager(ResourceManager&& rhs);

    ResourceManager& operator=(const ResourceManager& rhs) = delete;
    ResourceManager& operator=(ResourceManager&& rhs);

    ~ResourceManager() noexcept;

    /*!
     * Attach a given user to resources manager with given number of capacity per user.
     */
    void attachUser(
        const std::string& user,
        std::uint32_t userCapacity = std::numeric_limits<std::uint32_t>::infinity());

    /*!
     * Detach a given user from resources manager.
     */
    void detachUser(const std::string& user);

    /*!
     * Allocate the resource for given user.
     */
    std::string allocate(const std::string& userName);

    /*!
     * Deallocates the given resource.
     */
    void deallocate(const std::string& resourceId);

    /*!
     * List all allocated resources for the given user.
     */
    std::forward_list<std::string> listUserResources(const std::string& userName);

    /*!
     * List all resources managed by resource manger.
     */
    std::forward_list<std::pair<std::string, std::string>> listResources();

    /*!
     * Returns true if the resource manager has available capacity for allocation.
     */
    [[nodiscard]] bool hasCapacity() const noexcept;

    /*!
     * Returns true if given user hasn't reached its maximum capacity for allocation.
     */
    [[nodiscard]] bool hasUserCapacity(const std::string& userName) const noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace rm

