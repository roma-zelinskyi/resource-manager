/**
 *  Project  Resource Manger
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include <gtest/gtest.h>

#include <string>

#include "allocator.hpp"

namespace {

TEST(ResourceManagerTests, AllocatorOneResourceAllocatedTest)
{
    const auto expectedId = "rs1";
    auto alc = rm::Allocator{};
    auto id = alc.allocate();

    EXPECT_EQ(id, expectedId);
}

TEST(ResourceManagerTests, AllocatorMultiResourcesAllocatedTest)
{
    const auto expectedId = "rs4";
    auto alc = rm::Allocator{};
    alc.allocate();
    alc.allocate();
    alc.allocate();
    auto id = alc.allocate();

    EXPECT_EQ(id, expectedId);
}

} // namespace

