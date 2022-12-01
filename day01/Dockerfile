FROM frolvlad/alpine-gxx as BASE
COPY main.cpp .
RUN g++ -static main.cpp -o /bin/main

FROM scratch
COPY --from=BASE /bin/main /bin/main
COPY input.txt .
ENTRYPOINT ["/bin/main"]
