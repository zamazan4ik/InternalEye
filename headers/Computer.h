/***************************************************************************
 *   Copyright (C) 2016 by Zaitsev Alexander                               *
 *   zamazan4ik@tut.by	                                                   *
 *                                                                         *
 *   This file is part of InternalEye.                                     *
 *                                                                         *
 *   InternalEye is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   InternalEye is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with InternalEye.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
 
 
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
#include "AbstractModule.h"
#include "DateDifference.h"


class Computer
{
private:
    class OperatingSystem : public AbstractModule
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

        virtual void update();
    };

    class DisplayInfo : public AbstractModule
    {
        //TODO: Add checking: count of monitors, resolutions
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
        virtual void update();
    };

    class UptimeInfo : public AbstractModule
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
        virtual void update();
    };

    class LoadInfo : public AbstractModule
    {
    private:
        double load1, load5, load15;
        int workEntities, allEntities, mostRunPID;
        void _update();
    public:
        LoadInfo();

        double getLoad1() const;
        double getLoad5() const;
        double getLoad15() const;

        int getWorkEnt() const;
        int getAllEnt() const;
        int getMostRunPID() const;

        virtual void update();
    };

    class Languages : public AbstractModule
    {
    private:
        struct Language
        {
            QString _code, _name, _source, _address, _email, _language, _territory, _codeset, _revision, _date;
        };
        QVector<Language> languages;

        QVector<Language> _getLanguages();
    public:
        Languages();

        virtual void update();

        QVector<Language> getLanguages();
    };

    class Boots : public AbstractModule
    {
    private:
        struct Boot
        {
            QString _kernelVersion;
            QDateTime   _dateStart, _dateEnd;
            DateDifference _duringTime;
        };
        QVector<Boot> boots;

        QVector<Boot> _getBoots();
    public:
        Boots();

        virtual void update();

        QVector<Boot> getBoots();
    };


    class FileSystems : public AbstractModule
    {
    private:
        struct FileSystem
        {
            QString _filesystem, _device, _mountPoint;
            QStringList _mountFlags;
            double _size, _used, _available;
        };
        QVector<FileSystem> filesystems;

        QVector<FileSystem> _getFileSystems();
    public:
        virtual void update();

        QVector<FileSystem> getFileSystems();
    };

    class Modules : public AbstractModule
    {
    private:
        struct Module
        {
            QString _name, _description, _license, _versionMagic, _path;
            QStringList _usedBy, _author, _depends;
            double _size;
        };
        QVector<Module> modules;

        QVector<Module> _getModules();
    public:
        Modules();

        virtual void update();

        QVector<Module> getModules();
    };

    class Users : public AbstractModule
    {
    private:
        struct User
        {
            QString _name, _firstName, _secondName, _address, _workPhone, _homePhone,
                _workDir, _shell;
            int _id, _groupID;
        };
        QVector<User> users;

        QVector<User> _getUsers();
    public:
        Users();

        virtual void update();

        QVector<User> getUsers();
    };

    class Groups : public AbstractModule
    {
    private:
        struct Group
        {
            QString name;
            int id;
            QStringList members;
        };
        QVector<Group> groups;

        QVector<Group> _getGroups();
    public:
        Groups();
        virtual void update();

        QVector<Group> getGroups();
    };

    class DevTools : public AbstractModule
    {
    private:
        //TODO : Add info about installed libraries(version) like Boost, Qt, Cuda, etc.
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
        virtual void update();

        PairsStr getCompilers()  const;
        PairsStr getTools()      const;
        PairsStr getScripts()    const;
    };
    class EnvVariables : public AbstractModule
    {
    private:
        struct EnvVariable
        {
            QString name, value;
        };
        QVector<EnvVariable> variables;

        QVector<EnvVariable> _getEnvVariables();
    public:
        EnvVariables();

        virtual void update();

        QVector<EnvVariable> getEnvVariables();
    };

    QVector<AbstractModule*> modules;
public:
    Computer();
    ~Computer();
};

#endif // COMPUTER_H
