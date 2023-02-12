#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mt19937.h"

#define MT19937_STATE_LENGTH 624
#define MT19937_STATE_MIDDLE 397
#define MT19937_UPPER_MASK 0x80000000U
#define MT19937_LOWER_MASK 0x7FFFFFFFU
#define MT19937_TWIST_MASK 0x9908B0DFU
#define MT19937_MULTIPLIER 0x00010DCDU
#define MT19937_TEMPER_B 0x9D2C5680U
#define MT19937_TEMPER_C 0xEFC60000U
#define MT19937_TEMPER_D 0xFFFFFFFFU
#define MT19937_TEMPER_I 18
#define MT19937_TEMPER_S 7
#define MT19937_TEMPER_T 15
#define MT19937_TEMPER_U 11

static struct
{
    uint32_t state[MT19937_STATE_LENGTH];
    int index;
}
mt19937 =
{
    {
        0x00001105U, 0x11EFE201U, 0x6D9307CDU, 0x3DEFA829U, 0x6C9CBDD5U, 0xACFCD491U, 0x31D2951DU, 0x2C50E139U,
        0x796D3FA5U, 0x085C5821U, 0xBA8D3F6DU, 0xCEC15349U, 0xB5536675U, 0xD671FCB1U, 0x7FCD56BDU, 0x1B930E59U,
        0x9AD60245U, 0xDDC25241U, 0xC50A2B0DU, 0x78612269U, 0x76F0E315U, 0x5D82E8D1U, 0x70780C5DU, 0x351F9F79U,
        0xC4E4D8E5U, 0x232A5061U, 0x9F584AADU, 0x602B9589U, 0xCF07B3B5U, 0xE10018F1U, 0x474935FDU, 0x035B1499U,
        0x64944385U, 0x55ACD281U, 0x34961E4DU, 0xDA0D2CA9U, 0x747A5855U, 0xD4CA0D11U, 0xB587539DU, 0x9039EDB9U,
        0x5D2EC225U, 0xC07258A1U, 0x42B225EDU, 0x9A8267C9U, 0xC17B50F5U, 0x83D14531U, 0x7448E53DU, 0xB740AAD9U,
        0xB24ED4C5U, 0x9EB362C1U, 0x946AE18DU, 0x2897C6E9U, 0xFD8D1D95U, 0x52164151U, 0x1E746ADDU, 0xB783CBF9U,
        0x71DEFB65U, 0x7DB870E1U, 0x7B4ED12DU, 0x8FE9CA09U, 0xE7823E35U, 0x3EA98171U, 0x4AC0647DU, 0x05A7D119U,
        0xDE19B605U, 0xDEDA0301U, 0x89BC74CDU, 0x52A4F129U, 0x7F7D32D5U, 0xA5AB8591U, 0xE5B3521DU, 0x5DE13A39U,
        0xD78984A5U, 0x19809921U, 0x8CE24C6DU, 0x9B85BC49U, 0x10F07B75U, 0x424CCDB1U, 0xCBA3B3BDU, 0x15F48759U,
        0x8708E745U, 0x7D24B341U, 0xC6BED80DU, 0xAFD8AB69U, 0x7C9E9815U, 0x70CDD9D1U, 0xA2B8095DU, 0xAF363879U,
        0x47C25DE5U, 0xB34ED161U, 0x682097ADU, 0xA17A3E89U, 0xC29A08B5U, 0xB07F29F1U, 0xF4E6D2FDU, 0xA88ACD99U,
        0xD1306885U, 0x61977381U, 0x4AA60B4DU, 0x40D6F5A9U, 0xCC454D55U, 0x65C13E11U, 0x89F6909DU, 0x9066C6B9U,
        0xA11D8725U, 0x0BA719A1U, 0xEABDB2EDU, 0x4EEB50C9U, 0x7652E5F5U, 0xDC049631U, 0x017DC23DU, 0x56CEA3D9U,
        0xA5A439C5U, 0x353643C1U, 0xA1A60E8DU, 0xEF43CFE9U, 0xDAC55295U, 0x87C9B251U, 0xACE2E7DDU, 0xDF56E4F9U,
        0x272F0065U, 0xC40D71E1U, 0x1F6D9E2DU, 0x59FCF309U, 0xDAEF1335U, 0x88A11271U, 0xA95C817DU, 0xD3240A19U,
        0xF2785B05U, 0xA2052401U, 0x24F2E1CDU, 0xCDC33A29U, 0xE972A7D5U, 0x6B2B3691U, 0x39F10F1DU, 0xB2EA9339U,
        0xC28AC9A5U, 0x9F05DA21U, 0x7DE4596DU, 0xC1D32549U, 0x14429075U, 0x2B189EB1U, 0x617710BDU, 0x28EF0059U,
        0xEAC0CC45U, 0x93081441U, 0x3AC0850DU, 0x57F93469U, 0x4EA14D15U, 0x7529CAD1U, 0xBC95065DU, 0x9B05D179U,
        0x40C4E2E5U, 0xC0145261U, 0x2AD5E4ADU, 0x0E91E789U, 0xFB215DB5U, 0x292F3AF1U, 0x9BC16FFDU, 0xFC938699U,
        0x46918D85U, 0x74431481U, 0x9642F84DU, 0xB289BEA9U, 0xB5A54255U, 0x1C096F11U, 0x5D42CD9DU, 0xE08C9FB9U,
        0x94714C25U, 0xEBBCDAA1U, 0x37F63FEDU, 0x915D39C9U, 0x5D5F7AF5U, 0x19A8E731U, 0x072F9F3DU, 0xCB759CD9U,
        0x82FE9EC5U, 0x72BA24C1U, 0x77AE3B8DU, 0xEB18D8E9U, 0x5ED28795U, 0x270E2351U, 0x216E64DDU, 0xC562FDF9U,
        0x15240565U, 0xC78372E1U, 0xE3F96B2DU, 0xA4591C09U, 0x3DD0E835U, 0x0449A371U, 0xCFB59E7DU, 0x2BF94319U,
        0x221C0005U, 0xBC714501U, 0xEC364ECDU, 0x384A8329U, 0x5F7D1CD5U, 0xEE7BE791U, 0x2B8BCC1DU, 0xC46CEC39U,
        0xBF710EA5U, 0x19EC1B21U, 0xDA93666DU, 0xEAA98E49U, 0x1449A575U, 0xA1D56FB1U, 0xDE476DBDU, 0x0D827959U,
        0xEAFDB145U, 0xC06C7541U, 0x0E0F320DU, 0x39C2BD69U, 0xE1F90215U, 0x9B96BBD1U, 0xFB0F035DU, 0xD18E6A79U,
        0x74EC67E5U, 0x0A7AD361U, 0x747831ADU, 0x90729089U, 0x0D9DB2B5U, 0x9C104BF1U, 0x18D90CFDU, 0xF8753F99U,
        0x29B7B285U, 0x6EAFB581U, 0x446CE54DU, 0x382587A9U, 0x659A3755U, 0x68A2A011U, 0xAC6C0A9DU, 0x99AB78B9U,
        0x3C2A1125U, 0x61B39BA1U, 0xF75BCCEDU, 0x8AD822C9U, 0x4BA10FF5U, 0xCDBE3831U, 0xA25E7C3DU, 0x4E3595D9U,
        0xEF5E03C5U, 0x783F05C1U, 0x8383688DU, 0x6516E1E9U, 0xFEB4BC95U, 0xE0E39451U, 0x3916E1DDU, 0xC2A816F9U,
        0x80BE0A65U, 0xC91A73E1U, 0xD5F2382DU, 0xD7FE4509U, 0x2527BD35U, 0x82A33471U, 0x1ACBBB7DU, 0x89277C19U,
        0x5204A505U, 0x8F1E6601U, 0x8C86BBCDU, 0x1B3ACC29U, 0x969C91D5U, 0x209D9891U, 0xB783891DU, 0x2B684539U,
        0x533C53A5U, 0x0B335C21U, 0xEFEF736DU, 0xBF08F749U, 0x6605BA75U, 0xB78340B1U, 0xDF14CABDU, 0x7CAEF259U,
        0xACBF9645U, 0xA651D641U, 0x2DAADF0DU, 0x1E354669U, 0x2BA5B715U, 0x1514ACD1U, 0x9B26005DU, 0x2BD00379U,
        0xA938ECE5U, 0x53825461U, 0xD2077EADU, 0x101C3989U, 0x8F0F07B5U, 0x5A225CF1U, 0x492DA9FDU, 0x952FF899U,
        0xDFA2D785U, 0x31DD5681U, 0x8223D24DU, 0xDAAA50A9U, 0x11242C55U, 0xBC8CD111U, 0xF472479DU, 0xD4C351B9U,
        0x9D47D625U, 0x6E8B5CA1U, 0xF5EE59EDU, 0x645C0BC9U, 0x1617A4F5U, 0x89448931U, 0xF00A593DU, 0x180E8ED9U,
        0x8FC268C5U, 0x66C4E6C1U, 0x3225958DU, 0xA63DEAE9U, 0x2F6BF195U, 0x664A0551U, 0xB0DC5EDDU, 0x30262FF9U,
        0xAEFD0F65U, 0x09D274E1U, 0x0258052DU, 0x5DEC6E09U, 0xA5F39235U, 0xD4ADC571U, 0xE79ED87DU, 0x63AEB519U,
        0x67324A05U, 0x7B0C8701U, 0xB2E428CDU, 0xFF941529U, 0x43D106D5U, 0xF2904991U, 0xDAD8461DU, 0x80DC9E39U,
        0x02EC98A5U, 0xF3DB9D21U, 0x0AF8806DU, 0xE7F16049U, 0x5E76CF75U, 0x7D2211B1U, 0x00DF27BDU, 0x2F746B59U,
        0x55067B45U, 0xE5B83741U, 0x86938C0DU, 0xCE50CF69U, 0x20A76C15U, 0x12A39DD1U, 0xD9D9FD5DU, 0x82CA9C79U,
        0xA2AA71E5U, 0x5C2AD561U, 0xD083CBADU, 0x768EE289U, 0x14755CB5U, 0xB4656DF1U, 0x09BF46FDU, 0xCBC3B199U,
        0xCD52FC85U, 0x9ECBF781U, 0x7C67BF4DU, 0xA31819A9U, 0xED432155U, 0x88C80211U, 0xB255849DU, 0xAAD42AB9U,
        0xBCCA9B25U, 0x13441DA1U, 0x00ADE6EDU, 0x46E8F4C9U, 0x91C339F5U, 0xDD3BDA31U, 0x0D33363DU, 0x620087D9U,
        0x092BCDC5U, 0x5F4BC7C1U, 0xF094C28DU, 0xF78DF3E9U, 0x65F82695U, 0x68417651U, 0x45BEDBDDU, 0x66DD48F9U,
        0xE4E11465U, 0xCAAB75E1U, 0x762AD22DU, 0x9F239709U, 0xD5346735U, 0xCB695671U, 0x932EF57DU, 0x348EEE19U,
        0x46A4EF05U, 0xE13BA801U, 0x0C4E95CDU, 0x6E565E29U, 0x1C1A7BD5U, 0x5553FA91U, 0x928A031DU, 0x5DC9F739U,
        0x5381DDA5U, 0x54E4DE21U, 0x78AE8D6DU, 0x0E62C949U, 0x529CE475U, 0x03B1E2B1U, 0xE0A684BDU, 0xDED2E459U,
        0x08D26045U, 0x1F9F9841U, 0x05C9390DU, 0x13155869U, 0xB5FE2115U, 0xC5438ED1U, 0xF42AFA5DU, 0xAF7E3579U,
        0x2640F6E5U, 0xE5745661U, 0xFCED18ADU, 0xACCA8B89U, 0x32D0B1B5U, 0xFBD97EF1U, 0x378DE3FDU, 0x95306A99U,
        0x57C82185U, 0x967B9881U, 0x6038AC4DU, 0x9A6EE2A9U, 0x2EF71655U, 0x3E543311U, 0x6315C19DU, 0x34DE03B9U,
        0x9FB26025U, 0x50DDDEA1U, 0xE49A73EDU, 0x5B7EDDC9U, 0x93A3CEF5U, 0x5AA42B31U, 0x16D9133DU, 0x650B80D9U,
        0x009A32C5U, 0x82D3A8C1U, 0x2BD0EF8DU, 0xA206FCE9U, 0x17595B95U, 0x97C9E751U, 0xB4BE58DDU, 0xBFCD61F9U,
        0x676A1965U, 0x4CA576E1U, 0x3E6A9F2DU, 0x04A3C009U, 0xC7EA3C35U, 0x37D5E771U, 0x7A7C127DU, 0x74C82719U,
        0xD55C9405U, 0x22ABC901U, 0x45C602CDU, 0xF081A729U, 0xD478F0D5U, 0x39E8AB91U, 0xDB98C01DU, 0x5B305039U,
        0xC9FC22A5U, 0xAF4F1F21U, 0x86119A6DU, 0xDB5D3249U, 0x9777F975U, 0x5C32B3B1U, 0x1B6AE1BDU, 0x43CA5D59U,
        0xED234545U, 0xF507F941U, 0x984BE60DU, 0xB582E169U, 0xE0A9D615U, 0x5DF47FD1U, 0x2718F75DU, 0x8AEACE79U,
        0xF8FC7BE5U, 0xB05ED761U, 0xE44365ADU, 0x9BCF3489U, 0x7F2106B5U, 0x817E8FF1U, 0xAF9980FDU, 0xEA762399U,
        0xE4024685U, 0xF9EC3981U, 0x5A96994DU, 0xC9AEABA9U, 0x0B400B55U, 0x4E316411U, 0x83B2FE9DU, 0x8BE0DCB9U,
        0x4AFF2525U, 0x28589FA1U, 0x6EB400EDU, 0xCB1DC6C9U, 0xF0B963F5U, 0x927D7C31U, 0x29FBF03DU, 0x5A2F79D9U,
        0x1B0D97C5U, 0xF25C89C1U, 0x50DA1C8DU, 0xEEA905E9U, 0xB88F9095U, 0xA5E35851U, 0xBADAD5DDU, 0x93F67AF9U,
        0x7B981E65U, 0xD0C077E1U, 0x68176C2DU, 0xF76CE909U, 0x93151135U, 0xEAF37871U, 0xFA862F7DU, 0x9D5A6019U,
        0xF8593905U, 0xA05CEA01U, 0x0C4A6FCDU, 0x0F15F029U, 0x21EC65D5U, 0x914E5C91U, 0xB3047D1DU, 0x120FA939U,
        0xEB5B67A5U, 0x841A6021U, 0x8021A76DU, 0xF7E09B49U, 0x82080E75U, 0x97A484B1U, 0x4E2C3EBDU, 0x175AD659U,
        0x26F92A45U, 0x06F15A41U, 0x2B1B930DU, 0x7E996A69U, 0x95AA8B15U, 0x0DB670D1U, 0xAFA3F45DU, 0xEE106779U,
        0xDFDD00E5U, 0x7DEA5861U, 0x1386B2ADU, 0x2C9CDD89U, 0x8E665BB5U, 0x9654A0F1U, 0x4EE21DFDU, 0xC494DC99U,
        0xD7016B85U, 0xAA1DDA81U, 0x9881864DU, 0x39D774A9U, 0xB71E0055U, 0x295F9511U, 0x912D3B9DU, 0xC8DCB5B9U,
        0xC3B0EA25U, 0x9AB460A1U, 0x6BFA8DEDU, 0xBEC5AFC9U, 0x7E03F8F5U, 0x15C7CD31U, 0x639BCD3DU, 0x7A6C72D9U,
        0xFD85FCC5U, 0xCEE66AC1U, 0xCCB0498DU, 0x26740EE9U, 0xBE9AC595U, 0x438DC951U, 0x151452DDU, 0x3C5893F9U,
        0x666B2365U, 0x97FC78E1U, 0x0031392DU, 0xE07F1209U, 0x4BB4E635U, 0xB5C20971U, 0x704D4C7DU, 0x27459919U,
        0x949ADE05U, 0xBB4F0B01U, 0x0CDBDCCDU, 0x53133929U, 0xB974DAD5U, 0x4C850D91U, 0x15CD3A1DU, 0x1B680239U,
        0x3C9FACA5U, 0x5446A121U, 0xB3DEB46DU, 0x0CED0449U, 0x674D2375U, 0xC70755B1U, 0x15EA9BBDU, 0x12844F59U,
        0xDB540F45U, 0xF65BBB41U, 0xAB38400DU, 0x3758F369U, 0xCA004015U, 0x058961D1U, 0xCACBF15DU, 0xB1EF0079U,
        0x9FE285E5U, 0x0F16D961U, 0x17B6FFADU, 0x48338689U, 0xF5A0B0B5U, 0x8B5BB1F1U, 0xF267BAFDU, 0x1C8C9599U,
        0x95C59085U, 0x88107B81U, 0x46F9734DU, 0xF3E93DA9U, 0x6790F555U, 0x40DEC611U, 0x0884789DU, 0x04D18EB9U,
        0x0EC7AF25U, 0xA8F121A1U, 0xA96E1AEDU, 0x5F7698C9U, 0x10838DF5U, 0x75831E31U, 0xE0B8AA3DU, 0xFEC26BD9
    },
    MT19937_STATE_LENGTH
};

