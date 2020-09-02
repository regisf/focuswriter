#include "sound_theme.h"

#include <QFile>
#include <QDir>
#include <QSoundEffect>
#include <QApplication>
#include <QDebug>


static const QString DefaultKeyName{"keyany.wav"};
static const QString ReturnKeyName{"keyenter.wav"};
static const QString ShiftKeyName{"shift_key.wav"};
static const QString BackKeyName{"back_key.wav"};
static const QString TabKeyName{"tab_key.wav"};
static const QString SpaceKeyName{"space_key.wav"};
static const QString DeadKeyName{"dead_key.wav"};

SoundTheme::SoundTheme(QObject *parent)
    : QObject(parent)
{}

void SoundTheme::loadFromDirectory(const QDir &themeDir)
{
    m_is_valid = false;

    auto defaultKeyPath = themeDir.absoluteFilePath(DefaultKeyName);
    m_default_sound = loadFromFile(defaultKeyPath);

    auto returnKeyPath = themeDir.absoluteFilePath(ReturnKeyName);
    m_return_sound = loadFromFile(returnKeyPath);

    auto shiftKeyPath = themeDir.absoluteFilePath(ShiftKeyName);
    m_shift_sound = loadFromFile(shiftKeyPath);

    auto backKeyPath = themeDir.absoluteFilePath(BackKeyName);
    m_back_sound = loadFromFile(backKeyPath);

    auto tabKeyPath = themeDir.absoluteFilePath(TabKeyName);
    m_tab_sound = loadFromFile(tabKeyPath);

    auto spaceKeyPath = themeDir.absoluteFilePath(SpaceKeyName);
    m_space_sound = loadFromFile(spaceKeyPath);

    auto deadKeyPath = themeDir.absoluteFilePath(DeadKeyName);
    m_dead_sound = loadFromFile(deadKeyPath);

    m_is_valid = true;
}

bool SoundTheme::isValid() const
{
    return m_is_valid;
}

QSoundEffect* SoundTheme::loadFromFile(const QString& path)
{
    QSoundEffect* sound{nullptr};

    QFile soundFile{path};
    if (soundFile.exists()) {
        sound = new QSoundEffect(this);
        sound->setSource(QUrl::fromLocalFile(path));

        // Wait sound loaded
        while (sound->status() == QSoundEffect::Loading) {
            QApplication::processEvents();
        }
    } else {
        qDebug() << "Sound " << path << " wasn't found";
    }

    return sound;
}

void SoundTheme::playSound(Qt::Key key) {
    if (m_current_sound && m_current_sound->isPlaying()) {
//        m_current_sound->stop();
    }

    m_current_sound = nullptr;

    switch (key)  {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        m_current_sound = m_return_sound;
        break;

    case Qt::Key_Shift:
        m_current_sound = m_shift_sound;
        break;

    case Qt::Key_Tab:
        m_current_sound = m_tab_sound;
        break;

    case Qt::Key_Space:
        m_current_sound = m_space_sound;
        break;

    case Qt::Key_Dead_Circumflex:
    case Qt::Key_AsciiTilde:
    case Qt::Key_Dead_Diaeresis:
        m_current_sound = m_dead_sound;
        break;

    default:
        if (key > Qt::Key_Any && key < Qt::Key_Z) {
            m_current_sound = m_default_sound;
        }
    }

    if (m_current_sound) {
        m_current_sound->play();
    }
}
