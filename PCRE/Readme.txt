README file for PCRE (Perl-compatible regular expression library)
-----------------------------------------------------------------

The latest release of PCRE is always available in three alternative formats
from:

  ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-xxx.tar.gz
  ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-xxx.tar.bz2
  ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-xxx.zip

There is a mailing list for discussion about the development of PCRE at

  pcre-dev@exim.org

Please read the NEWS file if you are upgrading from a previous release.
The contents of this README file are:

  The PCRE APIs
  Documentation for PCRE
  Contributions by users of PCRE
  Building PCRE on non-Unix systems
  Building PCRE on Unix-like systems
  Retrieving configuration information on Unix-like systems
  Shared libraries on Unix-like systems
  Cross-compiling on Unix-like systems
  Using HP's ANSI C++ compiler (aCC)
  Using PCRE from MySQL
  Making new tarballs
  Testing PCRE
  Character tables
  File manifest


The PCRE APIs
-------------

PCRE is written in C, and it has its own API. There are two sets of functions,
one for the 8-bit library, which processes strings of bytes, and one for the
16-bit library, which processes strings of 16-bit values. The distribution also
includes a set of C++ wrapper functions (see the pcrecpp man page for details),
courtesy of Google Inc., which can be used to call the 8-bit PCRE library from
C++.

In addition, there is a set of C wrapper functions (again, just for the 8-bit
library) that are based on the POSIX regular expression API (see the pcreposix
man page). These end up in the library called libpcreposix. Note that this just
provides a POSIX calling interface to PCRE; the regular expressions themselves
still follow Perl syntax and semantics. The POSIX API is restricted, and does
not give full access to all of PCRE's facilities.

The header file for the POSIX-style functions is called pcreposix.h. The
official POSIX name is regex.h, but I did not want to risk possible problems
with existing files of that name by distributing it that way. To use PCRE with
an existing program that uses the POSIX API, pcreposix.h will have to be
renamed or pointed at by a link.

If you are using the POSIX interface to PCRE and there is already a POSIX regex
library installed on your system, as well as worrying about the regex.h header
file (as mentioned above), you must also take care when linking programs to
ensure that they link with PCRE's libpcreposix library. Otherwise they may pick
up the POSIX functions of the same name from the other library.

One way of avoiding this confusion is to compile PCRE with the addition of
-Dregcomp=PCREregcomp (and similarly for the other POSIX functions) to the
compiler flags (CFLAGS if you are using "configure" -- see below). This has the
effect of renaming the functions so that the names no longer clash. Of course,
you have to do the same thing for your applications, or write them using the
new names.


Documentation for PCRE
----------------------

If you install PCRE in the normal way on a Unix-like system, you will end up
with a set of man pages whose names all start with "pcre". The one that is just
called "pcre" lists all the others. In addition to these man pages, the PCRE
documentation is supplied in two other forms:

  1. There are files called doc/pcre.txt, doc/pcregrep.txt, and
     doc/pcretest.txt in the source distribution. The first of these is a
     concatenation of the text forms of all the section 3 man pages except
     those that summarize individual functions. The other two are the text
     forms of the section 1 man pages for the pcregrep and pcretest commands.
     These text forms are provided for ease of scanning with text editors or
     similar tools. They are installed in <prefix>/share/doc/pcre, where
     <prefix> is the installation prefix (defaulting to /usr/local).

  2. A set of files containing all the documentation in HTML form, hyperlinked
     in various ways, and rooted in a file called index.html, is distributed in
     doc/html and installed in <prefix>/share/doc/pcre/html.

Users of PCRE have contributed files containing the documentation for various
releases in CHM format. These can be found in the Contrib directory of the FTP
site (see next section).


Contributions by users of PCRE
------------------------------

You can find contributions from PCRE users in the directory

  ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/Contrib

There is a README file giving brief descriptions of what they are. Some are
complete in themselves; others are pointers to URLs containing relevant files.
Some of this material is likely to be well out-of-date. Several of the earlier
contributions provided support for compiling PCRE on various flavours of
Windows (I myself do not use Windows). Nowadays there is more Windows support
in the standard distribution, so these contibutions have been archived.


Building PCRE on non-Unix systems
---------------------------------

For a non-Unix system, please read the comments in the file NON-UNIX-USE,
though if your system supports the use of "configure" and "make" you may be
able to build PCRE in the same way as for Unix-like systems. PCRE can also be
configured in many platform environments using the GUI facility provided by
CMake's cmake-gui command. This creates Makefiles, solution files, etc.

