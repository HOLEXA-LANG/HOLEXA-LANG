#!/bin/sh
# HOLEXA Universal Installer v1.0.0
# Code like a Dragon. Think like a Human.
# Works on: Linux, Mac, Windows(WSL), iPad(iSH)

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
echo "  Installing HOLEXA v1.0.0..."
echo "  Code like a Dragon. Think like a Human."
echo ""

# Detect OS
OS="unknown"
if [ "$(uname)" = "Darwin" ]; then
    OS="mac"
elif [ "$(uname)" = "Linux" ]; then
    OS="linux"
fi

echo "${CYAN}Detected OS: $OS${NC}"

# Install gcc if needed
echo "${CYAN}Checking dependencies...${NC}"
if ! command -v gcc > /dev/null 2>&1; then
    echo "Installing gcc..."
    if [ "$OS" = "mac" ]; then
        xcode-select --install
    elif [ "$OS" = "linux" ]; then
        if command -v apt-get > /dev/null 2>&1; then
            apt-get install -y gcc make
        elif command -v apk > /dev/null 2>&1; then
            apk add gcc make
        fi
    fi
fi

# Clone repo
echo "${CYAN}Downloading HOLEXA...${NC}"
git clone https://github.com/HOLEXA-LANG/HOLEXA-LANG.git /tmp/holexa_install
cd /tmp/holexa_install/compiler

# Build
echo "${CYAN}Building compiler...${NC}"
make

# Install
echo "${CYAN}Installing...${NC}"
cp hlxc /usr/local/bin/hlxc
cp ../package-manager/hlxpm /usr/local/bin/hlxpm
cp ../tools/hlxfmt/hlxfmt /usr/local/bin/hlxfmt
cp ../tools/hlxlint/hlxlint /usr/local/bin/hlxlint
cp ../tools/hlxbuild/hlxbuild /usr/local/bin/hlxbuild

# Cleanup
cd /
rm -rf /tmp/holexa_install

# Verify
echo ""
if command -v hlxc > /dev/null 2>&1; then
    echo "${GREEN}✓ HOLEXA installed successfully!${NC}"
    echo ""
    echo "  Commands:"
    echo "  hlxc run hello.hlx     Run a program"
    echo "  hlxc --version         Version"
    echo "  hlxpm install math     Install package"
    echo "  hlxfmt hello.hlx       Format code"
    echo ""
    echo "  Quick start:"
    echo "  echo 'fn main() { print(\"Hello!\") }' > hello.hlx"
    echo "  hlxc run hello.hlx"
    echo ""
    echo "${GREEN}  Code like a Dragon. Think like a Human. 🐉${NC}"
else
    echo "${RED}✗ Installation failed${NC}"
    exit 1
fi
