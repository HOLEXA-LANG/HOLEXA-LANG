# HOLEXA Documentation v1.0.0

> Code like a Dragon. Think like a Human.

## Contents

1. [Language Guide](guide/LANGUAGE.md)
2. [Compiler Guide](guide/COMPILER.md)
3. [Standard Library](stdlib/README.md)
4. [Package Manager](guide/HLXPM.md)
5. [Developer Tools](guide/TOOLS.md)
6. [API Reference](api/README.md)
7. [Examples](examples/README.md)

## Quick Start

### Install
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/compiler
make
cp hlxc /usr/local/bin/hlxc
```

### Hello World
```hlx
fn main() {
    print("Hello, World!")
}
```

### Run
```sh
hlxc run hello.hlx
```
