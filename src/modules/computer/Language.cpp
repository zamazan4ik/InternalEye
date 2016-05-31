/***************************************************************************
 *   Copyright (C) 2016 by Zaitsev Alexander                               *
 *   zamazan4ik@tut.by	                                                   *
 *                                                                         *
 *   This file is part of InternalEye.                                     *
 *                                                                         *
 *   InternalEye is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   InternalEye is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with InternalEye.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
 
 
#include "Computer.h"
#include "Util.h"
#include <QTextStream>

Computer::Languages::Languages()
{
    update();
}

void Computer::Languages::update()
{
    languages = _getLanguages();
}

QVector<Computer::Languages::Language> Computer::Languages::_getLanguages()
{
    QByteArray out = getOutputConsole("locale -va");
    QTextStream stream(&out);
    QString line;
    QVector<Language> languages;
    while(!stream.atEnd())
    {
        QString code, name, source, address, email, language, territory, codeset, revision, date;
        code = name = source = address = email = language =
        territory = codeset = revision = date = "Unknown";

        line = stream.readLine().trimmed();
        while(!stream.atEnd() && !line.isEmpty())
        {
            if(line.indexOf("locale:") != -1)   code = line.split(' ', QString::SkipEmptyParts)[1].trimmed();
            else if(line.indexOf('|') != -1)
            {
                QString key = line.split('|')[0].trimmed(),
                        value = line.split('|')[1].trimmed();
                if(key == "title")          name        = value;
                else if(key == "source")    source      = value;
                else if(key == "email")     email       = value;
                else if(key == "language")  language    = value;
                else if(key == "territory") territory   = value;
                else if(key == "revision")  revision    = value;
                else if(key == "date")      date        = value;
                else if(key == "codeset")   codeset     = value;
                else if(key == "address")   address     = value;
            }
            line = stream.readLine().trimmed();
        }
        languages.push_back({code, name, source, address, email, language, territory,
                                     codeset, revision, date});
    }
    return languages;
}


QVector<Computer::Languages::Language> Computer::Languages::getLanguages()
{
    return languages;
}
