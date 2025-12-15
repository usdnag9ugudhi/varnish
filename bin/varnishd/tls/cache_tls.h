/*-
 * Copyright (c) 2015-2019 Varnish Software AS
 * All rights reserved.
 *
 * Author: Martin Blix Grydeland <martin@varnish-software.com>
 * Author: Dag Haavi Finstad <daghf@varnish-software.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Backend TLS support
 */

/* Forward declaration - OpenSSL types */
typedef struct ssl_st SSL;

struct vco;
struct vsl_log;

/*
 * struct vtls_log is used for unified logging across TLS operations.
 *
 * We need to support:
 *  - backend probes (non-transactional, vxid = 0, no vsl buf)
 *  - TLS handshake
 *    - backend: SLT_BackendSSL: logged to vsl buf
 *  - write/writev/read: backend logs SLT_BackendSSL
 */

struct vtls_log {
	struct vsl_log	*vsl;
	vxid_t		vxid;
};

struct vtls_sess {
	unsigned		magic;
#define VTLS_SESS_MAGIC		0x4795576c

	SSL			*ssl;
	struct vtls_log		log[1];
};

/* TLS VCO provider for backend connections */
const struct vco *VTLS_conn_oper_backend(struct vtls_sess *tsp, void **ppriv);

/* Logging helpers */
void VTLS_flush_errors(void);
void VTLS_vsl_ssllog(struct vtls_log *log);
void VTLS_vsl_sslerr(struct vtls_log *log, SSL *ssl, int i);

/* TLS handshake with poll loop */
int VTLS_do_handshake(struct vtls_sess *tsp, int fd, double tmo);

/* Log message macro - if vsl is NULL it is logged as non-transactional */
#define VTLS_LOG(log, tag, ...)					\
	do {							\
		if ((log)->vsl)					\
			VSLb((log)->vsl, tag, __VA_ARGS__);	\
		else						\
			VSL(tag, (log)->vxid, __VA_ARGS__);	\
	} while (0)
