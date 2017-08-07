"Alright for qt to work you need a few things"

sudo apt-install qt5-default qmake-qt5 qtmultimedia5-dev
2. MOST IMPORTANT PART (IT WON'T COMPILE IF YOU DO NOT DO THIS!)
Type these commands onto command line

export QT_SELECT=5 

then check to see if qmake is using right qt version with this
qt should have version 5 here
qmake --version

then:

qmake -project

you will then have a .pro file, vim into it and at the bottom, add

QT += widgets

3. after this, do qmake and make to compile successfully.
