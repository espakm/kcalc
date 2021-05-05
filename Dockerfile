FROM alpine:3.13 AS build

RUN apk --no-cache add \
        cmake \
        make \
        g++ \
        bash

COPY 3rd_party /src/3rd_party
COPY apps /src/apps
COPY libs /src/libs
COPY tests /src/tests
COPY CMakeLists.txt /src/

WORKDIR /src/build

RUN cmake .. \
 && make \
 && ctest \
 && strip apps/kcalc


FROM alpine:3.13

RUN apk --no-cache add libstdc++

COPY --from=build /src/build/apps/kcalc /usr/bin/

ENTRYPOINT ["/usr/bin/kcalc"]
