Name: libdeep
Version: 1.00
Release: 1%{?dist}
Summary: Library for deep learning
License: BSD
URL: https://github.com/fuzzgun/libdeep
Packager: Bob Mottram (4096 bits) <bob@robotics.uk.to>
Source0: http://yourdomainname.com/src/%{name}_%{version}.orig.tar.gz
Group: Development/ArtificialIntelligence

Requires: gnuplot, libpng-devel


%description
Makes using deep learning easy to include within any C/C++ application.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}
mkdir -p %{buildroot}/etc
mkdir -p %{buildroot}/etc/%{name}
mkdir -p %{buildroot}/usr
mkdir -p %{buildroot}/usr/bin
mkdir -p %{buildroot}/usr/lib
mkdir -p %{buildroot}/usr/lib/%{name}
mkdir -p %{buildroot}/usr/share
mkdir -p %{buildroot}/usr/share/man
mkdir -p %{buildroot}/usr/share/man/man1
# Make install but to the RPM BUILDROOT directory
make instlib -B DESTDIR=%{buildroot} PREFIX=/usr

%files
%doc README.md LICENSE
%defattr(-,root,root,-)
%{_bindir}/*
%{_mandir}/man1/*

%post
umask 007
ldconfig > /dev/null 2>&1

%postun
umask 007
ldconfig > /dev/null 2>&1

%changelog
* Sat Jan 5 2013 Bob Mottram (4096 bits) <bob@robotics.uk.to> - 1.00-1
- Initial release
