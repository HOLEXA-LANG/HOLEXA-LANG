# HOLEXA Editor Support Installation

> Code like a Dragon. Think like a Human. 🐉
> github.com/HOLEXA-LANG/HOLEXA-LANG

---

## Step 1: HOLEXA Compiler Install

**Linux / Mac:**
```sh
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

**iPad (iSH):**
```sh
apk add git gcc make
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
cd HOLEXA-LANG/compiler && make
cp hlxc /usr/local/bin/hlxc
```

**Verify:**
```sh
hlxc --version
```

---

## VS Code — Direct Install

### Step 1: Files Download करो
```sh
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git
```

### Step 2: Extension Folder में Copy करो

**Mac:**
```sh
cp -r HOLEXA-LANG/editor-support/vscode \
   ~/.vscode/extensions/holexa-lang
```

**Linux:**
```sh
cp -r HOLEXA-LANG/editor-support/vscode \
   ~/.vscode/extensions/holexa-lang
```

**Windows:**
```sh
xcopy HOLEXA-LANG\editor-support\vscode \
   %USERPROFILE%\.vscode\extensions\holexa-lang /E /I
```

### Step 3: VS Code Restart करो
VS Code बंद करो और फिर खोलो.

### Step 4: Test करो
```sh
echo 'fn main() { print("Hello!") }' > test.hlx
```
`test.hlx` VS Code में खोलो —
**Dragon logo + colors दिखेंगे!** 🐉

---

## Vim
```sh
mkdir -p ~/.vim/syntax ~/.vim/ftdetect
cp HOLEXA-LANG/editor-support/vim/holexa.vim \
   ~/.vim/syntax/holexa.vim
cp HOLEXA-LANG/editor-support/vim/ftdetect.vim \
   ~/.vim/ftdetect/holexa.vim
```

`~/.vimrc` में add करो:
```vim
syntax on
autocmd BufNewFile,BufRead *.hlx set syntax=holexa
autocmd BufNewFile,BufRead *.hlx set tabstop=4
```

---

## Neovim
```sh
cp HOLEXA-LANG/editor-support/neovim/holexa.lua \
   ~/.config/nvim/lua/holexa.lua
```

`init.lua` में add करो:
```lua
require('holexa')
```

---

## Emacs

`~/.emacs` में add करो:
```elisp
(load "~/HOLEXA-LANG/editor-support/emacs/holexa-mode.el")
```

---

## Sublime Text
```sh
cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-syntax \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/
```

---

## IntelliJ / PyCharm / WebStorm
```
Settings → Editor → File Types
→ + New → Import:
HOLEXA-LANG/editor-support/intellij/holexa.xml
→ Pattern: *.hlx → OK
```

---

## Test — Hello World
```sh
echo 'fn main() { print("Hello HOLEXA!") }' > hello.hlx
hlxc run hello.hlx
```

Output:
```
Hello HOLEXA!
```

---

## Try Online — No Install!
**https://holexa-lang.github.io/HOLEXA-LANG/**

---

*Created by Ayush | HOLEXA v1.0.0 | March 2025*
*Code like a Dragon. Think like a Human. 🐉*