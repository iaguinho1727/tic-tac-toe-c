FROM --platform=amd64 gcc:13.2.0 as library

RUN apt-get update -y && apt-get upgrade -y


WORKDIR /app

COPY . .
COPY Makefile .


RUN make -j 4



RUN make install

ENTRYPOINT [ "make" ]

CMD ["test"]