/******************************************************************************
 * Seed MT19937. If this function is not called, the initial state is the same
 * as if it were seeded with 4357.
 *
 * @param seed 32-bit number. If this is 0, MT19937 will be seeded with the
 *     sum of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_seed(uint32_t seed)
{
    if(seed == 0)
    {
        seed = time(NULL) + getpid();
    }
    mt19937.state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        // Overflow is okay. We only want the bottom 32 bits, and unsigned
        // overflow is defined behaviour.
        mt19937.state[i] = MT19937_MULTIPLIER * mt19937.state[i - 1];
    }
    mt19937.index = MT19937_STATE_LENGTH;
}

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 32-bit number.
 *****************************************************************************/
uint32_t mt19937_rand(void)
{
    // Twist.
    if(mt19937.index == MT19937_STATE_LENGTH)
    {
        mt19937.index = 0;
        uint32_t twist[] = {0, MT19937_TWIST_MASK};

        // I benchmarked this function and found that a single loop with modulo
        // operations runs slower than this.
        for(int i = 0; i < MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; ++i)
        {
            uint32_t upper = MT19937_UPPER_MASK & mt19937.state[i];
            uint32_t lower = MT19937_LOWER_MASK & mt19937.state[i + 1];
            uint32_t masked = upper | lower;
            uint32_t twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE] ^ twisted;
        }
        for(int i = MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; i < MT19937_STATE_LENGTH - 1; ++i)
        {
            uint32_t upper = MT19937_UPPER_MASK & mt19937.state[i];
            uint32_t lower = MT19937_LOWER_MASK & mt19937.state[i + 1];
            uint32_t masked = upper | lower;
            uint32_t twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE - MT19937_STATE_LENGTH] ^ twisted;
        }
        uint32_t upper = MT19937_UPPER_MASK & mt19937.state[MT19937_STATE_LENGTH - 1];
        uint32_t lower = MT19937_LOWER_MASK & mt19937.state[0];
        uint32_t masked = upper | lower;
        uint32_t twisted = (masked >> 1) ^ twist[masked & 1];
        mt19937.state[MT19937_STATE_LENGTH - 1] = mt19937.state[MT19937_STATE_MIDDLE - 1] ^ twisted;
    }

    // Generate.
    uint32_t curr = mt19937.state[mt19937.index++];
    curr ^= (curr >> MT19937_TEMPER_U) & MT19937_TEMPER_D;
    curr ^= (curr << MT19937_TEMPER_S) & MT19937_TEMPER_B;
    curr ^= (curr << MT19937_TEMPER_T) & MT19937_TEMPER_C;
    curr ^= curr >> MT19937_TEMPER_I;
    return curr;
}

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of the one
 * given in the original paper.
 *
 * Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister: A
 * 623-dimensionally Equidistributed Uniform Pseudo-random Number Generator",
 * in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1,
 * pp. 3-30, January 1998, doi:10.1145/272991.272995.
 *
 * @return `true` if the results match, else `false`.
 *****************************************************************************/
