#
# spec file for udo
#
# Written by Volker Janzen
#
# Build RPMs with: rpm -ba udo.spec
#
# Query example: rpm -q -l -p udo-6.2.1-1.i386.rpm
#
# These things have to be fixed for a new RPM:
# - Release: increase by 1, if no new upstream version is packaged,
#            else set it back to 1
# - Version: change if upstream version has changed
# - Source : change if new upstream version is packaged
#
Summary: Universal DOcument (UDO) - text processing utility
Name: udo
Version: 6.4.0
Release: 1
Copyright: GPL
Group: Productivity/Publishing/UDO
Prefix: %{_prefix}
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot
Source: http://www.udo-open-source.org/download/sources/udo_%{version}_src.tar.gz
URL: http://www.udo-open-source.org/
Vendor: UDO - Open Source
Packager: Volker Janzen <webmaster@udo-open-source.org>

%description
UDO is a powerful and multipurpose utility for making documentation or any
other text file that is needed in one text format or more. UDO documents can
be converted to ASCII, HTML, LaTeX, nroff, PostScript, RTF and many more.
Though UDO is powerful, it's quite easy to understand and to use.

%prep
%setup -q -n udo_%{version}

%build
cd Source
make -f Makefile.linux
cd ../doc/manpage/
../../Source/udo --nroff -q -o udo.1 manpage.u
gzip -9 udo.1

%install
cd Source
rm -rf "$RPM_BUILD_ROOT"
mkdir -p $RPM_BUILD_ROOT%{_mandir}/man1
mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p $RPM_BUILD_ROOT%{_docdir}/udo-%{version}
install -m 644 ../doc/manpage/udo.1.gz $RPM_BUILD_ROOT%{_mandir}/man1
install -m 644 ../README $RPM_BUILD_ROOT%{_docdir}/udo-%{version}
install -m 755 udo $RPM_BUILD_ROOT%{_bindir}
strip $RPM_BUILD_ROOT%{_bindir}/udo

%files
%defattr(-,root,root)
%doc README
%{_bindir}/*
%{_mandir}/man1/*

%changelog
* Wed Jan 07 2004 Volker Janzen <webmaster@udo-open-source.org>
- new manpage is used now
* Sat Dec 27 2003 Martin Tarenskeen <m.tarenskeen@zonnet.nl>
- revised specfile
