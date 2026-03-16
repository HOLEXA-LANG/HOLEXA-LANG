# HOLEXA Developer Tools Guide v1.0.0

## hlxfmt — Code Formatter
```sh
hlxfmt main.hlx
hlxfmt main.hlx --check
hlxfmt --version
```

## hlxlint — Code Linter
```sh
hlxlint main.hlx
hlxlint src/
hlxlint --version
```

### Lint Rules

| Rule | Level | Description |
|------|-------|-------------|
| Trailing whitespace | WARN | Remove spaces at line end |
| Line too long | WARN | Max 100 characters |
| TODO comment | HINT | Complete the task |
| FIXME comment | WARN | Fix the issue |
| Empty function | WARN | Add implementation |
| Missing space | WARN | After if/while/for |

## hlxbuild — Build Tool
```sh
hlxbuild init
hlxbuild
hlxbuild run
hlxbuild test
hlxbuild clean
hlxbuild --version
```

### hlxbuild.json
```json
{
    "name": "myapp",
    "version": "0.1.0",
    "main": "src/main.hlx",
    "output": "build/",
    "test": "tests/"
}
```

## hlx-lsp — Language Server

Provides editor support:
- Syntax highlighting
- Auto-complete
- Error detection
- Hover information
- Go to definition

### Editor Setup

**VS Code:** Install HOLEXA extension
**Vim/Neovim:** Add hlx-lsp to LSP config
**Emacs:** Configure lsp-mode with hlx-lsp
