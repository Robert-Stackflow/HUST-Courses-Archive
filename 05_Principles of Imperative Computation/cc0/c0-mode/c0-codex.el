;;; c0-codex.el --- Interaction with 'codex', the C0 debugger

;; Author:     2010 Jakob Max Uecker
;; Maintainer: 
;; Created:    August 2010
;; Modified:   August 2010
;; Version:    0.1
;; Keywords:   c0 codex debugger

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
;;    This code interacts with the 'codex' debugger. It expects
;;    the variable 'codex-path' to be set to the 'codex' executable

;;; Known Bugs:
;;    
;;
;;

;;; Versions:
;;
;;    0.1 - Initial release

;; User options
(defvar codex-path nil
  "*Path pointing to the codex executable")

;; Faces for highlighting the active portion of codex
(defface codex-normal-face
  '((((class color)
      (background dark))
     (:background "Yellow" :bold t :foreground "Black"))
    (((class color)
      (background light))
     (:background "Yellow" :bold t))
    (t
     ()))
  "*Face used for the next expression to be evaluated."
  :group 'codex)

(defface codex-error-face
  '((((class color)
      (background dark))
     (:background "Pink" :bold t :foreground "Black"))
    (((class color)
      (background light))
     (:background "Pink" :bold t))
    (t
     ()))
  "*Face used for highlighting erroneous expressions."
  :group 'codex)

