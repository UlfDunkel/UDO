#
# spec file for udo
#
# Written by Volker Janzen
#
# Build RPMs with: rpm -ba udo.spec
#
# Query example: rpm -q -l -p udo-6.2.0-1.i386.rpm
#
# These things have to be fixed for a new RPM:
# - Release: increase by 1, if now new upstream version is packaged,
#            else set it back to 1
# - Version: change if upstream version has changed
# - Source : change if new upstream version is packaged
# - Build-Skript needs to be changed, if archive name changes
#
Summary: Universal DOcument (UDO) - text processing utility
Name: udo
Version: 6.2.0
Release: 3
Copyright: GPL
Group: Applications/Text
Source: http://www.udo-open-source.org/download/sources/udo_6.2.0_src.tar.gz
URL: http://www.udo-open-source.org/
Vendor: UDO - Open Source
Packager: Volker Janzen <webmaster@udo-open-source.org>

%description
UDO is a powerful and multipurpose utility for making documentation or any
other text file that is needed in one text format or more. UDO documents can
be converted to ASCII, HTML, LaTeX, nroff, PostScript, RTF and many more.
Though UDO is powerful, it's quite easy to understand and to use.

%prep
rm -rf $RPM_BUILD_DIR/udo_6.2.0
tar xzf $RPM_SOURCE_DIR/udo_6.2.0_src.tar.gz

%build
make -C udo_6.2.0/Source -f Makefile.linux
chmod 755 udo_6.2.0/Source/udo
mkdir -p /usr/local/man/man1
$RPM_BUILD_DIR/udo_6.2.0/Source/udo --nroff -q -o /usr/local/man/man1/udo.1 $RPM_BUILD_DIR/udo_6.2.0/Guide/eng/manual/manpage.u
gzip -9 /usr/local/man/man1/udo.1

%install
strip udo_6.2.0/Source/udo
cp udo_6.2.0/Source/udo /usr/local/bin
mkdir -p /usr/share/doc/udo
cp $RPM_BUILD_DIR/udo_6.2.0/README /usr/share/doc/udo

%files
%doc /usr/share/doc/udo/README
/usr/local/bin/udo
/usr/local/man/man1/udo.1.gz
