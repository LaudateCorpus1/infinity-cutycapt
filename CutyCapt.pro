QT       +=  webkit svg network
SOURCES   =  CutyCapt.cpp CookieJar.cpp
HEADERS   =  CutyCapt.hpp CookieJar.hpp
CONFIG   +=  qt console debug

greaterThan(QT_MAJOR_VERSION, 4): {
  QT       +=  webkitwidgets
  QT       +=  printsupport
}

contains(CONFIG, static): {
  QTPLUGIN += qjpeg qgif qsvg qmng qico qtiff
  DEFINES  += STATIC_PLUGINS
}
