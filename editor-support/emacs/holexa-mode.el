;;; holexa-mode.el — HOLEXA Emacs Major Mode
;;; Code like a Dragon. Think like a Human.

(defconst holexa-keywords
  '("let" "const" "fn" "return" "if" "else" "while" "for" "loop"
    "break" "continue" "class" "import" "from" "async" "await"
    "spawn" "try" "catch" "finally" "raise" "match" "trait"
    "implements" "self" "extern" "in"))

(defconst holexa-types
  '("Int" "Float" "String" "Bool" "List" "Map" "None" "Any" "Byte"))

(defconst holexa-builtins
  '("print" "input" "len" "str" "int" "float" "type" "range" "append"))

(defconst holexa-constants
  '("true" "false" "none"))

(defvar holexa-font-lock-keywords
  `((,(regexp-opt holexa-keywords  'words) . font-lock-keyword-face)
    (,(regexp-opt holexa-types     'words) . font-lock-type-face)
    (,(regexp-opt holexa-builtins  'words) . font-lock-builtin-face)
    (,(regexp-opt holexa-constants 'words) . font-lock-constant-face)
    ("[a-zA-Z_][a-zA-Z0-9_]*\\s-*("        . font-lock-function-name-face)
    ("\\b[0-9]+\\.?[0-9]*\\b"              . font-lock-constant-face)))

(defvar holexa-mode-syntax-table
  (let ((st (make-syntax-table)))
    (modify-syntax-entry ?/ ". 124b" st)
    (modify-syntax-entry ?* ". 23"   st)
    (modify-syntax-entry ?\n "> b"   st)
    (modify-syntax-entry ?\" "\""    st)
    st))

(define-derived-mode holexa-mode prog-mode "HOLEXA"
  "Major mode for HOLEXA programming language."
  :syntax-table holexa-mode-syntax-table
  (setq font-lock-defaults '(holexa-font-lock-keywords))
  (setq-local comment-start "// ")
  (setq-local comment-end   "")
  (setq-local tab-width     4)
  (setq-local indent-tabs-mode nil))

;; Key bindings
(define-key holexa-mode-map (kbd "C-c C-r")
  (lambda () (interactive)
    (compile (concat "hlxc run " (buffer-file-name)))))

(define-key holexa-mode-map (kbd "C-c C-b")
  (lambda () (interactive)
    (compile (concat "hlxc " (buffer-file-name)))))

(define-key holexa-mode-map (kbd "C-c C-f")
  (lambda () (interactive)
    (shell-command (concat "hlxfmt " (buffer-file-name)))))

;; Auto-detect .hlx files
(add-to-list 'auto-mode-alist '("\\.hlx\\'" . holexa-mode))

(provide 'holexa-mode)
;;; holexa-mode.el ends here
