#include "stdafx.h"

// Question #1
// Write a function that determines whether or not a string contains only whitespace characters.
bool containsOnlyWhitespace(const wchar_t* inStr)
{
    while (*inStr != L'\0')
    {
        switch (*inStr)
        {
        case L' ':
        case L'\t':
        case L'\r':
        case L'\n':
        case L'\f':
            continue;
        default:
            return false;
        }
    }
    return true;
}

// If we are asked for a variation which doesn't assume null termination
bool containsOnlyWhitespace(const wchar_t* inStr, unsigned long count)
{
    while (count-- != 0)
    {
        switch (*inStr)
        {
        case L' ':
        case L'\t':
        case L'\r':
        case L'\n':
        case L'\f':
            continue;
        default:
            return false;
        }
    }
    return true;
}

// Question #2
// Write a function that determines if a string is composed only of 3 letter words. The string “foo bar baz” would return true. The string “The tan dog barks” would return false.
bool isOnly3Letters(const wchar_t* inStr)
{
    // First lets assume it is full normalized. No leading or trailing whitespaces, all word separators are a single character.
    if (inStr == nullptr)
    {
        return true;
    }
    size_t length = wcslen(inStr);
    if (length == 0)
    {
        return true;
    }

    // Make sure our string has precisely 3 {word} + (1 {space} + 3 {word}) characters
    if ((length - 3) % 4 == 0)
    {
        const wchar_t* spaceOffset = inStr + 3;
        const wchar_t* charOffset = inStr + 1; // Detects 1 character letters
        const wchar_t* end = inStr + length;
        while (spaceOffset <= end)
        {
            if ((*spaceOffset != L' ' && *spaceOffset != L'\0') || *charOffset == L' ')
            {
                return false;
            }
            spaceOffset += 4;
            charOffset += 4;
        }
        return true;
    }
    return false;
}

// In the preceding function we assumed no odd whitespace characters. But you can write a simpler function which works around this.
const wchar_t* SkipWhitespace(const wchar_t* inStr)
{
    while (*inStr == L' ')
    {
        inStr++;
    }
    return inStr;
}
bool isOnly3LettersImproved(const wchar_t* inStr)
{
    if (inStr == nullptr)
    {
        return true;
    }
    inStr = SkipWhitespace(inStr);
    while (*inStr != L'\0')
    {
        // Match 3 characters
        if (*inStr == L' ' || *inStr++ == L'\0') { return false; }
        if (*inStr == L' ' || *inStr++ == L'\0') { return false; }
        if (*inStr == L' ' || *inStr++ == L'\0') { return false; }
        if (*inStr != L'\0' && *inStr++ != L' ') { return false; }
        inStr = SkipWhitespace(inStr);
    }
    return true;
}

// Question #3
// This is another question that determines if you understand how pointers function.The solution here can be generalized to other 
// problems as well as you’ll see later.Make sure you clarify with the interviewer if whitespace is significant in the matching.
// Also, make sure you clarify if case insensitivity is important or not and account for that in your algorithm.
bool isPalindrome(const wchar_t* inStr)
{
    const wchar_t* pEnd = inStr;
    while (*pEnd != L'\0')
    {
        ++pEnd;
    }
    pEnd--; // Back off the null terminator
    while (inStr < pEnd)
    {
        if (*inStr++ != *pEnd--)
        {
            return false;
        }
    }
    return true;
}

bool isPunctuation(const wchar_t* inStr)
{
    switch (*inStr)
    {
    case L' ':
    case L'\t':
    case L'.':
    case L',':
    case L';':
    case L':':
    case L'\"':
    case L'\'':
    case L'?':
    case L'-':
    case L'!':
        return true;
    }
    return false;
}
bool isPalindromeSentence(const wchar_t* inStr)
{
    const wchar_t* pEnd = inStr;
    while (*pEnd != L'\0')
    {
        ++pEnd;
    }
    pEnd--; // Back off the null terminator

    while (inStr < pEnd)
    {
        while (inStr < pEnd && isPunctuation(inStr))
        {
            inStr++;
        }
        while (pEnd > inStr && isPunctuation(pEnd))
        {
            pEnd--;
        }
        if (towlower(*inStr++) != towlower(*pEnd--))
        {
            return false;
        }
    }
    return true;
}