PROJECT(extcalc)


CMAKE_MINIMUM_REQUIRED(VERSION 2.4.3 FATAL_ERROR)




FIND_PACKAGE(Qt4 REQUIRED)

ADD_DEFINITIONS(-DQT3_SUPPORT)

SET( CMAKE_BUILD_TYPE Release )

SET( QT_USE_QT3SUPPORT TRUE )
SET( QT_USE_QTOPENGL TRUE )
SET( QT_USE_QTGUI TRUE )

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR}
                    ${QT_INCLUDE_PATH}
                    src/
                    .)

SET(CPACK_INSTALL_CMAKE_PROJECTS "/home/user/Projekte/extcalc;Extcalc;ALL;/")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Scientific Graphic Calculator")
SET(CPACK_PACKAGE_VENDOR "")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION "0.93")
SET(CPACK_PACKAGE_NAME "extcalc")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_STRIP_FILES "bin/extcalc")
SET(CPACK_SOURCE_STRIP_FILES "")
SET(CPACK_PACKAGE_EXECUTABLES "extcalc;extcalc")
SET(CPACK_GENERATOR "TGZ")
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_IGNORE_FILES "CVS/")
#Debian speciefic
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 , libgcc1, libgl1-mesa-glx | libgl1, libglu1-mesa | libglu1, libqtcore4, libqt4-qt3support , libstdc++6, libx11-6, libxext6, libxft2")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rainer Strobel <rainer1223@users.sourceforge.net>")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Extcalc is a multifunctional scientific graphic calculator for Linux with features like graph drawing, graph analysis and calculation of scientific functions. Extcalc also provides an integrated programming language.")
SET(CPACK_DEBIAN_PACKAGE_SECTION "math")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

