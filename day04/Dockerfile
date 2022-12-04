FROM rust:1.61 as builder
WORKDIR /usr/src/day01
COPY . .
RUN cargo install --path .

FROM debian:buster-slim
COPY --from=builder /usr/local/cargo/bin/aoc /usr/local/bin/aoc
COPY input.txt .
CMD ["aoc"]
