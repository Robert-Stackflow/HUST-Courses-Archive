;;; c0-mode.el --- C0 mode derived mode

;; Author:     2010 Jakob Max Uecker
;; Maintainer: 
;; Created:    August 2010
;; Modified:   August 2010
;; Version:    0.1
;; Keywords:   c0 languages

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2 of the License, or
;; (at your option) any later version.
;; 
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;; 
;; You should have received a copy of the GNU General Public License
;; along with this program; see the file COPYING.  If not, write to
;; the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
;; Boston, MA 02111-1307, USA.

;;; Commentary:
;;
;;    This mode implements font-locking and indentation of C0 based on
;;    the functionality provided by cc-mode
;;
;;    Note: The interface used in this file requires CC Mode 5.30 or
;;    later.

;;; Known Bugs:
;;
;;   This code doesn't seem to work when you compile it, then
;;   load/require in the emacs file. You will get an error (error
;;   "`c-lang-defconst' must be used in a file") which happens because
;;   cc-mode doesn't think it is in a buffer while loading directly
;;   from the init. However, if you call it based on a file extension,
;;   it works properly. Interestingly enough, this doesn't happen if
;;   you don't byte-compile cc-mode.

;;; Versions:
;;
;;    0.1 - Initial release

;; Load cc-mode
(require 'cc-mode)

;; Load code for debugger interaction
(require 'c0-codex)

;; These are only required at compile time to get the sources for the
;; language constants.  (The cc-fonts require and the font-lock
;; related constants could additionally be put inside an
;; (eval-after-load "font-lock" ...) but then some trickery is
;; necessary to get them compiled.)
(eval-when-compile
  (let ((load-path
	 (if (and (boundp 'byte-compile-dest-file)
		  (stringp byte-compile-dest-file))
	     (cons (file-name-directory byte-compile-dest-file) load-path)
	   load-path)))
    (load "cc-mode" nil t)
    (load "cc-fonts" nil t)
    (load "cc-langs" nil t)))

(eval-and-compile
  ;; Make our mode known to the language constant system.  Use C
  ;; mode as the fallback for the constants we don't change here.
  ;; This needs to be done also at compile time since the language
  ;; constants are evaluated then.
  (c-add-language 'c0-mode 'c-mode))

;; Primitive types for C0
(c-lang-defconst c-primitive-type-kwds
  c0 '("string" "int" "bool" "char" "void"))

;; C0 has no primitive type prefixes (e.g. "long", "unsigned")
(c-lang-defconst c-primitive-type-prefix-kwds
  c0 nil)

;; The keywords that define that the following is a type and
;; where the keyword together with the symbol works as a type in
;; declarations.
(c-lang-defconst c-type-prefix-kwds
  c0 '("struct"))

;; C0 has no type modifier keywords. (e.g. "const")
(c-lang-defconst c-type-modifier-kwds
  c0 nil)

;; C0 has no classes, but for syntax highlighting purposes,
;; structs are classes
(c-lang-defconst c-class-decl-kwds
  c0 '("struct"))

;; Would be used for e.g. "enum", but c0 doesn't have that
(c-lang-defconst c-brace-list-decl-kwds
  c0 nil)

;; Would be used for "extern"
(c-lang-defconst c-other-block-decl-kwds
  c0 nil)
(c-lang-defconst c-nonsymbol-sexp-kwds
  c0 nil)

;; C0 has no declaration modifiers (e.g. "auto", "inline")
(c-lang-defconst c-modifier-kwds
  c0 nil)

;; C0 has no embedded struct definitions
(c-lang-defconst c-block-decls-with-vars
  c0 nil)

;; Statement keywords followed directly by a substatement
(c-lang-defconst c-block-stmt-1-kwds
  c0 '("else"))
;; Statement keywords followed by a paren sexp and then by a substatement
(c-lang-defconst c-block-stmt-2-kwds
  c0 '("for" "if" "while"))

;; Statement keywords followed by an expression or nothing
(c-lang-defconst c-simple-stmt-kwds
  c0 '("return" "continue" "break"))

;; C0 has no assembler statements
(c-lang-defconst c-asm-stmt-kwds
  c0 nil)

;; C0 has no switch/case construct
(c-lang-defconst c-case-kwds
  c0 nil)

;; C0 has no labels
(c-lang-defconst c-label-kwds
  c0 nil)
(c-lang-defconst c-before-label-kwds
  c0 nil)

;; Constant keywords
(c-lang-defconst c-constant-kwds
  c0 '("true" "false" "NULL"))

;; C0 has no bitfields
(c-lang-defconst c-bitfield-kwds
  c0 nil)
(c-lang-defconst c-opt-bitfield-key
  c0 nil)

;; Keywords unaccounted for by all the other defs
(c-lang-defconst c-other-kwds
  c0 '("alloc" "alloc_array" "assert" "error"))

;; C0 uses #use, like #include in C, and has no other preprocessor directives.
;; However, the lines below cause Emacs to hang when processing
;; '#use "'  interrupting with Ctrl-G will leave highlighting in some
;; inconsistent state.  The workaround attempts to turns of cpp
;; matching and highlight altogether by pretending cpp commands start
;; with '##' instead of '#'.  Strange, but I couldn't get anything
;; else work.  Tue Jan 11, 2011 -fp
;;
;; next workaround prevents highlighting, but pragmas still hang
;; (c-lang-defconst c-cpp-matchers
;;  c0 nil)
;;
;; setting c-opt-cpp-prefix to nil does not work, claims something
;; should be a string
;; (c-lang-defconst c-opt-cpp-prefix
;;   c0 nil)
(c-lang-defconst c-opt-cpp-prefix
  c0 "##")
(c-lang-defconst c-cpp-message-directives
  c0 nil)
(c-lang-defconst c-cpp-include-directives
  c0 '("use"))
(c-lang-defconst c-opt-cpp-macro-define
  c0 nil)
(c-lang-defconst c-cpp-expr-directives
  c0 nil)
(c-lang-defconst c-cpp-expr-functions
  c0 nil)

(defconst c0-font-lock-keywords-1 (c-lang-const c-matchers-1 c0)
  "Minimal highlighting for C0 mode.")

(defconst c0-font-lock-keywords-2 (c-lang-const c-matchers-2 c0)
  "Fast normal highlighting for C0 mode.")

(defconst c0-font-lock-keywords-3 (c-lang-const c-matchers-3 c0)
  "Accurate normal highlighting for C0 mode.")

(defvar c0-font-lock-keywords c0-font-lock-keywords-3
  "Default expressions to highlight in C0 mode.")

(defvar c0-mode-syntax-table nil
  "Syntax table used in C0 mode buffers.")
(or c0-mode-syntax-table
    (setq c0-mode-syntax-table
	  (funcall (c-lang-const c-make-mode-syntax-table c0))))

(defvar c0-mode-abbrev-table nil
  "Abbreviation table used in c0-mode buffers.")

(c-define-abbrev-table 'c0-mode-abbrev-table
  ;; Keywords that if they occur first on a line might alter the
  ;; syntactic context, and which therefore should trig reindentation
  ;; when they are completed.
  '(("else" "else" c-electric-continued-statement 0)))

(defvar c0-mode-map
  (let ((map (c-make-inherited-keymap)))
    ;; Add bindings which are only useful for C0
    (define-key map "\C-c\C-d" 'codex)
    (define-key map "\C-c\C-g" 'codex-delete-highlight)
    map)
  "Keymap used in C0 mode buffers.  \C-c\C-d starts debugger (codex).")

(defvar cc0-path (concat c0-root "bin/cc0")
  "*Path to cc0 executable")

(defvar codex-path (concat c0-root "bin/codex")
  "*Path to the debugger (codex) executable")

;; Custom variables
(defcustom c0-mode-hook nil
  "*Hook called by `c0-mode'."
  :type 'hook
  :group 'c)

;; (if awk-mode-map
;;     nil
;;   (setq awk-mode-map (c-make-inherited-keymap))
;;   (define-key awk-mode-map "\C-c\C-n" 'undefined) ; #if doesn't exist in awk.
;;   (define-key awk-mode-map "\C-c\C-p" 'undefined)
;;   (define-key awk-mode-map "\C-c\C-u" 'undefined))

(easy-menu-define c-c0-menu c0-mode-map "C0 Mode Commands"
		  (cons "C0" (c-lang-const c-mode-menu c0)))

;;; The entry point into the mode
;;;###autoload
(defun c0-mode ()
  "Major mode for editing C0 (pronounced \"see nod\") code.
Derived from cc-mode.

The hook `c-mode-common-hook' is run with no args at mode
initialization, then `c0-mode-hook'.

Key bindings:
\\{c0-mode-map}"
  (interactive)
  (kill-all-local-variables)
  (c-initialize-cc-mode t)
  (set-syntax-table c0-mode-syntax-table)
  (setq major-mode 'c0-mode
	mode-name "C0"
	local-abbrev-table c0-mode-abbrev-table
	abbrev-mode t
        indent-tabs-mode nil)
  ;; Add the "C0" menu options (defined above in c0-mode-map)
  (use-local-map c0-mode-map)
  ;; `c-init-language-vars' is a macro that is expanded at compile
  ;; time to a large `setq' with all the language variables and their
  ;; customized values for our language.
  (c-init-language-vars c0-mode)
  ;; `c-common-init' initializes most of the components of a CC Mode
  ;; buffer, including setup of the mode menu, font-lock, etc.
  ;; There's also a lower level routine `c-basic-common-init' that
  ;; only makes the necessary initialization to get the syntactic
  ;; analysis and similar things working.
  (set 'compile-command (concat cc0-path " " (file-relative-name buffer-file-name)))
  (c-common-init 'c0-mode)
  (c-run-mode-hooks 'c-mode-common-hook) ; 'awk-mode-hook 
  (c-update-modeline))

(provide 'c0-mode)

;;; c0-mode.el ends here
