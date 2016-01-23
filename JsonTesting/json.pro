SOURCES+=json.cpp \
    main.cpp \
    io_xml.cpp
TARGET=json

INCLUDEPATH+=/usr/local/include

HEADERS += \
    json.h \
    io_xml.h
INCLUDEPATH +=./include



NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}
