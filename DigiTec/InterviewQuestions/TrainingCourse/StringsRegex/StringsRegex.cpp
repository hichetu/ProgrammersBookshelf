// StringsRegex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Simple3LetterWordTests()
{
    // Test boundary conditions
    assert(isOnly3Letters(nullptr));
    assert(isOnly3Letters(L""));

    // Test simple passing conditions
    assert(isOnly3Letters(L"the"));
    assert(isOnly3Letters(L"the old tan dog"));

    // Test conditions of odd word lengths
    assert(!isOnly3Letters(L"   "));
    assert(!isOnly3Letters(L"a b"));
    assert(!isOnly3Letters(L"theory"));
    assert(!isOnly3Letters(L"paddles"));
    assert(!isOnly3Letters(L"a e i o u y"));
    assert(!isOnly3Letters(L"abe to four"));
}

void Simple3LetterWordTestsAndWhitespace()
{
    // Test boundary conditions
    assert(isOnly3LettersImproved(nullptr));
    assert(isOnly3LettersImproved(L""));
    assert(isOnly3LettersImproved(L"   "));

    // Test simple passing conditions
    assert(isOnly3LettersImproved(L"the"));
    assert(isOnly3LettersImproved(L"the old tan dog"));
    assert(isOnly3LettersImproved(L"the  old tan dog"));
    assert(isOnly3LettersImproved(L"the old tan dog "));
    assert(isOnly3LettersImproved(L"the old tan dog  "));
    assert(isOnly3LettersImproved(L" the old tan dog"));
    assert(isOnly3LettersImproved(L"  the old tan dog"));
    assert(isOnly3LettersImproved(L"  the old   tan  dog  "));

    // Test conditions of odd word lengths that don't pass
    assert(!isOnly3LettersImproved(L"a b"));
    assert(!isOnly3LettersImproved(L"theory"));
    assert(!isOnly3LettersImproved(L"paddles"));
    assert(!isOnly3LettersImproved(L"a e i o u y"));
    assert(!isOnly3LettersImproved(L" abe to four"));
}

int _tmain(int argc, _TCHAR* argv[])
{
    Simple3LetterWordTests();
    Simple3LetterWordTestsAndWhitespace();
    return 0;
}

