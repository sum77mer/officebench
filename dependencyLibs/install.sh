# commands in case link error

# place lib in dir first
export QT_QPA_PLATFORM=./platforms

# more qt-plugin information
export QT_DEBUG_PLUGIN=1

ln -s libicudata.so.56.1 libicudata.so.56
ln -s libicudata.so.56 libicudata.so

ln -s libicui18n.so.56.1 libicui18n.so.56
ln -s libicui18n.so.56 libicui18n.so

ln -s libicutu.so.56.1 libicutu.so.56
ln -s libicutu.so.56 libicutu.so

ln -s libicuuc.so.56.1 libicuuc.so.56
ln -s libicuuc.so.56 libicuuc.so

ln -s libQt5Core.so.5.15.2 libQt5Core.so.5.15
ln -s libQt5Core.so.5.15 libQt5Core.so.5

ln -s libQt5Gui.so.5.15.2 libQt5Gui.so.5.15
ln -s libQt5Gui.so.5.15 libQt5Gui.so.5

ln -s libQt5Widgets.so.5.15.2 libQt5Widgets.so.5.15
ln -s libQt5Widgets.so.5.15 libQt5Widgets.so.5

ln -s libQt5DBus.so.5.15.2 libQt5DBus.so.5.15
ln -s libQt5DBus.so.5.15 libQt5DBus.so.5

ln -s libQt5EglFsKmsSupport.so.5.15.2 libQt5EglFsKmsSupport.so.5.15
ln -s libQt5EglFsKmsSupport.so.5.15 libQt5EglFsKmsSupport.so.5

ln -s libQt5XcbQpa.so.5.15.2 libQt5XcbQpa.so.5.15
ln -s libQt5XcbQpa.so.5.15 libQt5XcbQpa.so.5  

ln -s libxcb-xinerama.so.0.0.0 libxcb-xinerama.so.0

# place officebenchmark in this dir, then execute
# LD_LIBRARY_PATH=. ./officebenchmark
