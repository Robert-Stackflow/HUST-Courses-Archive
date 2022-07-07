Requirements for source distribution:

    Standard GNU/Unix-like environment (rm, cp, GNU make, etc...)
    SML/NJ 110.67 or higher (can be replaced by mlton)
    MLton (needed for the Coin interactive toplevel and c0vm)

Requirements for binary distribution:

    gcc (which comes with the Xcode developer tools under Mac OS X)

Qt: as of C0 r7, Qt is no longer part of the distribution or standard
libraries.  It's use in the <img> image library has been replaced by
libpng.  Some information on Qt can be found in the qt/ subdirectory

gc: On Mac OS X 10.7 (Lion), 'make gc' will fail.  The latest version of
libgc works under Lion, but we have been unable to installed the update
so far.  The binary distribution for Mac OS X 10.6 (Snow Leopard) has
been reported to run under Lion.

----------------------------------------------------------------------
Minimal check of binary distribution
----------------------------------------------------------------------

    $ bin/cc0 -d doc/src/exp.c0 doc/src/exp-test.c0
    $ ./a.out
    All tests passed!
    0

    $ bin/coin -l conio doc/src/exp.c0
    --> print("Hello World!\n");
    Hello World!
    --> exp(2,3);
    8 (int)
    --> #quit

