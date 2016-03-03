#include "Computer.h"
#include "Util.h"
#include <QDebug>

#define CD Computer::DevTools

CD::Programs::Programs(const QString& name, const QString& command, const QRegExp& regex) :
                       _name(name), _command(command), _regex(regex)
{
}

const QVector<CD::Programs> CD::Compilers = {
    Programs("C (GCC)", "gcc -v", QRegExp("\\d+\\.\\d+\\.\\d+")),
    Programs("C (Clang)", "clang -v", QRegExp("\\d+\\.\\d+")),
    Programs("D (dmd)", "dmd --help", QRegExp("\\d+\\.\\d+")),
    Programs("Java", "javac -version", QRegExp("\\d+\\.\\d+\\.\\d+")),
    Programs("CSharp (Mono, old)", "mcs --version", QRegExp("\\d+\\.\\d+\\.\\d+\\.\\d+")),
    Programs("CSharp (Mono)", "gmcs --version", QRegExp("\\d+\\.\\d+\\.\\d+\\.\\d+")),
    Programs("Vala", "valac --version", QRegExp("\\d+\\.\\d+\\.\\d+")),
    Programs("Haskell (GHC)", "ghc -v", QRegExp("\\d+\\.\\d+\\.\\d+")),
    Programs("FreePascal", "fpc -iV", QRegExp("\\d+\\.\\d+\\.?\\d*"))
};

Computer::DevTools::DevTools()
{
    _update();
}


