/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef LIBDNF5_REPO_REPO_PGP_HPP
#define LIBDNF5_REPO_REPO_PGP_HPP

#include "libdnf5/base/base_weak.hpp"
#include "libdnf5/common/exception.hpp"
#include "libdnf5/repo/config_repo.hpp"
#include "libdnf5/repo/repo_callbacks.hpp"

#include <librepo/librepo.h>

#include <filesystem>
#include <string>
#include <vector>


namespace libdnf5::repo {

class Key {
public:
    Key(const LrGpgKey * key, const LrGpgSubkey * subkey);

    const std::string & get_id() const noexcept { return id; }
    const std::vector<std::string> & get_user_ids() const noexcept { return user_ids; }
    const std::string & get_fingerprint() const noexcept { return fingerprint; }
    long int get_timestamp() const noexcept { return timestamp; }
    const std::string & get_raw_key() const noexcept { return raw_key; }


private:
    std::string id;
    std::string fingerprint;
    std::vector<std::string> user_ids;
    long int timestamp;
    std::string raw_key;
};

/// Wraps pgp in a higher-level interface.
/// @exception RepoPgpError (public) Thrown on any pgp-related error.
class RepoPgp {
public:
    RepoPgp(const BaseWeakPtr & base, const ConfigRepo & config);

    void set_callbacks(RepoCallbacks * callbacks) noexcept { this->callbacks = callbacks; }

    std::filesystem::path get_keyring_dir() const { return std::filesystem::path(config.get_cachedir()) / "pubring"; }

    void import_key(int fd, const std::string & url);
    static std::vector<Key> rawkey2infos(int fd);

private:
    std::vector<std::string> load_keys_ids_from_keyring();
    BaseWeakPtr base;
    const ConfigRepo & config;
    RepoCallbacks * callbacks = nullptr;
};

}  // namespace libdnf5::repo

#endif  // LIBDNF5_REPO_REPO_PGP_HPP
