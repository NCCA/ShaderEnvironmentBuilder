# This specifies the exe name
TARGET=CEB.out
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES= $$PWD/src/*.cpp
# same for the .h files
HEADERS+= $$PWD/include/*.h
FORMS+= $$PWD/ui/MainWindow.ui
# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./
# add the glsl shader files
OTHER_FILES+= $$PWD/shaders/*.glsl
OTHER_FILES+= $$PWD/src/*.api
OTHER_FILES+= $$PWD/ui_MainWindow.h
# were are going to default to a console app
CONFIG += console
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}


# include QSci headers and lib
LIBS += $$PWD/lib/libqscintilla2.a
# include boost headers and libs. Used for creating a directory
# for temp output files json
INCLUDEPATH+=/usr/local/include
LIBS+= -lboost_system -lboost_filesystem


# include Flex libs
LIBS += $$PWD/lib/libfl.a

# Set up Flex to run on build
# Test if Flex is installed
FLEX_BIN = $$system(which flex)
isEmpty(FLEX_BIN) {
    error("Flex not found")
} else {
    message("Found Flex")

    # run Flex on .lex file to generate lexer

    # The following section is from :-
    # hipersayan_x (March 1, 2013)  The Samurai Code: Using Flex and Bison with Qt. [online]
    # [Accessed 18 Feb. 2016] Available at: <http://hipersayanx.blogspot.co.uk/2013/03/using-flex-and-bison-with-qt.html>.
    FLEXSOURCES = src/GlslLexer.lex

    flexsource.input = FLEXSOURCES
    flexsource.output = src/generated/${QMAKE_FILE_BASE}.cpp
    flexsource.commands = flex --header-file=include/generated/${QMAKE_FILE_BASE}.h -o src/generated/${QMAKE_FILE_BASE}.cpp -+ ${QMAKE_FILE_IN}
    flexsource.variable_out = SOURCES
    flexsource.clean = src/generated/${QMAKE_FILE_BASE}.cpp
    flexsource.name = Flex Sources ${QMAKE_FILE_IN}
    flexsource.CONFIG += target_predeps

    QMAKE_EXTRA_COMPILERS += flexsource

    flexheader.input = FLEXSOURCES
    flexheader.output = include/generated/${QMAKE_FILE_BASE}.h
    fleakheader.commands = @true
    flexheader.variable_out = HEADERS
    flexheader.clean = include/generated/${QMAKE_FILE_BASE}.h
    flexheader.name = Flex Headers ${QMAKE_FILE_IN}
    flexheader.CONFIG += target_predeps no_link

    QMAKE_EXTRA_COMPILERS += flexheader
    # end of Citation
}

# Supress yield warning
QMAKE_CXXFLAGS_WARN_ON += -Wno-deprecated-register
