#!/bin/bash

# A script which is used as base by other scripts to ensure that proper host OS
# dependencies and setup configuration is in place

SCRIPT_PATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
ROOT_PATH="$(dirname "$SCRIPT_PATH")"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "[Detected OS: Linux]\n"

    echo "Building Docker image..."
    docker build --build-arg os=linux $ROOT_PATH -t fll:pmt
    
    RUN_CONTAINER="docker run -it --init --device /dev/snd \
    -v '$ROOT_PATH:/app' fll:pmt"

elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "[Detected OS: Mac OSX]\n"

    echo "Checking brew installation..."
    which -s brew
    if [[ $? != 0 ]] ; then
        echo "Please install brew"
        exit 1
    fi

    echo "Checking pulseaudio installation..."
    which -s pulseaudio
    if [[ $? != 0 ]] ; then
        echo "Please install pulseaudio: brew install pulseaudio"
        exit 1
    fi

    echo "Checking pulseaudio daemon state..."
    pulseaudio --check -v
    if [[ $? != 0 ]] ; then
        echo "Pulseaudio daemon is not running, starting it..."
        pulseaudio --load=module-native-protocol-tcp --exit-idle-time=-1 --log-level=0 --daemon
        if [[ $? != 0 ]] ; then
            echo "Error initializing pulseaudio in host OS"
            exit 1
        fi
    fi

    echo "Building Docker image..."
    docker build --build-arg os=mac $ROOT_PATH -t fll:pmt

    echo "Running container..."
    RUN_CONTAINER="docker run -it --init -e PULSE_SERVER=host.docker.internal \
    -v ~/.config/pulse/cookie:/root/.config/pulse/cookie \
    -v '$ROOT_PATH:/app' fll:pmt"

else
    echo "Unsupported OS"
    exit 1
fi