<div align="center">

<img src="logo.png" alt="HOLEXA Logo" width="100" style="border-radius:50%;border:3px solid #58a6ff;padding:4px;">

# 🐉 HOLEXA

### Programming Language

**Code like a Dragon. Think like a Human.**

[![Version](https://img.shields.io/badge/version-1.0.0-58a6ff?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![License](https://img.shields.io/badge/license-MIT-3fb950?style=flat-square)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Mac%20%7C%20Windows%20%7C%20iPad-8b949e?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![Launch](https://img.shields.io/badge/🚀%20launched-March%2023%2C%202026-d29922?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![Built on](https://img.shields.io/badge/built%20on-iPad%20%F0%9F%93%B1-bc8cff?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)

<br>

[📖 Documentation](docs.html) &nbsp;·&nbsp;
[⚡ Quick Start](#quick-start) &nbsp;·&nbsp;
[📦 Install](#install) &nbsp;·&nbsp;
[🌐 Website](index.html)

</div>

---

## What is HOLEXA?

HOLEXA is a **modern, open-source programming language** built from scratch — combining the best of the world's most powerful languages into one clean, fast, and readable tool.

| | Language | What HOLEXA took |
|-|----------|-----------------|
| ⚡ | **C** | Raw speed and native performance |
| 🛡️ | **Rust** | Memory safety and reliability |
| 📖 | **Python** | Clean, readable syntax |
| 🔧 | **Go** | Simplicity and fast compilation |

---

## Hello World

```hlx
fn main() {
    print("Hello, World!")
    print("Code like a Dragon!")
}
```

```sh
hlxc run hello.hlx
# Hello, World!
# Code like a Dragon!
```

---

## Install

```sh
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

| Platform | Command |
|----------|---------|
| 🐧 Linux | `curl -fsSL .../install.sh \| sh` |
| 🍎 macOS | `curl -fsSL .../install.sh \| sh` |
| 📱 iPad (iSH) | `apk add curl git gcc make` then install |
| 🪟 Windows | `wsl --install` then use Linux command |

---

## Quick Start

```hlx
// Variables
let name  = "Dragon"
let count = 42
let pi    = 3.14
let flag  = true
const MAX = 100

// Function
fn greet(name: String) -> String {
    return "Hello " + name + "!"
}

// Loop
for i in 0..5 {
    print(str(i))
}

// Class
class Dragon {
    name:  String
    power: Int

    fn new(name: String, power: Int) -> Dragon {
        return Dragon { name: name, power: power }
    }

    fn roar(self) -> String {
        return self.name + " ROARS!"
    }
}

// Error handling
try {
    print("safe code")
} catch err {
    print("error: " + err)
}

fn main() {
    print(greet("HOLEXA"))
    let d = Dragon.new("Fire", 9999)
    print(d.roar())
}
```

---

## Launch

🚀 **Officially launched on March 23, 2026**

---

## Creator

**HOLEXA** was created by **Ayush Giri** in March 2026.

> *"I tried Python — too slow.*
> *I tried C — too unsafe.*
> *I tried Rust — too complex.*
> *I tried Go — too limited.*
> *So I built HOLEXA."*
>
> — Ayush Giri, Creator of HOLEXA

---

## 📁 Project Structure

```
📦 HOLEXA-LANG
┣ 📂 .github                              # GitHub configuration
┃ ┣ 📜 FUNDING.yml                        # Sponsor / donation links
┃ ┗ 📂 workflows
┃   ┗ 📜 deploy.yml                       # GitHub Actions auto-deploy
┃
┣ 📂 compiler                             # HOLEXA Compiler (written in C)
┃ ┣ 📜 Makefile                           # Build file — run: make
┃ ┣ 📜 hlxc                               # Compiled binary
┃ ┣ 📂 include                            # Header files
┃ ┃ ┣ 📜 codegen.h                        # Code generator interface
┃ ┃ ┣ 📜 holexa.h                         # Core types and structures
┃ ┃ ┣ 📜 interpreter.h                    # Interpreter interface
┃ ┃ ┣ 📜 parser.h                         # Parser interface
┃ ┃ ┗ 📜 semantic.h                       # Semantic analyzer interface
┃ ┗ 📂 src                                # Compiler source code
┃   ┣ 📜 ast.c                            # Abstract Syntax Tree builder
┃   ┣ 📜 codegen.c                        # Code generator / IR output
┃   ┣ 📜 interpreter.c                    # Tree-walking interpreter
┃   ┣ 📜 lexer.c                          # Tokenizer — code → tokens
┃   ┣ 📜 main.c                           # Entry point
┃   ┣ 📜 parser.c                         # Parser — tokens → AST
┃   ┗ 📜 semantic.c                       # Type checking and validation
┃
┣ 📂 stdlib                               # Standard Library (15 libraries)
┃ ┣ 📜 index.hlx                          # Stdlib registry
┃ ┣ 📂 crypto
┃ ┃ ┗ 📜 crypto.hlx                       # hash, encrypt, decrypt, sha256
┃ ┣ 📂 fs
┃ ┃ ┗ 📜 fs.hlx                           # read, write, delete, exists
┃ ┣ 📂 http
┃ ┃ ┗ 📜 http.hlx                         # get, post, server
┃ ┣ 📂 io
┃ ┃ ┗ 📜 io.hlx                           # stdin, stdout, streams
┃ ┣ 📂 json
┃ ┃ ┗ 📜 json.hlx                         # parse, stringify
┃ ┣ 📂 list
┃ ┃ ┗ 📜 list.hlx                         # push, pop, sort, filter, map
┃ ┣ 📂 map
┃ ┃ ┗ 📜 map.hlx                          # set, get, delete, keys
┃ ┣ 📂 math
┃ ┃ ┗ 📜 math.hlx                         # abs, sqrt, pow, sin, cos, PI
┃ ┣ 📂 net
┃ ┃ ┗ 📜 net.hlx                          # tcp, udp, socket
┃ ┣ 📂 os
┃ ┃ ┗ 📜 os.hlx                           # env, args, exit, platform
┃ ┣ 📂 process
┃ ┃ ┗ 📜 process.hlx                      # spawn, kill, pid, wait
┃ ┣ 📂 random
┃ ┃ ┗ 📜 random.hlx                       # int, float, choice, shuffle
┃ ┣ 📂 string
┃ ┃ ┗ 📜 string.hlx                       # upper, lower, trim, split
┃ ┗ 📂 time
┃   ┗ 📜 time.hlx                         # now, date, sleep, format
┃
┣ 📂 package-manager                      # hlxpm — Package Manager
┃ ┗ 📜 hlxpm                              # Binary (hlxpm install / create)
┃
┣ 📂 packages                             # Package Registry
┃ ┗ 📜 registry.json                      # All available packages
┃
┣ 📂 tools                                # Developer Tools
┃ ┣ 📂 hlxfmt
┃ ┃ ┗ 📜 hlxfmt                           # Code formatter
┃ ┣ 📂 hlxlint
┃ ┃ ┗ 📜 hlxlint                          # Code linter
┃ ┣ 📂 hlxbuild
┃ ┃ ┗ 📜 hlxbuild                         # Project builder
┃ ┗ 📂 lsp
┃   ┗ 📜 hlx-lsp                          # Language Server Protocol
┃
┣ 📂 editor-support                       # Support for 7 Code Editors
┃ ┣ 📜 INSTALL.md                         # Complete editor setup guide
┃ ┣ 📂 atom
┃ ┃ ┗ 📜 holexa.cson                      # Atom grammar
┃ ┣ 📂 emacs
┃ ┃ ┗ 📜 holexa-mode.el                   # Emacs major mode
┃ ┣ 📂 intellij
┃ ┃ ┗ 📜 holexa.xml                       # IntelliJ file type
┃ ┣ 📂 neovim
┃ ┃ ┗ 📜 holexa.lua                       # Neovim LSP config
┃ ┣ 📂 sublime
┃ ┃ ┣ 📜 HOLEXA.sublime-completions       # Auto-completions
┃ ┃ ┗ 📜 HOLEXA.sublime-syntax            # Syntax highlighting
┃ ┣ 📂 vim
┃ ┃ ┣ 📜 ftdetect.vim                     # File type detection
┃ ┃ ┗ 📜 holexa.vim                       # Vim syntax highlighting
┃ ┗ 📂 vscode                             # VS Code Extension (Full)
┃   ┣ 📜 LICENSE                          # MIT License
┃   ┣ 📜 extension.js                     # Extension logic
┃   ┣ 📜 language-configuration.json      # Brackets, comments config
┃   ┣ 📜 logo.png                         # Dragon logo
┃   ┣ 📜 package.json                     # Extension metadata
┃   ┣ 📜 snippets.json                    # Code snippets
┃   ┣ 📂 syntaxes
┃   ┃ ┗ 📜 holexa.tmLanguage.json         # Syntax highlighting grammar
┃   ┗ 📂 themes
┃     ┗ 📜 dragon-dark.json               # HOLEXA Dragon Dark theme
┃
┣ 📂 self-hosting                         # Compiler written in HOLEXA
┃ ┣ 📜 hlxc_interpreter.hlx              # Interpreter in HOLEXA
┃ ┣ 📜 hlxc_lexer.hlx                    # Lexer in HOLEXA
┃ ┣ 📜 hlxc_parser.hlx                   # Parser in HOLEXA
┃ ┗ 📜 hlxc_selfhosted.hlx               # Full compiler in HOLEXA
┃
┣ 📂 tests                                # Complete Test Suite
┃ ┣ 📜 final_test.hlx                     # Final test — all pass ✅
┃ ┣ 📜 run_tests.sh                       # Run all tests script
┃ ┣ 📂 integration                        # Integration tests
┃ ┃ ┣ 📜 test_algorithms.hlx
┃ ┃ ┣ 📜 test_class.hlx
┃ ┃ ┗ 📜 test_error.hlx
┃ ┣ 📂 realworld                          # Real-world program tests
┃ ┃ ┗ 📜 task_manager.hlx
┃ ┗ 📂 unit                               # Unit tests
┃   ┣ 📜 test_conditions.hlx
┃   ┣ 📜 test_functions.hlx
┃   ┣ 📜 test_loops.hlx
┃   ┣ 📜 test_strings.hlx
┃   ┗ 📜 test_variables.hlx
┃
┣ 📂 examples                             # Example Programs
┃ ┣ 📜 stdlib_test.hlx                    # Standard library examples
┃ ┣ 📂 advanced
┃ ┃ ┗ 📜 dragon.hlx                       # Dragon class demo
┃ ┗ 📂 basic
┃   ┗ 📜 hello.hlx                        # Hello World
┃
┣ 📂 docs                                 # Technical Documentation
┃ ┣ 📜 HOLEXA-SPEC.md                     # Full language specification
┃ ┣ 📜 README.md                          # Docs overview
┃ ┣ 📂 api
┃ ┃ ┗ 📜 README.md                        # API reference
┃ ┣ 📂 examples
┃ ┃ ┗ 📜 README.md                        # Examples docs
┃ ┣ 📂 guide
┃ ┃ ┣ 📜 COMPILER.md                      # Compiler internals guide
┃ ┃ ┣ 📜 HLXPM.md                         # Package manager guide
┃ ┃ ┣ 📜 LANGUAGE.md                      # Language guide
┃ ┃ ┗ 📜 TOOLS.md                         # Developer tools guide
┃ ┣ 📂 stdlib
┃ ┃ ┗ 📜 README.md                        # Standard library docs
┃ ┗ 📂 syntax
┃   ┣ 📜 GRAMMAR.md                       # Formal grammar spec
┃   ┗ 📜 HOLEXA-SYNTAX.md                 # Complete syntax reference
┃
┣ 📂 runtime                              # Runtime Library (C)
┃ ┣ 📜 README.md
┃ ┣ 📜 runtime.c                          # Runtime implementation
┃ ┗ 📜 runtime.h                          # Runtime header
┃
┣ 📂 myapp                                # Example Project (hlxpm create)
┃ ┣ 📜 README.md
┃ ┣ 📜 hlxpm.json                         # Project config
┃ ┣ 📂 src
┃ ┃ ┗ 📜 main.hlx                         # Main source file
┃ ┗ 📂 tests
┃   ┗ 📜 test_main.hlx                    # Project tests
┃
┣ 📜 HISTORY.md                           # Language history and story
┣ 📜 INSTALL_COMMAND.md                   # Quick install reference
┣ 📜 LICENSE                              # MIT License
┣ 📜 README.md                            # This file
┣ 📜 docs.html                            # Full documentation (23 chapters)
┣ 📜 hlxbuild.json                        # Build configuration
┣ 📜 index.html                           # Official website
┣ 📜 install.sh                           # Universal installer script
┗ 📜 logo.png                             # HOLEXA Dragon logo
```

---

## Tools

| Tool | Command | Description |
|------|---------|-------------|
| `hlxc` | `hlxc run file.hlx` | Run a HOLEXA program |
| `hlxc` | `hlxc build file.hlx` | Compile to binary |
| `hlxc` | `hlxc check file.hlx` | Check for errors only |
| `hlxpm` | `hlxpm install math` | Install a package |
| `hlxpm` | `hlxpm create myapp` | Create new project |
| `hlxfmt` | `hlxfmt file.hlx` | Auto-format code |
| `hlxlint` | `hlxlint file.hlx` | Check code quality |
| `hlxbuild` | `hlxbuild run` | Build and run project |

---

## Editor Support

| Editor | Status | Features |
|--------|--------|----------|
| VS Code | ✅ Full Support | Highlighting, autocomplete, run shortcut, Dragon theme |
| Vim | ✅ Supported | Syntax highlighting, filetype detection |
| Neovim | ✅ LSP Ready | Full LSP, highlighting, autocomplete |
| Emacs | ✅ Supported | Major mode, indentation |
| Sublime Text | ✅ Supported | Highlighting, snippets |
| IntelliJ | ✅ Supported | File type, highlighting |
| Atom | ✅ Supported | Grammar, highlighting |

---

## 🐉 Built on iPad

> **HOLEXA was built 100% on a normal iPad using iSH Shell.**

No MacBook. No PC. No expensive setup.
Just an iPad, determination, and a vision.

A full compiler, package manager, 15+ libraries, and editor support for 7 editors —
**all built on an iPad.**

> *"If you have an idea, your device doesn't matter. Your determination does."*
> — Ayush Giri, Creator of HOLEXA

---

## License

MIT License — Copyright (c) 2026 Ayush Giri

See [LICENSE](LICENSE) for details.

---

<div align="center">

**github.com/HOLEXA-LANG/HOLEXA-LANG**

🐉 *Code like a Dragon. Think like a Human.*

</div>
