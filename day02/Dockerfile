from alpine:latest as BASE

from BASE as BUILD

RUN apk add zig --repository=https://dl-cdn.alpinelinux.org/alpine/edge/testing

COPY aoc.zig .

RUN zig build-exe aoc.zig -O ReleaseFast --name aoc

from BASE as FINAL

COPY input.txt .
COPY --from=build aoc .

CMD ["./aoc"]
