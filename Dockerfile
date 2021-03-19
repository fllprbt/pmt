FROM ubuntu:18.04 AS base

ARG os

RUN if [ "$os" != "linux" ] && [ "$os" != "mac" ]; then exit 1 ; else exit 0 ; fi

RUN apt-get update \
    && apt-get --quiet --no-install-recommends -y install \
    git g++ qt5-default make libaubio-dev portaudio19-dev ca-certificates

RUN if [ "$os" = "mac" ] ; then apt-get --no-install-recommends -y install pulseaudio > /dev/null ; else usermod -aG audio root ; fi

WORKDIR /app
