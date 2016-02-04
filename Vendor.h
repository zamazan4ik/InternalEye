#ifndef VENDOR_H
#define VENDOR_H

#include <QString>

class Vendor
{
private:
    QString id, name, url;
public:
    Vendor(const QString& id, const QString& name, const QString& url);

    //Getters
    QString getName() const;
    QString getUrl() const;
};


#endif // VENDOR_H
