# Ft_ls [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/de54d3705c7045308409aae5d00b5f52)](https://www.codacy.com/app/Ant0wan/Ft_ls?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/Ft_ls&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.com/Ant0wan/Ft_ls.svg?token=VdyQsq19sYjUnnsje5hY&branch=master)](https://travis-ci.com/Ant0wan/Ft_ls)

---

## Description

`ft_ls` is a tiny and simplified copy of the functionalities of the command line tool ls.

It behaves almost as identical to the original ls command with the variations mentionned in its man page (please refer to Man ft_ls section).

It includes test tools. `make test` will execute them. tests can be customized in the `/tools/input-ls` text file.

- Authorized functions:

```
write
opendir
readdir
closedir
stat
lstat
getpwuid
getgrgid
listxattr
getxattr
time
ctime
readlink
malloc
free
perror
strerror
exit
```

---

## Man ft_ls

Below, details about ft_ls usage.

```shell=
FT_LS(1)				42 Projects Commands Manual					FT_LS(1)

NAME
	ft_ls -- list directory contents on OSX

SYNOPSIS
	ft_ls [-@ARTaceflrtu] [file ...]

DESCRIPTION
	For each operand that names a file of a type other than directory, ft_ls
	displays its name as well as any requested, associated information.
	For each operand that names a file of type directory, ft_ls displays the
	names of files contained within that directory, as well as any
	requested, associated information.

	If no operands are given, the contents of the current directory are
	displayed.  If more than one operand is given, non-directory operands
	are displayed first; directory and non-directory operands are sorted
	separately and in lexicographical order.

	The following options are available:

	-@	Display extended attribute keys and sizes in long (-l) output.

	-A	List all entries except for . and ...  Always set for the
		super-user.

	-a	Include directory entries whose names begin with a dot (.).

	-c	Use time when file status was last changed for sorting (-t) or
		long printing (-l).
	
	-e	Print the Access Control List (ACL) associated with the file,
		if present, in long (-l) output.
	
	-f	Output is not sorted.  This option turns on the -a option.

	-l	(The lowercase letter ``ell''.)  List in long format.  (See
		below.)  If the output is to a terminal, a total sum for all
		the file sizes is output on a line before the long listing.
	
	-R	Recursively list subdirectories encountered.

	-r	Reverse the order of the sort to get reverse lexicographical
		order or the oldest entries first (or largest files last, if
		combined with sort by size
	
	-T	When used with the -l (lowercase letter ``ell'') option, dis-
		play complete time information for the file, including month,
		day, hour, minute, second, and year.
	
	-t	Sort by time modified (most recently modified first) before
		sorting the operands by lexicographical order.
	
	-u	Use time of last access, instead of last modification of the
		file for sorting (-t) or long printing (-l).
	
	The -c and -u options override each other; the last one specified
	determines the file time used.

	By default, ft_ls lists one entry per line to standard output.

 The Long Format

	If the -l option is given, the following information is displayed for
	each file: file mode, number of links, owner name, group name, number
	of bytes in the file, abbreviated month, day-of-month file was last
	modified, hour file last modified, minute file last modified, and the
	pathname.  In addition, for each directory whose contents are dis-
	played, the total number of 512-byte blocks used by the files in the
	directory is displayed on a line by itself, immediately before the
	information for the files in the directory.  If the file or directory
	has extended attributes, the permissions field printed by the -l option
	is followed by a '@' character.  Otherwise, if the file or directory
	has extended security information (such as an access control list), the
	permissions field printed by the -l option is followed by a '+' charac-
	ter.

	If the modification time of the file is more than 6 months in the past
	or future, then the year of the last modification is displayed in place
	of the hour and minute fields.

	If the file is a character special or block special file, the major and
	minor device numbers for the file are displayed in the size field.  If
	the file is a symbolic link, the pathname of the linked-to file is pre-
	ceded by ``->''.

	The file mode printed under the -l option consists of the entry type,
	owner permissions, and group permissions.  The entry type character
	describes the type of file, as follows:

		b	Block special file.
		c	Character special file.
		d	Directory.
		l	Symbolic link.
		s	Socket link.
		p	FIFO.
		-	Regular file.

	The next three fields are three characters each: owner permissions,
	group permissions, and other permissions.  Each field has three charac-
	ter positions:

		1.	If r, the file is readable; if -, it is not readable.

		2.	If w, the file is writable; if -, it is not writable.

		3.	The first of the following that applies:

			S	If in the owner permissions, the file is not
				executable and set-user-ID mode is set.  If in
				the group permissions, the file is not exe-
				cutable and set-group-ID mode is set.

			s	If in the owner permissions, the file is exe-
				cutable and set-user-ID mode is set.  If in the
				group permissions, the file is executable and
				setgroup-ID mode is set.

			x	The file is executable or the directory is
				searchable.

			-	The file is neither readable, writable, exe-
				cutable, nor set-user-ID nor set-group-ID mode,
				nor sticky.  (See below.)

		  These next two apply only to the third character in the last
		  group (other permissions).

		  	T	The sticky bit is set (mode 1000), but not exe-
				cute or search permission.  (See chmod(1) or
				sticky(8).)

			t	The sticky bit is set (mode 1000), and is
				searchable or executable.  (See chmod(1) or
				sticky(8).)

EXAMPLES
	The following is how to do an ft_ls listing sorted by modified time

		ft_ls -lt

DIAGNOSTICS
	The ft_ls utility exits 0 on success, and >0 if an error occurs.

	Exit status:
		
		0		if OK,

		1		if minor problems (e.g., cannot access subdirectory),

		2		if serious trouble (e.g., cannot access command-line
				argument).

AUTHOR
	Written by sel-ahma and abarthel, 42 students.

SEE ALSO
	Full documentation:
	https://github.com/giacomoguiulfo/42-ft_ls/blob/master/pdfs/ft_ls.en.pdf

						July 2019
```

---

## Usage

Check Perl is up to date on your system.

- Compiling the project

```
git clone https://github.com/Ant0wan/Ft_ls ; cd Ft_ls ; make -j
```

- Executing program tests

```
make test
```

- Usage example

```
./ft_ls -lRA
```

## Demo

[![Demoft_ls](https://i.imgur.com/c1LECl5.gif)](i.imgur.com/c1LECl5.gif)
