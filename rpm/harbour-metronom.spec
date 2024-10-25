Name:       ru.krig.harbour-metronom

# >> macros
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    A simple metronome
Version:    0.1
Release:    1
Group:      Qt/Qt
License:    LICENSE
URL:        http://krig.ru/
Source:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(sailfishapp) >= 0.0.10
BuildRequires:  pkgconfig(libresourceqt5)
BuildRequires:  desktop-file-utils

%description
Metronome for AuroraOS

%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
%qmake5
%make_build
# << build pre

%qtc_qmake5 

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
#rm -rf %{buildroot}
# >> install pre
#install -D -m 0644  ./%{name}.desktop             %{buildroot}%{_datadir}/applications/%{name}.desktop
install -D -m 0644  icons/86x86/%{name}.png     %{buildroot}%{_datadir}/icons/hicolor/86x86/apps/%{name}.png
install -D -m 0644  icons/108x108/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/108x108/apps/%{name}.png
install -D -m 0644  icons/128x128/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/128x128/apps/%{name}.png
install -D -m 0644  icons/172x172/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/172x172/apps/%{name}.png
# << install pre
%qmake5_install

# >> install post
# << install post

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
#%defattr(-,root,root,-)
%{_bindir}/%{name}
#%{_datadir}/%{name}/qml
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/86x86/apps/%{name}.png
%{_datadir}/icons/hicolor/108x108/apps/%{name}.png
%{_datadir}/icons/hicolor/128x128/apps/%{name}.png
%{_datadir}/icons/hicolor/172x172/apps/%{name}.png
%{_datadir}/%{name}/data
# >> files
# << files