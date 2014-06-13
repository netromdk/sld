#ifndef SLD_VERSION_H
#define SLD_VERSION_H

#include <QString>
#include <QStringList>

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define BUILD_VERSION 0

#define BUILD_DATE "June 13, 2014"

#define MAJOR_FACTOR 1000000
#define MINOR_FACTOR 1000

static inline QString versionString(int major, int minor, int build,
                                    bool showDate = false) {
  return QString::number(major) + "." + QString::number(minor) + "." +
    QString::number(build) + (showDate ? " [" + QString(BUILD_DATE) + "]" : "");
}

static inline QString versionString(bool showDate = false) {
  return versionString(MAJOR_VERSION, MINOR_VERSION, BUILD_VERSION, showDate);
}

#endif // SLD_VERSION_H