SET(CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
SET(CPACK_RPM_PACKAGE_LICENSE "GPL")
SET(CPACK_RPM_PACKAGE_GROUP "Productivity/Schientific/Math")
SET(CPACK_RPM_PACKAGE_VENDOR "Rainer Strobel <rainer1223@users.sourceforge.net>")
SET(CPACK_RPM_PACKAGE_DESCRIPTION "Extcalc is a multifunctional scientific graphic calculator for Linux with features like graph drawing, graph analysis and calculation of scientific functions. Extcalc also provides an integrated programming language.")


INCLUDE(CPack)


SET(moc_h 
	src/buttons.h
	src/calcwidget.h
	src/graphinput.h
	src/table.h
	src/calcinput.h
	src/catalog.h
	src/graphout.h
	src/matrixwidget.h
	src/tablepref.h
	src/extcalc.h
	src/graphpref.h
	src/scriptedit.h
	src/functiontable.h
	src/graphsetdialog.h
	src/scriptio.h
	src/calcpref.h
	src/graphsolve.h
	src/scriptpref.h
	src/calctable.h
	src/graph.h
	src/importdialog.h
	src/tabwidget.h
	src/statistics.h
        src/scriptdisplay.h
        src/screenshotdialog.h
)

SET(src_h
	src/buttons.h
	src/calcwidget.h
	src/graphinput.h
	src/table.h
	src/calcinput.h
	src/catalog.h
	src/graphout.h
	src/matrixwidget.h
	src/tablepref.h
	src/extcalc.h
	src/graphpref.h
	src/scriptedit.h
	src/functiontable.h
	src/graphsetdialog.h
	src/scriptio.h
	src/calcpref.h
	src/graphsolve.h
	src/scriptpref.h
	src/calctable.h
	src/graph.h
	src/importdialog.h
	src/statistics.h
	src/tabwidget.h
	src/list.h
	src/calclocale.h
	src/global.h
        src/scriptdisplay.h
        src/screenshotdialog.h
)
	
SET(src_cxx 
	src/buttons.cpp
	src/calcwidget.cpp
	src/graphinput.cpp
	src/table.cpp
	src/calcinput.cpp
	src/catalog.cpp
	src/graphout.cpp
	src/matrixwidget.cpp
	src/tablepref.cpp
	src/extcalc.cpp
	src/graphpref.cpp
	src/scriptedit.cpp
	src/functiontable.cpp
	src/graphsetdialog.cpp
	src/scriptio.cpp
	src/calcpref.cpp
	src/graphsolve.cpp
	src/scriptpref.cpp
	src/calctable.cpp
	src/graph.cpp
	src/importdialog.cpp
	src/statistics.cpp
	src/tabwidget.cpp
	src/global.cpp
        src/scriptdisplay.cpp
        src/screenshotdialog.cpp
)

SET(src_ui src/screenshotdialog.ui
)

SET(src_qrc share/icons.qrc)


QT4_ADD_RESOURCES(qrc_cxx ${src_qrc})

QT4_WRAP_CPP(moc_cxx ${moc_h})

QT4_WRAP_UI(ui_h ${src_ui})



SET(CMAKE_INSTALL_PREFIX "/usr")
SET(SHAREDIR "share/extcalc/data")
SET(DOCDIR "share/extcalc/doc")
SET(DESKTOPDIR "share/applications")
SET(ICONDIR "share/icons")
SET(MANDIR "/usr/man")
SET(BINDIR "bin")
ADD_DEFINITIONS(-DINSTALLDIR=\"\\\"${CMAKE_INSTALL_PREFIX}/share/extcalc\\\"\")


#installer data
INSTALL(FILES
	share/binary.png
	share/catalog.png
	share/text.png
	share/scientific.png
	share/angle.png
	share/editcopy.png
	share/view_remove.png
	share/view_top_bottom.png
	share/undo.png
	share/modified.png
	share/redo.png
	share/rubber.png
	share/forward.png
	share/fileexport.png
	share/filenew.png
	share/back.png
	share/editpaste.png
	share/editdelete.png
	share/print.png
	share/save_all.png
	share/open.png
	share/zoomout.png
	share/filesaveas.png
	share/zoomin.png
	share/editcut.png
	share/exit.png
	share/fileimport.png
	share/exec.png
	share/rect.png
	share/free.png
	share/circle.png
	share/line.png
	share/icons.qrc
	DESTINATION ${SHAREDIR}
	)
INSTALL(FILES
	share/qt_fr.qm
	share/qt_de.qm
	share/french.qm
	share/german.qm
	DESTINATION ${SHAREDIR}
	)
INSTALL(FILES
	share/crossproduct
	share/dotproduct
	share/snake
	share/matrix-vector
	share/matrixproduct
	DESTINATION ${SHAREDIR}
)

INSTALL(FILES
	share/license.txt
	DESTINATION ${SHAREDIR}
)

INSTALL(FILES
	share/extcalc.desktop
	DESTINATION ${DESKTOPDIR}
)

INSTALL(FILES
	share/extcalc22.png
	share/extcalc48.png
	DESTINATION ${ICONDIR}
)

INSTALL(FILES
	doc/dev_docu.html
	doc/help_de.html
	doc/help_en.html
	doc/help_fr.html
	DESTINATION ${DOCDIR}
)

INSTALL(FILES
	doc/3dgraph.jpg
	doc/alpha.jpg
	doc/analyse.jpg
	doc/calculator.jpg
	doc/catalogbutton.jpg
	doc/curoot.jpg
	doc/diffbutton.jpg
	doc/diff.jpg
	doc/graph.jpg
	doc/integralbutton.jpg
	doc/integral.jpg
	doc/matvec.jpg
	doc/nrootbutton.jpg
	doc/nroot.jpg
	doc/randbutton.jpg
	doc/random.jpg
	doc/screenshot.jpg
	doc/scriptedit2.jpg
	doc/scriptedit.jpg
	doc/scriptrun.jpg
	doc/setbutton.jpg
	doc/setbutton.jpg
	doc/setvar.jpg
	doc/shift.jpg
	doc/sqrtbracket.jpg
	doc/sqrtbutton.jpg
	doc/sqrt.jpg
	doc/stat1.jpg
	doc/stat2.jpg
	doc/table.jpg
	doc/usevar.jpg
	DESTINATION ${DOCDIR}
)

ADD_EXECUTABLE(extcalc WIN32 ${src_cxx} ${src_h} ${moc_cxx} ${moc_ui_cxx} ${src_ui_cxx} ${ui_h} ${qrc_cxx})
TARGET_LINK_LIBRARIES(extcalc ${QT_LIBRARIES})

  INSTALL(TARGETS extcalc RUNTIME DESTINATION bin
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
		  GROUP_EXECUTE GROUP_READ
		  WORLD_EXECUTE WORLD_READ)




