/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <cstdint>
#include <string>

namespace rm {

class Allocator
{
public:
    constexpr Allocator()
        : _id{1}
    {
    }

    std::string allocate();

private:
    std::uint32_t _id;
};

} // namespace rm

