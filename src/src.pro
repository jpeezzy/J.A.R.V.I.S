######################################################################
# Automatically generated by qmake (3.0) Thu Aug 10 16:34:52 2017
######################################################################

TEMPLATE = app
TARGET = src
INCLUDEPATH += .

# Input
HEADERS += commands.h \
           music.h \
           myClock.h \
           Personality.h \
           user.h \
           simplemenu.h \
           network/websearch.h
SOURCES += commands.cpp \
           main.cpp \
           music.cpp \
           myClock.cpp \
           Personality.cpp \
           user.cpp \
           gui/simplemenu.cpp \
           network/test.cpp \
           network/websearch.cpp

QT += widgets gui core multimedia multimediawidgets