#include<string>
#include "Soundex.h"
#include "gmock/gmock.h"

using namespace testing;

class SoundexEncoding: public Test{
public :  
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLettterOfOneLetterWord){
  ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZeroToEnsureThreeDigits){
  ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}
