# Add more folders to ship with the application, here
folder_01.source = qml/Hofstadter
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE52545FA

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    Sequence.cpp \
    Calculator.cpp \
    FilterOptions.cpp \
    SummaryOptions.cpp \
    ConfigPage.cpp \
    SelectPage.cpp \
    ResultPage.cpp \
    Kernel.cpp \
    Main.cpp \
    ConfigWizard.cpp \
    OptionPage.cpp

HEADERS  += \
    Sequence.h \
    SummaryOptions.h \
    FilterOptions.h \
    Calculator.h \
    ClassDefs.h \
    ConfigPage.h \
    SelectPage.h \
    ResultPage.h \
    Errors.h \
    ConfigWizard.h \
    OptionPage.h


# Please do not modify the following two lines. Required for deployment.
# include(qmlapplicationviewer/qmlapplicationviewer.pri)
# qtcAddDeployment()
