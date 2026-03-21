# HOLEXA — Complete Installation Guide

> **Code like a Dragon. Think like a Human.** 🐉
> GitHub: https://github.com/HOLEXA-LANG/HOLEXA-LANG
> Try Online: https://holexa-lang.github.io/HOLEXA-LANG/

---

## Step 1: Install HOLEXA

### Linux / Mac
```sh
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

### iPad (iSH Shell)
```sh
apk add curl git gcc make
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

### Windows
```
1. Open PowerShell as Administrator
2. Run: wsl --install
3. Restart computer
4. Open Ubuntu
5. Run the Linux command above
```

### Manual (From Source)
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/compiler
make
sudo cp hlxc /usr/local/bin/hlxc
sudo cp ../package-manager/hlxpm /usr/local/bin/hlxpm
sudo cp ../tools/hlxfmt/hlxfmt /usr/local/bin/hlxfmt
sudo cp ../tools/hlxlint/hlxlint /usr/local/bin/hlxlint
sudo cp ../tools/hlxbuild/hlxbuild /usr/local/bin/hlxbuild
```

### Verify
```sh
hlxc --version
hlxpm --version
```

---

## Step 2: Hello World
```sh
cat > hello.hlx << 'EOF'
fn main() {
    print("Hello, HOLEXA!")
    print("Code like a Dragon!")
}
EOF

hlxc run hello.hlx
```

---

## Step 3: Package Manager (hlxpm)

### Install a Package
```sh
hlxpm install math
hlxpm install http
hlxpm install json
hlxpm install crypto
```

### Create New Project
```sh
hlxpm create myapp
cd myapp
hlxc run src/main.hlx
```

### List Installed Packages
```sh
hlxpm list
```

### Search Packages
```sh
hlxpm search math
```

### Available Packages
| Package | Description |
|---------|-------------|
| math | Mathematics functions |
| string | String operations |
| fs | File system |
| http | HTTP client/server |
| json | JSON parser |
| crypto | Cryptography |
| time | Date and time |
| random | Random generation |
| os | Operating system |
| net | Networking |
| io | Input/Output |
| list | List operations |
| map | Map operations |
| process | Process control |

---

## Step 4: Developer Tools

### Format Code
```sh
hlxfmt myfile.hlx
```

### Lint Code
```sh
hlxlint myfile.hlx
```

### Build Project
```sh
hlxbuild init
hlxbuild run
hlxbuild test
```

---

## Step 5: VS Code Extension

### Method 1 — Auto (via install.sh) ✅
Already installed automatically!

### Method 2 — Manual
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cp -r HOLEXA-LANG/editor-support/vscode \
   ~/.vscode/extensions/holexa-lang
```
Restart VS Code ✅

### Method 3 — Build & Install
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/editor-support/vscode
npm install -g @vscode/vsce
vsce package --no-dependencies
code --install-extension holexa-lang-1.0.0.vsix
```

### Features after install:
- Dragon logo on `.hlx` files 🐉
- Syntax highlighting
- Auto-complete
- `Ctrl+Shift+R` to run file
- Format on save

---

## Step 6: Online Browser IDE

### Option 1 — GitHub Codespaces (Best!)
```
1. github.com/HOLEXA-LANG/HOLEXA-LANG
2. Click green "Code" button
3. Click "Codespaces" tab
4. Click "Create codespace on main"
5. VS Code opens in browser with terminal!
```

Then in terminal:
```sh
cd compiler && make
./hlxc run ../examples/basic/hello.hlx
```

### Option 2 — HOLEXA Web Playground
```
https://holexa-lang.github.io/HOLEXA-LANG/
```
Write and run HOLEXA code directly in browser!
No installation needed! ✅

### Option 3 — Gitpod
```
https://gitpod.io/#https://github.com/HOLEXA-LANG/HOLEXA-LANG
```

---

## Step 7: Other Editors

### Vim
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
mkdir -p ~/.vim/syntax ~/.vim/ftdetect
cp HOLEXA-LANG/editor-support/vim/holexa.vim ~/.vim/syntax/
cp HOLEXA-LANG/editor-support/vim/ftdetect.vim ~/.vim/ftdetect/holexa.vim
```

Add to `~/.vimrc`:
```vim
syntax on
autocmd BufNewFile,BufRead *.hlx set syntax=holexa
autocmd BufNewFile,BufRead *.hlx set tabstop=4
```

### Neovim
```sh
cp HOLEXA-LANG/editor-support/neovim/holexa.lua \
   ~/.config/nvim/lua/holexa.lua
```
Add to `init.lua`: `require('holexa')`

### Emacs
Add to `~/.emacs`:
```elisp
(load "~/HOLEXA-LANG/editor-support/emacs/holexa-mode.el")
```

### Sublime Text
```sh
cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-syntax \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/
```

### IntelliJ / JetBrains
```
Settings → Editor → File Types
→ + → Import: editor-support/intellij/holexa.xml
→ Pattern: *.hlx → OK
```

---

## Complete Test
```sh
cat > fulltest.hlx << 'EOF'
fn greet(name: String) -> String {
    return "Hello " + name + "!"
}

fn factorial(n: Int) -> Int {
    if n <= 1 { return 1 }
    return n * factorial(n - 1)
}

fn is_even(n: Int) -> Bool {
    if n % 2 == 0 { return true }
    return false
}

fn main() {
    print(greet("HOLEXA"))

    print("Factorials:")
    for i in 1..6 {
        print(str(i) + "! = " + str(factorial(i)))
    }

    print("Even check:")
    print("is_even(4): " + str(is_even(4)))
    print("is_even(7): " + str(is_even(7)))

    let x = 42
    if x > 10 {
        print("x = " + str(x) + " is big!")
    }

    try {
        print("Error handling: OK")
    } catch err {
        print("Caught!")
    }

    print("Done! Code like a Dragon!")
}
EOF

hlxc run fulltest.hlx
```

**Expected Output:**
```
Hello HOLEXA!
Factorials:
1! = 1
2! = 2
3! = 6
4! = 24
5! = 120
Even check:
is_even(4): true
is_even(7): false
x = 42 is big!
Error handling: OK
Done! Code like a Dragon!
```

---

## Quick Reference

| Command | Description |
|---------|-------------|
| `hlxc run file.hlx` | Run program |
| `hlxc --version` | Show version |
| `hlxpm install pkg` | Install package |
| `hlxpm create app` | Create project |
| `hlxfmt file.hlx` | Format code |
| `hlxlint file.hlx` | Lint code |
| `hlxbuild run` | Build & run |

---

## Try Online — No Install!
**https://holexa-lang.github.io/HOLEXA-LANG/**

---

## Support
- Issues: https://github.com/HOLEXA-LANG/HOLEXA-LANG/issues
- Discussions: https://github.com/HOLEXA-LANG/HOLEXA-LANG/discussions

---

*Created by **Ayush Giri** | HOLEXA v1.0.0 | March 2026*
*Code like a Dragon. Think like a Human. 🐉*
