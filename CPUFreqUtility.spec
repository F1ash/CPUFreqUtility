%define cmake_build_dir build-cmake

Name:          CPUFreqUtility
Version:       1.4.3
Release:       1%{?dist}
Summary:       CPU Frequence Utility
Summary(ru):   Утилита для управления режимом работы процессора
Group:         Applications/System
License:       GPL2+
Source0:       https://github.com/F1ash/%{name}/archive/%{version}.tar.gz
URL:           https://github.com/F1ash/%{name}

Requires:      qt5-qtbase
Requires:      kf5-kauth
Requires:      kf5-knotifications

BuildRequires: desktop-file-utils
BuildRequires: qt5-qtbase-devel
BuildRequires: kf5-kauth-devel
BuildRequires: kf5-knotifications-devel
BuildRequires: extra-cmake-modules

%description
CPUFreqUtility
KDE Utility is managed the CPU work mode

%description -l ru
CPUFreqUtility
KDE Утилита для управления режимом работы процессора

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
%{_datadir}/knotifications5/%{name}.notifyrc

%changelog
* Wed Jul  1 2015 Fl@sh <kaperang07@gmail.com> - 1.4.3-1
- version updated;

* Sun Jun 21 2015 Fl@sh <kaperang07@gmail.com> - 1.2.2-1
- version updated;

* Sun Jun 14 2015 Fl@sh <kaperang07@gmail.com> - 1.1.2-2
- package renamed;

* Sat Jun 13 2015 Fl@sh <kaperang07@gmail.com> - 1.1.2-1
- version updated;

* Fri Jun 12 2015 Fl@sh <kaperang07@gmail.com> - 1.1.1-1
- version updated;

* Wed Jun 10 2015 Fl@sh <kaperang07@gmail.com> - 1.1-1
- added kf5-knotifications R, BR, %%files;

* Tue Jun  9 2015 Fl@sh <kaperang07@gmail.com> - 1.0-1
- Initial build
