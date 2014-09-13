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

void PalindromeSentenceTests()
{
    assert(isPalindromeSentence(L"Sore was I ere I saw Eros."));
    assert(isPalindromeSentence(L"A man, a plan, a canal -- Panama"));
    assert(isPalindromeSentence(L"Never a foot too far, even."));
    assert(isPalindromeSentence(L"Euston saw I was not Sue."));
    assert(isPalindromeSentence(L"Live on evasions? No, I save no evil."));
    assert(isPalindromeSentence(L"Red Roses run no risk, sir, on nurses order."));
    assert(isPalindromeSentence(L"Salisbury moor, sir, is roomy. Rub Silas."));
    assert(isPalindromeSentence(L"Marge, let\'s \"went.\" I await news telegram."));
    assert(isPalindromeSentence(L"A new order began, a more Roman age bred Rowena."));
    assert(isPalindromeSentence(L"I, man, am regal; a German am I."));
    assert(isPalindromeSentence(L"Tracy, no panic in a pony-cart."));
    assert(isPalindromeSentence(L"Egad! Loretta has Adams as mad as a hatter. Old age!"));
    assert(isPalindromeSentence(L"Eve, mad Adam, Eve!"));
    assert(isPalindromeSentence(L"Resume so pacific a pose, muser."));
    assert(isPalindromeSentence(L"Marge let a moody baby doom a telegram."));
    assert(isPalindromeSentence(L"Tenet C is a basis, a basic tenet."));
    assert(isPalindromeSentence(L"Nella\'s simple hymn: \"I attain my help, Miss Allen.\""));
    assert(isPalindromeSentence(L"Straw? No, too stupid a fad. I put soot on warts."));
    assert(isPalindromeSentence(L"Sir, I demand, I am a maid named Iris."));
    assert(isPalindromeSentence(L"Lay a wallaby baby ball away, Al."));
    assert(isPalindromeSentence(L"Tessa\'s in Italy, Latin is asset."));
    assert(isPalindromeSentence(L"Noel sees Leon."));
    assert(isPalindromeSentence(L"No, it can assess an action."));
    assert(isPalindromeSentence(L"Bob: \"Did Anna peep?\" Anna: \"Did Bob?\""));
    assert(isPalindromeSentence(L"Sex at noon taxes."));
    assert(isPalindromeSentence(L"Egad, a base life defiles a bad age."));
    assert(isPalindromeSentence(L"\"Stop!\" nine myriad murmur. \"Put up rum, rum, dairymen, in pots.\""));
    assert(isPalindromeSentence(L"Delia, here we nine were hailed."));
    assert(isPalindromeSentence(L"Not I, no hotel, cycle to Honiton."));
    assert(isPalindromeSentence(L"Anne, I vote more cars race Rome-to-Vienna."));
    assert(isPalindromeSentence(L"Mother Eve\'s noose we soon sever, eh, Tom?"));
    assert(isPalindromeSentence(L"\"Sue,\" Tom smiles, \"Selim smote us.\""));
    assert(isPalindromeSentence(L"Telegram, Margelet!"));
}

int _tmain(int argc, _TCHAR* argv[])
{
    Simple3LetterWordTests();
    Simple3LetterWordTestsAndWhitespace();
    PalindromeSentenceTests();
    return 0;
}

