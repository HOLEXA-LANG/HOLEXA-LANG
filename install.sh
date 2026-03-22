#!/bin/sh
# HOLEXA Universal Installer v1.0.0
# Code like a Dragon. Think like a Human.
# One command installs everything!

GREEN='\033[0;32m'
CYAN='\033[0;36m'
RED='\033[0;31m'
NC='\033[0m'

echo ""
echo "  ██╗  ██╗ ██████╗ ██╗     ███████╗██╗  ██╗ █████╗"
echo "  ██║  ██║██╔═══██╗██║     ██╔════╝╚██╗██╔╝██╔══██╗"
echo "  ███████║██║   ██║██║     █████╗   ╚███╔╝ ███████║"
echo "  ██╔══██║██║   ██║██║     ██╔══╝   ██╔██╗ ██╔══██║"
echo "  ██║  ██║╚██████╔╝███████╗███████╗██╔╝ ██╗██║  ██║"
echo "  ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝"
echo ""
echo "  HOLEXA Installer v1.0.0"
echo "  Code like a Dragon. Think like a Human."
echo ""

# ── Detect OS ─────────────────────────────────────────
OS="unknown"
ARCH=$(uname -m)

case "$(uname -s)" in
    Darwin)  OS="mac"   ;;
    Linux)   OS="linux" ;;
    MINGW*|MSYS*|CYGWIN*) OS="windows" ;;
esac

echo "  Detected OS:   $OS"
echo "  Architecture:  $ARCH"
echo ""

# ── Install Dependencies ──────────────────────────────
echo "  Checking dependencies..."

install_deps() {
    if [ "$OS" = "mac" ]; then
        if ! command -v gcc > /dev/null 2>&1; then
            echo "  Installing Xcode tools..."
            xcode-select --install
        fi
        if ! command -v git > /dev/null 2>&1; then
            echo "  Installing git..."
            brew install git 2>/dev/null || true
        fi
    elif [ "$OS" = "linux" ]; then
        if command -v apt-get > /dev/null 2>&1; then
            apt-get update -qq
            apt-get install -y -qq git gcc make
        elif command -v apk > /dev/null 2>&1; then
            apk add --quiet git gcc make
    	elif command -v pkg > /dev/null 2>&1; then
        	pkg update -y && pkg install -y git clang make
        elif command -v yum > /dev/null 2>&1; then
            yum install -y -q git gcc make
        elif command -v dnf > /dev/null 2>&1; then
            dnf install -y -q git gcc make
        fi
    fi
}

install_deps
echo "  Dependencies ready!"

# ── Clone Repository ──────────────────────────────────
echo ""
echo "  Downloading HOLEXA..."

INSTALL_DIR="/tmp/holexa_install"
rm -rf "$INSTALL_DIR"
git clone --quiet https://github.com/HOLEXA-LANG/HOLEXA-LANG.git "$INSTALL_DIR"

if [ ! -d "$INSTALL_DIR" ]; then
    echo "${RED}  Error: Download failed!${NC}"
    echo "  Check your internet connection."
    exit 1
fi

echo "  Download complete!"

# ── Build Compiler ────────────────────────────────────
echo ""
echo "  Building HOLEXA compiler..."

cd "$INSTALL_DIR/compiler"
make clean > /dev/null 2>&1
make > /dev/null 2>&1

if [ ! -f "hlxc" ]; then
    echo "${RED}  Error: Build failed!${NC}"
    echo "  Make sure gcc is installed."
    exit 1
fi

echo "  Compiler built!"

# ── Install Compiler ──────────────────────────────────
echo ""
echo "  Installing hlxc..."

# Try different install locations
if [ -w "/usr/local/bin" ]; then
    cp hlxc /usr/local/bin/hlxc
    cp "$INSTALL_DIR/package-manager/hlxpm" /usr/local/bin/hlxpm
    cp "$INSTALL_DIR/tools/hlxfmt/hlxfmt" /usr/local/bin/hlxfmt
    cp "$INSTALL_DIR/tools/hlxlint/hlxlint" /usr/local/bin/hlxlint
    cp "$INSTALL_DIR/tools/hlxbuild/hlxbuild" /usr/local/bin/hlxbuild
    chmod +x /usr/local/bin/hlxc
    chmod +x /usr/local/bin/hlxpm
    chmod +x /usr/local/bin/hlxfmt
    chmod +x /usr/local/bin/hlxlint
    chmod +x /usr/local/bin/hlxbuild
elif [ -w "$HOME/.local/bin" ]; then
    mkdir -p "$HOME/.local/bin"
    cp hlxc "$HOME/.local/bin/hlxc"
    cp "$INSTALL_DIR/package-manager/hlxpm" "$HOME/.local/bin/hlxpm"
    cp "$INSTALL_DIR/tools/hlxfmt/hlxfmt" "$HOME/.local/bin/hlxfmt"
    cp "$INSTALL_DIR/tools/hlxlint/hlxlint" "$HOME/.local/bin/hlxlint"
    cp "$INSTALL_DIR/tools/hlxbuild/hlxbuild" "$HOME/.local/bin/hlxbuild"
    chmod +x "$HOME/.local/bin/hlxc"
    chmod +x "$HOME/.local/bin/hlxpm"
    chmod +x "$HOME/.local/bin/hlxfmt"
    chmod +x "$HOME/.local/bin/hlxlint"
    chmod +x "$HOME/.local/bin/hlxbuild"
    export PATH="$HOME/.local/bin:$PATH"
    echo "export PATH=\"\$HOME/.local/bin:\$PATH\"" >> "$HOME/.bashrc"
    echo "export PATH=\"\$HOME/.local/bin:\$PATH\"" >> "$HOME/.zshrc" 2>/dev/null || true
