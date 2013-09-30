#ifndef VERSIONING_H
#define VERSIONING_H

#include <string> //std::string

using std::string;

namespace Versioning
{
    /**
     * \brief Gets an old file content and upgrades it to new version.
     *
     * \param version   Current world data version
     * \param content   String containing old world data structure.
     * \return          World data upgraded.
     */
    string upgrade(int version, string content);

    const int VERSION = 4;

    // Versioning functions
    typedef string (*UpgradeFunc) (string);

    /// Use relative coordinates for areas instead of absolute
    string upgradeFrom1To2(string content);

    /// Add background music "bgm" attribute to Room nodes
    string upgradeFrom2To3(string content);

    /// Rename attribute "id" to "next" in dialogs to improve readability
    string upgradeFrom3To4(string content);

    const UpgradeFunc upgrade_funcs[] = {upgradeFrom1To2,
                                         upgradeFrom2To3,
                                         upgradeFrom3To4};
}

#endif // VERSIONING_H