bool mt19937_test(void)
{
    uint32_t const expected[][2] =
    {
        {    1, 3510405877}, {    2, 4290933890}, {    4,  564929546}, {    8,  268830360}, {   16, 1452005258},
        {   32,  675678546}, {   64, 1413475797}, {  128,  979144237}, {  256, 2950091998}, {  512, 3769042770},
        { 1024, 1198529401}, { 2048, 1984791300}, { 4096, 1074066123}, { 8192, 1445832134}, {16384, 2454186801}
    };
    mt19937_seed(4357);
    for(uint32_t i = 1, j = 0; i <= 16384; ++i)
    {
        uint32_t r = mt19937_rand();
        if(i == expected[j][0])
        {
            if(r != expected[j][1])
            {
                return false;
            }
            ++j;
        }
    }
    return true;
}

/******************************************************************************
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 32-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
uint32_t mt19937_rand_integer(uint32_t modulus)
{
    uint32_t upper = 0xFFFFFFFFU - 0xFFFFFFFFU % modulus;
    uint32_t r;
    do
    {
        r = mt19937_rand();
    }
    while(r >= upper);
    return r % modulus;
}

/******************************************************************************
 * Choose a pseudorandom number in the unit interval.
 *
 * @return Pseudorandom real from 0 (inclusive) to 1 (inclusive), subject to
 *     the limitations of the return type.
 *****************************************************************************/
double mt19937_rand_real(void)
{
    return (double)mt19937_rand() / 0xFFFFFFFFU;
}

/******************************************************************************
 * Shuffle an array in place.
 *
 * @param items Array to shuffle.
 * @param items_length Number of elements in the array. Must not be 0.
 * @param item_size Size of each element of the array in bytes.
 *****************************************************************************/
void mt19937_rand_shuffle(void *items, uint32_t items_length, size_t item_size)
{
    char *temp = malloc(item_size);
    char *items_ = (char *)items;
    for(uint32_t i = items_length - 1; i > 0; --i)
    {
        uint32_t j = mt19937_rand_integer(i + 1);
        if(i != j)
        {
            char *items_i = items_ + i * item_size;
            char *items_j = items_ + j * item_size;
            memcpy(temp, items_i, item_size);
            memcpy(items_i, items_j, item_size);
            memcpy(items_j, temp, item_size);
        }
    }
    free(temp);
}
