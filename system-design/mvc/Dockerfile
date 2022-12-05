FROM golang:1.19 AS builder
WORKDIR /workdir
COPY ./ ./
RUN go mod download && \
    GOOS=linux GOARCH=amd64 go build -ldflags="-w -s" -o \
    gotodo-server ./cmd/gotodo-server/main.go


FROM alpine
COPY --from=builder /workdir/gotodo-server /server
RUN apk add --no-cache ca-certificates && update-ca-certificates && ls -la
EXPOSE 8080 8080
CMD ["/server"]