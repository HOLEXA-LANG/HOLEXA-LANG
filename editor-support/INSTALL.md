# HOLEXA Editor Support Installation

## VS Code
1. Copy `vscode/` folder
2. Place in `~/.vscode/extensions/holexa-lang/`
3. Restart VS Code
4. Open any `.hlx` file — syntax highlighting on!

## Vim
```sh
mkdir -p ~/.vim/syntax ~/.vim/ftdetect
cp vim/holexa.vim   ~/.vim/syntax/
cp vim/ftdetect.vim ~/.vim/ftdetect/holexa.vim
```

## Neovim
```sh
cp neovim/holexa.lua ~/.config/nvim/lua/
```
Add to `init.lua`:
```lua
require('holexa')
```

## Emacs
Add to `~/.emacs` or `~/.emacs.d/init.el`:
```elisp
(load "~/.emacs.d/holexa-mode.el")
```

## Sublime Text
```sh
cp sublime/HOLEXA.sublime-syntax \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/
cp sublime/HOLEXA.sublime-completions \
   ~/Library/Application\ Support/Sublime\ Text/Packages/User/
```

## IntelliJ / JetBrains IDEs
1. Settings → Editor → File Types
2. Click `+` → Add new file type
3. Import `intellij/holexa.xml`
4. Add `*.hlx` pattern

## Atom
```sh
cp atom/holexa.cson \
   ~/.atom/packages/language-holexa/grammars/
```