PCRE has been compiled on many different operating systems. It should be
straightforward to build PCRE on any system that has a Standard C compiler and
library, because it uses only Standard C functions.


Building PCRE on Unix-like systems
----------------------------------

If you are using HP's ANSI C++ compiler (aCC), please see the special note
in the section entitled "Using HP's ANSI C++ compiler (aCC)" below.

The following instructions assume the use of the widely used "configure, make,
make install" process. There is also support for CMake in the PCRE
distribution; there are some comments about using CMake in the NON-UNIX-USE
file, though it can also be used in Unix-like systems.

To build PCRE on a Unix-like system, first run the "configure" command from the
PCRE distribution directory, with your current directory set to the directory
where you want the files to be created. This command is a standard GNU
"autoconf" configuration script, for which generic instructions are supplied in
the file INSTALL.

Most commonly, people build PCRE within its own distribution directory, and in
this case, on many systems, just running "./configure" is sufficient. However,
the usual methods of changing standard defaults are available. For example:

CFLAGS='-O2 -Wall' ./configure --prefix=/opt/local

This command specifies that the C compiler should be run with the flags '-O2
-Wall' instead of the default, and that "make install" should install PCRE
under /opt/local instead of the default /usr/local.

If you want to build in a different directory, just run "configure" with that
directory as current. For example, suppose you have unpacked the PCRE source
into /source/pcre/pcre-xxx, but you want to build it in /build/pcre/pcre-xxx:

cd /build/pcre/pcre-xxx
/source/pcre/pcre-xxx/configure

PCRE is written in C and is normally compiled as a C library. However, it is
possible to build it as a C++ library, though the provided building apparatus
does not have any features to support this.

There are some optional features that can be included or omitted from the PCRE
library. They are also documented in the pcrebuild man page.

. By default, both shared and static libraries are built. You can change this
  by adding one of these options to the "configure" command:

  --disable-shared
  --disable-static

  (See also "Shared libraries on Unix-like systems" below.)

. By default, only the 8-bit library is built. If you add --enable-pcre16 to
  the "configure" command, the 16-bit library is also built. If you want only
  the 16-bit library, use "./configure --enable-pcre16 --disable-pcre8".

. If you are building the 8-bit library and want to suppress the building of
  the C++ wrapper library, you can add --disable-cpp to the "configure"
  command. Otherwise, when "configure" is run without --disable-pcre8, it will
  try to find a C++ compiler and C++ header files, and if it succeeds, it will
  try to build the C++ wrapper.

. If you want to include support for just-in-time compiling, which can give
  large performance improvements on certain platforms, add --enable-jit to the
  "configure" command. This support is available only for certain hardware
  architectures. If you try to enable it on an unsupported architecture, there
  will be a compile time error.

. When JIT support is enabled, pcregrep automatically makes use of it, unless
  you add --disable-pcregrep-jit to the "configure" command.

. If you want to make use of the support for UTF-8 Unicode character strings in
  the 8-bit library, or UTF-16 Unicode character strings in the 16-bit library,
  you must add --enable-utf to the "configure" command. Without it, the code
  for handling UTF-8 and UTF-16 is not included in the relevant library. Even
  when --enable-utf is included, the use of a UTF encoding still has to be
  enabled by an option at run time. When PCRE is compiled with this option, its
  input can only either be ASCII or UTF-8/16, even when running on EBCDIC
  platforms. It is not possible to use both --enable-utf and --enable-ebcdic at
  the same time.

. There are no separate options for enabling UTF-8 and UTF-16 independently
  because that would allow ridiculous settings such as requesting UTF-16
  support while building only the 8-bit library. However, the option
  --enable-utf8 is retained for backwards compatibility with earlier releases
  that did not support 16-bit character strings. It is synonymous with
  --enable-utf. It is not possible to configure one library with UTF support
  and the other without in the same configuration.

. If, in addition to support for UTF-8/16 character strings, you want to
  include support for the \P, \p, and \X sequences that recognize Unicode
  character properties, you must add --enable-unicode-properties to the
  "configure" command. This adds about 30K to the size of the library (in the
  form of a property table); only the basic two-letter properties such as Lu
  are supported.

