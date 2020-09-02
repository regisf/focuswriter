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

#include "sound_manager.h"

#include <QDir>
#include <QSoundEffect>
#include <iostream>

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
{
    m_sound_theme = new SoundTheme(this);
}

void SoundManager::setPath(const QString &path)
{
    m_path = path;
}

SoundManager* SoundManager::instance()
{
    static SoundManager* soundManager{nullptr};

    if (!soundManager) {
        soundManager = new SoundManager();
    }

    return soundManager;
}

void SoundManager::loadTheme(const QString &path)
{
    QDir dir{m_path};

    if (!path.isEmpty()) {
        dir.setPath(path);
    }

    if (dir.exists())
    {
        m_sound_theme->loadFromDirectory(dir);
        m_is_valid = m_sound_theme->isValid();
    }
}

bool SoundManager::isValid() const
{
    return m_is_valid;
}

void SoundManager::setActive(const bool active)
{
    m_is_active = active;
}

void SoundManager::playSound(Qt::Key key)
{
    if (!m_is_active) {
        return;
    }

    m_sound_theme->playSound(key);
}
