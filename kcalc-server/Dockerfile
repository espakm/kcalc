FROM kcalc AS kcalc

FROM alpine:3.13

RUN apk --no-cache add \
        libstdc++ \
        python3 \
        py3-pip \
 && pip install falcon gunicorn

COPY . /web-service/

COPY --from=kcalc /usr/bin/kcalc /usr/bin/

WORKDIR /web-service
CMD ["gunicorn", "-b", "0.0.0.0:8000", "kcalc.app"]