. You can build PCRE to recognize either CR or LF or the sequence CRLF or any
  of the preceding, or any of the Unicode newline sequences as indicating the
  end of a line. Whatever you specify at build time is the default; the caller
  of PCRE can change the selection at run time. The default newline indicator
  is a single LF character (the Unix standard). You can specify the default
  newline indicator by adding --enable-newline-is-cr or --enable-newline-is-lf
  or --enable-newline-is-crlf or --enable-newline-is-anycrlf or
  --enable-newline-is-any to the "configure" command, respectively.

  If you specify --enable-newline-is-cr or --enable-newline-is-crlf, some of
  the standard tests will fail, because the lines in the test files end with
  LF. Even if the files are edited to change the line endings, there are likely
  to be some failures. With --enable-newline-is-anycrlf or
  --enable-newline-is-any, many tests should succeed, but there may be some
  failures.

. By default, the sequence \R in a pattern matches any Unicode line ending
  sequence. This is independent of the option specifying what PCRE considers to
  be the end of a line (see above). However, the caller of PCRE can restrict \R
  to match only CR, LF, or CRLF. You can make this the default by adding
  --enable-bsr-anycrlf to the "configure" command (bsr = "backslash R").

. When called via the POSIX interface, PCRE uses malloc() to get additional
  storage for processing capturing parentheses if there are more than 10 of
  them in a pattern. You can increase this threshold by setting, for example,

  --with-posix-malloc-threshold=20

  on the "configure" command.

. PCRE has a counter that can be set to limit the amount of resources it uses.
  If the limit is exceeded during a match, the match fails. The default is ten
  million. You can change the default by setting, for example,

  --with-match-limit=500000

  on the "configure" command. This is just the default; individual calls to
  pcre_exec() can supply their own value. There is more discussion on the
  pcreapi man page.

. There is a separate counter that limits the depth of recursive function calls
  during a matching process. This also has a default of ten million, which is
  essentially "unlimited". You can change the default by setting, for example,

  --with-match-limit-recursion=500000

  Recursive function calls use up the runtime stack; running out of stack can
  cause programs to crash in strange ways. There is a discussion about stack
  sizes in the pcrestack man page.

. The default maximum compiled pattern size is around 64K. You can increase
  this by adding --with-link-size=3 to the "configure" command. In the 8-bit
  library, PCRE then uses three bytes instead of two for offsets to different
  parts of the compiled pattern. In the 16-bit library, --with-link-size=3 is
  the same as --with-link-size=4, which (in both libraries) uses four-byte
  offsets. Increasing the internal link size reduces performance.

. You can build PCRE so that its internal match() function that is called from
  pcre_exec() does not call itself recursively. Instead, it uses memory blocks
  obtained from the heap via the special functions pcre_stack_malloc() and
  pcre_stack_free() to save data that would otherwise be saved on the stack. To
  build PCRE like this, use

  --disable-stack-for-recursion

  on the "configure" command. PCRE runs more slowly in this mode, but it may be
  necessary in environments with limited stack sizes. This applies only to the
  normal execution of the pcre_exec() function; if JIT support is being
  successfully used, it is not relevant. Equally, it does not apply to
  pcre_dfa_exec(), which does not use deeply nested recursion. There is a
  discussion about stack sizes in the pcrestack man page.

. For speed, PCRE uses four tables for manipulating and identifying characters
  whose code point values are less than 256. By default, it uses a set of
  tables for ASCII encoding that is part of the distribution. If you specify

  --enable-rebuild-chartables

  a program called dftables is compiled and run in the default C locale when
  you obey "make". It builds a source file called pcre_chartables.c. If you do
  not specify this option, pcre_chartables.c is created as a copy of
  pcre_chartables.c.dist. See "Character tables" below for further information.

. It is possible to compile PCRE for use on systems that use EBCDIC as their
  character code (as opposed to ASCII) by specifying

  --enable-ebcdic

  This automatically implies --enable-rebuild-chartables (see above). However,
  when PCRE is built this way, it always operates in EBCDIC. It cannot support
  both EBCDIC and UTF-8/16.

. The pcregrep program currently supports only 8-bit data files, and so
  requires the 8-bit PCRE library. It is possible to compile pcregrep to use
  libz and/or libbz2, in order to read .gz and .bz2 files (respectively), by
  specifying one or both of

  --enable-pcregrep-libz
  --enable-pcregrep-libbz2

  Of course, the relevant libraries must be installed on your system.

