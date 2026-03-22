<div align="center">

<img src="logo.png" alt="HOLEXA Logo" width="110" height="110" style="border-radius:100%;border:3px solid #58a6ff;padding:4px;box-shadow:0 0 20px rgba(88,166,255,0.3);">

<br><br>

# 🐉 HOLEXA

### A Modern, Open-Source Programming Language

**Code like a Dragon. Think like a Human.**

<br>

[![Version](https://img.shields.io/badge/version-1.0.0-58a6ff?style=flat-square&logo=github)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![License](https://img.shields.io/badge/license-MIT-3fb950?style=flat-square)](LICENSE)
[![Launch](https://img.shields.io/badge/🚀_launched-March_23,_2026-d29922?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![Platform](https://img.shields.io/badge/platform-Linux_|_Mac_|_Windows_|_iPad_|_Android-8b949e?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![Built on](https://img.shields.io/badge/built_on-iPad_📱-bc8cff?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)
[![Self-Hosting](https://img.shields.io/badge/self--hosting-✅_complete-3fb950?style=flat-square)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)

<br>

[🌐 Website](https://holexa-lang.github.io/HOLEXA-LANG/) &nbsp;·&nbsp;
[📖 Full Documentation](https://holexa-lang.github.io/HOLEXA-LANG/docs.html) &nbsp;·&nbsp;
[⚡ Quick Start](#-quick-start) &nbsp;·&nbsp;
[📦 Install](#-install) &nbsp;·&nbsp;
[❤️ Sponsor](https://ko-fi.com/holexalang)

</div>

---

## 🐉 What is HOLEXA?

HOLEXA is a **compiled, statically-typed, open-source programming language** built completely from scratch in March 2026. It was designed to eliminate the biggest frustrations of every popular language — giving developers one tool that is fast, safe, readable, and simple all at once.

> **If Python is too slow, C is too unsafe, Rust is too complex, and Go is too limited —**
> **HOLEXA is the answer.**

---

## ⚡ Why Use HOLEXA?

Most languages make you choose between tradeoffs. HOLEXA removes those tradeoffs.

| Feature | HOLEXA | Python | C | Rust | Go |
|---------|:------:|:------:|:-:|:----:|:--:|
| ⚡ Native Speed | ✅ | ❌ | ✅ | ✅ | ✅ |
| 🛡️ Memory Safe | ✅ | ✅ | ❌ | ✅ | ✅ |
| 📖 Easy Syntax | ✅ | ✅ | ❌ | ❌ | ⚠️ |
| 🔧 Simple to Learn | ✅ | ✅ | ❌ | ❌ | ✅ |
| 📦 Built-in Stdlib | ✅ 14+ | ✅ | ⚠️ | ✅ | ✅ |
| 🌐 Cross Platform | ✅ | ✅ | ⚠️ | ✅ | ✅ |
| 🐉 Self-Hosting | ✅ | ✅ | ✅ | ✅ | ✅ |
| 📱 Runs on iPad | ✅ | ⚠️ | ❌ | ❌ | ❌ |
| ⏱️ Fast Compilation | ✅ | — | ✅ | ❌ | ✅ |
| 🤝 Beginner Friendly | ✅ | ✅ | ❌ | ❌ | ⚠️ |

> ✅ = Yes &nbsp; ❌ = No &nbsp; ⚠️ = Partial

### In plain words:

| If you use... | Problem | HOLEXA solves it by... |
|--------------|---------|----------------------|
| **Python** | Too slow for real-world performance | Compiling to native code — 10-50x faster |
| **C** | Memory crashes, buffer overflows | Built-in memory safety with zero overhead |
| **Rust** | Extremely hard to learn | Python-like clean syntax anyone can read |
| **Go** | Too limited for complex projects | Full OOP, 14+ libraries, AI integration |
| **Nothing** | Don't know where to start | Beginner-friendly — if you can read English, you can read HOLEXA |

---

## 🚀 Hello World

```hlx
// Your first HOLEXA program
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

## 📦 Install

**One command. Every platform. Under 2 minutes.**

```sh
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

| Platform | Command |
|----------|---------|
| 🐧 **Linux** | `curl -fsSL .../install.sh \| sh` |
| 🍎 **macOS** | `curl -fsSL .../install.sh \| sh` |
| 📱 **iPad (iSH)** | `apk add curl git gcc make` then run install |
| 🤖 **Android (Termux)** | `pkg install curl git clang make` then run install |
| 🪟 **Windows** | `wsl --install` → restart → use Linux command in Ubuntu |

**Installs:** `hlxc` compiler · `hlxpm` package manager · `hlxfmt` formatter · `hlxlint` linter

**Verify:**
```sh
hlxc --version
# HOLEXA Compiler v1.0.0
```

---

## ⚡ Quick Start

```hlx
// ── Variables ─────────────────────────────────────
let name   = "Dragon"      // String
let count  = 42            // Int
let pi     = 3.14          // Float
let active = true          // Bool
const MAX  = 100           // Constant — cannot change

// ── Functions ─────────────────────────────────────
fn greet(name: String) -> String {
    return "Hello " + name + "!"
}

fn is_even(n: Int) -> Bool {
    if n % 2 == 0 { return true }
    return false
}

// ── Loops ─────────────────────────────────────────
for i in 0..5 {
    print(str(i))
}

// ── Classes ───────────────────────────────────────
class Dragon {
    name:  String
    power: Int

    fn new(name: String, power: Int) -> Dragon {
        return Dragon { name: name, power: power }
    }

    fn roar(self) -> String {
        return self.name + " ROARS with power " + str(self.power) + "!"
    }
}

// ── Error Handling ────────────────────────────────
try {
    print("safe code here")
} catch err {
    print("caught: " + err)
}

// ── Libraries ─────────────────────────────────────
import math

fn main() {
    print(greet("HOLEXA"))
    let d = Dragon.new("Fire", 9999)
    print(d.roar())
    print(str(math.sqrt(144)))   // 12.0
    print(str(is_even(42)))      // true
}
```

---

## 📚 Documentation

| Resource | Link | Description |
|----------|------|-------------|
| 🌐 **Website** | [holexa-lang.github.io/HOLEXA-LANG](https://holexa-lang.github.io/HOLEXA-LANG/) | Official website with playground |
| 📖 **Full Docs** | [docs.html](https://holexa-lang.github.io/HOLEXA-LANG/docs.html) | Complete 32-chapter documentation |
| 📦 **Installation** | [#install](#-install) | Install on any device |
| ⚡ **Quick Start** | [#quick-start](#-quick-start) | Start coding in 5 minutes |
| 📜 **Language Spec** | [docs/HOLEXA-SPEC.md](docs/HOLEXA-SPEC.md) | Full language specification |
| 🔧 **Compiler Guide** | [docs/guide/COMPILER.md](docs/guide/COMPILER.md) | Compiler internals |
| 📦 **Package Manager** | [docs/guide/HLXPM.md](docs/guide/HLXPM.md) | hlxpm guide |
| 🛠️ **Tools Guide** | [docs/guide/TOOLS.md](docs/guide/TOOLS.md) | hlxfmt, hlxlint, hlxbuild |
| 📚 **Language Guide** | [docs/guide/LANGUAGE.md](docs/guide/LANGUAGE.md) | Full language tutorial |
| 🗂️ **Syntax Reference** | [docs/syntax/HOLEXA-SYNTAX.md](docs/syntax/HOLEXA-SYNTAX.md) | All syntax rules |
| 📐 **Grammar Spec** | [docs/syntax/GRAMMAR.md](docs/syntax/GRAMMAR.md) | Formal grammar |
| 📚 **Stdlib Docs** | [docs/stdlib/README.md](docs/stdlib/README.md) | All 14 libraries |

---

## 📦 Standard Library

14 built-in libraries — install any with `hlxpm install <name>`:

| Library | Install | What it does |
|---------|---------|-------------|
| `math` | `hlxpm install math` | sqrt, pow, sin, cos, PI, floor, ceil |
| `string` | `hlxpm install string` | upper, lower, trim, split, replace |
| `fs` | `hlxpm install fs` | read, write, delete, exists, mkdir |
| `http` | `hlxpm install http` | GET, POST, PUT, DELETE requests |
| `json` | `hlxpm install json` | parse, stringify, validate |
| `crypto` | `hlxpm install crypto` | sha256, md5, base64, uuid |
| `time` | `hlxpm install time` | now, date, sleep, elapsed |
| `random` | `hlxpm install random` | int, float, seed |
| `os` | `hlxpm install os` | env, platform, exec, cwd |
| `net` | `hlxpm install net` | tcp, udp, socket |
| `list` | `hlxpm install list` | push, pop, sort, filter, find |
| `map` | `hlxpm install map` | set, get, delete, keys, values |
| `io` | `hlxpm install io` | stdin, stdout, stderr, flush |
| `process` | `hlxpm install process` | spawn, kill, pid, wait |

---

## 🔧 Developer Tools

| Tool | Command | What it does |
|------|---------|-------------|
| `hlxc` | `hlxc run file.hlx` | Run a program directly |
| `hlxc` | `hlxc build file.hlx` | Compile to native binary |
| `hlxc` | `hlxc check file.hlx` | Check for errors only |
| `hlxpm` | `hlxpm install math` | Install a library |
| `hlxpm` | `hlxpm create myapp` | Create new project |
| `hlxpm` | `hlxpm update` | Update all packages |
| `hlxfmt` | `hlxfmt file.hlx` | Auto-format your code |
| `hlxlint` | `hlxlint file.hlx` | Check code quality |
| `hlxbuild` | `hlxbuild run` | Build and run project |

---

## 🖥️ Editor Support

HOLEXA works in 7 major code editors with full syntax highlighting, autocomplete, and more:

| Editor | Status | Key Features | Install |
|--------|--------|-------------|---------|
| **VS Code** | ✅ Full Support | Highlighting, autocomplete, Dragon theme, Ctrl+Shift+R | `cp -r editor-support/vscode ~/.vscode/extensions/holexa-lang` |
| **Neovim** | ✅ LSP Ready | Full LSP, autocomplete, error detection | `cp holexa.lua ~/.config/nvim/lua/` |
| **Vim** | ✅ Supported | Syntax highlighting, filetype detection | `cp holexa.vim ~/.vim/syntax/` |
| **Emacs** | ✅ Supported | Major mode, indentation | `(load "holexa-mode.el")` |
| **Sublime Text** | ✅ Supported | Highlighting, snippets | `cp HOLEXA.sublime-syntax Packages/User/` |
| **IntelliJ** | ✅ Supported | File type, syntax highlighting | Settings → File Types → Import |
| **Atom** | ✅ Supported | Grammar, highlighting | `cp holexa.cson ~/.atom/packages/` |

---

```
## 📁 Project Structure

📦 HOLEXA-LANG/
┃
┣ 📂 .github/                                  # GitHub configuration
┃ ┣ 📜 FUNDING.yml                             # Sponsor & donation links (Ko-fi, GitHub Sponsors)
┃ ┗ 📂 workflows/
┃   ┗ 📜 deploy.yml                            # GitHub Actions — auto-deploy to GitHub Pages
┃
┣ 📂 compiler/                                 # HOLEXA Compiler — written in C
┃ ┣ 📜 Makefile                                # Build instructions — run: make
┃ ┣ ⚙️  hlxc                                   # Compiled compiler binary — run: hlxc run file.hlx
┃ ┣ 📂 include/                                # C header files
┃ ┃ ┣ 📜 holexa.h                              # Core types, structs, and definitions
┃ ┃ ┣ 📜 parser.h                              # Parser interface
┃ ┃ ┣ 📜 semantic.h                            # Semantic analyzer interface
┃ ┃ ┣ 📜 interpreter.h                         # Interpreter interface
┃ ┃ ┗ 📜 codegen.h                             # Code generator interface
┃ ┗ 📂 src/                                    # Compiler source code
┃   ┣ 📜 main.c                                # Entry point — reads .hlx files
┃   ┣ 📜 lexer.c                               # Lexer — splits source code into tokens
┃   ┣ 📜 ast.c                                 # Abstract Syntax Tree builder
┃   ┣ 📜 parser.c                              # Parser — converts tokens into AST
┃   ┣ 📜 semantic.c                            # Semantic analysis — type checking & validation
┃   ┣ 📜 interpreter.c                         # Tree-walking interpreter — executes AST
┃   ┗ 📜 codegen.c                             # Code generator — AST to IR/native output
┃
┣ 📂 stdlib/                                   # Standard Library — 14 built-in libraries
┃ ┣ 📜 index.hlx                               # Stdlib registry — lists all libraries
┃ ┣ 📂 math/
┃ ┃ ┗ 📜 math.hlx                              # abs, sqrt, pow, sin, cos, floor, ceil, PI, E
┃ ┣ 📂 string/
┃ ┃ ┗ 📜 string.hlx                            # upper, lower, trim, split, replace, contains
┃ ┣ 📂 fs/
┃ ┃ ┗ 📜 fs.hlx                                # read, write, append, delete, exists, mkdir
┃ ┣ 📂 http/
┃ ┃ ┗ 📜 http.hlx                              # get, post, put, delete — HTTP client
┃ ┣ 📂 json/
┃ ┃ ┗ 📜 json.hlx                              # parse, stringify, pretty, valid
┃ ┣ 📂 crypto/
┃ ┃ ┗ 📜 crypto.hlx                            # sha256, md5, base64_encode, uuid
┃ ┣ 📂 time/
┃ ┃ ┗ 📜 time.hlx                              # now, date, datetime, sleep, elapsed
┃ ┣ 📂 random/
┃ ┃ ┗ 📜 random.hlx                            # int, float, seed
┃ ┣ 📂 os/
┃ ┃ ┗ 📜 os.hlx                                # env, args, platform, exec, cwd, home
┃ ┣ 📂 net/
┃ ┃ ┗ 📜 net.hlx                               # tcp_connect, tcp_send, udp_send, hostname
┃ ┣ 📂 list/
┃ ┃ ┗ 📜 list.hlx                              # push, pop, get, set, sort, contains, len
┃ ┣ 📂 map/
┃ ┃ ┗ 📜 map.hlx                               # set, get, has, delete, keys, values, len
┃ ┣ 📂 io/
┃ ┃ ┗ 📜 io.hlx                                # write, writeln, read_line, error, flush
┃ ┗ 📂 process/
┃   ┗ 📜 process.hlx                           # spawn, run, output, kill, wait, pid, exit
┃
┣ 📂 package-manager/                          # hlxpm — HOLEXA Package Manager
┃ ┗ ⚙️  hlxpm                                  # Binary — hlxpm install / create / update
┃
┣ 📂 packages/                                 # Package Registry
┃ ┗ 📜 registry.json                           # List of all available packages & versions
┃
┣ 📂 tools/                                    # Developer Tools
┃ ┣ 📂 hlxfmt/
┃ ┃ ┗ ⚙️  hlxfmt                               # Code formatter — hlxfmt file.hlx
┃ ┣ 📂 hlxlint/
┃ ┃ ┗ ⚙️  hlxlint                              # Code linter — hlxlint file.hlx
┃ ┣ 📂 hlxbuild/
┃ ┃ ┗ ⚙️  hlxbuild                             # Project builder — hlxbuild run
┃ ┗ 📂 lsp/
┃   ┗ ⚙️  hlx-lsp                              # Language Server Protocol — for editor support
┃
┣ 📂 editor-support/                           # Syntax highlighting for 7 code editors
┃ ┣ 📜 INSTALL.md                              # Step-by-step setup guide for all editors
┃ ┣ 📂 vscode/                                 # VS Code Extension — Full Support
┃ ┃ ┣ 📜 package.json                          # Extension metadata & config
┃ ┃ ┣ 📜 extension.js                          # Extension logic — run, build, format commands
┃ ┃ ┣ 📜 language-configuration.json           # Brackets, comments, auto-close config
┃ ┃ ┣ 📜 snippets.json                         # Code snippets (fn, let, for, class...)
┃ ┃ ┣ 📜 LICENSE                               # MIT License for extension
┃ ┃ ┣ 🖼️  logo.png                             # HOLEXA Dragon logo for VS Code
┃ ┃ ┣ 📂 syntaxes/
┃ ┃ ┃ ┗ 📜 holexa.tmLanguage.json              # TextMate grammar — syntax highlighting rules
┃ ┃ ┗ 📂 themes/
┃ ┃   ┗ 📜 dragon-dark.json                    # HOLEXA Dragon Dark color theme
┃ ┣ 📂 vim/
┃ ┃ ┣ 📜 holexa.vim                            # Vim syntax highlighting rules
┃ ┃ ┗ 📜 ftdetect.vim                          # Vim filetype detection for .hlx files
┃ ┣ 📂 neovim/
┃ ┃ ┗ 📜 holexa.lua                            # Neovim LSP config + highlighting
┃ ┣ 📂 emacs/
┃ ┃ ┗ 📜 holexa-mode.el                        # Emacs major mode for HOLEXA
┃ ┣ 📂 sublime/
┃ ┃ ┣ 📜 HOLEXA.sublime-syntax                 # Sublime Text syntax highlighting
┃ ┃ ┗ 📜 HOLEXA.sublime-completions            # Sublime Text auto-completions
┃ ┣ 📂 intellij/
┃ ┃ ┗ 📜 holexa.xml                            # IntelliJ / JetBrains file type config
┃ ┗ 📂 atom/
┃   ┗ 📜 holexa.cson                           # Atom editor grammar
┃
┣ 📂 self-hosting/                             # HOLEXA compiler written in HOLEXA itself
┃ ┣ 📜 hlxc_lexer.hlx                         # Lexer — written in HOLEXA
┃ ┣ 📜 hlxc_parser.hlx                        # Parser — written in HOLEXA
┃ ┣ 📜 hlxc_interpreter.hlx                   # Interpreter — written in HOLEXA
┃ ┗ 📜 hlxc_selfhosted.hlx                    # Full self-hosted compiler pipeline
┃
┣ 📂 tests/                                    # Complete Test Suite — 100+ tests, 0 failures
┃ ┣ 📜 final_test.hlx                          # Full integration test — all features
┃ ┣ 📜 run_tests.sh                            # Script to run all tests at once
┃ ┣ 📂 unit/                                   # Unit tests — one feature at a time
┃ ┃ ┣ 📜 test_variables.hlx                    # Tests: let, const, types
┃ ┃ ┣ 📜 test_functions.hlx                    # Tests: fn, return, parameters
┃ ┃ ┣ 📜 test_loops.hlx                        # Tests: for, while
┃ ┃ ┣ 📜 test_conditions.hlx                   # Tests: if, else if, else
┃ ┃ ┗ 📜 test_strings.hlx                      # Tests: str, len, concatenation
┃ ┣ 📂 integration/                            # Integration tests — multiple features together
┃ ┃ ┣ 📜 test_algorithms.hlx                   # Tests: sorting, searching, math algorithms
┃ ┃ ┣ 📜 test_class.hlx                        # Tests: class, self, methods
┃ ┃ ┗ 📜 test_error.hlx                        # Tests: try, catch, error handling
┃ ┗ 📂 realworld/                              # Real-world program tests
┃   ┗ 📜 task_manager.hlx                      # A complete task manager app
┃
┣ 📂 examples/                                 # Ready-to-run example programs
┃ ┣ 📜 stdlib_test.hlx                         # Demo of all standard library functions
┃ ┣ 📂 basic/
┃ ┃ ┗ 📜 hello.hlx                             # Hello World — the simplest HOLEXA program
┃ ┗ 📂 advanced/
┃   ┗ 📜 dragon.hlx                            # Dragon class — OOP demo program
┃
┣ 📂 docs/                                     # Technical Documentation
┃ ┣ 📜 HOLEXA-SPEC.md                          # Full language specification
┃ ┣ 📜 README.md                               # Docs overview & index
┃ ┣ 📂 guide/
┃ ┃ ┣ 📜 LANGUAGE.md                           # Complete language tutorial
┃ ┃ ┣ 📜 COMPILER.md                           # Compiler internals & architecture
┃ ┃ ┣ 📜 HLXPM.md                              # Package manager full guide
┃ ┃ ┗ 📜 TOOLS.md                              # hlxfmt, hlxlint, hlxbuild guide
┃ ┣ 📂 syntax/
┃ ┃ ┣ 📜 HOLEXA-SYNTAX.md                      # Complete syntax reference
┃ ┃ ┗ 📜 GRAMMAR.md                            # Formal grammar specification (BNF)
┃ ┣ 📂 stdlib/
┃ ┃ ┗ 📜 README.md                             # Standard library overview
┃ ┣ 📂 api/
┃ ┃ ┗ 📜 README.md                             # API reference
┃ ┗ 📂 examples/
┃   ┗ 📜 README.md                             # Code examples documentation
┃
┣ 📂 runtime/                                  # Runtime Library — C implementation
┃ ┣ 📜 README.md                               # Runtime documentation
┃ ┣ 📜 runtime.c                               # Runtime implementation
┃ ┗ 📜 runtime.h                               # Runtime header
┃
┣ 📂 myapp/                                    # Example project created with hlxpm create
┃ ┣ 📜 README.md                               # Project readme
┃ ┣ 📜 hlxpm.json                              # Project config — name, version, dependencies
┃ ┣ 📂 src/
┃ ┃ ┗ 📜 main.hlx                              # Main source file
┃ ┗ 📂 tests/
┃   ┗ 📜 test_main.hlx                         # Project test file
┃
┣ 📜 HISTORY.md                                # HOLEXA language history & creator story
┣ 📜 INSTALL_COMMAND.md                        # Quick install command reference
┣ 📜 LICENSE                                   # MIT License — Copyright (c) 2026 Ayush Giri
┣ 📜 README.md                                 # This file — project overview
┣ 📜 docs.html                                 # Full documentation — 32 chapters (online)
┣ 📜 index.html                                # Official website with live playground
┣ 📜 install.sh                                # Universal installer — works on all platforms
┣ 📜 hlxbuild.json                             # Build configuration file
┗ 🖼️  logo.png                                 # HOLEXA Dragon logo
```

---

## 🏆 Technical Achievements

| Achievement | Status |
|-------------|--------|
| Complete compiler pipeline (Lexer → Parser → AST → Semantic → Interpreter) | ✅ Done |
| Native code compilation | ✅ Done |
| 14 standard libraries | ✅ Done |
| Package manager with registry | ✅ Done |
| Self-hosting compiler | ✅ Done |
| VS Code extension with Dragon logo | ✅ Done |
| Support for 7 code editors | ✅ Done |
| Live web playground | ✅ Done |
| Cross-platform (Linux, Mac, Windows, iPad, Android) | ✅ Done |
| Full test suite — 100+ tests, 0 failures | ✅ Done |
| Python / JavaScript / C integration | ✅ Done |
| OpenAI / AI integration | ✅ Done |

---

## 🌍 Integration

HOLEXA works with other languages and tools:

```python
# Python + HOLEXA
import subprocess
result = subprocess.run(['hlxc', 'run', 'file.hlx'], capture_output=True, text=True)
print(result.stdout)
```

```js
// Node.js + HOLEXA
const { execSync } = require('child_process');
const out = execSync('hlxc run file.hlx').toString();
console.log(out);
```

Full integration guides for **Python, JavaScript, C, and OpenAI** are in the [documentation](https://holexa-lang.github.io/HOLEXA-LANG/docs.html).

---

## 👨‍💻 Creator

**HOLEXA** was created by **Ayush Giri** in March 2026.

> *"I tried Python — too slow.*
> *I tried C — too unsafe.*
> *I tried Rust — too complex.*
> *I tried Go — too limited.*
> *So I built HOLEXA."*
>
> — Ayush Giri, Creator of HOLEXA

---

## 📱 Built on iPad

> **HOLEXA was built 100% on a normal iPad using iSH Shell.**

No MacBook. No PC. No expensive workstation.
Just an iPad, determination, and a vision.

A full compiler, 14+ libraries, a package manager, and support for 7 editors —
**all built on a normal iPad.**

> *"If you have an idea, your device doesn't matter. Your determination does."*
> — Ayush Giri

---

## ❤️ Support HOLEXA

HOLEXA is free and open source forever. If it helps you, consider supporting:

[![Ko-fi](https://img.shields.io/badge/Ko--fi-Support_HOLEXA-ff5e5b?style=flat-square&logo=ko-fi)](https://ko-fi.com/holexalang)
[![GitHub Sponsors](https://img.shields.io/badge/GitHub-Sponsor-ea4aaa?style=flat-square&logo=github)](https://github.com/sponsors/HOLEXA-LANG)
[![Star](https://img.shields.io/badge/GitHub-⭐_Star_this_repo-yellow?style=flat-square&logo=github)](https://github.com/HOLEXA-LANG/HOLEXA-LANG)

---

## 📜 License

MIT License — Copyright (c) 2026 Ayush Giri

See [LICENSE](LICENSE) for full details.

---

<div align="center">

<img src="logo.png" alt="HOLEXA" width="60" style="border-radius:50%;opacity:0.8;">

<br>

**[github.com/HOLEXA-LANG/HOLEXA-LANG](https://github.com/HOLEXA-LANG/HOLEXA-LANG)**

🐉 *Code like a Dragon. Think like a Human.*

<br>

Made with ❤️ by **Ayush Giri** · March 23, 2026 · India

</div>