----------------------------------------------------------------------
Building from source
----------------------------------------------------------------------

   $ ./configure

   $ make [ NJ=true ]   # build the cc0 compiler, coin, codex, gc, runtimes,
                        # and libraries
                        # Optional NJ=true argument uses SML/NJ
                        # instead of MLton as a compiler. (Libraries
                        # for coin and codex will not work fully if
                        # compiled with SML/NJ.)

 [ $ make libs          # build the libraries separately ] 
 [                      # (libpng required for libimg) ]

   $ make check         # run the regression suite (currently requires MLton)
 [ $ make checkc0rt ]   # run the regression suite on the c0rt runtime
 [ $ make checkbare ]   # run the regression suite on the bare runtime
 [ $ make checkunsafe ] # run the regression suite on the unsafe runtime

 [ $ cd vm; make        # build c0vm, must run make libs first ]
 [ $ make checkvm       # test cc0 -b together with c0vm ]

 [ $ make coin-exec     # build the interpreter ]
 [ $ make checkcoin     # run the regression suite on the interpreter ]

If all tests succeed, you can roll out the current build with:

   $ make install    # install binaries, libs, runtimes, and include files

Alternatively, to only roll out the current libraries, you can run:

   $ make install-libs

NB: to run make check, you may need to put MLton on your PATH, e.g., by
adding /afs/andrew/usr/wlovas/public/mlton/usr/bin to it on Andrew.

NB: "make check" tests the default runtime (currently c0rt, so "make
check" and "make checkc0rt" do the same thing). 

The compiler is built as bin/cc0, installed as $(PREFIX)/bin/cc0.
Libraries and runtimes are placed in lib/* and runtime/*, and
are installed as $(PREFIX)/lib/* and $(PREFIX)/runtime/*, respectively.
Include files in include/* are installed as $(PREFIX)/include/*.

----------------------------------------------------------------------
Issue tracking
----------------------------------------------------------------------
While the sorce remains in a CMU-hosted subversion repositiory, issue
tracking is done through GitHub at
https://github.com/frankpfenning/C0/issues

----------------------------------------------------------------------
Known problems
----------------------------------------------------------------------
There are some issues with configuring zlib and libpng so they work
reliably on Linux and Darwin (Mac OS X).  Some expert help on this
would be appreciated.

Darwin: If they are configured with dynamic linking, then they
cannot be found when a binary distribution is unpacked and built.
So I configured them for static linking (since they are not part
of Xcode, as far as I can determine), which appears to work.

Linux: The static linking option seems to fail under Linux (it
complains some code is not position independent).  So I also copy the
files for dynamic linking (*.so*) into the cc0/lib/ directory, under
Linux only.  This succeeds, but I suspect a standalone executable
could not be produced from this.

Alternatively, we could just postulate that zlib and libpng are
available under Linux (are they, usually?) and not even build
them.

----------------------------------------------------------------------
Creating a binary distribution
----------------------------------------------------------------------
Binary distro (pristine Ubuntu distro):

  # Prerequisites
  apt-get update
  apt-get install subversion make g++ libpng-dev libncurses-dev texlive-latex-base texlive-fonts-recommended mlton
  svn co https://svn.concert.cs.cmu.edu/c0

  # Configuration
  cd c0/cc0
  ./configure
  make
  [ make check ]
  make coin-exec
  [ make checkcoin ]

  # Make docs
  cd doc/reference ; pdflatex c0-reference.tex ; pdflatex c0-reference.tex
  pdflatex c0-libraries.tex ; pdflatex c0-libraries.tex
  cd ../../..

  # Package
  tar --exclude .svn -p -T cc0/dist-bin.txt -cvzf cc0-v${REV}-${VERS}-bin.tgz
  scp cc0-v${REV}-${VERS}-bin.tgz c0.typesafety.net:/home/www/c0/dist/
  
  ** ${REV} is the four-digit revision number (0214, for instance)
  ** ${VERS} explains the build setup:
     - osx10.5.8 (Leapord)
     - osx10.6.8 (Snow Leapord)
     - osx10.8.2 (Mountain Lion)
     - linux3.6.5-32bit (32 bit Ubuntu Precise on Linode)
     - linux3.6.5-64bit (64 bit Ubuntu Precise on Linode)

  ** If distributing a source distribution for compilation, at this
  ** point the file compiler/bin/buildid can be edited to hard-code
  ** the subversion version number, and the distribution can be packed
  ** up.
  ** 
  ** Find version ???? with
  ** svn info https://svn.concert.cs.cmu.edu/c0

Ubuntu notes: 
 - Clients need gcc and libgmp3-dev installed 

OSX notes: 
 - It's hard to coax MLton into linking statically, but it's important
   to do so
     1. Download and install MacPorts, then do 
        "sudo /opt/local/bin/port install gmp"
     2. Get the *statically linked* version of MLton from mlton.org.
     3. Delete all *libgmp* files in /opt/local/lib *except* libgmp.a.
 - Clients presumably need, at minimum, xcode command line tools to
   use the cc0 compiler.

Windows notes:
 - replace all instances of "make" with "make STATIC=true"
 - Clients need the "libgmp3" and probably "libgmp-devel" Cygwin
   packages, as well as "libpng-dev" "libncurses-dev"
 - run "make libs STATIC=true" before "make STATIC=true" on Windows,
   as there's an extra dependency (coin and codex require libs to
   already exist) that is not present in the non-static compiles. This
   should eventually be fixed in the makefile.
 - in cymbol/cymbol-native.sml, extern-lib-native.sml needs to be
   replaced by extern-lib-static.sml, and extern-lib-static needs to
   have the args library commented out. (This should probably be
   standardized.)

Older versions:

http://www.cs.cmu.edu/~fp/misc/c0-v2379-osx10.5.8-bin.tgz
http://www.cs.cmu.edu/~fp/misc/c0-v2403-osx10.6.8-bin.tgz

----------------------------------------------------------------------
Source distribution
----------------------------------------------------------------------
Access at https://svn.concert.cs.cmu.edu/c0, username c0guest.
Ask fp@cs.cmu.edu for the password

Older versions:

tar -cvzf c0-src-v2760.tgz --exclude .svn --exclude vm 15-122/externals/gc 15-122/c0

----------------------------------------------------------------------
History
----------------------------------------------------------------------
The original version of the compiler was in a different repository
that shared 15-122 specific files; in early 2012 this was moved to a
C0-specific subversion repository. There were still a lot of C++
dependencies in this version inhereted from the use of Qt in the old
library, these were eliminated in the early 200-revisions (December
2012).

Around revision 238-241, some housekeeping was done:

cc0/debugger eliminated (not sure how related to debugger-r10, as of r252)
cc0/debugger-r10 eliminated (Jakob and Rob's early debugger infrastructure) 
cc0/debugger-r12 --> cc0/code --> cc0/codex
cc0/compiler/parse1 eliminated (Original LEX/YACC parser)
cc0/compiler/parse2 eliminated (Prototype by-hand shift-reduce parser)
cc0/compiler/parse3 -> cc0/compiler/parse
cc0/qt -> some versions/parts of files used to compile C0 with Qt
cc0/type/print-c.sml eliminated (out-of-date less compact printer to C)

--------------------------------------------------
To set svn properties:

svn propset svn:svnignore -F svnignore .
----------------------------------------------------------------------
The C0 to C# compiler is no longer current; the instructions
need to be updated

To build the C0 to C# compiler, use "make csharp". This will replace bin/cc0,
so you'll need to run make again to get the normal compiler back. To run the
regression suite for C0 to C#, you need to use a modified test driver, so do
"make csharp-test" and then "make checkcsharp".

Environment variables:
    C0_RESULT_FILE:   If set to a filename, dump a 0 byte followed by the
                      4-byte return value of main() to that filename
        - if the result file is not created, either the program failed to
          dynamically link or it failed with an OS error
        - if the result file ends up with only the 0 byte, the C0 program
          aborted with some kind of exception
        - if the result file has all 5 bytes, the C0 program finished
          successfully
----------------------------------------------------------------------

