/*-
 * Copyright (c) 2019-2026 Varnish Software AS
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * TLS client fingerprinting (JA3/JA4) API.
 * Opaque raw Client Hello blob; implementation in cache_tls_fingerprint.c.
 */

#include <openssl/ssl.h>
#include <stddef.h>

struct sess;
struct vtls_sess;

/* Free raw Client Hello blob; sets *praw = NULL. Safe if *praw == NULL. */
void VTLS_fingerprint_raw_free(void **praw);

/* Parse Client Hello into *out_raw. On success *out_raw is set and 0 returned; on failure -1. */
int VTLS_fingerprint_parse_clienthello(const unsigned char *buf, size_t len,
    void **out_raw);

/* Compute JA3 from tsp->ja3_ja4_raw into tsp->ja3. Returns 0 on success. */
int VTLS_fingerprint_get_ja3(SSL *ssl, struct sess *sp, struct vtls_sess *tsp);

/* Compute JA4 from tsp->ja3_ja4_raw into tsp->ja4, ja4_r, ja4_o, ja4_ro. Returns 0 on success. */
int VTLS_fingerprint_get_ja4(SSL *ssl, struct sess *sp, struct vtls_sess *tsp);
