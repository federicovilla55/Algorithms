// SHA1 implementation as described in the FIPS PUB 180-4 standard
// Nist Secure hash Standard: 
// https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.180-4.pdf 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 20  // SHA1 outputs a 20 byte digest

// SHA-1 Constants
#define K1 0x5A827999 //  0 <= t <= 19
#define K2 0x6ED9EBA1 // 20 <= t <= 39
#define K3 0x8F1BBCDC // 40 <= t <= 59
#define K4 0xCA62C1D6 // 60 <= t <= 79

// SHA-1 Initial Hash Value
#define H0 0x67452301;
#define H1 0xEFCDAB89;
#define H2 0x98BADCFE;
#define H3 0x10325476;
#define H4 0xC3D2E1F0;

typedef struct {
    uint8_t buff_data[64]; // To hold chunks of 64 bytes of input data
    uint32_t buffer_len; // length of the buffer
    unsigned long long tot_len; // total length of the input data
    uint32_t interm_state[5]; // This holds the intermediate values: A, B, C, D, E
} SHA1_CTX; // SHA1 Context Structure, to save the current state of the hashing

// To process a chunk of a message and update the Context Structure
void sha1_transform(SHA1_CTX *ctx, const uint8_t buff_data[]) {
    uint32_t a, b, c, d, e;
    
    uint32_t i = 0, j = 0;

    // Initializing message schedule array (generates first 16 words)
    uint32_t m[80]; 
    for (; i < 16; ++i, j += 4)
        m[i] = (buff_data[j] << 24) | (buff_data[j+1] << 16) 
                | (buff_data[j+2] << 8) | (buff_data[j+3]);
    
    // To generate the remaning elements of the array
    // from the values already created (generates remaining 64 words)
    for (; i < 80; ++i)
        m[i] = (m[i-3] ^ m[i-8] ^ m[i-14] ^ m[i-16]);

    // Retreive the current context structure
    a = ctx->interm_state[0];
    b = ctx->interm_state[1];
    c = ctx->interm_state[2];
    d = ctx->interm_state[3];
    e = ctx->interm_state[4];

    // Process the message schedule array
    for (i = 0; i < 80; ++i) {
        uint32_t t;
        if (i < 20) // Ch(x,y,z)=(x&y)^(!x&y) 
            t = ((b & c) | (~b & d))+K1+m[i];
        else if (i < 40) // Parity(x,y,z)=x^y^z
            t = (b ^ c ^ d)+K2+m[i];
        else if (i < 60) // Maj(x,y,z)=(x&y)^(x&z)^(y&z)
            t = ((b & c) | (b & d) | (c & d))+K3+m[i];
        else // Parity(x,y,z)=x^y^z
            t = (b ^ c ^ d)+K4+m[i];

        // Adds the left rotated "a" and "e" so that each bit
        // is contributing to the hash result
        t += ((a << 5) | (a >> 27))+e;

        // Updates variables to use in next cycle iteration
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    // Updates the context structure
    ctx->interm_state[0] += a;
    ctx->interm_state[1] += b;
    ctx->interm_state[2] += c;
    ctx->interm_state[3] += d;
    ctx->interm_state[4] += e;
}

// Initialize SHA1 Context Structure
void sha1_init(SHA1_CTX *ctx) {
    ctx->buffer_len = 0;
    ctx->tot_len = 0;
    ctx->interm_state[0] = H0;
    ctx->interm_state[1] = H1;
    ctx->interm_state[2] = H2;
    ctx->interm_state[3] = H3;
    ctx->interm_state[4] = H4;
}

// To updating the SHA-1 context with 64 bytes chunks of input
void sha1_update(SHA1_CTX *ctx, const uint8_t buff_data[], size_t len) {
    for (uint32_t i = 0; i < len; ++i) {
        ctx->buff_data[ctx->buffer_len] = buff_data[i]; // Updates buffer chunk
        ctx->buffer_len++;
        if (ctx->buffer_len == 64) { // BUffer is full
            sha1_transform(ctx, ctx->buff_data); // Process full buffer
            ctx->tot_len += 512;
            ctx->buffer_len = 0;
        }
    }
}

// To produce the final operations on the input data
void sha1_final(SHA1_CTX *ctx, uint8_t hash[]) {
    uint32_t i = ctx->buffer_len;

    // Padding the Data
    if (ctx->buffer_len < 56) {
        ctx->buff_data[i++] = 0x80;
        while (i < 56) ctx->buff_data[i++] = 0x00;
    } else {
        ctx->buff_data[i++] = 0x80;
        while (i < 64) ctx->buff_data[i++] = 0x00;
        sha1_transform(ctx, ctx->buff_data);
        memset(ctx->buff_data, 0, 56);
    }

    // Uses the modified input data as the 64 bits of the last block
    ctx->tot_len += ctx->buffer_len * 8;
    ctx->buff_data[63] = ctx->tot_len;
    ctx->buff_data[62] = ctx->tot_len >> 8;
    ctx->buff_data[61] = ctx->tot_len >> 16;
    ctx->buff_data[60] = ctx->tot_len >> 24;
    ctx->buff_data[59] = ctx->tot_len >> 32;
    ctx->buff_data[58] = ctx->tot_len >> 40;
    ctx->buff_data[57] = ctx->tot_len >> 48;
    ctx->buff_data[56] = ctx->tot_len >> 56;
    sha1_transform(ctx, ctx->buff_data);

    // For converting the internal hash state in the 20 bytes hash value.
    for (i = 0; i < 4; ++i) {
        // Each 32-bit word in the state is split into four 8-bit segments
        hash[i] = (ctx->interm_state[0] >> (24-i * 8)) & 0x000000ff;
        hash[i+4] = (ctx->interm_state[1] >> (24-i * 8)) & 0x000000ff;
        hash[i+8] = (ctx->interm_state[2] >> (24-i * 8)) & 0x000000ff;
        hash[i+12] = (ctx->interm_state[3] >> (24-i * 8)) & 0x000000ff;
        hash[i+16] = (ctx->interm_state[4] >> (24-i * 8)) & 0x000000ff;
    }
}

// To compute the SHA-1 hash of the data given as parameter
void sha1(const uint8_t *buff_data, size_t len, uint8_t result[BLOCK_SIZE]) {
    SHA1_CTX ctx; // To hold SHA1 context
    sha1_init(&ctx); // To initialize SHA1 context
    sha1_update(&ctx, buff_data, len); // Process given data
    sha1_final(&ctx, result); // Computes final hash value

    // "result" array will contain the calculated hash.
}

// Compute SHA-1 Hash of a File
void sha1_file(const char *filename, uint8_t result[]) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error while opening the file: %s", filename);
        return;
    }

    SHA1_CTX ctx; // To hold SHA1 context
    sha1_init(&ctx); // To initialize SHA1 context

    uint8_t buffer[1024]; // Creates file buffer
    size_t bytesRead; // To keep trace of how many bytes have been read in a single fread
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        sha1_update(&ctx, buffer, bytesRead);
    }
    fclose(file);

    sha1_final(&ctx, result);
    // "result" array will contain the calculated hash.

}

int main(int argc, char *argv[]) {
    
    // SHA-1 of a given string
    const char *buff_data = "Hey There!";
    uint8_t hash[BLOCK_SIZE];

    sha1((uint8_t *)buff_data, strlen(buff_data), hash);
    printf("SHA-1 of '%s' is: ", buff_data);
    
    // SHA-1 from given file 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    uint8_t hash[BLOCK_SIZE];
    sha1_file(argv[1], hash);
    printf("SHA-1 of %s file content is: ", argv[1]);


    for (int i = 0; i < BLOCK_SIZE; i++)
        printf("%02x", hash[i]);
    printf("\n");

    return 0;
}