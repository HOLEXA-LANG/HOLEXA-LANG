# 🐉 HOLEXA — Complete Installation Guide

> **Code like a Dragon. Think like a Human.**
>
> This guide explains **exactly** how to install HOLEXA on every device,
> step by step. If you can read English, you can follow this guide.
> Every single step is explained — nothing is skipped.

---

## 📋 Table of Contents

1. [What is HOLEXA?](#what-is-holexa)
2. [What gets installed?](#what-gets-installed)
3. [Linux — Step by Step](#-linux--ubuntu--debian--mint--arch)
4. [macOS — Step by Step](#-macos-mac-computer)
5. [Windows — Step by Step](#-windows-1011)
6. [iPad & iPhone — Step by Step](#-ipad--iphone-ios)
7. [Android — Step by Step](#-android-termux)
8. [Write Your First Program](#-write-your-first-holexa-program)
9. [Editor Setup — 7 Editors](#-editor-setup--syntax-highlighting)
10. [Common Errors & Fixes](#-common-errors--fixes)
11. [Uninstall](#-uninstall)

---

## What is HOLEXA?

HOLEXA is a **programming language** — a tool that lets you give instructions to a computer.
You write code in a file, then HOLEXA runs it and produces output.

Think of it like this:
- You write: `print("Hello!")`
- HOLEXA reads it and shows: `Hello!`

HOLEXA works on **every device** — Linux, Mac, Windows, iPad, iPhone, and Android.

---

## What gets installed?

When you install HOLEXA, you get **4 tools**:

| Tool | What you type | What it does |
|------|--------------|-------------|
| `hlxc` | `hlxc run hello.hlx` | **Runs** your HOLEXA programs |
| `hlxpm` | `hlxpm install math` | **Installs** extra libraries |
| `hlxfmt` | `hlxfmt hello.hlx` | **Formats** your code neatly |
| `hlxlint` | `hlxlint hello.hlx` | **Checks** your code for mistakes |

You will use `hlxc` the most — it runs your programs.

---

## 🐧 Linux — Ubuntu / Debian / Mint / Arch

### What is a Terminal?
A Terminal is a black window where you type commands.
To open it: press **Ctrl + Alt + T** on your keyboard.
Or search for "Terminal" in your apps.

---

### Step 1 — Open Terminal

Press **Ctrl + Alt + T**. A black or dark window opens. That is your Terminal.

---

### Step 2 — Install required tools

Copy this command and paste it in Terminal, then press **Enter**:

**Ubuntu / Debian / Mint / Pop OS:**
```bash
sudo apt update && sudo apt install -y curl git gcc make
```

> **What does this do?**
> - `sudo` = run as administrator
> - `apt update` = refresh the list of available software
> - `apt install` = download and install the tools
> - `curl` = tool to download files from internet
> - `git` = tool to download code from GitHub
> - `gcc` = C compiler — needed to build HOLEXA
> - `make` = build tool

> **It will ask for your password.** Type it (you won't see it — that's normal) and press Enter.

**Arch Linux / Manjaro:**
```bash
sudo pacman -S curl git gcc make
```

**Fedora / RHEL / CentOS:**
```bash
sudo dnf install -y curl git gcc make
```

---

### Step 3 — Install HOLEXA

Copy this **one command** and paste it in Terminal, then press **Enter**:

```bash
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

> **What does this do?**
> - Downloads the HOLEXA installer from GitHub
> - Builds the compiler automatically
> - Copies it to `/usr/local/bin/` so you can use it anywhere

Wait for it to finish. You will see a success message.

---

### Step 4 — Check it worked

Type this and press **Enter**:

```bash
hlxc --version
```

You should see:
```
HOLEXA Compiler v1.0.0
```

✅ **If you see that — HOLEXA is installed!**

---

### Step 5 — Run your first program

```bash
echo 'fn main() { print("Hello from HOLEXA!") }' > hello.hlx
hlxc run hello.hlx
```

You should see:
```
Hello from HOLEXA!
```

🎉 **It works! You just ran your first HOLEXA program!**

---

## 🍎 macOS (Mac computer)

### Step 1 — Open Terminal

Press **Command (⌘) + Space** to open Spotlight Search.
Type `Terminal` and press **Enter**.
A white or dark window opens. That is your Terminal.

---

### Step 2 — Install Xcode Command Line Tools

These are Apple's developer tools — needed to compile code.

```bash
xcode-select --install
```

> A popup window will appear saying **"Install developer tools?"**
> Click **Install** and wait. This may take 5-10 minutes.

When it finishes, come back to Terminal.

---

### Step 3 — Install HOLEXA

```bash
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

Wait for the installer to finish.

---

### Step 4 — Fix PATH (if needed)

If you get `hlxc: command not found` after installing, run:

```bash
echo 'export PATH=$PATH:/usr/local/bin' >> ~/.zshrc
source ~/.zshrc
```

---

### Step 5 — Check it worked

```bash
hlxc --version
```

Expected output:
```
HOLEXA Compiler v1.0.0
```

---

### Step 6 — Test it

```bash
echo 'fn main() { print("Hello Mac!") }' > hello.hlx
hlxc run hello.hlx
```

Output:
```
Hello Mac!
```

---

## 🪟 Windows 10/11

> Windows does not run Linux programs directly.
> We use **WSL2** (Windows Subsystem for Linux) which gives you a Linux environment inside Windows.
> This is free, official, and made by Microsoft.

---

### Step 1 — Open PowerShell as Administrator

Click the **Start button** (Windows icon at bottom left).
Search for **PowerShell**.
Right-click on **Windows PowerShell**.
Click **"Run as administrator"**.
Click **Yes** when asked.

---

### Step 2 — Install WSL2 with Ubuntu

In PowerShell, type this and press **Enter**:

```powershell
wsl --install
```

> **What this does:** Downloads and installs Ubuntu Linux inside Windows.
> This is completely safe — it's made by Microsoft.

Wait for it to finish. It will say "Please restart your machine".

---

### Step 3 — Restart your computer

Click Start → Power → Restart.

---

### Step 4 — Set up Ubuntu

After restarting, Ubuntu will open automatically and ask:
- **"Enter new UNIX username"** — type any username (like `ayush`) and press Enter
- **"Enter new UNIX password"** — type a password and press Enter (you won't see it — normal!)
- **"Retype new UNIX password"** — type it again

---

### Step 5 — Install HOLEXA inside Ubuntu

In the Ubuntu window, type:

```bash
sudo apt update && sudo apt install -y curl git gcc make
```

Then:

```bash
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

---

### Step 6 — Check it worked

```bash
hlxc --version
```

Expected output:
```
HOLEXA Compiler v1.0.0
```

---

### Step 7 — Open Ubuntu next time

To open Ubuntu in the future:
- Click Start → search "Ubuntu" → click it
- Or open Windows Terminal and select "Ubuntu"

---

### Step 8 — Test it

```bash
echo 'fn main() { print("Hello Windows!") }' > hello.hlx
hlxc run hello.hlx
```

Output:
```
Hello Windows!
```

---

## 📱 iPad & iPhone (iOS)

> We use an app called **iSH Shell** — it's a free Linux terminal for iPad and iPhone.
> This is how HOLEXA itself was built! 🐉

---

### Step 1 — Install iSH Shell

1. Open the **App Store** on your iPad or iPhone
2. Search for **"iSH Shell"**
3. Tap the app made by **Theodore Dubois**
4. Tap **Get** → **Install**
5. Wait for it to download (it's free)

---

### Step 2 — Open iSH Shell

Tap the iSH Shell icon on your home screen.
A black screen with a `#` prompt will appear. That is your terminal.

---

### Step 3 — Install required tools

Type this and press the Enter key on your keyboard:

```bash
apk update
```

Wait for it to finish. Then:

```bash
apk add curl git gcc make
```

> This will take a few minutes — iSH is slower than a PC but it works!
> Wait until you see the `#` prompt again.

---

### Step 4 — Install HOLEXA

```bash
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

> This may take **5-15 minutes** on iPad — iSH compiles slower. Be patient!
> The screen will show many lines of text. That's normal.

---

### Step 5 — Check it worked

```bash
hlxc --version
```

Expected output:
```
HOLEXA Compiler v1.0.0
```

---

### Step 6 — Test it

```bash
echo 'fn main() { print("Hello iPad!") }' > hello.hlx
hlxc run hello.hlx
```

Output:
```
Hello iPad!
```

> 💡 **Tip for iPad:** You can connect a Bluetooth keyboard for easier typing.
> In iSH settings, you can also enable "Disable Dimming" to keep screen on.

---

### 📣 Fun Fact

> **HOLEXA was built 100% on a normal iPad using iSH Shell.**
> No MacBook. No PC. Just an iPad and determination.
> — Ayush Giri, Creator of HOLEXA

---

## 🤖 Android (Termux)

> We use an app called **Termux** — a free Linux terminal for Android.

---

### Step 1 — Install Termux

> ⚠️ **IMPORTANT:** Do NOT install Termux from the Google Play Store.
> The Play Store version is outdated and broken.
> Download it from **F-Droid** instead — it's free and safe.

1. Open your browser on Android
2. Go to: **https://f-droid.org**
3. Search for **"Termux"**
4. Download and install the `.apk` file
5. If your phone asks to allow installing from unknown sources — tap **Allow**

---

### Step 2 — Open Termux

Tap the Termux icon. A dark screen with `$` appears. That is your terminal.

---

### Step 3 — Update Termux

```bash
pkg update && pkg upgrade
```

> Press **Y** and Enter when asked to confirm. Wait for it to finish.

---

### Step 4 — Install required tools

```bash
pkg install curl git clang make python
```

> Press **Y** and Enter when asked.

---

### Step 5 — Install HOLEXA

```bash
curl -fsSL https://raw.githubusercontent.com/HOLEXA-LANG/HOLEXA-LANG/main/install.sh | sh
```

Wait for it to complete.

---

### Step 6 — Fix PATH if needed

```bash
echo 'export PATH=$PATH:$PREFIX/bin' >> ~/.bashrc
source ~/.bashrc
```

---

### Step 7 — Check it worked

```bash
hlxc --version
```

Expected output:
```
HOLEXA Compiler v1.0.0
```

---

### Step 8 — Test it

```bash
echo 'fn main() { print("Hello Android!") }' > hello.hlx
hlxc run hello.hlx
```

Output:
```
Hello Android!
```

---

## 📝 Write Your First HOLEXA Program

Now that HOLEXA is installed, let's write a real program from scratch.

### Step 1 — Create a new file

In your terminal, type:

```bash
nano hello.hlx
```

> `nano` is a simple text editor inside the terminal.
> A new screen opens — this is where you write code.

---

### Step 2 — Write this code

Type exactly this (or copy-paste it):

```hlx
// My first HOLEXA program!
// Lines starting with // are comments — ignored by the computer

fn main() {
    print("Hello, World!")
    print("I am learning HOLEXA!")
    print("This is amazing!")

    // Variables
    let name = "Dragon"
    let age  = 10
    print("My name is " + name)
    print("I am " + str(age) + " years old")

    // Loop
    for i in 1..6 {
        print("Count: " + str(i))
    }
}
```

---

### Step 3 — Save the file

Press **Ctrl + X** → then press **Y** → then press **Enter**

---

### Step 4 — Run it

```bash
hlxc run hello.hlx
```

You should see:
```
Hello, World!
I am learning HOLEXA!
This is amazing!
My name is Dragon
I am 10 years old
Count: 1
Count: 2
Count: 3
Count: 4
Count: 5
```

🎉 **Congratulations! You wrote and ran your first real HOLEXA program!**

---

### Other ways to create files

**VS Code (on PC/Mac):**
```bash
code hello.hlx
```

**Vim:**
```bash
vim hello.hlx
# Press i to start typing
# Press Esc then :wq to save and quit
```

**Simple redirect (quickest):**
```bash
echo 'fn main() { print("Hi!") }' > hi.hlx
hlxc run hi.hlx
```

---

## 🖥️ Editor Setup — Syntax Highlighting

An editor with **syntax highlighting** makes code much easier to read.
Keywords turn colors, errors get underlined — like autocorrect for code.

---

### 1️⃣ VS Code — Full Support (Recommended)

VS Code is the most popular code editor. It's free.

**Install VS Code:**
- Download from: https://code.visualstudio.com
- Install it like any normal app

**Install HOLEXA extension:**

```bash
# First, clone the HOLEXA repository
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git

# Copy the VS Code extension
cp -r HOLEXA-LANG/editor-support/vscode ~/.vscode/extensions/holexa-lang
```

**Restart VS Code.** Open any `.hlx` file — you will see:
- 🎨 Syntax highlighting (keywords turn colors)
- 🐉 Dragon Dark theme
- ▶️ Press **Ctrl+Shift+R** to run
- 💡 Auto-complete suggestions

---

### 2️⃣ Vim — Syntax Highlighting

Vim is a powerful terminal editor.

```bash
# Clone repo if you haven't already
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git

# Install
mkdir -p ~/.vim/syntax ~/.vim/ftdetect
cp HOLEXA-LANG/editor-support/vim/holexa.vim ~/.vim/syntax/
cp HOLEXA-LANG/editor-support/vim/ftdetect.vim ~/.vim/ftdetect/holexa.vim
```

Open any `.hlx` file in Vim — colors appear automatically.

---

### 3️⃣ Neovim — Full LSP Support

Neovim gives you autocomplete, error detection, and more.

```bash
mkdir -p ~/.config/nvim/lua
cp HOLEXA-LANG/editor-support/neovim/holexa.lua ~/.config/nvim/lua/
```

Add to `~/.config/nvim/init.lua`:
```lua
require('holexa')
```

---

### 4️⃣ Emacs — Major Mode

```bash
cp HOLEXA-LANG/editor-support/emacs/holexa-mode.el ~/.emacs.d/
```

Add to `~/.emacs`:
```elisp
(load "~/.emacs.d/holexa-mode.el")
```

---

### 5️⃣ Sublime Text — Highlighting

```bash
# Find Sublime packages folder:
# Mac:     ~/Library/Application Support/Sublime Text/Packages/User/
# Linux:   ~/.config/sublime-text/Packages/User/
# Windows: %APPDATA%\Sublime Text\Packages\User\

cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-syntax [YOUR_PACKAGES_FOLDER]
cp HOLEXA-LANG/editor-support/sublime/HOLEXA.sublime-completions [YOUR_PACKAGES_FOLDER]
```

---

### 6️⃣ IntelliJ IDEA / JetBrains

```
1. Open IntelliJ IDEA
2. Go to: Settings (Ctrl+Alt+S)
3. Click: Editor → File Types
4. Click the + button
5. Import: HOLEXA-LANG/editor-support/intellij/holexa.xml
6. Click OK
```

---

### 7️⃣ Atom — Grammar

```bash
mkdir -p ~/.atom/packages/language-holexa
cp HOLEXA-LANG/editor-support/atom/holexa.cson ~/.atom/packages/language-holexa/
```

---

### Editor Comparison

| Editor | Best for | Difficulty |
|--------|---------|-----------|
| **VS Code** | Everyone — beginners to experts | ⭐ Easy |
| **Neovim** | Power users who love the terminal | ⭐⭐⭐ Hard |
| **Vim** | Terminal users | ⭐⭐ Medium |
| **Sublime** | Lightweight and fast | ⭐ Easy |
| **IntelliJ** | Java/JVM developers | ⭐⭐ Medium |
| **Emacs** | Advanced users | ⭐⭐⭐ Hard |
| **Atom** | Beginners | ⭐ Easy |

---

## ❌ Common Errors & Fixes

---

### Error: `hlxc: command not found`

**What it means:** The terminal can't find the `hlxc` program.
**Fix:**

```bash
export PATH=$PATH:/usr/local/bin
```

To make this permanent (so it works every time):

```bash
# For bash users:
echo 'export PATH=$PATH:/usr/local/bin' >> ~/.bashrc
source ~/.bashrc

# For zsh users (Mac):
echo 'export PATH=$PATH:/usr/local/bin' >> ~/.zshrc
source ~/.zshrc
```

---

### Error: `gcc: not found` or `gcc: command not found`

**What it means:** The C compiler is missing — needed to build HOLEXA.
**Fix by platform:**

```bash
# Ubuntu/Debian/Mint:
sudo apt install gcc

# Arch Linux:
sudo pacman -S gcc

# Fedora:
sudo dnf install gcc

# iPad (iSH):
apk add gcc

# Android (Termux):
pkg install clang
```

---

### Error: `make: not found`

**Fix:**

```bash
# Ubuntu/Debian:
sudo apt install make

# iPad:
apk add make

# Android:
pkg install make
```

---

### Error: `Permission denied`

**What it means:** You need administrator access.
**Fix:** Add `sudo` before the command:

```bash
sudo cp hlxc /usr/local/bin/hlxc
```

---

### Error: `git clone failed` or `Could not resolve host`

**What it means:** No internet connection.
**Fix:** Check your WiFi or mobile data is on. Try again.

---

### Error: `curl: command not found`

**Fix:**

```bash
# Ubuntu:
sudo apt install curl

# iPad:
apk add curl

# Android:
pkg install curl
```

---

### Error in your HOLEXA code: `Variable 'x' is not defined`

**What it means:** You used a variable before declaring it.
**Fix:** Always declare with `let` first:

```hlx
// Wrong:
print(str(x))     // x doesn't exist yet!

// Right:
let x = 42
print(str(x))     // Now x exists
```

---

### Error: `Division by zero`

**What it means:** You divided a number by 0.
**Fix:** Check before dividing:

```hlx
fn safe_divide(a: Int, b: Int) -> Int {
    if b == 0 {
        print("Cannot divide by zero!")
        return 0
    }
    return a / b
}
```

---

### Error: `Cannot reassign constant`

**What it means:** You tried to change a `const` variable.
**Fix:** Use `let` instead of `const` if the value needs to change:

```hlx
// Wrong:
const score = 0
score = 10    // ERROR! const can't change

// Right:
let score = 0
score = 10    // OK! let can change
```

---

## 🗑️ Uninstall

To completely remove HOLEXA:

```bash
# Remove compiler and tools
sudo rm -f /usr/local/bin/hlxc
sudo rm -f /usr/local/bin/hlxpm
sudo rm -f /usr/local/bin/hlxfmt
sudo rm -f /usr/local/bin/hlxlint
sudo rm -f /usr/local/bin/hlxbuild

# Remove repository (if cloned)
rm -rf ~/HOLEXA-LANG
```

---

## ✅ Quick Reference Card

Save this — you'll use it every day:

```bash
# ── Running programs ──────────────────────
hlxc run hello.hlx           # Run a program
hlxc build hello.hlx         # Compile to binary
hlxc build hello.hlx -o app  # Compile with name
hlxc check hello.hlx         # Check for errors only

# ── Package manager ───────────────────────
hlxpm install math           # Install math library
hlxpm install string fs      # Install multiple
hlxpm create myapp           # Create new project
hlxpm list                   # See installed packages
hlxpm update                 # Update all packages

# ── Code tools ────────────────────────────
hlxfmt hello.hlx             # Auto-format code
hlxlint hello.hlx            # Check code quality

# ── Version check ─────────────────────────
hlxc --version               # Show version
hlxpm --version              # Show package manager version
```

---

## 🌐 Links

| Resource | Link |
|----------|------|
| 🌐 Website | https://holexa-lang.github.io/HOLEXA-LANG/ |
| 📖 Documentation | https://holexa-lang.github.io/HOLEXA-LANG/docs.html |
| 💻 GitHub | https://github.com/HOLEXA-LANG/HOLEXA-LANG |
| ❤️ Support | https://ko-fi.com/holexalang |

---

<div align="center">

🐉 **Code like a Dragon. Think like a Human.**

Created by **Ayush Giri** · Launched March 23, 2026 · Built on iPad · MIT License

</div>
