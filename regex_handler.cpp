/*
Regexes-file:
Regex0\n
Regex1\n
Regex2\n
...
RegexN\n
*/


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include <hs/hs.h>


using namespace std;

vector<string> read_regex_file(string filename) {

    ifstream file(filename);
    string line;

    vector<string> rgxs_strings;

    if (file.is_open()) {

        while (getline(file, line)) {
            rgxs_strings.push_back(line);
        }
        file.close();

    } else {
        cerr << "Unable to open regex file!" << endl; 
    }

    return rgxs_strings; 

}


hs_database_t* precompile_regexes(vector<string> rgxs_strings) {

    hs_database_t *database;
    hs_compile_error_t *compile_err;

    vector<const char*> rgxs_refrences;
    for (int i = 0; i < rgxs_strings.size(); i++) {
        rgxs_refrences.push_back((rgxs_strings[i]).c_str());
    }

    const char* const* rgxs = rgxs_refrences.data();
    int size = rgxs_strings.size();

    vector<unsigned int> flags(size, HS_FLAG_DOTALL);

    vector<unsigned int> ids(size);
    iota(ids.begin(), ids.end(), 1);

    unsigned int mode = HS_MODE_BLOCK;

    if (hs_compile_multi(rgxs, flags.data(), ids.data(), size, mode, nullptr, 
    &database, &compile_err) != HS_SUCCESS) {
            fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            rgxs, compile_err->message);
            hs_free_compile_error(compile_err);
    }

    return database;
}

int main() {
    vector<string> rgxs_strings = read_regex_file("./regexTest.rgx");

    vector<const char*> rgxs_refrences;
    for (int i = 0; i < rgxs_strings.size(); i++) {
        rgxs_refrences.push_back((rgxs_strings[i]).c_str());
    }

    const char* const* rgxs = rgxs_refrences.data();
    int size = rgxs_strings.size();


    for (int i = 0; i < size; i++) {
        cout << rgxs[i] << endl;
    }
    return 1;
}
