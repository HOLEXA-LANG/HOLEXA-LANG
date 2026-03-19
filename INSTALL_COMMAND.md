# HOLEXA Editor Support — Installation Guide

> **Code like a Dragon. Think like a Human.** 🐉
> 
> GitHub: [github.com/HOLEXA-LANG/HOLEXA-LANG](https://github.com/HOLEXA-LANG/HOLEXA-LANG)

---

## Step 1: Install HOLEXA Compiler

**Linux / Mac:**
```sh
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

**iPad (iSH Shell):**
```sh
apk add git gcc make
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/compiler && make
cp hlxc /usr/local/bin/hlxc
```

**Windows (WSL):**
```sh
wsl --install
# Then use Linux commands above
```

**Verify Installation:**
```sh
hlxc --version
```

---

## VS Code — Direct Install

### Step 1: Clone the Repository
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
```

### Step 2: Copy Extension Files

**Mac / Linux:**
```sh
cp -r HOLEXA-LANG/editor-support/vscode \
   ~/.vscode/extensions/holexa-lang
```

**Windows:**
```sh
xcopy HOLEXA-LANG\editor-support\vscode ^
   %USERPROFILE%\.vscode\extensions\holexa-lang /E /I
```

### Step 3: Restart VS Code
Close and reopen VS Code.

### Step 4: Test
Create a file named `hello.hlx` and open it in VS Code.
You will see the **Dragon logo** and **syntax highlighting**! 🐉

---

## Vim
```sh
mkdir -p ~/.vim/syntax ~/.vim/ftdetect

cp HOLEXA-LANG/editor-support/vim/holexa.vim \
   ~/.vim/syntax/holexa.vim

cp HOLEXA-LANG/editor-support/vim/ftdetect.vim \
   ~/.vim/ftdetect/holexa.vim
```

Add to `~/.vimrc`:
```vim
syntax on
autocmd BufNewFile,BufRead *.hlx set syntax=holexa
autocmd BufNewFile,BufRead *.hlx set tabstop=4
autocmd BufNewFile,BufRead *.hlx set shiftwidth=4
autocmd BufNewFile,BufRead *.hlx set expandtab
```

---

## Neovim
```sh
cp HOLEXA-LANG/editor-support/neovim/holexa.lua \
   ~/.config/nvim/lua/holexa.lua
```

Add to `init.lua`:
```lua
require('holexa')
```

---

## Emacs

Add to `~/.emacs` or `~/.emacs.d/init.el`:
```elisp
(load "~/HOLEXA-LANG/editor-support/emacs/holexa-mode.el")
```

---

## Sublime Text

**Mac:**
```sh
cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-syntax \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/

cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-completions \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/
```

**Linux:**
```sh
cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-syntax \
   ~/.config/sublime-text/Packages/User/
```

**Windows:**
```sh
copy HOLEXA-LANG\editor-support\sublime\HOLEXA.sublime-syntax ^
   "%APPDATA%\Sublime Text\Packages\User\"
```

---

## IntelliJ / PyCharm / WebStorm / JetBrains IDEs

1. Open `Settings`
2. Go to `Editor` → `File Types`
3. Click `+` to add new file type
4. Import `HOLEXA-LANG/editor-support/intellij/holexa.xml`
5. Add pattern: `*.hlx`
6. Click `OK`

---

## Atom
```sh
mkdir -p ~/.atom/packages/language-holexa/grammars/

cp HOLEXA-LANG/editor-support/atom/holexa.cson \
   ~/.atom/packages/language-holexa/grammars/holexa.cson
```

---

## Test Your Installation

Create `hello.hlx`:
```hlx
fn main() {
    print("Hello, HOLEXA!")
    print("Code like a Dragon!")
}
```

Run:
```sh
hlxc run hello.hlx
```

Expected output:
```
Hello, HOLEXA!
Code like a Dragon!
```

---

## Try Online — No Installation Required!

Visit: **[https://holexa-lang.github.io/HOLEXA-LANG/](https://holexa-lang.github.io/HOLEXA-LANG/)**

Write and run HOLEXA code directly in your browser! 🐉

---

## Support

- GitHub Issues: [Report a bug](https://github.com/HOLEXA-LANG/HOLEXA-LANG/issues)
- GitHub Discussions: [Ask a question](https://github.com/HOLEXA-LANG/HOLEXA-LANG/discussions)

---

*Created by **Ayush** | HOLEXA v1.0.0 | March 2025*

*Code like a Dragon. Think like a Human. 🐉*
