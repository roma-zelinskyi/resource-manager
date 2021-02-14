FROM ubuntu

RUN apt-get update && apt-get -y install cmake protobuf-compiler \
    -y ninja-build \
    -y clang \
    -y libgtest-dev

RUN cd /usr/src/gtest \
    cmake CMakeLists.txt \
    make \
    make install

WORKDIR /proj

CMD bash
