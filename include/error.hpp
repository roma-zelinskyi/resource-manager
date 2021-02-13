/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <cstdint>
#include <stdexcept>
#include <string>

namespace rm {

enum class ErrorCode : std::uint8_t
{
    NoError,
    NoResource,
    NoUserCapacity,
    NoCapacity,
};

class Error : public std::runtime_error
{
public:
    explicit Error(const std::string& msg, ErrorCode code);

    ErrorCode code() const noexcept;

private:
    ErrorCode _code;
};

} // namespace rm
