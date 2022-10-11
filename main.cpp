#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

void myMessageOutput(const QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    FILE *out = stdout;
    QString message;

    switch (type) {
    case QtMsgType::QtSystemMsg:
        message = QString("Critical!!! %1[%2]: %3").arg(context.file).arg(context.line).arg(msg);
        out = stderr;
        QMessageBox::critical(nullptr, QT_TR_NOOP("Критическая ошибка!"), msg);
        break;

    case QtMsgType::QtFatalMsg:
        message = QString("Fatal!!! %1[%2]: %3").arg(context.file).arg(context.line).arg(msg);
        out = stderr;
        QMessageBox::critical(nullptr, QT_TR_NOOP("Критическая ошибка!"), msg);
        break;

    case QtMsgType::QtWarningMsg:
        message = QString("Warning! %1[%2]: %3").arg(context.file).arg(context.line).arg(msg);
        out = stderr;
        QMessageBox::warning(nullptr, QT_TR_NOOP("Ошибка!"), msg);
        break;

    case QtMsgType::QtInfoMsg:
        message = msg;
        QMessageBox::information(nullptr, QT_TR_NOOP("Сообщение"), msg);
        break;

    case QtMsgType::QtDebugMsg:
        message = QString("Debug: %1[%2]: %3").arg(context.file).arg(context.line).arg(msg);
#ifndef QT_DEBUG
        return;
#endif
        break;
    }

    QTextStream(out) << message << Qt::endl;

    if (type == QtFatalMsg || type == QtCriticalMsg)
        abort();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(&myMessageOutput);

    MainWindow w;
    w.show();
    return a.exec();
}
