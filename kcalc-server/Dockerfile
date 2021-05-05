FROM kcalc AS kcalc-cl

FROM alpine:3.13

RUN apk --no-cache add \
        python3 \
        py3-pip \
 && pip install falcon gunicorn

COPY . /web-service/

COPY --from=kcalc-cl /usr/bin/kcalc /usr/bin/

WORKDIR /web-service
CMD ["gunicorn", "kcalc.app"]
