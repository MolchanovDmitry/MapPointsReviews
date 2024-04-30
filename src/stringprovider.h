#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <QObject>
#include <QtGui/QGuiApplication>

enum AppString {
    PointSentNotification,
    AppName,
};

class StringProvider : public QObject {
    Q_OBJECT
  public:
    explicit StringProvider(QGuiApplication *app, QObject *parent = nullptr);

    QString provide(AppString str);

  private:
    QHash<AppString, QString> strHash;
};

#endif // STRINGPROVIDER_H
