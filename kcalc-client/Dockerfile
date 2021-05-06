FROM alpine:3.13

RUN apk --no-cache add \
        python3 \
        py3-pip \
 && pip install requests

COPY kcalc_client.py /kcalc-client/

ENV KCALC_SERVER_URI "http://127.0.0.1:8000/calculator"
ENV KCALC_SYNTAX_FORMAT "infix"

WORKDIR /kcalc-client
CMD ["./kcalc_client.py"]
