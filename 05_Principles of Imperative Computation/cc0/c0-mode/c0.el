;;; c0.el --- setting up c0-mode

(add-to-list 'auto-mode-alist '("\.c0$" . c0-mode))
(add-to-list 'auto-mode-alist '("\.h0$" . c0-mode))
(add-to-list 'auto-mode-alist '("\.c1$" . c0-mode))
(add-to-list 'auto-mode-alist '("\.h1$" . c0-mode))

(autoload 'c0-mode "c0-mode" "\
Major mode for editing C0 (pronounced \"see naught\" or \"see not\") code.
Derived from cc-mode." t)

(add-to-list 'load-path (concat c0-root "c0-mode"))
(setq codex-path (concat c0-root "bin/codex"))
