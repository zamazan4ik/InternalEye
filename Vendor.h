#ifndef VENDOR_H
#define VENDOR_H

#include <QString>

class Vendor
{
private:
    QString name, url;
public:
    Vendor(const QString& name, const QString& url);

    //Getters
    QString getName() const;
    QString getUrl() const;
};


#endif // VENDOR_H
