/*	$OpenBSD: bcrypt.c,v 1.55 2015/09/13 15:33:48 guenther Exp $	*/

/*
 * Copyright (c) 2014 Ted Unangst <tedu@openbsd.org>
 * Copyright (c) 1997 Niels Provos <provos@umich.edu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/* This password hashing algorithm was designed by David Mazieres
 * <dm@lcs.mit.edu> and works as follows:
 *
 * 1. state := InitState ()
 * 2. state := ExpandKey (state, salt, password)
 * 3. REPEAT rounds:
 *      state := ExpandKey (state, 0, password)
 *	state := ExpandKey (state, 0, salt)
 * 4. ctext := "OrpheanBeholderScryDoubt"
 * 5. REPEAT 64:
 * 	ctext := Encrypt_ECB (state, ctext);
 * 6. RETURN Concatenate (salt, ctext);
 *
 */

#include "types.h"
#include "user.h"

#define NULL 0

#include "bcrypt.h"
#include "blf.h"

int
timingsafe_bcmp(const void *b1, const void *b2, size_t n)
{
    const unsigned char *p1 = b1, *p2 = b2;
    int ret = 0;

    for (; n > 0; n--)
        ret |= *p1++ ^ *p2++;
    return (ret != 0);
}

/*
 * the core bcrypt function
 */
int
bcrypt_hashpass(const char *key, const uchar *csalt, uchar *encrypted, uint8_t logr)
{
	blf_ctx state;
	u_int32_t rounds, i, k;
	u_int16_t j;
	size_t key_len;
	u_int8_t salt_len;
	u_int8_t ciphertext[4 * BCRYPT_WORDS] = "OrpheanBeholderScryDoubt";
	u_int32_t cdata[BCRYPT_WORDS];

    /* strlen() returns a size_t, but the function calls
     * below result in implicit casts to a narrower integer
     * type, so cap key_len at the actual maximum supported
     * length here to avoid integer wraparound */
    key_len = strlen(key);
    if (key_len > 72)
        key_len = 72;
    key_len++; /* include the NUL */

	if (logr < BCRYPT_MINBCRYPT_DEFAULT_LOGROUNDS || logr > 31)
		goto inval;
	/* Computer power doesn't increase linearly, 2^x should be fine */
	rounds = 1U << logr;
	salt_len = BCRYPT_SALTLEN;

	/* Setting up S-Boxes and Subkeys */
	Blowfish_initstate(&state);
	Blowfish_expandstate(&state, csalt, salt_len,
	    (u_int8_t *) key, key_len);
	for (k = 0; k < rounds; k++) {
		Blowfish_expand0state(&state, (u_int8_t *) key, key_len);
		Blowfish_expand0state(&state, csalt, salt_len);
	}

	/* This can be precomputed later */
	j = 0;
	for (i = 0; i < BCRYPT_WORDS; i++)
		cdata[i] = Blowfish_stream2word(ciphertext, 4 * BCRYPT_WORDS, &j);

	/* Now do the encryption */
	for (k = 0; k < 64; k++)
		blf_enc(&state, cdata, BCRYPT_WORDS / 2);

	for (i = 0; i < BCRYPT_WORDS; i++) {
		ciphertext[4 * i + 3] = cdata[i] & 0xff;
		cdata[i] = cdata[i] >> 8;
		ciphertext[4 * i + 2] = cdata[i] & 0xff;
		cdata[i] = cdata[i] >> 8;
		ciphertext[4 * i + 1] = cdata[i] & 0xff;
		cdata[i] = cdata[i] >> 8;
		ciphertext[4 * i + 0] = cdata[i] & 0xff;
	}

    memmove(encrypted, ciphertext, sizeof(ciphertext));
    /* Clear sensitive data */
    memset(ciphertext, 0, sizeof(ciphertext));
	memset(&state, 0, sizeof(state));
	memset(cdata, 0, sizeof(cdata));
	return 0;

inval:
	return -1;
}

/*
 * user friendly functions
 */
int
bcrypt_checkpass(const char *pass, const uchar *salt, const uchar *goodhash)
{
	uchar hash[BCRYPT_HASHLEN];

	if (bcrypt_hashpass(pass, salt, hash, BCRYPT_DEFAULT_LOGR) != 0)
		return -1;
	if (timingsafe_bcmp(hash, goodhash, BCRYPT_HASHLEN) != 0) {
		return -1;
	}

	memset(hash, 0, sizeof(hash));
	return 0;
}

/*
 * classic interface
 */
uchar *
bcrypt(const char *pass, const uchar *salt)
{
	static uchar gencrypted[BCRYPT_HASHLEN];

	if (bcrypt_hashpass(pass, salt, gencrypted, BCRYPT_DEFAULT_LOGR) != 0)
		return NULL;

	return gencrypted;
}
