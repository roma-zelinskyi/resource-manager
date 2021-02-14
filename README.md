# resource-manager
## Description
The ResourceManger provides the possibility to manage resources for the given users. The users can be attached to ResourceManger in order to manage allocated resources. Resource manager provides small and easy to use API that would make it a lot easier for users to track allocated resources.

## Build
```bash
cmake -B<folder> -H. -G<build system> -DCMAKE_BUILD_TYPE=<type>
cmake --build build -- -j`nproc`
```
**Example**

```bash
cmake -Bbuild -H. -GNinja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```
**Build using Docker**
```bash
docker build -t rm ./
docker run --privileged -ti -v $(pwd):/proj rm
cmake -Bbuild -H. -GNinja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```
## Tests
**Run tests**
```bash
cmake --build build --target tests
build/bin/unit-tests
```
## Examples
```cpp
/// main.cpp

#include <resource_manger.hpp>

int main()
{
  auto rm = rm::ResourceManager{10};
  rm.attachUser("user_1", 5);
  const auto rsId1 = rm.allocate("user_1");
  const auto rsId2 = rm.allocate("user_1");
  rm.deallocate(rsId1);
}
```
