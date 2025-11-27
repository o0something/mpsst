#include <vector>
#include <string>
#include <hs/hs.h>

using namespace std;

class AbstractFileScanner {
    protected:
        hs_database_t *database;
    public:
        HSFileScanner(hs_database_t *database);
        ~HSFileScanner() override;
        void scan_file(const std::string &path) override;
        void debug_scan_literal() override;
};      