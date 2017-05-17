#ifndef Soundex_h
#define Soundex_h
class Soundex{
public :
  std::string encode(const std::string& word) const{
    return zeropad(word);
  }
private :
  std::string zeropad(const std::string& word) const {
    return word + "000";
  }
};

#endif
