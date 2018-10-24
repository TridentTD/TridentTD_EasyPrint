#ifndef __TRIDENTTD_SPACE___
#define __TRIDENTTD_SPACE___
namespace TridentTD {
// public:
  String UTF8_to_TIS620(String utf8_str, bool debug = false){
    size_t sz = utf8_str.length();
    if( debug)
      Serial << "UTF8 String length : " << sz << endl;

    String ret;
    int i =0;
    // for(int i = 0; i < sz; ++i){
    while( (int)utf8_str[i] != 0 ) {
      if( (int)(utf8_str[i]) == 224 && i < sz-2) {
        int unicode = ((int)(utf8_str[i+2]) & 0x3F);
        unicode    |= ((int)(utf8_str[i+1]) & 0x3F) << 6;
        unicode    |= ((int)(utf8_str[i])   & 0x0F) << 12;
        ret += (char) ( unicode - 0x0E00 + 0xA0);
        if(debug) {
          String cur_char; cur_char += utf8_str[i]; cur_char += utf8_str[i+1]; cur_char += utf8_str[i+2];
          Serial  << "[" << i << "] "
                  << "UTF8: "   << TD_HEX((int)(utf8_str[i])) << ", "
                                << TD_HEX((int)(utf8_str[i+1])) << ", "
                                << TD_HEX((int)(utf8_str[i+2])) << " --> "
                  << "TIS620: " << TD_HEX((int)( unicode - 0x0E00 + 0xA0)) 
                  << " --> Character: " << cur_char <<endl;
        }
        i +=2;
      }else{
        ret += utf8_str[i];
        if(debug) {
          Serial  << "[" << i << "] "
                  << "UTF8: "   << TD_HEX((int)(utf8_str[i])) << " --> "
                  << "TIS620: " << TD_HEX((int)(utf8_str[i])) 
                  << " --> Character: " << utf8_str[i] <<endl;
        }
      }
      i++;
    } // while
    if( debug)
      Serial << "TIS620 String length : " << ret.length() << endl << TD_FILL('-',50) << endl;
    return ret;
  }

  String TIS620_to_UTF8(String tis620_str, bool debug = false){
    size_t sz = tis620_str.length();
    String utf8_str;
    for(int i=0; i < sz; ++i) {
      int c = (int) tis620_str[i];
      if( c < 0x80 ){
        utf8_str += (char) c;
        if(debug) {
          Serial  << "TIS620: " << TD_HEX((int) tis620_str[i]) << " --> "
                  << "UTF8: "   << TD_HEX(c) << endl;
        }
      }else if((0xA1 <= c && c <=0xDA) || (0xDF <= c && c <=0xFB)){
        int unicode = 0x0E00 + c - 0xA0;
        utf8_str += (char)( 0xE0 |  (unicode >> 12 ));
        utf8_str += (char)( 0x80 | ((unicode >> 6) & 0x3F));
        utf8_str += (char) (0x80 |  (unicode & 0x3F));
        if(debug) {
          Serial  << "TIS620: " << TD_HEX((int) tis620_str[i]) << " --> "
                  << "UTF8: "   << TD_HEX((int)( 0xE0 |  (unicode >> 12 ))) << ", "
                                << TD_HEX((int)( 0x80 | ((unicode >> 6) & 0x3F))) << ", "
                                << TD_HEX((int)( 0x80 | (unicode & 0x3F))) <<endl;
        }
      }
    }
    return utf8_str;
  }
}

#endif //__TRIDENTTD_SPACE___
