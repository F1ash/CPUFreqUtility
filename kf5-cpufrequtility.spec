%define cmake_build_dir build-cmake

Name:        kf5-cpufrequtility
Version:     1.0
Release:     1%{?dist}
Summary:     CPU Frequence Utility
Summary(ru): Утилита для управления режимом работы процессора
Group:       Applications/Utility
License:     GPL2+
Source0:     https://github.com/F1ash/%{name}/archive/%{version}.tar.gz 
URL:         https://github.com/F1ash/%{name}

Requires: qt5-qtbase, kf5-kauth
BuildRequires: qt5-qtbase-devel, kf5-kauth-devel, extra-cmake-modules

%description
kf5-cpufrequtility
CPU Frequence Utility.

%description -l ru
kf5-cpufrequtility
Утилита для управления режимом работы процессора.

%prep
%setup -q

%build
mkdir %{cmake_build_dir}
pushd %{cmake_build_dir}
      %cmake ..
      %{make_build}
popd

%install
pushd %{cmake_build_dir}
      %{make_install}
popd

%check
desktop-file-validate %{buildroot}/%{_datadir}/applications/%{name}.desktop

%files
%doc README.md COPYING Changelog
%{_bindir}/%{name}
%{_libexecdir}/kf5/kauth/cpu_freq_helper
%{_datadir}/applications/%{name}.desktop
%{_datadir}/dbus-1/system-services/org.freedesktop.auth.cpufrequtility.service
%{_datadir}/polkit-1/actions/org.freedesktop.auth.cpufrequtility.policy
%{_sysconfdir}/dbus-1/system.d/org.freedesktop.auth.cpufrequtility.conf

%changelog
* Tue Jun  9 2015 Fl@sh <kaperang07@gmail.com> - 1.0-1
- Initial build
