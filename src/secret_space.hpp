#ifndef SECRET_SPACE_HPP
#define SECRET_SPACE_HPP

#include <vector>

class match_value;

class secret_space {
public:
    secret_space();

    auto narrow(int guess, const match_value& match) -> void;
    auto get_narrowed_size(int guess, const match_value& match) const -> int;

    auto size() const -> int {
        return possible_secrets_.size();
    }

    auto begin() const {
        return possible_secrets_.begin();
    }

    auto end() const {
        return possible_secrets_.end();
    }

    auto operator[](int index) const {
        return possible_secrets_[index];
    }

private:
    std::vector<int> possible_secrets_;
};

#endif
