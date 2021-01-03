#ifndef SECRETS_HPP
#define SECRETS_HPP

#include "match_table.hpp"
#include "random.hpp"

auto fixed_secret(int secret) {
    return [secret](int guess) -> match_value {
        return match_table::get(guess, secret);
    };
}

auto random_secret() {
    return fixed_secret(random::index(match_table::MAX_GUESS));
}

#endif
