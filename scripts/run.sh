#!/bin/bash

# A script to fire up a docker container with the project and attach a terminal

BASE_SCRIPT_NAME="base.sh"
SCRIPT_PATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

source "$SCRIPT_PATH/$BASE_SCRIPT_NAME"

eval $RUN_CONTAINER
