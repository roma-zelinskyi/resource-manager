/**
 *  Project  Resource Manager
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "error.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace rm {

Error::Error(const std::string& msg, ErrorCode code)
    : std::runtime_error{msg}
    , _code{code}
{
}

ErrorCode Error::code() const noexcept
{
    return _code;
}

} // namespace rm

