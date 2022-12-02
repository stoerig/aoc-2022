FROM alpine:latest as base

FROM base as build

RUN apk add zig --repository=https://dl-cdn.alpinelinux.org/alpine/edge/testing

COPY aoc.zig .

RUN zig build-exe aoc.zig -O ReleaseFast --name aoc

FROM base as final

COPY input.txt .
COPY --from=build aoc .

CMD ["./aoc"]
