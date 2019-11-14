#!/bin/bash

set -e

TAG="registry.gitlab.gnome.org/gnome/gobject-introspection:min-v1"

sudo docker build --build-arg HOST_USER_ID="$UID" --tag "${TAG}" \
    --file "minimal.Dockerfile" .
sudo docker run --rm \
    --volume "$(pwd)/..:/home/user/app" --workdir "/home/user/app" \
    --tty --interactive "${TAG}" bash
