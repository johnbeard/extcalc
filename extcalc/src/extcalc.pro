HEADERS= extcalc.h
HEADERS+= buttons.h
HEADERS+= calcwidget.h
HEADERS+= global.h
HEADERS+= graph.h
HEADERS+= graphout.h
HEADERS+= graphpref.h
HEADERS+= graphsolve.h
HEADERS+= calctable.h
HEADERS+= calclocale.h
HEADERS+= calcinput.h
HEADERS+= calcpref.h
HEADERS+= table.h
HEADERS+= functiontable.h
HEADERS+= tablepref.h
HEADERS+= scriptedit.h
HEADERS+= scriptpref.h
HEADERS+= scriptio.h
HEADERS+= matrixwidget.h
HEADERS+= statistics.h
HEADERS+= catalog.h
HEADERS+= importdialog.h
SOURCES= extcalc.cpp
SOURCES+= buttons.cpp
SOURCES+= calcwidget.cpp
SOURCES+= global.cpp
SOURCES+= graph.cpp
SOURCES+= graphout.cpp
SOURCES+= graphpref.cpp
SOURCES+= graphsolve.cpp
SOURCES+= calctable.cpp
SOURCES+= calcinput.cpp
SOURCES+= calcpref.cpp
SOURCES+= table.cpp
SOURCES+= functiontable.cpp
SOURCES+= tablepref.cpp
SOURCES+= scriptedit.cpp
SOURCES+= scriptpref.cpp
SOURCES+= scriptio.cpp
SOURCES+= matrixwidget.cpp
SOURCES+= statistics.cpp
SOURCES+= catalog.cpp
SOURCES+= importdialog.cpp
ISQT=TRUE
CONSOLE=FALSE
AUTOMAKE=TRUE
ISCVS=TRUE
COMPILE=make -j4 CC='gcc -g'  CXX='g++ -g'
CVSPROTOCOL=ssh
CVSUSER=local1
CVSSERVER=rainer.homeunix.org
CVSSERVERPATH=/srv/cvs
CVSCHECK=TRUE
CVSCHECKUSER=cvs
CVSCHECKPASSWORD=cvs
OPENFILES=global.h, extcalc.h, graphsolve.cpp, graphsolve.h, extcalc.cpp, importdialog.h, importdialog.cpp
CONFIG+=opengl
CONFIG+=thread
