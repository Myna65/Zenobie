//////////////////////////////////////////////////////////////////////
//Zenobie 2.4.0
//Copyright (C) 2011-2014 Meynaert Nathan
//
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 3 of the License.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator,translator2;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    translator2.load(QString("Zenobie_") + locale);
    app.installTranslator(&translator2);
    Dialog w;
    w.show();
    return app.exec();
}
