#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

void SoftwareVersion(const string &versionStr)
{
    static const regex VERSION_PATTERN("([0-9]+)\\.([0-9]+)\\.([0-9]+)(.*)");

    smatch match;
    if (!regex_match(versionStr.begin(), versionStr.end(), match, VERSION_PATTERN))
    {
        cout << "Invalid version string:" << std::endl;
        throw runtime_error("Invalid version string: " + versionStr);
    }

    int major  = stoi(match[1]);
    int middle = stoi(match[2]);
    int minor  = stoi(match[3]);
    string tag    = match[4];
    
    cout << "Major=" << major << " middle=" << middle << " minor=" << minor << " Tag=" << tag << std::endl;
}

int test_regex_main()
{
    std::cout<<"Hello World";
    
    SoftwareVersion("7.0.0-rc2");
    SoftwareVersion("6.3.1");
    SoftwareVersion("6.3.9999");
    SoftwareVersion("6.3.w");
    return 0;
}