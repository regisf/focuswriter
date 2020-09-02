#ifndef SOUNDTHEME_H
#define SOUNDTHEME_H

#include <QObject>

class QDir;
class QSoundEffect;


class SoundTheme : public QObject
{
    Q_OBJECT

public:
    explicit SoundTheme(QObject* parent = nullptr);

    /*
     * Load all from
     */
    void loadFromDirectory(const QDir& themeDir);

    /*
     * Play the sound from the key. If there's no sound, play nothing.
     * If the key is not known, play nothing
     */
    void playSound(Qt::Key key);

    /*
     * Check if the Sound Theme loads correctly the sounds
     */
    bool isValid() const;

private:
    QSoundEffect* loadFromFile(const QString& path);


private:
    bool m_is_valid{false};
    QSoundEffect* m_default_sound{nullptr};
    QSoundEffect* m_return_sound{nullptr};
    QSoundEffect* m_shift_sound{nullptr};
    QSoundEffect* m_back_sound{nullptr};
    QSoundEffect* m_tab_sound{nullptr};
    QSoundEffect* m_space_sound{nullptr};
    QSoundEffect* m_dead_sound{nullptr};
    QSoundEffect* m_current_sound{nullptr};
};

#endif // SOUNDTHEME_H
