For users:

http://c0.typesafety.net           - Information on C0 and courses using it
http://c0.typesafety.net/tutorial  - C0 language tutorial
http://c0.typesafety.net/doc/c0-reference.pdf - C0 language reference
http://c0.typesafety.net/doc/c0-libraries.pdf - C0 library reference

reference/c0-reference.pdf - C0 language reference
reference/c0-libraries.pdf - C0 library reference
src/*                      - examples from tutorial

----------------------------------------------------------------------
For developers:

notes/ - notes on further tools and language developments
reference/ - rigorous language and library reference
C0-Tutorial.wiki/ - copy of a tutorial on github
  https://github.com/frankpfenning/C0-Tutorial/wiki
  This is synced to c0.typesafety.net/tutorial in
  html form (see more below)
src/ - sources used in the tutorial
  These are synced to c0.typesafety.net/tutorial-src
  and typesafety.net/tutorial/src.tgz.
formalization/ - formalization of a slight variant of C0
  by Rob Arnold as part of his MS thesis research.
  (also contains library documentation: make libdoc.pdf)
  libdoc.pdf is now obsolete - see reference/c0-libraries.*

To update on c0.typesafety.net after making changes
to the tutorial:

% ssh typesafety.net './update_wiki'

notes [obsolete]:
% svn propset svn:externals "C0-Tutorial.wiki https://svn.github.com/frankpfenning/C0-Tutorial.wiki\
C0-Tutorial https://svn.github.com/frankpfenning/C0-Tutorial" .

now:

% svn propset svn:externals -F svnexternals .

Checking it out directly:
% svn checkout https://svn.github.com/frankpfenning/C0-Tutorial.wiki   
% svn checkout https://svn.github.com/frankpfenning/C0-Tutorial
% svn commit --username frankpfenning -m "edit message"

To export html; see 
C0-Tutorial.wiki/README.me
or https://github.com/frankpfenning/C0-Tutorial/wiki/README
or https://github.com/robsimmons/C0-Tutorial or

[% git clone git://github.com/frankpfenning/C0-Tutorial.wiki.git git-wiki] (first time)

% cd git-wiki
% git pull --rebase
% gollum-site --base_path http://www.cs.cmu.edu/~fp/c0/tutorial/ generate
% cp -rp _site/* ~/fp/www/c0/tutorial/
