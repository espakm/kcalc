FROM alpine:3.13

RUN apk --no-cache add \
        python3 \
        py3-pip \
 && pip install requests

COPY kcalc_client.py /kcalc-client/

WORKDIR /kcalc-client
CMD ["./kcalc_client.py"]
