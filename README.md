<div align="center">

<img src="logo.png" alt="HOLEXA Logo" width="110" style="border-radius:50%;border:3px solid #58a6ff;padding:4px;box-shadow:0 0 20px rgba(88,166,255,0.3);">

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
┣ 📂 stdlib                               # Standard Library (14 libraries)
┃ ┣ 📜 index.hlx                          # Stdlib registry
┃ ┣ 📂 math/      📄 math.hlx             # abs, sqrt, pow, sin, cos, PI
┃ ┣ 📂 string/    📄 string.hlx           # upper, lower, trim, split
┃ ┣ 📂 fs/        📄 fs.hlx               # read, write, delete, exists
┃ ┣ 📂 http/      📄 http.hlx             # get, post, server
┃ ┣ 📂 json/      📄 json.hlx             # parse, stringify
┃ ┣ 📂 crypto/    📄 crypto.hlx           # hash, encrypt, sha256
┃ ┣ 📂 time/      📄 time.hlx             # now, date, sleep, format
┃ ┣ 📂 random/    📄 random.hlx           # int, float, seed
┃ ┣ 📂 os/        📄 os.hlx               # env, args, platform
┃ ┣ 📂 net/       📄 net.hlx              # tcp, udp, socket
┃ ┣ 📂 list/      📄 list.hlx             # push, pop, sort, filter
┃ ┣ 📂 map/       📄 map.hlx              # set, get, keys, values
┃ ┣ 📂 io/        📄 io.hlx               # stdin, stdout, streams
┃ ┗ 📂 process/   📄 process.hlx          # spawn, kill, pid, wait
┃
┣ 📂 package-manager                      # hlxpm — Package Manager
┃ ┗ 📜 hlxpm                              # Binary (hlxpm install / create)
┃
┣ 📂 packages                             # Package Registry
┃ ┗ 📜 registry.json                      # All available packages
┃
┣ 📂 tools                                # Developer Tools
┃ ┣ 📂 hlxfmt/    📄 hlxfmt              # Code formatter
┃ ┣ 📂 hlxlint/   📄 hlxlint             # Code linter
┃ ┣ 📂 hlxbuild/  📄 hlxbuild            # Project builder
┃ ┗ 📂 lsp/       📄 hlx-lsp             # Language Server Protocol
┃
┣ 📂 editor-support                       # Support for 7 Code Editors
┃ ┣ 📜 INSTALL.md                         # Editor setup guide
┃ ┣ 📂 vscode/                            # VS Code Extension (Full)
┃ ┃ ┣ 📜 package.json · extension.js · snippets.json · logo.png
┃ ┃ ┣ 📂 syntaxes/ 📄 holexa.tmLanguage.json
┃ ┃ ┗ 📂 themes/   📄 dragon-dark.json
┃ ┣ 📂 vim/        📄 holexa.vim · ftdetect.vim
┃ ┣ 📂 neovim/     📄 holexa.lua
┃ ┣ 📂 emacs/      📄 holexa-mode.el
┃ ┣ 📂 sublime/    📄 HOLEXA.sublime-syntax · completions
┃ ┣ 📂 intellij/   📄 holexa.xml
┃ ┗ 📂 atom/       📄 holexa.cson
┃
┣ 📂 self-hosting                         # Compiler written in HOLEXA
┃ ┣ 📜 hlxc_lexer.hlx                    # Lexer in HOLEXA
┃ ┣ 📜 hlxc_parser.hlx                   # Parser in HOLEXA
┃ ┣ 📜 hlxc_interpreter.hlx              # Interpreter in HOLEXA
┃ ┗ 📜 hlxc_selfhosted.hlx               # Full compiler in HOLEXA
┃
┣ 📂 tests                                # Complete Test Suite
┃ ┣ 📜 final_test.hlx                     # Final test — all pass ✅
┃ ┣ 📜 run_tests.sh                       # Run all tests
┃ ┣ 📂 unit/                              # Unit tests
┃ ┃ ┣ 📜 test_variables.hlx · test_functions.hlx · test_loops.hlx
┃ ┃ ┣ 📜 test_conditions.hlx · test_strings.hlx
┃ ┣ 📂 integration/                       # Integration tests
┃ ┃ ┣ 📜 test_algorithms.hlx · test_class.hlx · test_error.hlx
┃ ┗ 📂 realworld/
┃   ┗ 📜 task_manager.hlx
┃
┣ 📂 examples                             # Example Programs
┃ ┣ 📜 stdlib_test.hlx                    # Standard library examples
┃ ┣ 📂 basic/      📄 hello.hlx           # Hello World
┃ ┗ 📂 advanced/   📄 dragon.hlx          # Dragon class demo
┃
┣ 📂 docs                                 # Technical Documentation
┃ ┣ 📜 HOLEXA-SPEC.md                     # Full language specification
┃ ┣ 📂 guide/      COMPILER · HLXPM · LANGUAGE · TOOLS
┃ ┣ 📂 syntax/     GRAMMAR · HOLEXA-SYNTAX
┃ ┣ 📂 stdlib/     README.md
┃ ┣ 📂 api/        README.md
┃ ┗ 📂 examples/   README.md
┃
┣ 📂 runtime                              # Runtime Library (C)
┃ ┣ 📜 runtime.c · runtime.h
┃
┣ 📂 myapp                                # Example Project (hlxpm create)
┃ ┣ 📜 hlxpm.json
┃ ┣ 📂 src/     📄 main.hlx
┃ ┗ 📂 tests/   📄 test_main.hlx
┃
┣ 📜 HISTORY.md                           # Language history and story
┣ 📜 INSTALL_COMMAND.md                   # Quick install reference
┣ 📜 LICENSE                              # MIT License (2026)
┣ 📜 README.md                            # This file
┣ 📜 docs.html                            # Full documentation (32 chapters)
┣ 📜 index.html                           # Official website
┣ 📜 install.sh                           # Universal installer
┣ 📜 hlxbuild.json                        # Build configuration
┗ 📜 logo.png                             # HOLEXA Dragon logo
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