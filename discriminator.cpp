#include <vector>
#include <string>
#include <unordered_map>
#include <clocale>
#include <fstream>

std::vector<std::vector<std::wstring>> Discriminator(
        const std::vector<std::wstring>& v) {
    std::vector<std::vector<std::wstring>> result;
    std::vector<std::unordered_map<wchar_t, size_t>> patterns;
    
    for (const auto& cur_str : v) {
        std::unordered_map<wchar_t, size_t> letters_amount;
        for (const auto c : cur_str) {
            letters_amount[towlower(c)]++;
        }

        bool is_new_pattern = true;
        for (size_t i = 0; i < patterns.size(); i++) {
            if (letters_amount == patterns[i]) {
                is_new_pattern = false;
                result[i].push_back(cur_str);
            }
        }

        if (is_new_pattern) {
            patterns.push_back(letters_amount);
            result.push_back(std::vector<std::wstring> {cur_str});
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<std::wstring> v = {
        L"материк",
        L"клоун",
        L"метрика",
        L"уклон",
        L"Керамит",
        L"норка",
        L"колун",
        L"рок",
    };

    std::wofstream output_file("result.txt", std::ios::out);
    for (const auto cur_v : Discriminator(v)) {
        for (const auto str : cur_v) {
            output_file << str << ' ';
        }
        output_file << '\n';
    }
    output_file.close();
}