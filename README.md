# qt-epub
qt based epub reader

epub format is basically a .zip file with .xml and .jpg files

.zip fil decompression is achieved with libarchive and an included qt wrapper -> QZip
.xml is processed with qt xml package

uses QTextBrowser derived class with loadResource override to load image and css files.
