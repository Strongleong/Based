#!/bin/sh

CFLAGS="-Wall -Wextra -std=c99 -pedantic"
CLIBS="-I./"
CDEBUG="-O0 -ggdb -fsanitize=address -fno-omit-frame-pointer"
CPROFILE="-pg"
CRELEASE="-O3 -march=native"
CC="clang"

OUTDIR="./out"
VERBOSE=true
DEBUG=false

usage() {
  echo "-d --debug     Compile with debug flags"
  echo "-p --profile   Compile with profile flags"
  echo "-s --silent    Compile without unnececary output"
  echo "-o --outdir    Set output dir (default: ./out)"
  echo "-c --compiler  Set which compier to use (default: clang)"
  echo "-h --help      Print help"
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    "-d"|"--debug") DEBUG=true
      shift
      ;;
    "-p"|"--profile") CFLAGS="$CPROFILE $CFLAGS"
      shift
      ;;
    "-s"|"--silent") VERBOSE=false
      shift
      ;;
    "-c"|"--compiler") CC="$2"
      shift
      shift
      ;;
    "-o"|"--outdir") OUTDIR="$2"
      shift
      shift
      ;;
    "-h"|"--help") usage;
      shift
      exit 1;
      ;;
    "") # pass through
      ;;
    *) echo "Unknown command '$1'";
      shift
      usage;
      exit 1;
  esac
done

set -e

if [ ! -d "$OUTDIR" ]; then
  mkdir -p "$OUTDIR";
fi

if $DEBUG; then
  CFLAGS="$CFLAGS $CDEBUG"
else
  CFLAGS="$CFLAGS $CRELEASE"
fi

examples=$(find ./examples -name '*.c')

if $VERBOSE; then
  set -x
fi

$CC $CFLAGS $CLIBS -o "$OUTDIR/test" ./test/test.c &
$CC $CFLAGS $CLIBS -o "$OUTDIR/generate_decoding_table" ./utils/generate_decoding_table.c &
$CC $CFLAGS $CLIBS -o ./examples/base64_encode        ./examples/base64_encode.c &
$CC $CFLAGS $CLIBS -o ./examples/base64_decode        ./examples/base64_decode.c &
$CC $CFLAGS $CLIBS -o ./examples/base32_custom_encode ./examples/base32_custom_encode.c &
$CC $CFLAGS $CLIBS -o ./examples/base32_custom_decode ./examples/base32_custom_decode.c &
$CC $CFLAGS $CLIBS -o ./examples/base16_encdoe_decode ./examples/base16_encdoe_decode.c &

{ set +x; } 2> /dev/null
wait