. The default size of internal buffer used by pcregrep can be set by, for
  example:

  --with-pcregrep-bufsize=50K

  The default value is 20K.

. It is possible to compile pcretest so that it links with the libreadline
  or libedit libraries, by specifying, respectively,

  --enable-pcretest-libreadline or --enable-pcretest-libedit

  If this is done, when pcretest's input is from a terminal, it reads it using
  the readline() function. This provides line-editing and history facilities.
  Note that libreadline is GPL-licenced, so if you distribute a binary of
  pcretest linked in this way, there may be licensing issues. These can be
  avoided by linking with libedit (which has a BSD licence) instead. 

  Enabling libreadline causes the -lreadline option to be added to the pcretest
  build. In many operating environments with a sytem-installed readline
  library this is sufficient. However, in some environments (e.g. if an
  unmodified distribution version of readline is in use), it may be necessary
  to specify something like LIBS="-lncurses" as well. This is because, to quote
  the readline INSTALL, "Readline uses the termcap functions, but does not link
  with the termcap or curses library itself, allowing applications which link
  with readline the to choose an appropriate library." If you get error
  messages about missing functions tgetstr, tgetent, tputs, tgetflag, or tgoto,
  this is the problem, and linking with the ncurses library should fix it.

The "configure" script builds the following files for the basic C library:

. Makefile             the makefile that builds the library
. config.h             build-time configuration options for the library
. pcre.h               the public PCRE header file
. pcre-config          script that shows the building settings such as CFLAGS
                         that were set for "configure"
. libpcre.pc         ) data for the pkg-config command
. libpcre16.pc       )
. libpcreposix.pc    )
. libtool              script that builds shared and/or static libraries
. RunTest              script for running tests on the basic C library
. RunGrepTest          script for running tests on the pcregrep command

Versions of config.h and pcre.h are distributed in the PCRE tarballs under the
names config.h.generic and pcre.h.generic. These are provided for those who
have to built PCRE without using "configure" or CMake. If you use "configure"
or CMake, the .generic versions are not used.

When building the 8-bit library, if a C++ compiler is found, the following
files are also built:

. libpcrecpp.pc        data for the pkg-config command
. pcrecpparg.h         header file for calling PCRE via the C++ wrapper
. pcre_stringpiece.h   header for the C++ "stringpiece" functions

The "configure" script also creates config.status, which is an executable
script that can be run to recreate the configuration, and config.log, which
contains compiler output from tests that "configure" runs.

Once "configure" has run, you can run "make". This builds either or both of the
libraries libpcre and libpcre16, and a test program called pcretest. If you
enabled JIT support with --enable-jit, a test program called pcre_jit_test is
built as well.

If the 8-bit library is built, libpcreposix and the pcregrep command are also
built, and if a C++ compiler was found on your system, and you did not disable
it with --disable-cpp, "make" builds the C++ wrapper library, which is called
libpcrecpp, as well as some test programs called pcrecpp_unittest,
pcre_scanner_unittest, and pcre_stringpiece_unittest.

The command "make check" runs all the appropriate tests. Details of the PCRE
tests are given below in a separate section of this document.

You can use "make install" to install PCRE into live directories on your
system. The following are installed (file names are all relative to the
<prefix> that is set when "configure" is run):

  Commands (bin):
    pcretest
    pcregrep (if 8-bit support is enabled)
    pcre-config

  Libraries (lib):
    libpcre16     (if 16-bit support is enabled)
    libpcre       (if 8-bit support is enabled)
    libpcreposix  (if 8-bit support is enabled)
    libpcrecpp    (if 8-bit and C++ support is enabled)

  Configuration information (lib/pkgconfig):
    libpcre16.pc
    libpcre.pc
    libpcreposix.pc
    libpcrecpp.pc (if C++ support is enabled)

  Header files (include):
    pcre.h
    pcreposix.h
    pcre_scanner.h      )
    pcre_stringpiece.h  ) if C++ support is enabled
    pcrecpp.h           )
    pcrecpparg.h        )

  Man pages (share/man/man{1,3}):
    pcregrep.1
    pcretest.1
    pcre-config.1
    pcre.3
    pcre*.3 (lots more pages, all starting "pcre")

  HTML documentation (share/doc/pcre/html):
    index.html
    *.html (lots more pages, hyperlinked from index.html)

  Text file documentation (share/doc/pcre):
    AUTHORS
    COPYING
    ChangeLog
    LICENCE
    NEWS
    README
    pcre.txt         (a concatenation of the man(3) pages)
    pcretest.txt     the pcretest man page
    pcregrep.txt     the pcregrep man page
    pcre-config.txt  the pcre-config man page

