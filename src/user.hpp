/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <cstdint>
#include <string>
#include <unordered_set>

namespace rm {

class User
{
public:
    User();
    explicit User(std::uint32_t capacity);

    void addResource(const std::string& resource);
    void removeResource(const std::string& resource);

    std::uint32_t availableCapacity() const noexcept;

    const std::unordered_set<std::string>& resources() const noexcept;

private:
    std::uint32_t _capacity;
    std::uint32_t _size;
    std::unordered_set<std::string> _resources;
};

} // namespace rm
