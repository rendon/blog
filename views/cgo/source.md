---
tags:
    - go
    - c
    - programming
    - post
created: 2021-04-26
updated: 2024-11-04
---
# Hello-World CGO program

I had the chance to experiment with CGO for a project at work (an encryption SDK only available in C++ that we wanted to use in Go). Just sharing a hello-world program that might come in handy when using this feature for the first time.

Let's start by creating a brand new Go module:
```sh
mkdir cgo
cd cgo
go mod init cgo
```

Then we'll add the following files:

- hello.c
- hello.h
- main.go

## hello.c
```c
#include <stdio.h>

#include "hello.h"

void Greet() {
    printf("Hello, world!\n");
}
```
## hello.h

```c
#ifndef PLAYGROUND_HELLO_H
#define PLAYGROUND_HELLO_H

void Greet();

#endif //PLAYGROUND_HELLO_H
```

## main.go
```go
package main

// #include "hello.h"
import "C"

import (
	"fmt"
	"log"
)

func main() {
	if err := greet(); err != nil {
		log.Fatalf("Failed to call hello: %s", err)
	}
	log.Printf("Successfully called hello!\n");
}

func greet() error {
	_, err := C.Greet()
	if err != nil {
		return fmt.Errorf("call to hello failed: %s", err)
	}
	return nil
}
```
## Build & run
```
$ go build
$ ./cgo
Hello, world!
2021/04/26 14:30:39 Successfully called hello!
```
Full source code: [code-samples/cgo](https://github.com/rendon/code-samples/tree/master/cgo).

## References
I followed [Cgo: First steps tutorial](https://riptutorial.com/go/example/21315/cgo--first-steps-tutorial), but the examples provided didn't compile for me (see the error down below), I had to create a header file (hello.h) and a source file (hello.c), as shown in this post.
```
/tmp/go-build070036073/b001/_x003.o: In function `printf':
/usr/include/x86_64-linux-gnu/bits/stdio2.h:104: multiple definition of `Greet'
/tmp/go-build070036073/b001/_x002.o:/usr/include/x86_64-linux-gnu/bits/stdio2.h:104: first defined here
collect2: error: ld returned 1 exit status
```

**UPDATE**: Just realized that the tutorial referenced above explains how to fix the error. Anyway, now we have two slightly different ways to write a hello-world CGO program.
