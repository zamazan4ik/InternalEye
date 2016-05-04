#ifndef COMPUTER_H
#define COMPUTER_H

#include <QSize>
#include <QString>
#include <QVector>
#include <QPair>
#include <QHash>
#include <QVariant>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QRegExp>
#include <functional>
#include "DateDifference.h"


class Computer
{
private:
    class OperatingSystem
    {
        //TODO:Add username
    private:
        static const QString DB_PREFIX;
        using DistroAndCode = QPair<QString, QString>;
        static const QVector<DistroAndCode> distroDB;

        QString kernel, libc, distrocode, distro, hostname, language, homedir, kernelVersion,
                languages, desktop, username, boots;
        QString _getUsername();
        QString _getLibcVersion();
        QString _getLanguage();
        QString _getLanguages();
        QString _getDesktopEnv();
        QString _getDistro();

        void _update();
    public:
        OperatingSystem();

        QString getKernel() const;
        QString getKernelVersion() const;
        QString getDistro() const;
        QString getDistroCode() const;
        QString getHomeDir() const;
        QString getLanguage() const;
        QString getLanguages() const;
        QString getDesktop() const;
        QString getUsername() const;
        QString getBoots() const;
        QString getLibc() const;

    };

    class DisplayInfo
    {
        //TODO: Add checking: count of monotors, resolutions
    private:
        QString oglVendor, oglRenderer, oglVersion, displayName, vendor, version,
                monitors;
        QStringList extensions;
        bool dri;
        QSize size;

        void _getGLXinfo();
        void _getX11info();
        void _update();

    public:
        DisplayInfo();

        QSize getSize() const;
        bool DRI() const;
        void update();
    };

    class UptimeInfo
    {
        //TODO : Rewrite it with std::chrono or QTime
    private:
        int compMonths, compWeeks, compDays, compHours, compMinutes, compSeconds,
            cpuMonths, cpuWeeks, cpuDays, cpuHours, cpuMinutes, cpuSeconds;
        void _update();
    public:

        int getCompMonths() const;
        int getCompWeeks() const;
        int getCompDays() const;
        int getCompHours() const;
        int getCompMinutes() const;
        int getCompSeconds() const;

        int getCpuMonths() const;
        int getCpuWeeks() const;
        int getCpuDays() const;
        int getCpuHours() const;
        int getCpuMinutes() const;
        int getCpuSeconds() const;

        UptimeInfo();
    };

    class LoadInfo
    {
    private:
        double load1, load5, load15;
        int workEntities, allEntities, mostRunPID;
        void _update();
    public:
        LoadInfo();

        //Getters
        double getLoad1() const;
        double getLoad5() const;
        double getLoad15() const;

        int getWorkEnt() const;
        int getAllEnt() const;
        int getMostRunPID() const;

    };

    class Language
    {
    private:
        QString _code, _name, _source, _address, _email, _language, _territory, _codeset, _revision, _date;
    public:
        Language();
        Language(const QString& code, const QString& name, const QString& source, const QString& address,
                 const QString& email, const QString& language, const QString& territory, const QString& codeset,
                 const QString& revision, const QString& date);

        static QVector<Language> getLanguages();
    };

    class Boot
    {
    private:
        QString _kernelVersion;
        QDateTime   _dateStart, _dateEnd;
        DateDifference _duringTime;
    public:
        Boot();
        Boot(const QString& kernelVersion, const QDateTime& dateStart,
             const QDateTime& dateEnd);

        QString getKernelVersion() const;
        QDateTime getDateStart() const;
        QDateTime getDateEnd() const;
        DateDifference getDuringTime() const;

        static QVector<Boot> getBoots();
    };


    class FileSystem
    {
    private:
        QString _filesystem, _device, _mountPoint;
        QStringList _mountFlags;
        double _size, _used, _available;
    public:
        FileSystem();
        FileSystem(const QString& filesystem, const QString& device, const QString& mountPoint,
              const QStringList& mountFlags, const double size, const double used, const double available);

        static QVector<FileSystem> getFileSystems();
    };

    class Module
    {
    private:
        QString _name, _description, _license, _versionMagic, _path;
        QStringList _usedBy, _author, _depends;
        double _size;
    public:
        Module();
        Module(const QString& name, const QStringList& author, const QString& description, const QString& license,
               const QStringList& depends, const QString& versionMagic, const QString& path, const QStringList& usedBy,
               const double size);

        static QVector<Module> getModules();
    };

    class User
    {
    private:
        QString _name, _firstName, _secondName, _address, _workPhone, _homePhone,
                _workDir, _shell;
        int _id, _groupID;
    public:
        User();
        User(const QString& name, const QString& firstName, const QString& secondName,
             const QString& address, const QString& workPhone, const QString& homePhone,
             const QString& workDir, const QString& shell, const int id, const int groupID);

        static QVector<User> getUsers();
    };

    class Group
    {
    private:
        QString _name;
        int _id;
        QStringList _members;
    public:
        Group();
        Group(const QString& name, const int id, const QStringList& members);

        static QVector<Group> getGroups();
    };

    class DevTools
    {
    private:
        class Program
        {
        private:
            QString _name, _command;
            QRegExp _regex;
        public:
            Program(const QString& name, const QString& command, const QRegExp& regex);
            QString name()      const;
            QString command()   const;
            QRegExp regex()     const;

        };
        static const QVector<Program> Compilers, ScriptLang, Tools;

        using PairsStr = QVector<QPair<QString, QString>>;
        PairsStr compilers, tools, scripts;

        PairsStr _getVersion(const QVector<Program>& var);
    public:
        DevTools();
        void update();

        PairsStr getCompilers()  const;
        PairsStr getTools()      const;
        PairsStr getScripts()    const;
    };


    using PairOfStrings = QPair<QString, QString>;

    //UptimeInfo info;
    //OperatingSystem os;
    //LoadInfo load;
    //DisplayInfo display;
    //DevTools development;

    QVector<PairOfStrings> env;
    QVector<Boot> boots;
    QVector<User> users;
    QVector<Group> groups;
    QVector<Module> modules;
    QVector<FileSystem> filesystems;
    QVector<Language> languages;

    void _getEnvVariables();
public:
    Computer();
};

#endif // COMPUTER_H