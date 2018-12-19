typedef uchar uint8_t;
typedef uchar u_int8_t;
typedef ushort uint16_t;
typedef ushort u_int16_t;
typedef uint uint32_t;
typedef uint u_int32_t;
typedef uint size_t;

/* This implementation is adaptable to current computing power.
 * You can have up to 2^31 rounds which should be enough for some
 * time to come.
 */
#define BCRYPT_SALTLEN 16	/* Precomputation is just so nice */
#define BCRYPT_WORDS 6		/* Ciphertext words */
#define BCRYPT_MINBCRYPT_DEFAULT_LOGROUNDS 4	/* we have log2(rounds) in salt */
#define	BCRYPT_HASHLEN (BCRYPT_WORDS * 4)

#define BCRYPT_DEFAULT_LOGR 10

/* bcrypt_checkpass
 *   Check a password/salt combination to see if it matches an existing hash.
 *
 *   Parameters:
 *     pass: the password to check. Maximum 72 characters, null-terminated.
 *     salt: the salt to use with the hash. Must be exactly BCRYPT_SALTLEN bytes.
 *     goodhash: the hash to compare against. Must be BCRYPT_HASHLEN bytes long.
 *   Returns:
 *     0 if the passwords match, -1 otherwise
 */
int bcrypt_checkpass(const char *pass, const uchar *salt, const uchar *goodhash);

/* bcrypt
 *   Hash a password using the bcrypt algorithm.
 *   
 *   Parameters:
 *     pass: the password to hash. Maximum 72 characters, null-terminated.
 *     salt: a random salt to use with the hash. Must be exactly BCRYPT_SALTLEN
 *           bytes.
 *   Returns:
 *     A pointer to the hashed password (binary). The returned data is
 *     BCRYPT_HASHLEN bytes long.
 */
uchar * bcrypt(const char *pass, const uchar *salt);
