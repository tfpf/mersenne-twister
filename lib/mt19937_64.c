#include <inttypes.h>
#include <time.h>
#include <unistd.h>

#include "mt19937_64.h"

#define MT19937_WIDTH 64
#define MT19937_STATE_LENGTH 312
#define MT19937_STATE_MIDDLE 156
#define MT19937_MASK_UPPER 0xFFFFFFFF80000000U
#define MT19937_MASK_LOWER 0x000000007FFFFFFFU
#define MT19937_MASK_TWIST 0xB5026F5AA96619E9U
#define MT19937_MULTIPLIER 0x5851F42D4C957F2DU
#define MT19937_TEMPER_B 0x71D67FFFEDA60000U
#define MT19937_TEMPER_C 0xFFF7EEE000000000U
#define MT19937_TEMPER_D 0x5555555555555555U
#define MT19937_TEMPER_I 43
#define MT19937_TEMPER_S 17
#define MT19937_TEMPER_T 37
#define MT19937_TEMPER_U 29

typedef uint64_t Word;

static struct
{
    Word state[MT19937_STATE_LENGTH];
    int index;
}
mt19937 =
{
    {
        0x0000000000001571U, 0xB5347F47116BD3DEU, 0x9165B5762D1A61AEU, 0xD139B6BBED337F3FU,
        0x37E740001C182190U, 0xE398F84731B45655U, 0x097392E1FB95D724U, 0x102FF8F17705AD5BU,
        0xAFD3B741A6F69E07U, 0x3673B7B326A741EAU, 0x967BEFB79A4BAC2CU, 0x81579A10887E1621U,
        0xFA4F68BAD1844133U, 0xD26A818BA186457DU, 0x58EA399ADB69B934U, 0x7BE61CE78C4FD960U,
        0x6520FC5E9855551DU, 0xC641EF0DF584D9FDU, 0xE8B0B2F1595553B8U, 0x2ACC772248607CF2U,
        0xE21A56B927CC049EU, 0x222B48008087B2AEU, 0xCFFD407690C4BAACU, 0x185E6D58A70CA1DAU,
        0xA47F692D8D65996AU, 0xD80BA31C6B7E8F61U, 0xB35584C73A6AD254U, 0x92AAD4BC372DA339U,
        0x59C35BD9DC56F67BU, 0x5FEEE4D68C91D98FU, 0xA20C5CE2D836B014U, 0x6EE0DD1C27C5DDFDU,
        0x8A81EF0B2A94096CU, 0xA161CA6211B93A77U, 0x2A3A52C2C3A851B3U, 0x8CD8FCFC964D299AU,
        0x039559F108AAB7DCU, 0xAA981E498A4475D1U, 0x47B66D6F7C4B633DU, 0x9FF6E624D16735B3U,
        0x7F7D617ACECC3F45U, 0x38FCFDCAAFDDDB1DU, 0x14928B261D93E743U, 0xFE6000E410B8E3F2U,
        0xB208B107E0D9A089U, 0x82F135B131CD2D9CU, 0x987DDA96FFA866F4U, 0xE1EBB23270DC236DU,
        0x02F775D6534BCC86U, 0x2916B16310C76DBFU, 0x8BB8A2F776AB0BC5U, 0x7ED20066A5BBCB2EU,
        0xBF99B825822A0877U, 0x175137B563AE87C6U, 0x8ED13207E9471804U, 0xC8BE8AAF09E83345U,
        0xD6F2A55B8EFEBD86U, 0x33EC6BF14D354B9AU, 0x1AA08340BB81B04CU, 0x658C3F94787DB197U,
        0x3E32761E6D7FA19AU, 0xB6DFAB00573CCE4FU, 0xC4EDB5826ED976C7U, 0x9E186133AE391CB3U,
        0xC8B2D463344ADA5DU, 0x01182F4C543304C7U, 0xB99FD847F829903DU, 0xB5ADE6D9E6889C56U,
        0x53F2F45B38752708U, 0x9E6E49666F3253DAU, 0xFC88FE527028E53EU, 0x0B8275B6896A8F00U,
        0x6964FFBB3FAC2348U, 0x957EC9FFCC406B1EU, 0x8149ED8183C1B836U, 0x0B6423B4E9B32D6FU,
        0x8FEA06065DA40DCFU, 0x737C3D30BD002056U, 0x800B954BEFB3D899U, 0x0F91A17D7148F88EU,
        0x23044078EFC82346U, 0xD2413979BF6BED9FU, 0x3C786924CCA528BEU, 0x147B229D06D46BB9U,
        0xCAC949203374B6D9U, 0xB47359B9171C4AA7U, 0x7AB3D4A18709FA57U, 0x82C40AA0EBFFAB75U,
        0x877A85FE72442D43U, 0xDAB66FF48B4433C6U, 0x4BF32AC4EE54D4FBU, 0x6A57D5662813764DU,
        0xF2E186A51D577FB8U, 0x368B524C6C96393CU, 0x4BFA6D46BCB8D3EAU, 0x5D423FDAF965D5AEU,
        0x19C09AAFAEC36123U, 0xF8BB804992E77088U, 0x0DF7875C686ABDD1U, 0x7741AB42D5930D20U,
        0x429CFBFCEE91AE31U, 0xBE763EC0D6F56ED5U, 0x9AC91415E2442531U, 0x2CCA75C45F1DD75EU,
        0xC5CDCA88C7CC7DEEU, 0xB0887B3A385BB612U, 0x2B73D36F1EC0F13AU, 0xB73E27E5BE582D9DU,
        0x113C84A0F5ACE65FU, 0x8F1386E53EF8A020U, 0xCD9074C2B4EF0468U, 0x5B702538B77BDC3EU,
        0xDC4A018B97B3F883U, 0x9B0BEDD1956A2EF1U, 0xAAB8206B6863CE29U, 0x999B98859FD99302U,
        0x9E999210982BD774U, 0x46B1D5A1EF466A33U, 0x06F16177A5297940U, 0x248F3E5A2DB110B7U,
        0x8B1F37B4EDEDB9A3U, 0x8FB8B09C989580C6U, 0x9A8C5EEB1F3CDEEEU, 0x04BAB3EB7FA643F7U,
        0x68327B16CEB47BE7U, 0x652AD6D0440EE1EBU, 0xF57FDA3C4DE2CCA0U, 0x247245A5B341D626U,
        0xE8012FA117ED7F2EU, 0x31E6F8156807AE6AU, 0x5524BF4114923F24U, 0x89ECA903E7917504U,
        0x9D78E605C21D8C92U, 0x8213008D57BD25D5U, 0x2845027D1C285051U, 0x88CF2E81BE134DC4U,
        0xE59A4A3B0937E656U, 0xA14CCCCEA590A87AU, 0x8A7FD0C38BD925A2U, 0xC505AE6EB4F5FDABU,
        0x1EDAA63E5ADBEF14U, 0x48086B892AE7F311U, 0x2CE7C25ED4AAAA5EU, 0x6A9E329B1D3A9515U,
        0xBE9684A2E7E52114U, 0xEAB0E8BA387EBB6FU, 0xE7CBAE25F31D868EU, 0x5581BF318E019A5CU,
        0xB07E184435FD45EDU, 0x20BACEF5CB51DC98U, 0xAAAA9BECDE4B2F4EU, 0x898B5F1376EA04F3U,
        0xCB65A0736BDB6DF5U, 0x47E02E65D94D5ED7U, 0x99EAC4824F33D638U, 0xA1C29D298B256ECDU,
        0x245B1C66FA082BFFU, 0x0252CFC850AE3D70U, 0x16CD2293A14B5D4EU, 0x3EE1503E33EF1955U,
        0x411AA452B9119F91U, 0x2D092B4AE5117CF1U, 0x3518F270355385FFU, 0x29E0B76580930F76U,
        0xF0A7458D96334262U, 0x67E039FE4365CAB2U, 0x44E9050476A26F1DU, 0x699496166AF86C93U,
        0x67B9C17E94818452U, 0x888E102E03B87040U, 0x362F3B3615867A44U, 0x7E3BFEB4D8DF3A9FU,
        0xA2A5E27AE347B072U, 0xCAB81B257551945DU, 0x85F487D65AA7B734U, 0xE03C7226CDCCFF2DU,
        0x7ABEA8130D66ADC6U, 0x409B7F54841545ACU, 0xB4CAA3DBAEFF131BU, 0x69AC8CF4D6DCC318U,
        0x6937F56F4324B319U, 0xD607AB9D5F4463EDU, 0x64EF663B7E1EA38CU, 0x42C020326B96B380U,
        0x716D89EA729F8D65U, 0x7C9BCC7E4864774DU, 0x0F3CF65C9013AD16U, 0x32F951735C215799U,
        0x957D4B4A245E4DA1U, 0x23792FA9C0F68364U, 0x513D7EA15FB7B552U, 0x39598C32238E0D56U,
        0x69EBB23503A402DEU, 0x88E67CA2E10C22F4U, 0x0E3FE9F5F5A83000U, 0x13B37E3E8E6070C3U,
        0x36FC67836463900BU, 0x09452B8B245CC7B4U, 0x7B250E6D1725676AU, 0x090964F095284396U,
        0xF6FDB6270FE94C26U, 0xDDB691A7D651BE4AU, 0x087EE6B9A641AA9FU, 0x4EA774EF4FBADFBEU,
        0x95F18962A704165FU, 0xBB13159002F11226U, 0x0ECD03CC5B540D22U, 0x3206DF067D142DC9U,
        0xBC8AD6DC513FC425U, 0x02DAF03CA937D4ACU, 0x5325B57A496DB70EU, 0xCF2459C355D49F76U,
        0x18784E931C941365U, 0x67B50FBBC16F8496U, 0x1A17D4C753443861U, 0x44E65DD7176B08E4U,
        0x88F06F9E60832C19U, 0x8F1BCAE7B9A72698U, 0xEF6EDEA6BE2A2FECU, 0x242C4972354CFEDEU,
        0xB136D804D02EEFE2U, 0xBF2B2107FEA04B3DU, 0x9A0AD56EC72C7BF1U, 0xB93D00AF5CBE5796U,
        0x976C0FA2A40BD1E4U, 0x300689982613004FU, 0xFEE5D1ABC0793FC5U, 0x7B4402FBE23170B1U,
        0xF5F95EA820081FD4U, 0x4EF59E6B055C42B0U, 0x876EE01513528903U, 0x3F10A12D610E9514U,
        0x9F16EE630029216CU, 0x19DC0AAE8BD6733FU, 0xD78ED428BF8983FDU, 0x24481C0E1E7D3691U,
        0x7BC2A62C48798769U, 0x59455DF3B7116635U, 0x1DECAA44BC06C412U, 0xE6A918ABDEEF6619U,
        0x6CCE280718DDD982U, 0x7A5EFC4EEB2639F8U, 0x9E5E3BC1F667B8B7U, 0xC8CDEB5B023643C4U,
        0x6AAF80C7D5FCA3EFU, 0x3188FBD50441E3CBU, 0xE22F823748BDC0A5U, 0x3138119E548B3825U,
        0xC38A50F996DC3A79U, 0x1496CCB306BACE6BU, 0x0BB0709FC3845EC9U, 0x2F206397E0476150U,
        0x27B0EF753962CC0CU, 0xDDCE48436C93D319U, 0x1D011EFF01D80290U, 0xEB84DB89BA0DE44FU,
        0x47BEE5BB08EED65CU, 0x8EC2984E6E74D25AU, 0x2111807DEC1AA27AU, 0xE6593972804B1675U,
        0xF8DB47E2E8057DC2U, 0xE20BEF71FFAEDAF2U, 0x95CF8F03AA9F0C63U, 0x79AB1C95E58E4D14U,
        0x00C7CEA10B79F8B9U, 0xE5CF275A3681808EU, 0x0186D438819A8CD3U, 0xA07F84140ED66F22U,
        0x73C07F4F2A7269ACU, 0xDC3ECA59163A6776U, 0x9CC3BDF5D4B03B9FU, 0x655793981EEE5EA8U,
        0x00EEE5A1F5397BC5U, 0x306206F4252A7DB2U, 0xA76856B09D6D675CU, 0x0B5FBA080438CE99U,
        0xFE5824CB978738F9U, 0xC7681A86198B0B07U, 0xD24C1525113BECCAU, 0x2E5F20923EFD576CU,
        0x0ABA7458B2C2F314U, 0x74782A6B8D7FA79DU, 0xE85337951162DB86U, 0x2ED08AEA59B0927CU,
        0x257D3CBE6EE144E8U, 0x5C95CCD539D035E5U, 0x2652086C82099632U, 0x4104E68AE04C35E9U,
        0x24D531D37C2B92E8U, 0x9D3BD487D291EBE9U, 0xDD62129D7B770E71U, 0x178DCC8E0472192DU,
        0xABAC2FF665BCC10DU, 0xB19C269857AF61C8U, 0x543E2EE54DE967A8U, 0x1416F049FDD110DCU,
        0x9315644875291BD4U, 0x7DEED4AAB8970FC7U, 0x8FE2D9FE599F00F8U, 0xC5A651F36BF1331DU,
        0x923A2D2C4A37DF72U, 0x80ABB9250FDAD7DDU, 0xE7179F0A335A9461U, 0xEE9749446B92B469U,
        0x34FBBAF929FC4DD2U, 0xA875A67E2F2EDD1BU, 0xDA9BEEE5A6794597U, 0xBF791C35DBF9A837U,
        0x35E9E928282DDD85U, 0xBB5D9CD43B5DEC96U, 0x593BF0ACAA04033AU, 0xC65AE95C45A5D796U,
    },
    MT19937_STATE_LENGTH,
};

/******************************************************************************
 * Seed MT19937. If this function is not called, the initial state is the same
 * as if it were seeded with 5489.
 *
 * @param seed 64-bit number. If this is 0, MT19937 will be seeded with the sum
 *     of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_64_seed(Word seed)
{
    if(seed == 0)
    {
        seed = time(NULL) + getpid();
    }
    mt19937.state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        Word shifted = mt19937.state[i - 1] >> (MT19937_WIDTH - 2);
        mt19937.state[i] = MT19937_MULTIPLIER * (mt19937.state[i - 1] ^ shifted) + i;
    }
    mt19937.index = MT19937_STATE_LENGTH;
}

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 64-bit number.
 *****************************************************************************/
Word mt19937_64_rand(void)
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
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 64-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
Word mt19937_64_rand_integer(Word modulus)
{
    Word upper = 0xFFFFFFFFFFFFFFFFU - 0xFFFFFFFFFFFFFFFFU % modulus;
    Word r;
    do
    {
        r = mt19937_64_rand();
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
double mt19937_64_rand_real(void)
{
    return (double)mt19937_64_rand() / 0xFFFFFFFFFFFFFFFFU;
}
