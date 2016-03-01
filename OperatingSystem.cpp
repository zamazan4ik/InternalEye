//QString computerGetOS(void)
//{
//    struct utsname utsbuf;
//    OperatingSystem *os;
//    int i;

//    os = g_new0(OperatingSystem, 1);

//    /* Attempt to get the Distribution name; try using /etc/lsb-release first,
//       then doing the legacy method (checking for /etc/$DISTRO-release files) */
//    if (g_file_test("/etc/lsb-release", G_FILE_TEST_EXISTS))
//    {
//        FILE *release;
//        gchar buffer[128];

//        release = popen("lsb_release -d", "r");
//        if (release)
//        {
//            (void)fgets(buffer, 128, release);
//            pclose(release);

//            os->distro = buffer;
//            os->distro = g_strdup(os->distro + strlen("Description:\t"));
//        }
//    }
//    else if (g_file_test("/etc/arch-release", G_FILE_TEST_EXISTS))
//    {
//        os->distrocode = g_strdup("arch");
//        os->distro = g_strdup("Arch Linux");
//    }
//    else
//    {
//        for (i = 0;; i++)
//        {
//            if (distro_db[i].file == NULL)
//            {
//                os->distrocode = g_strdup("unk");
//                os->distro = g_strdup(_("Unknown distribution"));
//                break;
//            }

//            if (g_file_test(distro_db[i].file, G_FILE_TEST_EXISTS))
//            {
//                FILE *distro_ver;
//                char buf[128];

//                distro_ver = fopen(distro_db[i].file, "r");
//                if (distro_ver) {
//                    (void)fgets(buf, 128, distro_ver);
//                    fclose(distro_ver);
//                }
//                else
//                {
//                    continue;
//                }

//                buf[strlen(buf) - 1] = 0;

//                if (!os->distro)
//                {
//                    /*
//                     * HACK: Some Debian systems doesn't include
//                     * the distribuition name in /etc/debian_release,
//                     * so add them here.
//                     */
//                    if (!strncmp(distro_db[i].codename, "deb", 3) &&
//                            ((buf[0] >= '0' && buf[0] <= '9') || buf[0] != 'D'))
//                    {
//                        os->distro = g_strdup_printf
//                                ("Debian GNU/Linux %s", buf);
//                    }
//                    else
//                    {
//                        os->distro = g_strdup(buf);
//                    }
//                }

//                if (g_str_equal(distro_db[i].codename, "ppy"))
//                {
//                    gchar *tmp;
//                    tmp = g_strdup_printf("Puppy Linux");
//                    g_free(os->distro);
//                    os->distro = tmp;
//                }
//                os->distrocode = g_strdup(distro_db[i].codename);

//                break;
//            }
//        }
//    }

//    os->distro = g_strstrip(os->distro);

//    /* Kernel and hostname info */
//    uname(&utsbuf);
//    os->kernel_version = g_strdup(utsbuf.version);
//    os->kernel = g_strdup_printf("%s %s (%s)", utsbuf.sysname,
//                                 utsbuf.release, utsbuf.machine);
//    os->hostname = g_strdup(utsbuf.nodename);
//    os->language = g_strdup(g_getenv("LC_MESSAGES"));
//    os->homedir = g_strdup(g_get_home_dir());
//    os->username = g_strdup_printf("%s (%s)",
//                                   g_get_user_name(), g_get_real_name());
//    os->libc = get_libc_version();
//    scan_languages(os);
//    detect_desktop_environment(os);

//    return os;
//}

//#include <string.h>
//#include "hardinfo.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include "Util.h"
#include "Computer.h"

const QString Computer::OperatingSystem::DB_PREFIX = "/etc/";

using DistroAndCode = QPair<QString, QString>;