If you want to remove PCRE from your system, you can run "make uninstall".
This removes all the files that "make install" installed. However, it does not
remove any directories, because these are often shared with other programs.


Retrieving configuration information on Unix-like systems
---------------------------------------------------------

Running "make install" installs the command pcre-config, which can be used to
recall information about the PCRE configuration and installation. For example:

  pcre-config --version

prints the version number, and

  pcre-config --libs

outputs information about where the library is installed. This command can be
included in makefiles for programs that use PCRE, saving the programmer from
having to remember too many details.

The pkg-config command is another system for saving and retrieving information
about installed libraries. Instead of separate commands for each library, a
single command is used. For example:

  pkg-config --cflags pcre

The data is held in *.pc files that are installed in a directory called
<prefix>/lib/pkgconfig.


Shared libraries on Unix-like systems
-------------------------------------

The default distribution builds PCRE as shared libraries and static libraries,
as long as the operating system supports shared libraries. Shared library
support relies on the "libtool" script which is built as part of the
"configure" process.

The libtool script is used to compile and link both shared and static
libraries. They are placed in a subdirectory called .libs when they are newly
built. The programs pcretest and pcregrep are built to use these uninstalled
libraries (by means of wrapper scripts in the case of shared libraries). When
you use "make install" to install shared libraries, pcregrep and pcretest are
automatically re-built to use the newly installed shared libraries before being
installed themselves. However, the versions left in the build directory still
use the uninstalled libraries.

To build PCRE using static libraries only you must use --disable-shared when
configuring it. For example:

./configure --prefix=/usr/gnu --disable-shared

Then run "make" in the usual way. Similarly, you can use --disable-static to
build only shared libraries.


Cross-compiling on Unix-like systems
------------------------------------

You can specify CC and CFLAGS in the normal way to the "configure" command, in
order to cross-compile PCRE for some other host. However, you should NOT
specify --enable-rebuild-chartables, because if you do, the dftables.c source
file is compiled and run on the local host, in order to generate the inbuilt
character tables (the pcre_chartables.c file). This will probably not work,
because dftables.c needs to be compiled with the local compiler, not the cross
compiler.

When --enable-rebuild-chartables is not specified, pcre_chartables.c is created
by making a copy of pcre_chartables.c.dist, which is a default set of tables
that assumes ASCII code. Cross-compiling with the default tables should not be
a problem.

If you need to modify the character tables when cross-compiling, you should
move pcre_chartables.c.dist out of the way, then compile dftables.c by hand and
run it on the local host to make a new version of pcre_chartables.c.dist.
Then when you cross-compile PCRE this new version of the tables will be used.


Using HP's ANSI C++ compiler (aCC)
----------------------------------

Unless C++ support is disabled by specifying the "--disable-cpp" option of the
"configure" script, you must include the "-AA" option in the CXXFLAGS
environment variable in order for the C++ components to compile correctly.

Also, note that the aCC compiler on PA-RISC platforms may have a defect whereby
needed libraries fail to get included when specifying the "-AA" compiler
option. If you experience unresolved symbols when linking the C++ programs,
use the workaround of specifying the following environment variable prior to
running the "configure" script:

  CXXLDFLAGS="-lstd_v2 -lCsup_v2"


Using Sun's compilers for Solaris
---------------------------------

A user reports that the following configurations work on Solaris 9 sparcv9 and
Solaris 9 x86 (32-bit):

  Solaris 9 sparcv9: ./configure --disable-cpp CC=/bin/cc CFLAGS="-m64 -g"
  Solaris 9 x86:     ./configure --disable-cpp CC=/bin/cc CFLAGS="-g"


Using PCRE from MySQL
---------------------

On systems where both PCRE and MySQL are installed, it is possible to make use
of PCRE from within MySQL, as an alternative to the built-in pattern matching.
There is a web page that tells you how to do this:

  http://www.mysqludf.org/lib_mysqludf_preg/index.php


Making new tarballs
-------------------

The command "make dist" creates three PCRE tarballs, in tar.gz, tar.bz2, and
zip formats. The command "make distcheck" does the same, but then does a trial
build of the new distribution to ensure that it works.

