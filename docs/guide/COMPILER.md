# HOLEXA Compiler Guide v1.0.0

## hlxc — HOLEXA Compiler

### Installation
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/compiler
make
cp hlxc /usr/local/bin/hlxc
```

### Commands

| Command | Description |
|---------|-------------|
| `hlxc <file.hlx>` | Compile and check |
| `hlxc run <file.hlx>` | Run a program |
| `hlxc build <file.hlx>` | Generate IR |
| `hlxc --version` | Show version |

### Examples
```sh
hlxc main.hlx
hlxc run main.hlx
hlxc build main.hlx
hlxc --version
```

### Compiler Pipeline
```
Source (.hlx)
    ↓
Lexer — Tokenization
    ↓
Parser — AST Generation
    ↓
Semantic Analysis
    ↓
Code Generation
    ↓
Output
```

### Error Codes

| Code | Description |
|------|-------------|
| HLX100 | Syntax error |
| HLX101 | Unexpected token |
| HLX201 | Duplicate declaration |
| HLX202 | Undefined variable |
| HLX301 | Warning — undefined function |
