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
BuildRequires:  pulseaudio-devel
BuildRequires:  pulseaudio

%description
Metronome for AuroraOS

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5
%make_build

%install
install -D -m 0644 %{_sourcedir}/../app/data/fine1.wav  %{buildroot}%{_datadir}/%{name}/data/fine1.wav
install -D -m 0644 %{_sourcedir}/../app/data/fine2.wav  %{buildroot}%{_datadir}/%{name}/data/fine2.wav
install -D -m 0644 %{_sourcedir}/../app/data/high.wav   %{buildroot}%{_datadir}/%{name}/data/high.wav
install -D -m 0644 %{_sourcedir}/../app/data/low.wav    %{buildroot}%{_datadir}/%{name}/data/low.wav
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%defattr(644,root,root,-)
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
%{_datadir}/%{name}/data/fine1.wav
%{_datadir}/%{name}/data/fine2.wav
%{_datadir}/%{name}/data/high.wav
%{_datadir}/%{name}/data/low.wav
