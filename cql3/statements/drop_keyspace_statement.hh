/*
 * Copyright (C) 2015-present ScyllaDB
 *
 * Modified by ScyllaDB
 */

/*
 * SPDX-License-Identifier: (AGPL-3.0-or-later and Apache-2.0)
 */

#pragma once

#include "cql3/statements/schema_altering_statement.hh"

namespace cql3 {

class query_processor;

namespace statements {

class drop_keyspace_statement : public schema_altering_statement {
    sstring _keyspace;
    bool _if_exists;
public:
    drop_keyspace_statement(const sstring& keyspace, bool if_exists);

    virtual future<> check_access(query_processor& qp, const service::client_state& state) const override;

    virtual void validate(query_processor&, const service::client_state& state) const override;

    virtual const sstring& keyspace() const override;

    future<std::tuple<::shared_ptr<cql_transport::event::schema_change>, std::vector<mutation>, cql3::cql_warnings_vec>> prepare_schema_mutations(query_processor& qp, service::migration_manager& mm, api::timestamp_type) const override;

    virtual std::unique_ptr<prepared_statement> prepare(data_dictionary::database db, cql_stats& stats) override;
};

}

}
