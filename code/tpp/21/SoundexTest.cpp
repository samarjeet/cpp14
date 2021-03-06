#include "CppUTest/TestHarness.h"

#include "Soundex.h"

TEST_GROUP(ASoundexEncoding) {
   Soundex soundex;
};

TEST(ASoundexEncoding, AppendsZerosToWordForOneLetterWord) {
   CHECK_EQUAL("A000", soundex.encode("A"));
   CHECK_EQUAL("B000", soundex.encode("B"));
}

TEST(ASoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
   CHECK_EQUAL("A100", soundex.encode("Ab"));
   CHECK_EQUAL("A200", soundex.encode("Ac"));
}

TEST(ASoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
   CHECK_EQUAL("A234", soundex.encode("Acdl"));
}

TEST(ASoundexEncoding, IgnoresVowelLikeLetters) {
   CHECK_EQUAL("B234", soundex.encode("BAaEeIiOoUuHhYycdl"));
}

TEST(ASoundexEncoding, IgnoresNonAlphabetics) {
   CHECK_EQUAL("F234", soundex.encode("F987654321%#.=+cdl"));
}

TEST(ASoundexEncoding, CombinesDuplicateEncodings) {
   CHECK_EQUAL(soundex.codeFor('f'), soundex.codeFor('b'));
   CHECK_EQUAL(soundex.codeFor('g'), soundex.codeFor('c'));
   CHECK_EQUAL(soundex.codeFor('t'), soundex.codeFor('d'));

   CHECK_EQUAL("A123", soundex.encode("Abfcgdt"));
}

TEST(ASoundexEncoding, CombinesMultipleDuplicateEncodings) {
   CHECK_EQUAL("J100", soundex.encode("Jbbb"));
}

TEST(ASoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {
   CHECK_EQUAL("B230", soundex.encode("bbcd"));
}

TEST(ASoundexEncoding, UppercasesFirstLetter) {
   CHECK_EQUAL("A", soundex.encode("abcd").substr(0, 1));
}

TEST(ASoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
   CHECK_EQUAL(soundex.encode("BCDL"), soundex.encode("bcdl"));
}

TEST(ASoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
   CHECK_EQUAL("J110", soundex.encode("Jbob")); 
}

TEST(ASoundexEncoding, LimitsLengthToFourCharacters) {
   CHECK_EQUAL(4u, soundex.encode("Dcdlb").length());
}

TEST(ASoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
   CHECK_EQUAL("I000", soundex.encode("I"));
}

