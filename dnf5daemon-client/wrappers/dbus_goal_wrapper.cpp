/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "dbus_goal_wrapper.hpp"

#include <libdnf/transaction/transaction_item_type.hpp>

namespace dnfdaemon::client {

DbusGoalWrapper::DbusGoalWrapper(std::vector<dnfdaemon::DbusTransactionItem> transaction) {
    for (auto & ti : transaction) {
        auto object_type = libdnf::transaction::transaction_item_type_from_string(std::get<0>(ti));
        if (object_type == libdnf::transaction::TransactionItemType::PACKAGE) {
            transaction_packages.push_back(DbusTransactionPackageWrapper(ti));
        } else if (object_type == libdnf::transaction::TransactionItemType::GROUP) {
            transaction_groups.push_back(DbusTransactionGroupWrapper(ti));
        }
    }
}

}  // namespace dnfdaemon::client
