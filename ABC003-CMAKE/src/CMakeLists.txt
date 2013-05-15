cmake_minimum_required(VERSION 2.8)

PROJECT(abc)


if( NOT CMAKE_BUILD_TYPE )

  set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
       FORCE )
endif()


#----------------------------------------------------------------------------
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

#----------------------------------------------------------------------------
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Cmake/Modules/")

#----------------------------------------------------------------------------
FIND_PATH(QEXT_INCLUDE_DIR
    NAMES Qext Qextserial qextserialport.h
	HINTS ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${QEXT_INCLUDE_DIR})
	
FIND_LIBRARY(QEXT_LIBRARY
    NAMES qextserial
	HINTS ${QT_LIBRARY_DIR})
SET(QEXT_LIBRARIES ${QEXT_LIBRARY})
	
#----------------------------------------------------------------------------
FIND_PACKAGE(Qwt)
INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})

#----------------------------------------------------------------------------
FIND_PATH(QXT_INCLUDE_CORE
    NAMES Qxt QxtCore qxtCore.h
	HINTS ${QT_INCLUDE_CORE})
FIND_PATH(QXT_INCLUDE_GUI
    NAMES Qxt QxtGui qxtGui.h
	HINTS ${QT_INCLUDE_GUI})
SET(QXT_INCLUDE_DIRS ${QXT_INCLUDE_CORE} ${QXT_INCLUDE_GUI})
INCLUDE_DIRECTORIES(${QXT_INCLUDE_DIRS})
		
FIND_LIBRARY(QXT_LIBRARY_CORE
    NAMES QxtCore
	HINTS ${QT_LIBRARY_DIR})
FIND_LIBRARY(QXT_LIBRARY_GUI
    NAMES QxtGui
	HINTS ${QT_LIBRARY_DIR})	
SET(QXT_LIBRARIES ${QXT_LIBRARY_CORE} ${QXT_LIBRARY_GUI})
    




# use what QVTK built with
SET(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")


# Use the include path and library for Qt that is used by VTK.
INCLUDE_DIRECTORIES(
  ${QT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


# Set your files and resources here  
# SET(SimpleViewSrcs main.cxx View.cxx)
# SET(SimpleViewUI SimpleView.ui)
# SET(SimpleViewHeaders SimpleView.h)
# SET(SimpleViewResources Icons/icons.qrc)

QT4_WRAP_UI(UISrcs com.ui dialog.ui)
QT4_WRAP_CPP(MOCSrcs com.h dialog.h io.h)
#QT4_ADD_RESOURCES(ResourceSrcs Icons/icons.qrc)



ADD_EXECUTABLE( abc main.cpp com.cpp dialog.cpp io.cpp ${UISrcs} ${MOCSrcs} )

TARGET_LINK_LIBRARIES( abc
  ${QT_LIBRARIES}
  ${QXT_LIBRARIES}
  ${QWT_LIBRARIES}
  ${QEXT_LIBRARIES}
)



