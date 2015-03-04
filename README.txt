Short readme:
Install QT SDK
Install QT Creator (as a standalone, not the package)
Install MinGW (if not included in SDK)

Checkout the GIT repo

Open Hofstadter.pro in QT and click on Projects on the left
Update the build directory to <current_folder>/builds
Update the Environments (Build & Run) so QTDIR points to the directory you installed QT in (eg: c:\Qt\4.8.2)


Board: https://trello.com/board/hofstadter
Git: https://bitbucket.org/mmargel/hofstadter


Testing:
Go to test folder:
qmake -project "CONFIG += QTESTLIB"
qmake
make
<run test.exe>