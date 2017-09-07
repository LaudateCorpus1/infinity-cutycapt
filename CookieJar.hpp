#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>
#include <QString>

class CookieJar : public QNetworkCookieJar {
    public:
        bool serialize(const QString& path);
        bool deserialize(const QString& path);
};

#endif
