#include <algorithm>
#include <string>

std::string sajat_to_lower(std::string string) {
    std::transform(string.begin(), string.end(), string.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    // this function iterates through the characters of the parameter string,
    // and runs a function on all characters, which converts any character to
    // lowercase form using std::tolower, and stores the converted values in
    // their original place in the string, than returns the string
    return string;
}
