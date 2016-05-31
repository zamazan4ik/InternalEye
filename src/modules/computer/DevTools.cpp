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
#include <QDebug>

#define CD Computer::DevTools
#define CDP CD::Program

CDP::Program(const QString& name, const QString& command, const QRegExp& regex) :
                       _name(name), _command(command), _regex(regex)
{
}

QString CDP::name() const
{
    return _name;
}

QString CDP::command() const
{
    return _command;
}

QRegExp CDP::regex() const
{
    return _regex;
}

const QVector<CD::Program> CD::Compilers = {
    {"C (GCC)",         "gcc -v",           QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"C (Clang)",       "clang -v",         QRegExp("(\\d+\\.\\d+)")},
    {"D (dmd)",         "dmd --help",       QRegExp("(\\d+\\.\\d+)")},
    {"Java",            "javac -version",   QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"CSharp (Mono, old)", "mcs --version", QRegExp("(\\d+\\.\\d+\\.\\d+\\.\\d+)")},
    {"CSharp (Mono)",   "gmcs --version",   QRegExp("(\\d+\\.\\d+\\.\\d+\\.\\d+)")},
    {"Vala",            "valac --version",  QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"Haskell (GHC)",   "ghc -v",           QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"FreePascal",      "fpc -iV",          QRegExp("(\\d+\\.\\d+\\.?\\d*)")}
};

const QVector<CD::Program> CD::Tools = {
    {"make",       "make --version",     QRegExp("(\\d+\\.\\d+)")},
    {"GDB",        "gdb --version",      QRegExp("(\\d+\\.\\S+)")},
    {"strace",     "strace -V",          QRegExp("(\\d+\\.\\d+\\.?\\d*)")},
    {"valgrind",   "valgrind --version", QRegExp("(\\d+\\.\\d+\\.\\S+)")},
    {"QMake",      "qmake --version",    QRegExp("(\\d+\\.\\S+)")}
};

const QVector<CD::Program> CD::ScriptLang = {
    {"Python 2","python --version",     QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"Python 3","python3 --version",    QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"Perl",    "perl --version",       QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"PHP",     "php --version",        QRegExp("(\\d+\\.\\d+\\.\\S+)")},
    {"Ruby",    "ruby --version",       QRegExp("(\\d+\\.\\d+\\.\\d+)")},
    {"Bash",    "bash --version",       QRegExp("(\\d+\\.\\d+\\.\\S+)")}
};

CD::DevTools()
{
    update();
}

void CD::update()
{
    compilers   = _getVersion(Compilers);
    tools       = _getVersion(Tools);
    scripts     = _getVersion(ScriptLang);
}

CD::PairsStr CD::_getVersion(const QVector<Program>& var)
{
    PairsStr ans;
    for(const auto& x : var)
    {
        QString version = "Unknown";
        QRegExp regex = x.regex();
        QString out = getOutputConsole(x.command());
        if (regex.indexIn(out, 0) != -1)
        {
            version = regex.cap();
        }
        ans.push_back({x.name(), version});
    }
    return ans;
}