If you have modified any of the man page sources in the doc directory, you
should first run the PrepareRelease script before making a distribution. This
script creates the .txt and HTML forms of the documentation from the man pages.


Testing PCRE
------------

To test the basic PCRE library on a Unix system, run the RunTest script that is
created by the configuring process. There is also a script called RunGrepTest
that tests the options of the pcregrep command. If the C++ wrapper library is
built, three test programs called pcrecpp_unittest, pcre_scanner_unittest, and
pcre_stringpiece_unittest are also built. When JIT support is enabled, another
test program called pcre_jit_test is built.

Both the scripts and all the program tests are run if you obey "make check" or
"make test". For other systems, see the instructions in NON-UNIX-USE.

The RunTest script runs the pcretest test program (which is documented in its
own man page) on each of the relevant testinput files in the testdata
directory, and compares the output with the contents of the corresponding
testoutput files. Some tests are relevant only when certain build-time options
were selected. For example, the tests for UTF-8/16 support are run only if
--enable-utf was used. RunTest outputs a comment when it skips a test.

Many of the tests that are not skipped are run up to three times. The second
run forces pcre_study() to be called for all patterns except for a few in some
tests that are marked "never study" (see the pcretest program for how this is
done). If JIT support is available, the non-DFA tests are run a third time,
this time with a forced pcre_study() with the PCRE_STUDY_JIT_COMPILE option.

When both 8-bit and 16-bit support is enabled, the entire set of tests is run
twice, once for each library. If you want to run just one set of tests, call
RunTest with either the -8 or -16 option.

RunTest uses a file called testtry to hold the main output from pcretest.
Other files whose names begin with "test" are used as working files in some
tests. To run pcretest on just one or more specific test files, give their
numbers as arguments to RunTest, for example:

  RunTest 2 7 11

The first test file can be fed directly into the perltest.pl script to check
that Perl gives the same results. The only difference you should see is in the
first few lines, where the Perl version is given instead of the PCRE version.

The second set of tests check pcre_fullinfo(), pcre_study(),
pcre_copy_substring(), pcre_get_substring(), pcre_get_substring_list(), error
detection, and run-time flags that are specific to PCRE, as well as the POSIX
wrapper API. It also uses the debugging flags to check some of the internals of
pcre_compile().

If you build PCRE with a locale setting that is not the standard C locale, the
character tables may be different (see next paragraph). In some cases, this may
cause failures in the second set of tests. For example, in a locale where the
isprint() function yields TRUE for characters in the range 128-255, the use of
[:isascii:] inside a character class defines a different set of characters, and
this shows up in this test as a difference in the compiled code, which is being
listed for checking. Where the comparison test output contains [\x00-\x7f] the
test will contain [\x00-\xff], and similarly in some other cases. This is not a
bug in PCRE.

The third set of tests checks pcre_maketables(), the facility for building a
set of character tables for a specific locale and using them instead of the
default tables. The tests make use of the "fr_FR" (French) locale. Before
running the test, the script checks for the presence of this locale by running
the "locale" command. If that command fails, or if it doesn't include "fr_FR"
in the list of available locales, the third test cannot be run, and a comment
is output to say why. If running this test produces instances of the error

  ** Failed to set locale "fr_FR"

in the comparison output, it means that locale is not available on your system,
despite being listed by "locale". This does not mean that PCRE is broken.

[If you are trying to run this test on Windows, you may be able to get it to
work by changing "fr_FR" to "french" everywhere it occurs. Alternatively, use
RunTest.bat. The version of RunTest.bat included with PCRE 7.4 and above uses
Windows versions of test 2. More info on using RunTest.bat is included in the
document entitled NON-UNIX-USE.]

The fourth and fifth tests check the UTF-8/16 support and error handling and
internal UTF features of PCRE that are not relevant to Perl, respectively. The
sixth and seventh tests do the same for Unicode character properties support.

The eighth, ninth, and tenth tests check the pcre_dfa_exec() alternative
matching function, in non-UTF-8/16 mode, UTF-8/16 mode, and UTF-8/16 mode with
Unicode property support, respectively.

The eleventh test checks some internal offsets and code size features; it is
run only when the default "link size" of 2 is set (in other cases the sizes
change) and when Unicode property support is enabled.

The twelfth test is run only when JIT support is available, and the thirteenth
test is run only when JIT support is not available. They test some JIT-specific
features such as information output from pcretest about JIT compilation.

