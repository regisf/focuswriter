/***********************************************************************
 *
 * Copyright (C) 2010, 2011, 2012, 2018, 2019 Graeme Gott <graeme@gottcode.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "sound_theme.h"

#include <QObject>


class SoundManager : public QObject
{
    Q_OBJECT

    explicit SoundManager(QObject *parent = nullptr);

public:
    static SoundManager* instance();

    void setPath(const QString& path);

    /*
     * Load a theme from a directory or a zip file
     */
    void loadTheme(const QString& path = "");

    /*
     * Check if the sounds for the theme are loaded correctly
     */
    bool isValid() const;


    /*
     * Enable or disable sound on the fly
     */
    void setActive(const bool active);

    /*
     * Play a sound regarding the key
     */
    void playSound(Qt::Key key);

private:
    bool m_is_active{false};
    bool m_is_valid{false};
    SoundTheme* m_sound_theme{nullptr};
    QString m_path;
};

#endif // SOUNDMANAGER_H
