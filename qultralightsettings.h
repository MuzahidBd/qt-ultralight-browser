/*
    Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
    Copyright (C) 2008 Holger Hans Peter Freyther
    Copyright (C) 2009 Girish Ramakrishnan <girish@forwardbias.in>
    Copyright (C) 2021 Jerzy Głowacki
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef QULTRALIGHTSETTINGS_H
#define QULTRALIGHTSETTINGS_H

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qicon.h>
#include <QtCore/qshareddata.h>
#include <QUrl>

namespace WebCore {
class Page;
}

class QUltralightPage;
class QWebPluginDatabase;
QT_BEGIN_NAMESPACE
class QUrl;
QT_END_NAMESPACE

void qt_networkAccessAllowed(bool isAllowed);

class QUltralightSettings {
public:
    enum FontFamily {
        StandardFont,
        FixedFont,
        SerifFont,
        SansSerifFont,
        CursiveFont,
        FantasyFont
    };
    enum WebAttribute {
        AutoLoadImages,
        JavascriptEnabled,
        JavaEnabled,
        PluginsEnabled,
        PrivateBrowsingEnabled,
        JavascriptCanOpenWindows,
        JavascriptCanAccessClipboard,
        DeveloperExtrasEnabled,
        LinksIncludedInFocusChain,
        ZoomTextOnly,
        PrintElementBackgrounds,
        OfflineStorageDatabaseEnabled,
        OfflineWebApplicationCacheEnabled,
        LocalStorageEnabled,
#if defined(QT_DEPRECATED) || defined(qdoc)
        LocalStorageDatabaseEnabled = LocalStorageEnabled,
#endif
        LocalContentCanAccessRemoteUrls,
        DnsPrefetchEnabled,
        XSSAuditingEnabled,
        AcceleratedCompositingEnabled,
        SpatialNavigationEnabled,
        LocalContentCanAccessFileUrls,
        TiledBackingStoreEnabled,
        FrameFlatteningEnabled,
        SiteSpecificQuirksEnabled,
        JavascriptCanCloseWindows,
        WebGLEnabled,
        CSSRegionsEnabled,
        HyperlinkAuditingEnabled,
        CSSGridLayoutEnabled,
        ScrollAnimatorEnabled,
        CaretBrowsingEnabled,
        NotificationsEnabled,
        WebAudioEnabled,
        Accelerated2dCanvasEnabled,
        MediaSourceEnabled,
        MediaEnabled,
        WebSecurityEnabled,
        FullScreenSupportEnabled,
        ImagesEnabled,
        AllowRunningInsecureContent,
        ErrorPageEnabled
    };
    enum WebGraphic {
        MissingImageGraphic,
        MissingPluginGraphic,
        DefaultFrameIconGraphic,
        TextAreaSizeGripCornerGraphic,
        DeleteButtonGraphic,
        InputSpeechButtonGraphic,
        SearchCancelButtonGraphic,
        SearchCancelButtonPressedGraphic
    };
    enum FontSize {
        MinimumFontSize,
        MinimumLogicalFontSize,
        DefaultFontSize,
        DefaultFixedFontSize
    };
    enum ThirdPartyCookiePolicy {
        AlwaysAllowThirdPartyCookies,
        AlwaysBlockThirdPartyCookies,
        AllowThirdPartyWithExistingCookies
    };

    static QUltralightSettings *globalSettings();

    void setFontFamily(FontFamily which, const QString &family);
    QString fontFamily(FontFamily which) const;
    void resetFontFamily(FontFamily which);

    void setFontSize(FontSize type, int size);
    int fontSize(FontSize type) const;
    void resetFontSize(FontSize type);

    void setAttribute(WebAttribute attr, bool on);
    bool testAttribute(WebAttribute attr) const;
    void resetAttribute(WebAttribute attr);

    void setUserStyleSheetUrl(const QUrl &location);
    QUrl userStyleSheetUrl() const;

    void setDefaultTextEncoding(const QString &encoding);
    QString defaultTextEncoding() const;

    static void setIconDatabasePath(const QString &location);
    static QString iconDatabasePath();
    static void clearIconDatabase();
    static QIcon iconForUrl(const QUrl &url);

    static void setPluginSearchPaths(const QStringList& paths);
    static QStringList pluginSearchPaths();

    //static QWebPluginDatabase *pluginDatabase();

    static void setWebGraphic(WebGraphic type, const QPixmap &graphic);
    static QPixmap webGraphic(WebGraphic type);

    static void setMaximumPagesInCache(int pages);
    static int maximumPagesInCache();
    static void setObjectCacheCapacities(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity);

    static void setOfflineStoragePath(const QString& path);
    static QString offlineStoragePath();
    static void setOfflineStorageDefaultQuota(qint64 maximumSize);
    static qint64 offlineStorageDefaultQuota();

    static void setOfflineWebApplicationCachePath(const QString& path);
    static QString offlineWebApplicationCachePath();
    static void setOfflineWebApplicationCacheQuota(qint64 maximumSize);
    static qint64 offlineWebApplicationCacheQuota();

    void setLocalStoragePath(const QString& path);
    QString localStoragePath() const;

    static void clearMemoryCaches();

    static void enablePersistentStorage(const QString& path = QString());

    void setThirdPartyCookiePolicy(ThirdPartyCookiePolicy);
    QUltralightSettings::ThirdPartyCookiePolicy thirdPartyCookiePolicy() const;

    void setCSSMediaType(const QString&);
    QString cssMediaType() const;

    //inline QUltralightSettingsPrivate* handle() const { return d; }

private:
    friend class QUltralightPage;
//    friend class QUltralightPageAdapter;
//    friend class QUltralightPagePrivate;
//    friend class QUltralightSettingsPrivate;

    Q_DISABLE_COPY(QUltralightSettings)

    QUltralightSettings();
    QUltralightSettings(WebCore::Page* page);
    ~QUltralightSettings();

    QHash<int, QString> _fontFamilies;
    QHash<int, int> _fontSizes;
    QHash<int, bool> _attributes;
    QUrl _userStyleSheetLocation;
    QString _defaultTextEncoding;
    QString _localStoragePath;
    QString _offlineWebApplicationCachePath;
    QString _offlineDatabasePath;
    QString _mediaType;
    qint64 _offlineStorageDefaultQuota;
    ThirdPartyCookiePolicy _thirdPartyCookiePolicy;

    void apply();
};

#endif // QULTRALIGHTSETTINGS_H
