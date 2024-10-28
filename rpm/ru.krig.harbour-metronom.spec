Name:       ru.krig.harbour-metronom
Summary:    A simple metronome
Version:    0.1
Release:    1
Group:      Qt/Qt
License:    LICENSE
URL:        http://krig.ru/
Source0:    %{name}-%{version}.tar.bz2
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


%build
%qmake5
%make_build

# // %qtc_qmake5
# // %qtc_make %{?_smp_mflags}

%install
# install -D -m 0644  ../app/%{name}.desktop             %{buildroot}%{_datadir}/applications/%{name}.desktop
# install -D -m 0644  ../app/icons/86x86/%{name}.png     %{buildroot}%{_datadir}/icons/hicolor/86x86/apps/%{name}.png
# install -D -m 0644  ../app/icons/108x108/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/108x108/apps/%{name}.png
# install -D -m 0644  ../app/icons/128x128/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/128x128/apps/%{name}.png
# install -D -m 0644  ../app/icons/172x172/%{name}.png   %{buildroot}%{_datadir}/icons/hicolor/172x172/apps/%{name}.png
# install -D -m 0644  ./data/fine1.wav       %{buildroot}%{_datadir}/data/fine1.wav
# install -D -m 0644  ./data/fine2.wav       %{buildroot}%{_datadir}/data/fine2.wav
# install -D -m 0644  ./data/high.wav        %{buildroot}%{_datadir}/data/high.wav
# install -D -m 0644  ./data/low.wav         %{buildroot}%{_datadir}/data/low.wav
%make_install

#  desktop-file-install --delete-original       \
#    --dir %{buildroot}%{_datadir}/applications             \
#     %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%defattr(644,root,root,-)
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png

# //////%{_datadir}/data/*