const QVector<DistroAndCode> Computer::OperatingSystem::distroDB =
{
    { Computer::OperatingSystem::DB_PREFIX + "debian_version",	"deb"  },
    { Computer::OperatingSystem::DB_PREFIX + "slackware-version",	"slk"  },
    { Computer::OperatingSystem::DB_PREFIX + "mandrake-release",	"mdk"  },
    { Computer::OperatingSystem::DB_PREFIX + "mandriva-release",     "mdv"  },
    { Computer::OperatingSystem::DB_PREFIX + "fedora-release",       "fdra" },
    { Computer::OperatingSystem::DB_PREFIX + "coas",                 "coas" },
    { Computer::OperatingSystem::DB_PREFIX + "environment.corel",    "corel"},
    { Computer::OperatingSystem::DB_PREFIX + "gentoo-release",	"gnt"  },
    { Computer::OperatingSystem::DB_PREFIX + "conectiva-release",	"cnc"  },
    { Computer::OperatingSystem::DB_PREFIX + "versão-conectiva",	"cnc"  },
    { Computer::OperatingSystem::DB_PREFIX + "turbolinux-release",	"tl"   },
    { Computer::OperatingSystem::DB_PREFIX + "yellowdog-release",	"yd"   },
    { Computer::OperatingSystem::DB_PREFIX + "sabayon-release",      "sbn"  },
    { Computer::OperatingSystem::DB_PREFIX + "arch-release",         "arch" },
    { Computer::OperatingSystem::DB_PREFIX + "enlisy-release",       "enlsy"},
    { Computer::OperatingSystem::DB_PREFIX + "SuSE-release",		"suse" },
    { Computer::OperatingSystem::DB_PREFIX + "sun-release",		"sun"  },
    { Computer::OperatingSystem::DB_PREFIX + "zenwalk-version",	"zen"  },
    { Computer::OperatingSystem::DB_PREFIX + "DISTRO_SPECS",		"ppy"  },
    { Computer::OperatingSystem::DB_PREFIX + "distro-release",	"fl"   },
    { Computer::OperatingSystem::DB_PREFIX + "vine-release",         "vine" },
    { Computer::OperatingSystem::DB_PREFIX + "PartedMagic-version",	"pmag" },
     /*
     * RedHat must be the *last* one to be checked, since
     * some distros (like Mandrake) includes a redhat-relase
     * file too.
     */
    { Computer::OperatingSystem::DB_PREFIX + "redhat-release",	"rh"   },
    { NULL,				NULL   }
};



Computer::OperatingSystem::OperatingSystem()
{
//    QString  distrocode, username, boots;
    struct utsname sysInfo;
    uname(&sysInfo);
    kernelVersion = sysInfo.version;
    kernel = QString(sysInfo.sysname) + " " + QString(sysInfo.release) +
             " (" + QString(sysInfo.machine) + ")";
    hostname = sysInfo.nodename;
    homedir = QDir::homePath();
    username = _getUsername();
    libc = _getLibcVersion();
    language = _getLanguage();
    languages = _getLanguages();
    desktop = _getDesktopEnv();
    distro = _getDistro();

}

QString Computer::OperatingSystem::_getDistro()
{
    const QString FlagDE = "Distro";
    QString arr(getOutputConsole("inxi -S | grep Distro"));
    arr.chop(2);
    int pos = arr.indexOf(FlagDE);
    if(pos == -1)    return "Unknown";
    QString ans = arr.mid(pos + FlagDE.length() + 2);
    return ans;
}

QString Computer::OperatingSystem::_getLibcVersion()
{
    //TODO : Make return only version
    const int LineWithVersion = 0;
    QString result = getOutputConsole("ldd --version");
    return getLineOfString(result, LineWithVersion);
}

QString Computer::OperatingSystem::_getUsername()
{
    const char* p = getenv("USERNAME");
    return p ? p : "Unknown";
}

QString Computer::OperatingSystem::_getLanguage()
{
    const char* p = getenv("LANG");
    return p ? p : "Unknown";
}

QString Computer::OperatingSystem::_getLanguages()
{
    const char* p = getenv("LANGUAGE");
    QStringList list;
    if (p) // LANGUAGE can contain several values divided by ':'
    {
        QString str(p);
        list = str.split(':');
    }
    else if ((p = getenv("LC_ALL")))
    {
        list.push_back(p);
    }
    else if ((p = getenv("LC_MESSAGES")))
    {
        list.push_back(p);
    }
    else if ((p = getenv("LANG")))
    {
        list.push_back(p);
    }
    QString result;
    for(const auto& x : list)
    {
        result += x;
        if(x != " ")
        {
            result += " ";
        }
    }
    return result;
}

QString Computer::OperatingSystem::_getDesktopEnv()
{
    const QString FlagDE = "Desktop";
    QString arr(getOutputConsole("inxi -S | grep Desktop"));
    arr.chop(2);
    int pos = arr.indexOf(FlagDE);
    if(pos == -1)    return "Unknown";
    QString ans = arr.mid(pos + FlagDE.length() + 2);
    return ans;
}

QString Computer::OperatingSystem::getHomeDir() const
{
    return homedir;
}



//QString Computer::OperatingSystem::get
