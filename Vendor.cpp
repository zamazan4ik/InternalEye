#include <Vendor.h>


Vendor::Vendor(const QString &id_, const QString &name_, const QString &url_)
                : name(name_), id(id_), url(url_)
{
}


QString Vendor::getName() const
{
    return name;
}

QString Vendor::getUrl() const
{
    return url;
}
