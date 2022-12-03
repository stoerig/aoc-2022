FROM frolvlad/alpine-gcc as BASE
COPY main.c .
RUN gcc -static main.c -o /bin/main

FROM scratch
COPY --from=BASE /bin/main /bin/main
COPY input.txt .
ENTRYPOINT ["/bin/main"]
