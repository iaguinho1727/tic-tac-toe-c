FROM --platform=amd64 gcc:13.2.0 as build

WORKDIR /app

COPY src/ src/
COPY include/ include/
COPY Makefile.in .
COPY configure.ac .


RUN autoconf && ./configure && make -j$(nproc)



FROM debian:bookworm-slim as game

RUN useradd -m gamer

COPY --from=build /app/out/TicTacToe /usr/local/bin/

USER gamer

ENTRYPOINT [ "TicTacToe" ]

