#include "ini.h"

#include <cassert>
#include <optional>
#include <utility>

using namespace std;

namespace ini {

Section& Document::AddSection(std::string name) {
    assert(sections_.count(name) == 0);
    return sections_[name];
}

const Section& Document::GetSection(const std::string& name) const {
    static const Section dummy;
    if (sections_.count(name) == 0) {
        return dummy;
    }

    return sections_.at(name);
}

std::size_t Document::GetSectionCount() const {
    return sections_.size();
}

Document Load(istream& input) {
    Document res;

    string line;

    Section cur_section;
    optional<string> section_name;

    auto close_section = [&]() {
        if (!section_name) {
            return;
        }

        res.AddSection(move(*section_name)) = exchange(cur_section, {});
        section_name = nullopt;
    };

    while (getline(input, line)) {
        auto first_char = line.find_first_not_of(" "s);
        if (first_char == line.npos) {
            continue;
        }

        if (line[first_char] == '[') {
            auto sec_close = line.find(']', first_char);
            if (sec_close != line.npos) {
                close_section();
                section_name = line.substr(first_char + 1, sec_close - first_char - 1);
                continue;
            }
        }

        const auto eq_pos = line.find('=', first_char);
        if (eq_pos == line.npos) {
            continue;
        }

        const auto name_end = line.find_last_not_of(" ", eq_pos - 1);
        const auto val_start = line.find_first_not_of(" ", eq_pos + 1);
        const auto val_end = line.find_last_not_of(" ");

        if (name_end == line.npos || val_start == line.npos || val_end == line.npos || name_end < first_char
            || val_end < val_start) {
            continue;
        }

        string name = line.substr(first_char, name_end - first_char + 1);
        string val = line.substr(val_start, val_end - val_start + 1);

        cur_section[name] = val;
    }

    close_section();

    return res;
}

}  // namespace ini