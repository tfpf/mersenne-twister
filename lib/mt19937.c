#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mt19937.h"

#define MT19937_WIDTH 32
#define MT19937_STATE_LENGTH 624
#define MT19937_STATE_MIDDLE 397
#define MT19937_MASK_UPPER 0x80000000U
#define MT19937_MASK_LOWER 0x7FFFFFFFU
#define MT19937_MASK_TWIST 0x9908B0DFU
#define MT19937_MULTIPLIER 0x6C078965U
#define MT19937_TEMPER_B 0x9D2C5680U
#define MT19937_TEMPER_C 0xEFC60000U
#define MT19937_TEMPER_D 0xFFFFFFFFU
#define MT19937_TEMPER_I 18
#define MT19937_TEMPER_S 7
#define MT19937_TEMPER_T 15
#define MT19937_TEMPER_U 11

typedef uint32_t Word;

static struct
{
    Word state[MT19937_STATE_LENGTH];
    int index;
}
mt19937 =
{
    {
        0x00001571U, 0x4D98EE96U, 0xAF25F095U, 0xAFD9BA96U, 0x6FCBD068U, 0x2CD06A72U, 0x384F0100U, 0x85B46507U,
        0x295E8801U, 0x0D1B316EU, 0x7B305E70U, 0xBDB6BBA0U, 0x1CEFB8F6U, 0x8B499F1BU, 0x3FDF25EBU, 0xCBC1B8C6U,
        0x38B252C9U, 0xDC273A5EU, 0xAE40CBC3U, 0x6AE1AC38U, 0xB1C27391U, 0x5E964414U, 0x744B195FU, 0x6BC6502DU,
        0x67592D74U, 0x19B58C42U, 0xFA7DA824U, 0x1FA1367EU, 0x6635EDD2U, 0xB451BF5CU, 0xC73BCE34U, 0x7374CAD2U,
        0x9D63F05FU, 0x629A99D2U, 0xDC159B61U, 0xFC5BBFCDU, 0xD079EA6AU, 0x336AAC92U, 0xAF6E37C0U, 0x90A0D1B1U,
        0x5F9086C7U, 0x438F2247U, 0xB8B9FBC8U, 0x83A570DDU, 0xA3C5DF27U, 0x377ED6C6U, 0x2D64B24CU, 0xBC39042BU,
        0x2ED7955DU, 0x2B87B2E2U, 0x0772855CU, 0xAF10D97FU, 0xC474B385U, 0x66C78A13U, 0xB41B1B50U, 0xE78EA991U,
        0xEF0608D2U, 0xF1D053AEU, 0x29B3987BU, 0x9FD1FBC2U, 0x4FD212FCU, 0x2AF5E30EU, 0xA6E712C4U, 0x8DA05E5DU,
        0x5B5F12BBU, 0xE89DEDA3U, 0x49D96062U, 0xDE0D0252U, 0xCD964339U, 0xD4D89027U, 0xFF90227AU, 0xF39F5B04U,
        0xD6C6A90BU, 0x0C0DF871U, 0xB28E7DDFU, 0x609DED7CU, 0xDCD1979DU, 0x16265FA3U, 0xA7C6F69DU, 0x7DD3640AU,
        0x253D5BA7U, 0x7CD28834U, 0xFF671A3BU, 0x483D506BU, 0x3B1F7426U, 0x5D9B2953U, 0xB0922FB0U, 0x4B111391U,
        0x0A24C828U, 0x08B86021U, 0xA916965FU, 0x24EC180CU, 0xA257E918U, 0x7023E19FU, 0x453791B4U, 0x63D959C8U,
        0xF64BFDADU, 0x2E7F3407U, 0xCB384625U, 0x3DC80361U, 0x6D5F3EA9U, 0xB5B3A0ADU, 0x09A50C71U, 0x24DD61FCU,
        0x02AB84D4U, 0xE98CDC0DU, 0x72B84FF0U, 0xC1168380U, 0x16D7FE1BU, 0xF0F0B414U, 0x7FF85C81U, 0xEDFCFEEFU,
        0xD1B0DF8CU, 0xD354BADCU, 0xE888116DU, 0x7104BED9U, 0x78E8E3ACU, 0x8B7468B6U, 0x1DE1A37AU, 0x7AD7C999U,
        0x952CE170U, 0x2178F473U, 0x22AEFCD9U, 0xCA48E318U, 0x6A080D23U, 0xD82260E7U, 0x81A63E72U, 0x131092AFU,
        0x3AD2868BU, 0x30DC7858U, 0xADCA933AU, 0xA03D0D9BU, 0xCF8C3EE1U, 0x0029C1AFU, 0x88E91191U, 0x3D609A86U,
        0xAB78AD66U, 0x2922ECFDU, 0x2285E55BU, 0xF00E3072U, 0x4C9C9621U, 0xA0FE5B2DU, 0xF56F2119U, 0x2D44F9D1U,
        0xC69E6905U, 0x89DDA5EFU, 0x87B94C13U, 0xF6471C48U, 0xA23F4D2BU, 0x4B6362C2U, 0xE5655285U, 0x83CD4575U,
        0xF46A178BU, 0x392B1141U, 0x7F00983FU, 0xBE673F11U, 0x1D020E1BU, 0x52190444U, 0x010A9CD7U, 0x14FFF072U,
        0xEBC4DF9AU, 0x098418FEU, 0x496FCAD8U, 0xE4982940U, 0x02F22313U, 0xB7D20224U, 0x000B2FA4U, 0x7E64905BU,
        0x99631E2AU, 0x42564E71U, 0xC116E2DAU, 0x2D5CA148U, 0x40D32A14U, 0x9767D7F6U, 0x2635C7F2U, 0x6AD66529U,
        0x86D05178U, 0x5E206FD3U, 0x2561808CU, 0x8116A3EFU, 0x83238235U, 0x8132CF68U, 0x8DF18F88U, 0x6AE47C29U,
        0xB7AE6480U, 0x63253A03U, 0x77C8F584U, 0xA0500B34U, 0x2C0E530AU, 0x895D1DAFU, 0xD2594AFFU, 0x233F722BU,
        0x1F4E0EB7U, 0xBAACBDF4U, 0x118998D0U, 0x7BC09AD3U, 0xB995779EU, 0x4A3EAD51U, 0x52AA3156U, 0xBEEE071AU,
        0x075CA540U, 0x00BC7309U, 0x15283457U, 0xFF40361EU, 0xC815DF3DU, 0xE7CB4243U, 0x0965640EU, 0x9BEDF855U,
        0x5D2A8A23U, 0xA4A2B23BU, 0xF11FD24FU, 0xF92CA4CFU, 0xC4623150U, 0x6467E194U, 0x3BC7BD9FU, 0xBDA0E792U,
        0x01576CA8U, 0x293BC721U, 0xA00D39DFU, 0x0A3A1A0CU, 0xE730B398U, 0x9391D004U, 0x7904493CU, 0xC68D8AF0U,
        0x65D8DDBFU, 0x756C2AD7U, 0xAA736D50U, 0x9A49043DU, 0xA3CD64BFU, 0x081CE476U, 0xB0E34974U, 0x36362275U,
        0xA8FF3611U, 0xBF258168U, 0xBDF3C9BCU, 0x145746E1U, 0x978460B1U, 0xC7DEF28CU, 0x20AD3A59U, 0xBD00A70CU,
        0x640A6776U, 0x11BA81E4U, 0x8B5443E6U, 0x1BCFCDE7U, 0x437DDC17U, 0x48099BA3U, 0x298219E0U, 0x354D1657U,
        0x98BF604BU, 0x1C070EC6U, 0xC51ACB18U, 0x0C0095A2U, 0x7BBCBBE6U, 0x6955C220U, 0xAEA04103U, 0xDB0A2F64U,
        0x9E33D3A3U, 0xDC1AA886U, 0xD256AA7BU, 0xA6B37A5BU, 0xB5B7E721U, 0x3234ECD4U, 0x0B6AE4AAU, 0xAE313219U,
        0xCFF638AFU, 0xED2C68E5U, 0x3CF279C8U, 0x834E14F3U, 0xD59A3D21U, 0xD47F5177U, 0x22FE37D2U, 0xF8E968E9U,
        0xB3A19F62U, 0x38AE41F1U, 0x17A0FE27U, 0xE1982576U, 0xCF45653DU, 0xD641208BU, 0xA5D29EBEU, 0xCA2F3D43U,
        0xB92A6B58U, 0xA8A5859BU, 0x50FB9777U, 0x838AE8A9U, 0xBCFE4F93U, 0x01E0FE52U, 0xB21C3978U, 0x6A3AF841U,
        0x41DE3260U, 0x3246CA66U, 0x49087160U, 0x5AA8A568U, 0xD6ED7491U, 0xA70F20BFU, 0xA2A810B7U, 0xEE327590U,
        0x35D90F27U, 0x45CFDA8CU, 0x3CD1AFCBU, 0xA85AFF42U, 0x193FF56CU, 0x7686A0C9U, 0x94A07816U, 0x3C1E1513U,
        0x68AA7CAFU, 0x58BE4FD7U, 0x52A906A0U, 0x2BA2C7B8U, 0x6A2244CCU, 0x93F1DB16U, 0x3A35241AU, 0x5BFF2979U,
        0x9B249590U, 0x787825D3U, 0x74624F14U, 0x8CAE7184U, 0x7E3D811AU, 0xA41863E4U, 0x8E5F80FCU, 0xF6A7D375U,
        0xB09A94CEU, 0x8831E1BDU, 0x2DB6489DU, 0xCE11AC34U, 0xABA361F7U, 0x3094C3EEU, 0x8B0DAC2CU, 0x4ACB8D6DU,
        0xDEF198E4U, 0xE275F36CU, 0xF3D87315U, 0x77962EF9U, 0x762B4124U, 0x28F081E6U, 0x71B1570CU, 0x9FE84E70U,
        0xA5BFF64AU, 0x3B80B3B9U, 0x5003EA4FU, 0xFA113019U, 0x243BE596U, 0xE898DB83U, 0x92461AD6U, 0x65D00AFBU,
        0x45CA1FFAU, 0x77B8F260U, 0xC2548A9FU, 0x83CC2CE7U, 0x19D744B5U, 0xA2A5F9C6U, 0x82816FB2U, 0x0FA641CFU,
        0x4678BF0BU, 0xDD25BA53U, 0x48C752F2U, 0x2AACC642U, 0x90118B6EU, 0x9A7CCF01U, 0xAB1B4895U, 0xCBBD73FAU,
        0xFC9E03A5U, 0x5BD547E7U, 0x5DE97528U, 0x7CED2B98U, 0xF31615C9U, 0x89E5B41FU, 0x7DCE95DFU, 0xF1C6F005U,
        0xF219E9CEU, 0x42F2F452U, 0x20DFD131U, 0x2397C2C8U, 0xF594E25CU, 0xD57B27F0U, 0xBD9CCF55U, 0x19345DCAU,
        0xC0601C2AU, 0x661C0EA6U, 0x277A285DU, 0x4956B32CU, 0x3752C73DU, 0x4EF3418EU, 0x72F765E9U, 0x6A7C5E07U,
        0xAB8C4FDEU, 0xC41C3F4DU, 0x2027B948U, 0x62CBA2EBU, 0x20EC81D6U, 0x63A4C0F3U, 0xD9DFA300U, 0x5C8CECB6U,
        0x9B4854BBU, 0x55EF6F86U, 0x0AD740CDU, 0xBA35476CU, 0x56410DF2U, 0xBDC68D6CU, 0x6707ABF4U, 0xD0BFF638U,
        0xB61EB9D7U, 0x3C654F9AU, 0x30C7D354U, 0x663A55B7U, 0xACDC3862U, 0x17AD9F75U, 0xFA0887BFU, 0x3C252AC3U,
        0x0DE13B87U, 0x9768BCDCU, 0x9B775330U, 0x8FF79655U, 0x1C83E0EFU, 0xCDF0A6E8U, 0xBDB29F55U, 0x7E1F6DF2U,
        0x19E26D7FU, 0xF5672BBCU, 0xCE567AFDU, 0x34E275D9U, 0xD358A141U, 0x1111F2AFU, 0xCDBD67B1U, 0x76162CE1U,
        0x2EE39608U, 0xC54C7AD1U, 0xB8A4D884U, 0x84932489U, 0xB068CF83U, 0xC8ECE892U, 0x95E45BE3U, 0xC76AAA74U,
        0x9F8FF1A3U, 0x83807F36U, 0x10310536U, 0x8B9AF601U, 0xFFDFABE3U, 0xD959B115U, 0xDFC1A564U, 0xE2BB625AU,
        0xF7FE6FD5U, 0x5815A727U, 0xF10849B8U, 0x6FD72B82U, 0xBAC2476BU, 0xE6BC5F2AU, 0xBD5D7DEBU, 0x7BA35FACU,
        0xCF635601U, 0x2D46028BU, 0x09C86599U, 0x6D9DF820U, 0x7E038FC9U, 0xEDD1C3ADU, 0xD73C536CU, 0x4F7C5392U,
        0x31CBA5C7U, 0x1D80E84CU, 0x0A4053C6U, 0x4AA004E9U, 0x161A1954U, 0xD125F3F1U, 0x9723C248U, 0x4C1B4301U,
        0x729C70D0U, 0x31CF5D46U, 0xB4A44470U, 0x248E04CDU, 0x0A349BB5U, 0xCC084D3EU, 0xC9471FE7U, 0x885C9ACBU,
        0x62DDA425U, 0x4B45080DU, 0xEBDE9A96U, 0x459FBBA4U, 0xB0F356F5U, 0x9E4C8050U, 0x7F188438U, 0xECFDAD5CU,
        0x13763F5BU, 0x150BB3C8U, 0xDB4BF7CAU, 0xBF125530U, 0x9E31609EU, 0x4A729B71U, 0x34764516U, 0x293C0995U,
        0x84E386B1U, 0x63BEF188U, 0xF0569DF7U, 0x6E5FE72FU, 0x98CFD512U, 0x1674A13DU, 0x6AF843FFU, 0x1447C325U,
        0x59C1CC89U, 0x17A27B99U, 0x346EA64FU, 0xC6D0E61EU, 0xC25B5065U, 0xC6D75033U, 0x1E2C54E6U, 0xFB3696B5U,
        0x3A2ADDC6U, 0x7C027717U, 0xC84DC3A8U, 0x2211B772U, 0x084763F6U, 0xFC63180BU, 0xA32CC526U, 0xEA260D33U,
        0x5A61E5F0U, 0x0244B316U, 0xD68B6FB0U, 0xD5AEDEA2U, 0xE5890089U, 0x1C1D1277U, 0x5B9AF9F9U, 0x89B258DFU,
        0x6EF65639U, 0x96DBFE21U, 0xF6C100D9U, 0xA190020DU, 0x3153D8F7U, 0x77F1CA80U, 0xAD4AEFF3U, 0xB48FA524U,
        0xA817800EU, 0x751FF2CDU, 0x021DF88EU, 0x93B91019U, 0x265ECFBBU, 0x72B009DCU, 0xF5C62B47U, 0xE33277EBU,
        0xCC6C78A0U, 0xC3CFD568U, 0x74227851U, 0x4E2C49ABU, 0x468B0C2EU, 0x67A9F7A8U, 0xED3728CBU, 0x990E2107U,
        0xF561B619U, 0x0CB6C463U, 0xF5E97831U, 0x57CD2FDDU, 0x91949FF0U, 0x70D99E9FU, 0xFA10247CU, 0xDF5F5F42U,
        0x31615FCDU, 0xB24A830AU, 0x2CBCFC52U, 0x47D57085U, 0x54080A40U, 0x286FD6D2U, 0x45D42508U, 0xE3C36FBCU,
        0x15214F8BU, 0xFA82C708U, 0xE76A6C89U, 0x70D8AEA5U, 0x716EACE8U, 0x0191EB22U, 0x7B54F8A0U, 0xD9FB42BCU,
        0xDE128E93U, 0x318D5109U, 0x305DCBC7U, 0xCD7FE6BEU, 0x911C2FCDU, 0xF85DA5E8U, 0xC82A3AF5U, 0xF6F0EB4DU,
        0xB21B9606U, 0xD24655D5U, 0x3A8965B0U, 0xA77050B3U, 0x0B559119U, 0xC717A222U, 0x8CFDA24BU, 0x97E91A14U,
        0xAC8712F6U, 0xCF1B108DU, 0x8D6B8850U, 0xA99EACA5U, 0x02907F2FU, 0xA55B56D8U, 0x7679F050U, 0xBDEE2B44U,
        0x1B098AEEU, 0xFA9F3037U, 0x5305DAD6U, 0x934D6826U, 0x93415C88U, 0xD3155EC7U, 0xFE8149AAU, 0xE90C8304U,
        0x2D3F731BU, 0x585EDF00U, 0x27CC86BFU, 0x6B0662B6U, 0x8B59E38FU, 0xCA183DFEU, 0x22A7DC2FU, 0x5A5807EAU,
        0x1C64E517U, 0x2A08B374U, 0x15A3E326U, 0x7C41F661U, 0x8F7F9644U, 0x88ABC203U, 0x909D15CBU, 0x83212BB4U,
        0x7674A736U, 0xF0036A1CU, 0x7FFC77A5U, 0x101DFA1FU, 0x518747A7U, 0x8D411CEBU, 0xA9881B5BU, 0x04C46D8CU,
    },
    MT19937_STATE_LENGTH,
};

