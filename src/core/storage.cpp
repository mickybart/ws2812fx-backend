#include "core.h"
#include "settings.h"
#include "EEPROM.h"

constexpr ulong WRITE_SETTINGS_EVERY_MS = 120000;

/*
 * Prepare the storage to support read/write operation of settings.
 */
void Core::storage_setup()
{
    EEPROM.begin(sizeof(settings_t));
}

/*
 * Read settings from storage.
 *
 * If an invalid value is present, returns default settings.
 */
settings_t Core::read_settings()
{
    settings_t settings{};
    EEPROM.get(0, settings);

    if (settings.mime == MIME_V1)
    {
        return settings;
    }

    // settings is corrupted; send a default one.
    return {};
}

/*
 * Write settings in storage
 *
 * This operation is only performed when a timeout is reached.
 * The timeout solution permit to avoid to write on the storage at every change.
 * Nothing is written on storage if the data is the same between memory and storage (a buffered memory is used).
 */
void Core::write_settings_when_dirty(ulong now)
{
    if (!can_write_settings(now))
        return;

    EEPROM.put(0, settings);
    EEPROM.commit();

    unset_dirty_settings_flag();
}

/*
 * Settings has been changed and must be flagged as dirty to be written on the storage.
 */
void Core::set_dirty_settings_flag()
{
    if (_dirty_settings)
        return;

    _dirty_settings_timestamp = millis();
    _dirty_settings = true;
}

/*
 * Settings has been stored and the flag must be removed.
 */
void Core::unset_dirty_settings_flag()
{
    _dirty_settings = false;
    _dirty_settings_timestamp = 0;
}

bool Core::can_write_settings(ulong now)
{
    return _dirty_settings && (now - _dirty_settings_timestamp > WRITE_SETTINGS_EVERY_MS);
}