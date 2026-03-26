FROM gcc:13.2.0 as base

WORKDIR /app

COPY src/ src/
COPY include/ include/
COPY Makefile.in .
COPY configure.ac .


RUN ./bootstrap.sh && make -j$(nproc)

FROM emscripten/emsdk:5.0.3-x64 as wasm

WORKDIR /app

COPY src/ src/
COPY include/ include/
COPY Makefile.in .
COPY configure.ac .

RUN apt update -y && apt install -y autoconf automake

RUN ./bootstrap.sh && emconfigure ./configure && emmake make

FROM nginx as web

COPY --from=wasm /app/out /usr/share/nginx/html

FROM debian:bookworm-slim as game

RUN useradd -m gamer

COPY --from=build /app/out/TicTacToe /usr/local/bin/

USER gamer

ENTRYPOINT [ "TicTacToe" ]

