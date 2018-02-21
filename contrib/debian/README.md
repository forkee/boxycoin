
Debian
====================
This directory contains files used to package boxycoind/boxycoin-qt
for Debian-based Linux systems. If you compile boxycoind/boxycoin-qt yourself, there are some useful files here.

## boxycoin: URI support ##


boxycoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install boxycoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your boxycoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/boxycoin128.png` to `/usr/share/pixmaps`

boxycoin-qt.protocol (KDE)