else
    sudo cp hlxc /usr/local/bin/hlxc
    sudo cp "$INSTALL_DIR/package-manager/hlxpm" /usr/local/bin/hlxpm
    sudo cp "$INSTALL_DIR/tools/hlxfmt/hlxfmt" /usr/local/bin/hlxfmt
    sudo cp "$INSTALL_DIR/tools/hlxlint/hlxlint" /usr/local/bin/hlxlint
    sudo cp "$INSTALL_DIR/tools/hlxbuild/hlxbuild" /usr/local/bin/hlxbuild
    sudo chmod +x /usr/local/bin/hlxc
fi

echo "  Compiler installed!"

# ── Install VS Code Extension ─────────────────────────
echo ""
echo "  Checking VS Code..."

install_vscode_extension() {
    EXT_SRC="$INSTALL_DIR/editor-support/vscode"

    # Check VS Code locations
    if command -v code > /dev/null 2>&1; then
        # Use vsce if available
        if command -v vsce > /dev/null 2>&1; then
            cd "$EXT_SRC"
            vsce package --no-dependencies > /dev/null 2>&1
            code --install-extension holexa-lang-1.0.0.vsix > /dev/null 2>&1
            echo "  VS Code extension installed via marketplace!"
            return
        fi

        # Direct copy method
        EXT_DIR="$HOME/.vscode/extensions/holexa-lang"
        mkdir -p "$EXT_DIR"
        cp -r "$EXT_SRC/." "$EXT_DIR/"
        echo "  VS Code extension installed!"

    elif [ -d "$HOME/.vscode-server/extensions" ]; then
        # VS Code Server (Codespaces/Remote)
        EXT_DIR="$HOME/.vscode-server/extensions/holexa-lang"
        mkdir -p "$EXT_DIR"
        cp -r "$EXT_SRC/." "$EXT_DIR/"
        echo "  VS Code Server extension installed!"

    elif [ -d "$HOME/Library/Application Support/Code/User/extensions" ]; then
        # Mac VS Code
        EXT_DIR="$HOME/Library/Application Support/Code/User/extensions/holexa-lang"
        mkdir -p "$EXT_DIR"
        cp -r "$EXT_SRC/." "$EXT_DIR/"
        echo "  VS Code extension installed (Mac)!"

    else
        echo "  VS Code not found — skipping extension."
        echo "  Install VS Code from: code.visualstudio.com"
        echo "  Then run: cp -r $EXT_SRC ~/.vscode/extensions/holexa-lang"
    fi
}

install_vscode_extension

# ── Install Vim Support ───────────────────────────────
if command -v vim > /dev/null 2>&1 || command -v nvim > /dev/null 2>&1; then
    echo ""
    echo "  Installing Vim/Neovim support..."
    mkdir -p "$HOME/.vim/syntax" "$HOME/.vim/ftdetect"
    cp "$INSTALL_DIR/editor-support/vim/holexa.vim" "$HOME/.vim/syntax/" 2>/dev/null || true
    cp "$INSTALL_DIR/editor-support/vim/ftdetect.vim" "$HOME/.vim/ftdetect/holexa.vim" 2>/dev/null || true

    if command -v nvim > /dev/null 2>&1; then
        mkdir -p "$HOME/.config/nvim/lua"
        cp "$INSTALL_DIR/editor-support/neovim/holexa.lua" "$HOME/.config/nvim/lua/" 2>/dev/null || true
    fi
    echo "  Vim/Neovim support installed!"
fi

# ── Cleanup ───────────────────────────────────────────
cd /
rm -rf "$INSTALL_DIR"

# ── Verify ────────────────────────────────────────────
echo ""
echo "  Verifying installation..."

if command -v hlxc > /dev/null 2>&1; then
    VERSION=$(hlxc --version 2>/dev/null || echo "1.0.0")
    echo ""
    echo "${GREEN}  ✓ HOLEXA installed successfully!${NC}"
    echo "${GREEN}  ✓ Version: $VERSION${NC}"
    echo ""
    echo "  ════════════════════════════════════"
    echo "  Commands:"
    echo "    hlxc run hello.hlx     Run a program"
    echo "    hlxc --version         Show version"
    echo "    hlxpm install math     Install package"
    echo "    hlxfmt hello.hlx       Format code"
    echo "    hlxlint hello.hlx      Lint code"
    echo "  ════════════════════════════════════"
    echo ""
    echo "  Quick Start:"
    echo ""
    echo '    echo '"'"'fn main() { print("Hello HOLEXA!") }'"'"' > hello.hlx'
    echo "    hlxc run hello.hlx"
    echo ""
    echo "  Try Online:"
    echo "    https://holexa-lang.github.io/HOLEXA-LANG/"
    echo ""
    echo "${GREEN}  Code like a Dragon. Think like a Human. 🐉${NC}"
    echo ""
else
    echo "${RED}  Error: Installation failed!${NC}"
    echo "  Please try manual installation:"
    echo "  github.com/HOLEXA-LANG/HOLEXA-LANG"
    exit 1
fi
