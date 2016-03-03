#include "Computer.h"
#include "Util.h"
#include <QTextStream>

Computer::Language::Language()
{
}

Computer::Language::Language(const QString& code, const QString& name, const QString& source, const QString& address,
                             const QString& email, const QString& language, const QString& territory, const QString& codeset,
                             const QString& revision, const QString& date) : _code(code), _name(name), _source(source), _address(address),
                             _email(email), _language(language), _territory(territory), _codeset(codeset), _revision(revision),
                             _date(date)
{
}

QVector<Computer::Language> Computer::Language::getLanguages()
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
        languages.push_back(Language(code, name, source, address, email, language, territory,
                                     codeset, revision, date));
    }
    return languages;
}
