FROM kcalc AS kcalc

FROM alpine:3.13

RUN apk --no-cache add \
        libstdc++ \
        python3 \
        py3-pip \
 && pip install falcon gunicorn

COPY kcalc /kcalc-server/kcalc

COPY --from=kcalc /usr/bin/kcalc /usr/bin/

WORKDIR /kcalc-server

RUN pwd && python3 -m unittest discover

CMD ["gunicorn", "-b", "0.0.0.0:8000", "kcalc.app"]
