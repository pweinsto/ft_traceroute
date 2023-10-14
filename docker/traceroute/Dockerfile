FROM debian:12

RUN apt update -y && apt install -y \
    build-essential \
    traceroute \
    man-db \
    valgrind

ENTRYPOINT ["tail", "-f", "/dev/null"]