The fourteenth, fifteenth, and sixteenth tests are run only in 8-bit mode, and
the seventeenth, eighteenth, and nineteenth tests are run only in 16-bit mode.
These are tests that generate different output in the two modes. They are for
general cases, UTF-8/16 support, and Unicode property support, respectively.

The twentieth test is run only in 16-bit mode. It tests some specific 16-bit
features of the DFA matching engine.

The twenty-first and twenty-second tests are run only in 16-bit mode, when the
link size is set to 2. They test reloading pre-compiled patterns.


Character tables
----------------

For speed, PCRE uses four tables for manipulating and identifying characters
whose code point values are less than 256. The final argument of the
pcre_compile() function is a pointer to a block of memory containing the
concatenated tables. A call to pcre_maketables() can be used to generate a set
of tables in the current locale. If the final argument for pcre_compile() is
passed as NULL, a set of default tables that is built into the binary is used.

The source file called pcre_chartables.c contains the default set of tables. By
default, this is created as a copy of pcre_chartables.c.dist, which contains
tables for ASCII coding. However, if --enable-rebuild-chartables is specified
for ./configure, a different version of pcre_chartables.c is built by the
program dftables (compiled from dftables.c), which uses the ANSI C character
handling functions such as isalnum(), isalpha(), isupper(), islower(), etc. to
build the table sources. This means that the default C locale which is set for
your system will control the contents of these default tables. You can change
the default tables by editing pcre_chartables.c and then re-building PCRE. If
you do this, you should take care to ensure that the file does not get
automatically re-generated. The best way to do this is to move
pcre_chartables.c.dist out of the way and replace it with your customized
tables.

When the dftables program is run as a result of --enable-rebuild-chartables,
it uses the default C locale that is set on your system. It does not pay
attention to the LC_xxx environment variables. In other words, it uses the
system's default locale rather than whatever the compiling user happens to have
set. If you really do want to build a source set of character tables in a
locale that is specified by the LC_xxx variables, you can run the dftables
program by hand with the -L option. For example:

  ./dftables -L pcre_chartables.c.special

The first two 256-byte tables provide lower casing and case flipping functions,
respectively. The next table consists of three 32-byte bit maps which identify
digits, "word" characters, and white space, respectively. These are used when
building 32-byte bit maps that represent character classes for code points less
than 256.

The final 256-byte table has bits indicating various character types, as
follows:

    1   white space character
    2   letter
    4   decimal digit
    8   hexadecimal digit
   16   alphanumeric or '_'
  128   regular expression metacharacter or binary zero

You should not alter the set of characters that contain the 128 bit, as that
will cause PCRE to malfunction.


File manifest
-------------

The distribution should contain the files listed below. Where a file name is
given as pcre[16]_xxx it means that there are two files, one with the name
pcre_xxx and the other with the name pcre16_xxx.

