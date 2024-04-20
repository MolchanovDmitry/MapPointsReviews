Name:       ru.auroraos.PointsMapReviews
Summary:    Моё приложение для ОС Аврора
Version:    0.1
Release:    1
License:    BSD-3-Clause
URL:        https://auroraos.ru
Source0:    %{name}-%{version}.tar.bz2

BuildRequires: pkgconfig(auroraapp)
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5Qml)
BuildRequires: pkgconfig(Qt5Quick)
BuildRequires: pkgconfig(Qt5Network)
BuildRequires: pkgconfig(Qt5Sensors)
BuildRequires: pkgconfig(Qt5Location)
BuildRequires: pkgconfig(Qt5Positioning)
Requires: sailfishsilica-qt5 >= 0.10.9
Requires: qt5-qtlocation
Requires: qt5-qtpositioning
Requires: qt5-qtdeclarative-import-location
Requires: qt5-qtdeclarative-import-positioning
Requires: qt5-plugin-geoservices-webtiles

%description
Короткое описание моего приложения для ОС Аврора

%prep
%autosetup

%build
%qmake5
%make_build

%install
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%defattr(644,root,root,-)
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
