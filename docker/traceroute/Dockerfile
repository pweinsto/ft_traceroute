FROM debian:12

RUN apt update -y && apt install -y \
    build-essential \
    inetutils-traceroute \
    inetutils-ping \
    man-db \
    valgrind

ENTRYPOINT ["tail", "-f", "/dev/null"]