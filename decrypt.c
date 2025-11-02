#include "headers.h"

void decrypt(FILE *in, FILE *out)
{
    unsigned char buf[8];
    size_t n;
    while ((n = fread(buf, 1, 8, in)) > 0)
    {
        if (n < 8)
        {
            fwrite(buf, 1, n, out);
            break;
        }

        unsigned char src = buf[7];

        for (int i = 0; i < 7; ++i)
        {
            int bitPos = 7 - i;
            int srcBitPos = 6 - i;
            unsigned char a_bit = (buf[i] >> bitPos) & 1;
            unsigned char b_bit = (src >> srcBitPos) & 1;
            if (a_bit != b_bit)
            {
                buf[i] ^= (1u << bitPos);
                src ^= (1u << srcBitPos);
            }
        }

        buf[7] = src;
        fwrite(buf, 1, 8, out);
    }
}
