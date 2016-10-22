/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum : int {
    EXIT_DEBUG = 2,
    EXIT_RELEASE = 3
};

#define STR_DEBUG "DEBUG"
#define STR_RELESAE "RELEASE"

void ShowUsage()
{
    wcout <<
        L"Usage: BuildConfGetTarget <target-filepath>\n"
        L"Exit Codes:\n"
        L"  1: Failed to recognized build target or an error occurred\n"
        L"  2: Build target is Debug\n"
        L"  3: Build target is Release\n";
}

int wmain(int argc, wchar_t* argv[])
{
    if (argc != 2) {
        wcout << L"Error: Invalid number of parameters provided\n";
        ShowUsage();
        return EXIT_FAILURE;
    }

    wstring filepath(argv[1]);
    ifstream confFile(filepath);
    if (!confFile.is_open()) {
        wcout << L"Error: Failed to open " << filepath.c_str() << endl;
        return EXIT_FAILURE;
    }

    auto confFileBegin = istreambuf_iterator<char>(confFile);
    string fileContent(confFileBegin, istreambuf_iterator<char>());
    // Look for TARGET=RELEASE|DEBUG pattern using case insensitive character match
    regex words_regex("target\\s*=\\s*(release|debug)", regex::icase);
    auto words_begin =
        std::sregex_iterator(fileContent.begin(), fileContent.end(), words_regex);
    auto words_end = sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        auto& match = *i;

        if (match.size() != 2)
            continue;

        auto targetMatchStr = match[1].str();

        if (!_stricmp(targetMatchStr.c_str(), STR_RELESAE)) {
#ifdef DEBUG
            wcout << "TARGET=RELEASE\n";
#endif // DEBUG
            return EXIT_RELEASE;
        } else if (!_stricmp(targetMatchStr.c_str(), STR_DEBUG)) {
#ifdef DEBUG
            wcout << "TARGET=DEBUG\n";
#endif // DEBUG
            return EXIT_DEBUG;
        } else {
            cout << targetMatchStr;
            // Based on the regex, this case can't happen, match will only
            // happen with release or debug
            _ASSERTE(!"Error: Unexpected target match");
        }
    }

    wcout << L"Error: Couldn't recognize build target\n";

    return EXIT_FAILURE;
}