/******************************************************************************
 * Seed MT19937. If this function is not called, the initial state is the same
 * as if it were seeded with 5489.
 *
 * @param seed 32-bit number. If this is 0, MT19937 will be seeded with the sum
 *     of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_seed(Word seed)
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
        Word shifted = mt19937.state[i - 1] >> (MT19937_WIDTH - 2);
        mt19937.state[i] = MT19937_MULTIPLIER * (mt19937.state[i - 1] ^ shifted) + i;
    }
    mt19937.index = MT19937_STATE_LENGTH;
}

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 32-bit number.
 *****************************************************************************/
Word mt19937_rand(void)
{
    // Twist.
    if(mt19937.index == MT19937_STATE_LENGTH)
    {
        mt19937.index = 0;
        Word twist[] = {0, MT19937_MASK_TWIST};

        // I benchmarked this function and found that a single loop with modulo
        // operations runs slower than this.
        for(int i = 0; i < MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; ++i)
        {
            Word upper = MT19937_MASK_UPPER & mt19937.state[i];
            Word lower = MT19937_MASK_LOWER & mt19937.state[i + 1];
            Word masked = upper | lower;
            Word twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE] ^ twisted;
        }
        for(int i = MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; i < MT19937_STATE_LENGTH - 1; ++i)
        {
            Word upper = MT19937_MASK_UPPER & mt19937.state[i];
            Word lower = MT19937_MASK_LOWER & mt19937.state[i + 1];
            Word masked = upper | lower;
            Word twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE - MT19937_STATE_LENGTH] ^ twisted;
        }
        Word upper = MT19937_MASK_UPPER & mt19937.state[MT19937_STATE_LENGTH - 1];
        Word lower = MT19937_MASK_LOWER & mt19937.state[0];
        Word masked = upper | lower;
        Word twisted = (masked >> 1) ^ twist[masked & 1];
        mt19937.state[MT19937_STATE_LENGTH - 1] = mt19937.state[MT19937_STATE_MIDDLE - 1] ^ twisted;
    }

    // Generate.
    Word curr = mt19937.state[mt19937.index++];
    curr ^= (curr >> MT19937_TEMPER_U) & MT19937_TEMPER_D;
    curr ^= (curr << MT19937_TEMPER_S) & MT19937_TEMPER_B;
    curr ^= (curr << MT19937_TEMPER_T) & MT19937_TEMPER_C;
    curr ^= curr >> MT19937_TEMPER_I;
    return curr;
}

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of a C++
 * standard library implementation. See
 * https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.
 *
 * @return Whether the test passed or not.
 *****************************************************************************/
bool mt19937_test(void)
{
    mt19937_seed(5489);
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_rand();
    }
    return mt19937_rand() == 0xF5CA0EDBU;
}

/******************************************************************************
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 32-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
Word mt19937_rand_integer(Word modulus)
{
    Word upper = 0xFFFFFFFFU - 0xFFFFFFFFU % modulus;
    Word r;
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
void mt19937_rand_shuffle(void *items, Word items_length, size_t item_size)
{
    char *temp = malloc(item_size);
    char *items_ = (char *)items;
    for(Word i = items_length - 1; i > 0; --i)
    {
        Word j = mt19937_rand_integer(i + 1);
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
