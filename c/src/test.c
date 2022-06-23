#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "libnum.h"

int main(){

  /*
   * Testing should be deterministic.
   */
  srand(0);

  /*
   * Test that random number generation works.
   */
  char *num1 = generate_numerical_string(100);
  assert(strlen(num1)==100);
  for(int i=0;i<strlen(num1);i++){
    assert(isdigit(num1[i]));
  }

  /*
   * Test that printing a number using a separator doesn't cause a crash.
   */
  print_with_separators("1234", ',', stdout);

  /*
   * General number test #1 - basic numbers.
   */
  char *num2=representation_of_number("1234");
  puts(num2);
  assert(strcmp(num2, "one thousand, two hundred thirty four")==0);

  /*
   * General number test #2 - Slightly larger numbers.
   */
  char *num3=representation_of_number("8675309");
  puts(num3);
  assert(strcmp(num3, "eight million, six hundred seventy five thousand, three hundred nine")==0);

  /*
   * General number test #3 - Round numbers.
   */
  char *num4=representation_of_number("1000000");
  puts(num4);
  assert(strcmp(num4, "one million")==0);

  /*
   * General number test #4 - Numbers with a "0" prefix.
   */
  char *num5=representation_of_number("00100");
  puts(num5);
  assert(strcmp(num5, "one hundred")==0);

  /*
   * General number test #5 - Extremely large numbers.
   */
  char *num6=representation_of_number("804641733868228386051616044394004183078479646652895842356339048712722901475887303829579038541998183354770984973811149075914540608196262817106382048951704506350713922931928211517988663011056078208292321942787060764839514026434032704506447872546526405623686117839434270124237089061882164265825101919999741442");
  puts(num6);
  assert(strcmp(num6, "eight hundred four centillion, six hundred fourty one novennonagintillion, seven hundred thirty three octononagintillion, eight hundred sixty eight septnonagintillion, two hundred twenty eight sesnonagintillion, three hundred eighty six quinnonagintillion, fifty one quattuornonagintillion, six hundred sixteen tresnonagintillion, fourty four duononagintillion, three hundred ninety four unnonagintillion, four nonagintillion, one hundred eighty three novenoctogintillion, seventy eight octooctogintillion, four hundred seventy nine septoctogintillion, six hundred fourty six sesoctogintillion, six hundred fifty two quinoctogintillion, eight hundred ninety five quattuoroctogintillion, eight hundred fourty two tresoctogintillion, three hundred fifty six duooctogintillion, three hundred thirty nine unoctogintillion, fourty eight octogintillion, seven hundred twelve novenseptuagintillion, seven hundred twenty two octoseptuagintillion, nine hundred one septseptuagintillion, four hundred seventy five sesseptuagintillion, eight hundred eighty seven quinseptuagintillion, three hundred three quattuorseptuagintillion, eight hundred twenty nine tresseptuagintillion, five hundred seventy nine duoseptuagintillion, thirty eight unseptuagintillion, five hundred fourty one septuagintillion, nine hundred ninety eight novensexagintillion, one hundred eighty three octosexagintillion, three hundred fifty four septsexagintillion, seven hundred seventy sessexagintillion, nine hundred eighty four quinsexagintillion, nine hundred seventy three quattuorsexagintillion, eight hundred eleven tressexagintillion, one hundred fourty nine duosexagintillion, seventy five unsexagintillion, nine hundred fourteen sexagintillion, five hundred fourty novenquinquagintillion, six hundred eight octoquinquagintillion, one hundred ninety six septquinquagintillion, two hundred sixty two sesquinquagintillion, eight hundred seventeen quinquinquagintillion, one hundred six quattuorquinquagintillion, three hundred eighty two tresquinquagintillion, fourty eight duoquinquagintillion, nine hundred fifty one unquinquagintillion, seven hundred four quinquagintillion, five hundred six novenquadragintillion, three hundred fifty octoquadragintillion, seven hundred thirteen septquadragintillion, nine hundred twenty two sesquadragintillion, nine hundred thirty one quinquadragintillion, nine hundred twenty eight quattuorquadragintillion, two hundred eleven tresquadragintillion, five hundred seventeen duoquadragintillion, nine hundred eighty eight unquadragintillion, six hundred sixty three quadragintillion, eleven noventrigintillion, fifty six octotrigintillion, seventy eight septtrigintillion, two hundred eight sestrigintillion, two hundred ninety two quintrigintillion, three hundred twenty one quattuortrigintillion, nine hundred fourty two trestrigintillion, seven hundred eighty seven duotrigintillion, sixty untrigintillion, seven hundred sixty four trigintillion, eight hundred thirty nine novenvigintillion, five hundred fourteen octovigintillion, twenty six septvigintillion, four hundred thirty four sesvigintillion, thirty two quinvigintillion, seven hundred four quattuorvigintillion, five hundred six tresvigintillion, four hundred fourty seven duovigintillion, eight hundred seventy two unvigintillion, five hundred fourty six vigintillion, five hundred twenty six novendecillion, four hundred five octodecillion, six hundred twenty three septdecillion, six hundred eighty six sesdecillion, one hundred seventeen quindecillion, eight hundred thirty nine quattuordecillion, four hundred thirty four tresdecillion, two hundred seventy duodecillion, one hundred twenty four undecillion, two hundred thirty seven decillion, eighty nine nonillion, sixty one octillion, eight hundred eighty two septillion, one hundred sixty four sextillion, two hundred sixty five quintillion, eight hundred twenty five quadrillion, one hundred one trillion, nine hundred nineteen billion, nine hundred ninety nine million, seven hundred fourty one thousand, four hundred fourty two")==0);

  /*
   * General number test #6 - Zero.
   */
  char *num7=representation_of_number("0");
  puts(num7);
  assert(strcmp(num7, "zero")==0);
}
