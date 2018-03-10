FROM fedora:27

RUN dnf -y install \
    cairo-devel \
    cairo-gobject-devel \
    ccache \
    gcc \
    gcc-c++ \
    gettext \
    git \
    glib2-devel \
    itstool \
    libffi-devel \
    meson

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.utf8
