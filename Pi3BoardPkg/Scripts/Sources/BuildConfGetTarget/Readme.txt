Description:
This tool extracts the build target specified in EDK2 Conf\target.txt as TARGET=DEBUG|RELEASE
It uses the regex target\s*=\s*(release|debug) to do a case insensitive string match. 

- This tool gets statically linked against MSVCRT library and it should run on any Windows machine as standalone exe without the need to install MSVC runtime.
- BuildConfGetTarget is tested on Win10 , but should have no problems running on older versions.

Usage:
    BuildConfGetTarget <target-filepath>
    <target-filepath>: The fullpath of EDK2 target.txt
    Returns: An exit code that indicates the recognized build target

Exit Codes:
    1: Failed to recognized build target or an error occurred
    2: Build target is Debug
    3: Build target is Release