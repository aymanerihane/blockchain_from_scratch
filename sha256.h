/*
*   SHA-256 implementation.
*
*   Copyright (c) 2010,2014,2018,2021,2022 Willem H. Hengeveld <itsme@xs4all.nl>
*
*   This code is released under the MIT license.
*
*   This is a plain C implementation of the SHA-256 algorithm.
*   It has been written to be as clear as possible, with a focus on
*   the algorithm itself, and not on performance.
*
*   The most recent version of this code can be found at:
*   https://github.com/whe-its-me/sha256
*
*/
#ifndef SHA256_H
#define SHA256_H
#include <stdint.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

// The algorithm can be defined to use 32-bit or 64-bit words,
// and to use a big-endian or little-endian representation.
//
// The algorithm is designed for 32-bit words.
//
// The 64-bit version is slower, and is only included for demonstration purposes.
// The little-endian version is slower on big-endian machines.
//
// default is 32-bit, big-endian
//
// to use the 64-bit version, define SHA256_USE_64BIT
// to use the little-endian version, define SHA256_USE_LITTLE_ENDIAN
//
// (note: the little-endian version is not yet implemented)

#ifdef SHA256_USE_64BIT
typedef uint64_t sha256_word;
#else
typedef uint32_t sha256_word;
#endif

typedef struct {
    sha256_word h[8];
    uint64_t size;
    sha256_word W[16];
    uint8_t buflen;
} sha256_context;

void sha256_init(sha256_context *ctx);
void sha256_update(sha256_context *ctx, const uint8_t *data, size_t len);
void sha256_final(sha256_context *ctx, uint8_t *hash);  // hash is a 32-byte array

// convenience function
void sha256_hash(const uint8_t *data, size_t len, uint8_t *hash);

#ifdef __cplusplus
}
#endif

std::string sha256(const std::string& str);

#endif
