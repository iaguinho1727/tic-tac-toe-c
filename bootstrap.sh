#!/bin/sh

set -e

autoreconf --install && ./configure && make clean
