#include <Vendor.h>


Vendor::Vendor(const QString &name_, const QString &url_)
                : name(name_), url(url_)
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
