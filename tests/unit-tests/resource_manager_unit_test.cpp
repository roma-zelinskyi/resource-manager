/**
 *  Project  Resource Manger
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "resource_manager.hpp"

using namespace std::string_literals;

namespace {

TEST(ResourceManagerTests, AllocateResourceTest)
{
    auto resourceMgr = rm::ResourceManager{10};

    const auto u1 = "u1"s;
    const auto u2 = "u2"s;
    resourceMgr.attachUser(u1, 5);
    resourceMgr.attachUser(u2, 3);

    auto r1 = std::string{};
    auto r2 = std::string{};
    auto r3 = std::string{};
    EXPECT_NO_THROW(r1 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r2 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r3 = resourceMgr.allocate(u2));

    const auto expectedU1Resources = std::unordered_set<std::string>{r1, r2};
    const auto expectedU2Resources = std::unordered_set<std::string>{r3};
    auto expectedResources =
        std::unordered_map<std::string, std::string>{{r1, u1}, {r2, u1}, {r3, u2}};

    EXPECT_EQ(resourceMgr.listUserResources(u1), expectedU1Resources);
    EXPECT_EQ(resourceMgr.listUserResources(u2), expectedU2Resources);

    for (const auto& it : resourceMgr.listResources()) {
        EXPECT_TRUE(expectedResources.count(it.second));
        EXPECT_EQ(expectedResources.at(it.second), it.first);
        expectedResources.erase(it.second);
    }

    EXPECT_TRUE(expectedResources.empty());
}

TEST(ResourceManagerTests, DeallocateResourceTest)
{
    auto resourceMgr = rm::ResourceManager{10};

    const auto u1 = "u1"s;
    const auto u2 = "u2"s;
    resourceMgr.attachUser(u1, 5);
    resourceMgr.attachUser(u2, 3);

    auto r1 = std::string{};
    auto r2 = std::string{};
    auto r3 = std::string{};
    auto r4 = std::string{};
    EXPECT_NO_THROW(r1 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r2 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r3 = resourceMgr.allocate(u2));

    EXPECT_NO_THROW(resourceMgr.deallocate(r2));
    EXPECT_NO_THROW(r4 = resourceMgr.allocate(u1));

    EXPECT_TRUE(resourceMgr.hasCapacity());
    EXPECT_TRUE(resourceMgr.hasUserCapacity(u1));
    EXPECT_TRUE(resourceMgr.hasUserCapacity(u2));

    const auto expectedU1Resources = std::unordered_set<std::string>{r1, r4};
    const auto expectedU2Resources = std::unordered_set<std::string>{r3};
    auto expectedResources =
        std::unordered_map<std::string, std::string>{{r1, u1}, {r3, u2}, {r4, u1}};

    EXPECT_EQ(resourceMgr.listUserResources(u1), expectedU1Resources);
    EXPECT_EQ(resourceMgr.listUserResources(u2), expectedU2Resources);

    for (const auto& it : resourceMgr.listResources()) {
        EXPECT_TRUE(expectedResources.count(it.second));
        EXPECT_EQ(expectedResources.at(it.second), it.first);
        expectedResources.erase(it.second);
    }

    EXPECT_TRUE(expectedResources.empty());
}

TEST(ResourceManagerTests, CapacityOverflowResourceTest)
{
    auto resourceMgr = rm::ResourceManager{3};

    const auto u1 = "u1"s;
    const auto u2 = "u2"s;
    resourceMgr.attachUser(u1, 5);
    resourceMgr.attachUser(u2, 3);

    auto r1 = std::string{};
    auto r2 = std::string{};
    auto r3 = std::string{};
    auto r4 = std::string{};
    EXPECT_NO_THROW(r1 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r2 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r3 = resourceMgr.allocate(u2));
    EXPECT_FALSE(resourceMgr.hasCapacity());
    EXPECT_ANY_THROW(r4 = resourceMgr.allocate(u2));
}

TEST(ResourceManagerTests, ReachUnreachFullCapacityTest)
{
    auto resourceMgr = rm::ResourceManager{3};

    const auto u1 = "u1"s;
    const auto u2 = "u2"s;
    resourceMgr.attachUser(u1, 5);
    resourceMgr.attachUser(u2, 3);

    auto r1 = std::string{};
    auto r2 = std::string{};
    auto r3 = std::string{};
    EXPECT_NO_THROW(r1 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r2 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r3 = resourceMgr.allocate(u2));

    EXPECT_FALSE(resourceMgr.hasCapacity());

    EXPECT_NO_THROW(resourceMgr.deallocate(r2));

    EXPECT_TRUE(resourceMgr.hasCapacity());
}

TEST(ResourceManagerTests, DetachUserTest)
{
    auto resourceMgr = rm::ResourceManager{3};

    const auto u1 = "u1"s;
    const auto u2 = "u2"s;
    resourceMgr.attachUser(u1, 5);
    resourceMgr.attachUser(u2, 3);

    auto r1 = std::string{};
    auto r2 = std::string{};
    auto r3 = std::string{};
    EXPECT_NO_THROW(r1 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r2 = resourceMgr.allocate(u1));
    EXPECT_NO_THROW(r3 = resourceMgr.allocate(u2));

    resourceMgr.detachUser(u1);

    EXPECT_ANY_THROW(resourceMgr.allocate(u1));
}

} // namespace

