#include "CookieJar.hpp"
#include <QNetworkCookie>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE_LENGTH 4096

bool CookieJar::serialize(const QString& path) {
    FILE* f = fopen(path.toUtf8(), "w");
    if(f == NULL) {
        perror("fopen");
        return false;
    }

    bool success = true;
    QList<QNetworkCookie> cookies = allCookies();

    for(QList<QNetworkCookie>::const_iterator itr = cookies.begin(); itr != cookies.end(); itr++) {
        int ret = fprintf(f, "%s\n", itr->toRawForm().constData());

        if(ret < 0) {
            perror("fprintf");
            success = false;
        }
    }

    fclose(f);
    return success;
}

bool CookieJar::deserialize(const QString& path) {
    FILE* f = fopen(path.toUtf8(), "r");
    if(f == NULL) {
        return true; // cookie jar file didn't exist - do nothing
    }

    QList<QNetworkCookie> cookies;
    char line[MAX_LINE_LENGTH + 1];

    while(fgets(line, MAX_LINE_LENGTH, f) != NULL) {
        QList<QNetworkCookie> tmp = QNetworkCookie::parseCookies(line);

        if(tmp.size() == 0) {
            continue;
        }

        if(tmp.size() > 1) {
            fprintf(stderr, "warning: cookie jar contains multiple cookies on a single line. We are only taking the first.\n");
            fprintf(stderr, "%s\n",  line);
        }

        cookies.push_back(tmp.first());
    }

    if(errno != 0) {
        perror("fgets");
    }

    setAllCookies(cookies);
    fclose(f);

    return true;
}
