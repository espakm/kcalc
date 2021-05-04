FROM alpine:3.13 AS build

RUN apk --no-cache add \
        cmake \
        make \
        g++ \
        bash

COPY . /src
WORKDIR /src/build

RUN cmake .. \
 && make \
 && ctest \
 && strip apps/kcalc


FROM alpine:3.13

RUN apk --no-cache add libstdc++

COPY --from=build /src/build/apps/kcalc /usr/bin/

ENTRYPOINT ["/usr/bin/kcalc"]
