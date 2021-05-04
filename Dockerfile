FROM alpine:3.13 AS build

RUN apk --no-cache add \
        cmake \
        make \
        g++

COPY . /src
WORKDIR /build

RUN cmake /src \
 && make \
 && cp apps/kcalc /usr/bin/kcalc \
 && strip /usr/bin/kcalc


FROM alpine:3.13

RUN apk --no-cache add libstdc++

COPY --from=build /usr/bin/kcalc /usr/bin/

ENTRYPOINT ["/usr/bin/kcalc"]