;; The keymap used for debugging
(defvar codex-map
  (let ((map (make-sparse-keymap)))
    (define-key map "s" 'codex-step)
    (define-key map (kbd "RET") 'codex-step)
    (define-key map "n" 'codex-next)
    (define-key map "v" 'codex-locals)
    (define-key map "e" 'codex-eval-exp)
    (define-key map "r" 'codex-run-exp)
    (define-key map "c" 'codex-complete)
    (define-key map "b" 'codex-break)
    (define-key map "u" 'codex-unbreak)
    (define-key map "q" 'codex-exit-debug)
    (define-key map "i" 'codex-interrupt)
    (define-key map "?" 'codex-help)
    (define-key map "h" 'codex-help-long)
    (define-key map "0" 'digit-argument)
    (define-key map "1" 'digit-argument)
    (define-key map "2" 'digit-argument)
    (define-key map "3" 'digit-argument)
    (define-key map "4" 'digit-argument)
    (define-key map "5" 'digit-argument)
    (define-key map "6" 'digit-argument)
    (define-key map "7" 'digit-argument)
    (define-key map "8" 'digit-argument)
    (define-key map "9" 'digit-argument)
    map))

;;; Local variables follows
;;; These should not be set by the user

(defvar codex-locals-buffer nil
  "Buffer which will display values of local variables")

(defvar codex-temp-buffer nil
  "Buffer which will display temporary code")

(defvar codex-locals-accum nil
  "Accumulator for local variable values for 'v' command")

(defvar codex-output-accum nil
  "Accumulator for output, shown when prompt is encountered")

(defvar codex-highlight-overlay nil
  "Overlay to highlight currently evaluated region")

(defvar codex-point-old nil
  "Old point in current codex buffer")

(defvar codex-local-map-old nil
  "Old local keymap in current codex buffer")

(defvar codex-proc nil
  "Process running codex")

(defvar codex-args-history nil
  "History of arguments in calls to 'codex'")

(defvar codex-main-directory nil
  "Directory of the C0 file with main function")

;; Column positions between cc0 and emacs are off by 1
(defun codex-get-pos (line column)
  "Get buffer position from line.column position"
  (+
   (line-beginning-position (- (+ line 1) (line-number-at-pos)))
   (- column 1)))

;;; Functions for highlighting

(defun codex-highlight
  (line-begin column-begin line-end column-end)
  "Move highlight overlay to specified region, point to beginning of region"
  (let ((pos-begin (codex-get-pos line-begin column-begin))
	(pos-end (codex-get-pos line-end column-end)))
    (if (not (null codex-highlight-overlay))
	(move-overlay codex-highlight-overlay pos-begin pos-end)
      (setq codex-highlight-overlay (make-overlay pos-begin pos-end)))
    (goto-char pos-begin)))

(defun codex-highlight-normal (line-begin column-begin line-end column-end)
  "Set normal highlight"
  (codex-highlight line-begin column-begin line-end column-end)
  (overlay-put codex-highlight-overlay 'face 'codex-normal-face))

(defun codex-highlight-error (line-begin column-begin line-end column-end)
  "Set highlight to indicate error"
  (codex-highlight line-begin column-begin line-end column-end)
  (overlay-put codex-highlight-overlay 'face 'codex-error-face))

(defun codex-delete-highlight ()
  "*Remove highlight overlay"
  (if (not (null codex-highlight-overlay))
      (progn
	(delete-overlay codex-highlight-overlay)
	(setq codex-highlight-overlay nil))))

(defun codex-enter-buffer ()
  "Set current buffer to codex mode"
  (setq buffer-read-only t)
  (setq codex-local-map-old (current-local-map))
  (use-local-map codex-map)
  (setq codex-point-old (point)))

(defun codex-leave-buffer ()
  "Restore current buffer to normal mode"
  (codex-delete-highlight)
  (use-local-map codex-local-map-old)
  (goto-char codex-point-old)
  (setq buffer-read-only nil))

(defun codex-switch-to-file (filename)
  "Switch to stepping in filename"
  (codex-leave-buffer)			; leave current buffer
  (find-file-existing filename)		; visit other file
  (codex-enter-buffer)			; enter into debug mode
  )

(defun codex-switch-to-buffer (buffer)
  "Switch to stepping in buffer"
  (if (null buffer)
      ()                          ; no action if buffer does not exist
    (codex-leave-buffer)          ; otherwise, leave current buffer
    (switch-to-buffer buffer)     ; switch to new buffer
    (codex-enter-buffer)          ; enter into debug mode
  ))

(defun codex-display-output-accum ()
  "Display accumulated output, if not empty"
  (if (not (null codex-output-accum))
      (progn
	(with-current-buffer codex-locals-buffer
	  (goto-char (point-max))
	  (insert codex-output-accum))
	(setq codex-output-accum nil))))

(defun codex-find-matching-input (file-name-quoted args-history index)
  (if (null args-history)
      0                                 ; no matching input
    (if (string-match file-name-quoted (car args-history))
        index
      (codex-find-matching-input file-name-quoted (cdr args-history) (1+ index)))))

(defun codex-history-index (file-name)
  "Index of most recent arguments to 'codex' matching FILE-NAME.
0 if there is no matching input"
  (codex-find-matching-input (regexp-quote file-name) codex-args-history 1))

;;; Functions for parsing of codex output

(defun codex-canon-filename (filename)
  "Canonicalize the given filename, relative to codex main directory"
  (if (file-name-absolute-p filename)
      filename
    (expand-file-name (concat codex-main-directory filename))))

(defun codex-parse (string)
  (let ((newline-pos (string-match "\n" string)))
    (if (null newline-pos)
	;; no trailing newline
	(codex-parse-line string string)
      ;; trailing newline
      (if (not (codex-parse-line (substring string 0 newline-pos) string))
	  (codex-parse (substring string (+ 1 newline-pos)))))))

(defconst codex-position-regexp
  "\\([0-9]*\\)[.]\\([0-9]*\\)-\\([0-9]*\\)[.]\\([0-9]*\\)"
  "Regular expression matched against codex position.  Must define 4 numbers.")

(defconst codex-location-regexp
  (concat "^\\([^:]*\\):" codex-position-regexp)
  "Regular expression matched against codex output")

(defconst codex-interactive-regexp
  (concat "^\\(<codex>\\):" codex-position-regexp)
  "Regular expression matched against error in interactive parsing")

(defconst error-msg-regexp
  "\\(:error:.*\\|: @.*\\|: assert failed\\)"
  "Regular expression matched against error output")

(defun codex-parse-line (string whole-string)
  "Parse one line of output from codex program, returns non-NIL to abort rest"
  (cond ((string-match "^(codex)" string)
	 ;; prompt - display values of local variables
         ;; and accumulated output since last prompt
	 (if (not (null codex-locals-accum))
	     (progn
	       ;; (message "%d" (length codex-locals-accum))
	       (with-current-buffer codex-locals-buffer
		 (delete-region (point-min) (point-max))
		 (insert codex-locals-accum)
		 (goto-char (point-max)))
	       (setq codex-locals-accum nil))
             ;; Bugfix - entering a new function doesn't clear locals
             ;; - rjs 8/24/2012
           ;; should always produce something now..
           (progn
             (with-current-buffer codex-locals-buffer
               (delete-region (point-min) (point-max))
               ;; (insert "(no local variables)")
               (goto-char (point-max)))))
         (if (not (null codex-output-accum))
	     (progn
	       (message "%s" codex-output-accum)
	       (setq codex-output-accum nil)))
	 ())
	((string-match "^main function" string)
	 ;; main function returned
	 (codex-exit-debug)
	 (message "%s" string)
	 ())
	((string-match (concat "^" error-msg-regexp) string)
	 ;; :error:<errormsg>
	 (let ((errormsg (match-string 1 string)))
	   (codex-exit-debug)
	   (with-current-buffer codex-locals-buffer
	     (delete-region (point-min) (point-max))
	     (insert whole-string))
	   (message "%s" errormsg)
	   ;; abort more parsing (return t)
	   t))
	((string-match (concat codex-interactive-regexp error-msg-regexp) string)
	 ;; error message during interactive parsing or type-checking
	 ;; applies during "e <exp>" evaluation
	 ;; ignore error location, just show error message
	 (let* ((errormsg (match-string 6 string)))
	   (message "%s" errormsg)
	   ;; continue parsing
	   ()))
        ((string-match codex-interactive-regexp string)
         ;; location message during interactive evaluation "e <exp>" or
         ;; run "r <exp>".  Display in *codex-temp* buffer.
         (let* ((line0 (string-to-number (match-string 2 string)))
                (col0 (string-to-number (match-string 3 string)))
                (line1 (string-to-number (match-string 4 string)))
                (col1 (string-to-number (match-string 5 string))))
           (if (not (equal (current-buffer) codex-temp-buffer))
               (codex-switch-to-buffer codex-temp-buffer))
           (codex-highlight-normal line0 col0 line1 col1)
           ()))
	((string-match "^<codex>:\\(.*\\)" string)
	 ;; remaining runtime messages from codex during "e <exp>" evaluation
	 ;; must come after the located error message above and before
	 ;; the general runtime error below
	 (let* ((errormsg (match-string 1 string)))
	   (message "%s" errormsg)
	   ;; continue parsing
	   ()))
	((string-match (concat codex-location-regexp error-msg-regexp) string)
	 ;; error message during parsing or type-checking
	 ;; must come before the next clause
	 (let* ((canon-filename (codex-canon-filename (match-string 1 string)))
		(line0 (string-to-number (match-string 2 string)))
		(col0 (string-to-number (match-string 3 string)))
		(line1 (string-to-number (match-string 4 string)))
		(col1 (string-to-number (match-string 5 string)))
		(errormsg (match-string 6 string)))
	   (if (not (string-equal canon-filename (buffer-file-name)))
	       (codex-switch-to-file canon-filename))
	   (codex-exit-debug)
	   (codex-highlight-error line0 col0 line1 col1)
	   (with-current-buffer codex-locals-buffer
	     (delete-region (point-min) (point-max))
	     (insert whole-string))
	   (message "%s" errormsg)
	   ;; abort more parsing (return t)
	   t))
	((string-match codex-location-regexp string)
	 ;; location of codex currently executed
	 (let* ((canon-filename (codex-canon-filename (match-string 1 string)))
		(line0 (string-to-number (match-string 2 string)))
		(col0 (string-to-number (match-string 3 string)))
		(line1 (string-to-number (match-string 4 string)))
		(col1 (string-to-number (match-string 5 string))))
	   (if (not (string-equal canon-filename (buffer-file-name)))
	       (codex-switch-to-file canon-filename))
	   (codex-highlight-normal line0 col0 line1 col1)
	   ()))
	((string-match "^exception: \\(.*\\)" string)
	 (codex-exit-debug)
	 (with-current-buffer codex-locals-buffer
	   (delete-region (point-min) (point-max))
	   (insert whole-string))
	 (message "%s" whole-string)
	 ;; abort more parsing (return t)
	 t)
	;; ((string-match "^\\(_tmp_[0-9]*\\|_caller\\): " string)
        ;; _tmp_n: value or _caller: value
        ;; do not display values of temporary variables
	;; ())
	((string-match "^[a-zA-Z0-9_]*: " string)
	 ;; varname: value, accumulate to be shown upon next prompt
	 ;; might be better solved with \\w*, but above is more specific
	 (setq codex-locals-accum (concat codex-locals-accum string "\n"))
	 ())
        ((string-match "^step " string)
         ;; display of step count; add to locals buffer
         (setq codex-locals-accum (concat codex-locals-accum string "\n"))
         ())
	;; suppress blank lines
	((string-equal "\n" string) ())
	((string-equal "" string) ())
	(t
	 ;; collect other output, usually from print statements
	 ;; in program being executed, or from "e <exp>" commands
	 (setq codex-output-accum (concat codex-output-accum string "\n"))
	 ())
	))

;;; Filter and Sentinel functions

;; Receives output from the codex. Logs all output in
;; the codex's associated buffer before passing it on
;; to the parsing function
(defun codex-filter (proc string)
  "Filter function for codex interaction"
  (with-current-buffer (process-buffer proc)
    (let ((moving (= (point) (process-mark proc))))
      (save-excursion
	(goto-char (process-mark proc))
	(insert string)
	(set-marker (process-mark proc) (point)))
      (if moving (goto-char (process-mark proc)))))
  (codex-parse string))
	 
;; Is called if the codex process receives a signal
;; or exits
(defun codex-sentinel (proc string)
  "Sentinel for codex process"
  (cond
   ((string-match "^exited abnormally" string)
    (codex-exit-debug)
    (codex-display-output-accum)
    (message "%s" "program aborted"))
   (t (codex-exit-debug)
      (codex-display-output-accum)
      (message "%s" "codex terminated"))))

;;; Functions for sending input to codex

(defun codex-send-string (string)
  "Send STRING to codex process"
  (process-send-string codex-proc string))

(defun codex-step (p)
  "Step to next statement, potentially entering a function.
Prefix argument is the number of (small) steps to take."
  (interactive "p")
  (codex-send-string (concat "s " (int-to-string p) "\n"))
  (codex-send-string "v\n"))

(defun codex-next (p)
  "Step to next statement, passing over functions.
Prefix argument is the number of steps to take."
  (interactive "p")
  (codex-send-string (concat "n " (int-to-string p) "\n"))
  (codex-send-string "v\n"))

(defun codex-eval-exp (exp)
  "Evaluate an expression in the current state"
  (interactive "sEvaluate expression: ")
  (codex-send-string (concat "e " exp "\n"))
  (codex-send-string "v\n"))

(defun codex-temp-insert (exp)
  "Insert 'exp' into *codex-temp* buffer"
  (if (null codex-temp-buffer)
      (setq codex-temp-buffer (generate-new-buffer "*codex-temp*")))
  (save-excursion
    (set-buffer codex-temp-buffer)
    (delete-region (point-min) (point-max))
    (insert exp)))  

(defun codex-run-exp (exp)
  "Run an expression in stepping mode in the current state"
  (interactive "sRun expression: ")
  (codex-temp-insert exp)
  (codex-send-string (concat "r " exp "\n"))
  (codex-send-string "v\n"))

(defun codex-complete ()
  "Complete current run until end (or breakpoint)"
  (interactive)
  (codex-send-string "c\n")
  (codex-send-string "v\n"))

(defun codex-break (funs)
  "Set a breakpoint on given functions"
  (interactive "sBreak at functions: ")
  (codex-send-string (concat "b " funs "\n")))

(defun codex-unbreak (funs)
  "Set a breakpoint on given functions"
  (interactive "sUnbreak functions (default: all): ")
  (codex-send-string (concat "u " funs "\n")))

(defun codex-locals (p)
  "Show the value of local variables"
  (interactive "p")
  (codex-send-string (concat "v " (int-to-string p) "\n")))

(defun codex-interrupt ()
  "Interrupt the codex"
  (interactive)
  (interrupt-process "codex"))

(defun codex-help ()
  "Show the Emacs help for codex"
  (interactive)
  (message "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"
           "(0-9)+ - set prefix argument N"
	   "return or s - step N (stepping into functions)"
	   "n - next N (stepping over function)"
	   "e <exp> - evaluate <exp>"
           "r <exp> - run (step through) <exp>"
           "c - complete run (until breakpoint)"
           "b <f1> ... - break <f1> ..."
           "b - show breakpoints"
           "u <f1> ... - unbreak <f1> ..."
           "u - unbreak all"
           "v - show N frames of call stack"
	   "q - quit"
	   "i - interrupt codex"
	   "? - this short help"
	   "h - detailed help"))

(defun codex-help-long ()
  "Show the longish help for codex"
  (interactive)
  (find-file-other-frame (concat c0-root "c0-mode/README")))

;;; Enter and Exit functions

;; Start codex on the current buffer. The buffer must
;; be associated with ('visiting') a file.
;; After initial checks, the function
;; -makes the buffer read only
;; -saves the current keymap and point
;; -adds a hook that quits codex if the buffer is killed
;; -runs codex

(defun codex ()
  "Enter debugging mode in current buffer."
  (interactive)
  (codex-enter-debug))

(defun codex-enter-debug ()
  "Enter debugging mode."
  (interactive)
  (if (get-process "codex")
      (message "%s" "codex already running")
    (if (null codex-path)
	(message "%s" "codex path not set")
      (if (and (buffer-modified-p) (yes-or-no-p "save buffer? "))
	  (save-buffer))
      (let* ((current-file-name (file-relative-name (buffer-file-name)))
             (history-index (codex-history-index current-file-name))
             (codex-args (read-from-minibuffer
                          "Call with: codex " ; prompt
                          (if (= history-index 0)
                              (concat "-e " current-file-name) ; initial-contents
                            (nth (1- history-index) codex-args-history))
                          nil ; keymap, use default
                          nil ; do not interpret result as Lisp object
                          (if (= history-index 0)
                              'codex-args-history ; history of inputs
                            (cons 'codex-args-history history-index))
                          (concat "-e " current-file-name) ; default-value
                          )))
        ;;(setq codex-args (read-string "Call with: codex" 
        ;;(concat " -e " (file-relative-name (buffer-file-name)))))
        ;; start codex process
        (setq codex-proc
              (start-process-shell-command
               "codex"
               "*codex*"
               codex-path
               codex-args))
        ;; kill-buffer-hook activated when switching to another file
        ;; the first time; disabled
        ;; (add-hook 'kill-buffer-hook 'codex-kill-process)
        (setq codex-output-accum nil)	; in case we are in a strange state
        (setq codex-locals-accum nil)	; in case we are in a strange state
        (set-process-filter codex-proc 'codex-filter)
        (set-process-sentinel codex-proc 'codex-sentinel)
        ;; switch current buffer to debugging mode
        (codex-enter-buffer)
        (setq codex-main-directory (file-name-directory (buffer-file-name)))
        ;; create and display buffer for local variables
        (setq codex-locals-buffer (get-buffer-create "*codex-locals*"))
        (display-buffer codex-locals-buffer) ; do not switch
        (save-window-excursion
          (switch-to-buffer-other-window codex-locals-buffer)
          (delete-region (point-min) (point-max)))
        (if (string-match "\\(-r[ \t]*\\|-run[ \t]*\\)['\"]\\([^ '\"]*\\)['\"]" codex-args)
            (let ((exp (match-string 2 codex-args)))
              (codex-temp-insert exp)))
        (codex-locals 1)                ; display step number 1 and local variables
        (message "Type '?' for help")))))

;; Hook to be run if the buffer is killed while debugging
;; Kills codex
(defun codex-kill-process ()
  (if (get-process "codex")
      (delete-process "codex")))

;; Quit codex. Restores the buffers keymap and point
(defun codex-exit-debug ()
  "Exit debugging mode"
  (interactive)
  (codex-kill-process)
  ;; for now, keep buffers
  ;; (kill-buffer "*codex*")
  ;; (kill-buffer codex-locals-buffer)
  ;; (remove-hook 'kill-buffer-hook 'codex-kill-process)
  (codex-leave-buffer)
  (message "%s" "codex exited"))

(provide 'c0-codex)

;;; c0-codex.el ends here
