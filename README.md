# MyFTP

Asynchronous FTP server compliant with RFC 959 written in C.

## Overview

Supports dual TCP connections (control on port 21 and dynamic data connection in PASV/PORT modes), user authentication, and standard RFC commands.

## Getting Started

```bash
# Compile
make

# Run server: ./myftp <port> <path>
./myftp 4242 ./
```
