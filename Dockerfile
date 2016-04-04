FROM ubuntu:14.04

RUN apt-get update && apt-get install -y \
    wget \
    make \
    gcc \
    g++ \
    libsnappy-dev \
    zlib1g-dev \
    libbz2-dev \
    libgflags-dev \
    cmake \
    git \
    python-pip

RUN pip install requests

RUN git clone https://github.com/facebook/rocksdb.git

RUN cd rocksdb  && \
    make static_lib

WORKDIR /app-server

#CMD /app-server/make-and-run.server.sh

EXPOSE 8000