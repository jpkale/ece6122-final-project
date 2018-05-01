# Final Project for ECE6122

## Description
A simple client-server banking application.  Details can be found in the
submitted report.

## Required Packages
The client GUI runs on top of curses.  You will need a terminal capable of
supporting curses for this to work, i.e. any UNIX-like terminal, or Cygwin in
Windows.

If curses is not already installed on your system, install it with the
following instructions:

### Archlinux
- `pacman -S ncurses`

### Ubuntu/Debian
- `apt install ncurses-bin ncurses-base`

### Fedora/CentOS/RHEL
- `yum install ncurses-devel`

### MacOS
- First install Homebrew via their [instructions](https://brew.sh/)
- `brew install ncurses`

### Windows
- First, install Cygwin via their [instructions](https://www.cygwin.com/)
- When going through the package install, `libncurses-devel` and `ncurses`
