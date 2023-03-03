FROM gcc:latest as build
WORKDIR /build

ADD ./cat/ ./cat/ 
ADD ./grep/ ./grep/
ADD ./common/ ./common/

RUN ls && cd cat && make
RUN cd grep && make

FROM ubuntu:latest as suite
RUN sed -E 's/\/\/.+?\.com\//\/\/mirror\.yandex\.ru\//g' -i /etc/apt/sources.list &&\
    apt-get update
RUN apt-get install make python3 valgrind -y

FROM suite
COPY --from=build /build/ /build/

WORKDIR /build/common

COPY ./common/docker-entrypoint.sh .
RUN chmod +x ./docker-entrypoint.sh

ENTRYPOINT [ "./docker-entrypoint.sh" ]