(A) Source files of the PCRE library functions and their headers:

  dftables.c              auxiliary program for building pcre_chartables.c
                            when --enable-rebuild-chartables is specified

  pcre_chartables.c.dist  a default set of character tables that assume ASCII
                            coding; used, unless --enable-rebuild-chartables is
                            specified, by copying to pcre[16]_chartables.c

  pcreposix.c             )
  pcre[16]_byte_order.c   )
  pcre[16]_compile.c      )
  pcre[16]_config.c       )
  pcre[16]_dfa_exec.c     )
  pcre[16]_exec.c         )
  pcre[16]_fullinfo.c     )
  pcre[16]_get.c          ) sources for the functions in the library,
  pcre[16]_globals.c      )   and some internal functions that they use
  pcre[16]_jit_compile.c  )
  pcre[16]_maketables.c   )
  pcre[16]_newline.c      )
  pcre[16]_refcount.c     )
  pcre[16]_string_utils.c )
  pcre[16]_study.c        )
  pcre[16]_tables.c       )
  pcre[16]_ucd.c          )
  pcre[16]_version.c      )
  pcre[16]_xclass.c       )
  pcre_ord2utf8.c         )
  pcre_valid_utf8.c       )
  pcre16_ord2utf16.c      )
  pcre16_utf16_utils.c    )
  pcre16_valid_utf16.c    )

  pcre[16]_printint.c     ) debugging function that is used by pcretest,
                          )   and can also be #included in pcre_compile()

  pcre.h.in               template for pcre.h when built by "configure"
  pcreposix.h             header for the external POSIX wrapper API
  pcre_internal.h         header for internal use
  sljit/*                 16 files that make up the JIT compiler
  ucp.h                   header for Unicode property handling

  config.h.in             template for config.h, which is built by "configure"

  pcrecpp.h               public header file for the C++ wrapper
  pcrecpparg.h.in         template for another C++ header file
  pcre_scanner.h          public header file for C++ scanner functions
  pcrecpp.cc              )
  pcre_scanner.cc         ) source for the C++ wrapper library

  pcre_stringpiece.h.in   template for pcre_stringpiece.h, the header for the
                            C++ stringpiece functions
  pcre_stringpiece.cc     source for the C++ stringpiece functions

(B) Source files for programs that use PCRE:

  pcredemo.c              simple demonstration of coding calls to PCRE
  pcregrep.c              source of a grep utility that uses PCRE
  pcretest.c              comprehensive test program

(C) Auxiliary files:

  132html                 script to turn "man" pages into HTML
  AUTHORS                 information about the author of PCRE
  ChangeLog               log of changes to the code
  CleanTxt                script to clean nroff output for txt man pages
  Detrail                 script to remove trailing spaces
  HACKING                 some notes about the internals of PCRE
  INSTALL                 generic installation instructions
  LICENCE                 conditions for the use of PCRE
  COPYING                 the same, using GNU's standard name
  Makefile.in             ) template for Unix Makefile, which is built by
                          )   "configure"
  Makefile.am             ) the automake input that was used to create
                          )   Makefile.in
  NEWS                    important changes in this release
  NON-UNIX-USE            notes on building PCRE on non-Unix systems
  PrepareRelease          script to make preparations for "make dist"
  README                  this file
  RunTest                 a Unix shell script for running tests
  RunGrepTest             a Unix shell script for pcregrep tests
  aclocal.m4              m4 macros (generated by "aclocal")
  config.guess            ) files used by libtool,
  config.sub              )   used only when building a shared library
  configure               a configuring shell script (built by autoconf)
  configure.ac            ) the autoconf input that was used to build
                          )   "configure" and config.h
  depcomp                 ) script to find program dependencies, generated by
                          )   automake
  doc/*.3                 man page sources for PCRE
  doc/*.1                 man page sources for pcregrep and pcretest
  doc/index.html.src      the base HTML page
  doc/html/*              HTML documentation
  doc/pcre.txt            plain text version of the man pages
  doc/pcretest.txt        plain text documentation of test program
  doc/perltest.txt        plain text documentation of Perl test program
  install-sh              a shell script for installing files
  libpcre16.pc.in         template for libpcre16.pc for pkg-config
  libpcre.pc.in           template for libpcre.pc for pkg-config
  libpcreposix.pc.in      template for libpcreposix.pc for pkg-config
  libpcrecpp.pc.in        template for libpcrecpp.pc for pkg-config
  ltmain.sh               file used to build a libtool script
  missing                 ) common stub for a few missing GNU programs while
                          )   installing, generated by automake
  mkinstalldirs           script for making install directories
  perltest.pl             Perl test program
  pcre-config.in          source of script which retains PCRE information
  pcre_jit_test.c         test program for the JIT compiler
  pcrecpp_unittest.cc          )
  pcre_scanner_unittest.cc     ) test programs for the C++ wrapper
  pcre_stringpiece_unittest.cc )
  testdata/testinput*     test data for main library tests
  testdata/testoutput*    expected test results
  testdata/grep*          input and output for pcregrep tests
  testdata/*              other supporting test files

(D) Auxiliary files for cmake support

  cmake/COPYING-CMAKE-SCRIPTS
  cmake/FindPackageHandleStandardArgs.cmake
  cmake/FindEditline.cmake
  cmake/FindReadline.cmake
  CMakeLists.txt
  config-cmake.h.in

(E) Auxiliary files for VPASCAL

  makevp.bat
  makevp_c.txt
  makevp_l.txt
  pcregexp.pas

(F) Auxiliary files for building PCRE "by hand"

  pcre.h.generic          ) a version of the public PCRE header file
                          )   for use in non-"configure" environments
  config.h.generic        ) a version of config.h for use in non-"configure"
                          )   environments

(F) Miscellaneous

  RunTest.bat            a script for running tests under Windows

Philip Hazel
Email local part: ph10
Email domain: cam.ac.uk
Last updated: 26 February 2012
