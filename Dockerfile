FROM ubuntu:20.04 AS build

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y \
        cmake \
        g++

COPY . /src
WORKDIR /build

RUN cmake /src \
 && make \
 && cp apps/kcalc /usr/bin/kcalc \
 && strip /usr/bin/kcalc


FROM ubuntu:20.04

COPY --from=build /usr/bin/kcalc /usr/bin/

ENTRYPOINT ["/usr/bin/kcalc"]
