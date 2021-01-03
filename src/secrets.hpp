#ifndef SECRETS_HPP
#define SECRETS_HPP

#include "match_table.hpp"
#include "random.hpp"

auto fixed_secret(int secret) {
    return [secret](int guess) -> match_value {
        return match_table::instance().get_match(guess, secret);
    };
}

auto random_secret() {
    return fixed_secret(random::range(0, match_table::MAX_GUESS - 1));
}

#endif
