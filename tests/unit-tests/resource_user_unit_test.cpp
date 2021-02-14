/**
 *  Project  Resource Manger
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "user.hpp"

namespace {

TEST(ResourceManagerTests, ResourceUserAddResourceTest)
{
    auto resourceUser = rm::User{5};

    EXPECT_NO_THROW(resourceUser.addResource("r1"));
    EXPECT_EQ(resourceUser.availableCapacity(), 4);
    EXPECT_EQ(resourceUser.resources().size(), 1);

    EXPECT_NO_THROW(resourceUser.addResource("r2"));
    EXPECT_NO_THROW(resourceUser.addResource("r3"));

    EXPECT_EQ(resourceUser.availableCapacity(), 2);
    EXPECT_EQ(resourceUser.resources().size(), 3);
}

TEST(ResourceManagerTests, ResourceUserRemoveResourceTest)
{
    auto resourceUser = rm::User{5};

    EXPECT_NO_THROW(resourceUser.addResource("r1"));
    EXPECT_NO_THROW(resourceUser.addResource("r2"));
    EXPECT_EQ(resourceUser.availableCapacity(), 3);
    EXPECT_EQ(resourceUser.resources().size(), 2);

    EXPECT_NO_THROW(resourceUser.removeResource("r2"));

    EXPECT_EQ(resourceUser.availableCapacity(), 4);
    EXPECT_EQ(resourceUser.resources().size(), 1);
}

TEST(ResourceManagerTests, ResourceUserInfinitCapacityTest)
{
    auto resourceUser = rm::User{std::numeric_limits<std::uint32_t>::infinity()};

    for (auto i = 0; i < 10000; ++i)
        EXPECT_NO_THROW(resourceUser.addResource({"r" + std::to_string(i)}));
}

TEST(ResourceManagerTests, ResourceUserCapacityOverflowTest)
{
    auto resourceUser = rm::User{3};
    EXPECT_NO_THROW(resourceUser.addResource("r1"));
    EXPECT_NO_THROW(resourceUser.addResource("r2"));
    EXPECT_NO_THROW(resourceUser.addResource("r3"));

    EXPECT_ANY_THROW(resourceUser.addResource("r4"));
}

TEST(ResourceManagerTests, ResourceUserInvalidResourceTest)
{
    auto resourceUser = rm::User{2};

    EXPECT_NO_THROW(resourceUser.addResource("r4"));
    EXPECT_ANY_THROW(resourceUser.removeResource("r2"));
}

} // namespace

