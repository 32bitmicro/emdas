//  Copyright (c) 2014 Jakub Filipowicz <jakubf@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "emdas/buf.h"

// -----------------------------------------------------------------------
struct emdas_buf * emdas_buf_create(int len)
{
	struct emdas_buf *buf = NULL;

	if (len < 1) {
		goto cleanup;
	}

	buf = malloc(sizeof(struct emdas_buf));
	if (!buf) {
		goto cleanup;
	}

	buf->buf = malloc(len+1);
	if (!buf->buf) {
		goto cleanup;
	}

	buf->len = len;
	emdas_buf_reset(buf);

	return buf;

cleanup:
	emdas_buf_destroy(buf);
	return NULL;
}

// -----------------------------------------------------------------------
void emdas_buf_destroy(struct emdas_buf *buf)
{
	if (!buf) return;

	free(buf->buf);
	free(buf);
}

// -----------------------------------------------------------------------
int emdas_buf_reset(struct emdas_buf *buf)
{
	if (!buf) return -1;

	buf->pos = 0;
	buf->lpos = 0;
	buf->buf[0] = '\0';

	return 0;
}

// -----------------------------------------------------------------------
int emdas_buf_c(struct emdas_buf *buf, char c)
{
	if (!buf) return 0;

	int clen = 0;

	if (buf->pos < buf->len) {
		buf->buf[buf->pos] = c;
		buf->pos++;
		buf->lpos++;
		clen++;
	}
	buf->buf[buf->pos] = '\0';

	return clen;
}

// -----------------------------------------------------------------------
int emdas_buf_nl(struct emdas_buf *buf)
{
	if (!buf) return 0;

	int clen = emdas_buf_c(buf, '\n');
	if (clen != 0) {
		buf->lpos = 0;
	}

	return clen;
}

// -----------------------------------------------------------------------
int emdas_buf_app(struct emdas_buf *buf, const char *fmt, ...)
{
	if (!buf) return 0;

	va_list ap;
	va_start(ap, fmt);
	int clen = vsnprintf(buf->buf + buf->pos, buf->len - buf->pos, fmt, ap);
	va_end(ap);

	buf->lpos += clen;
	buf->pos += clen;

	return clen;
}

// -----------------------------------------------------------------------
int emdas_buf_tab(struct emdas_buf *buf, unsigned tab)
{
	if (!buf) return 0;

	int clen;
	int left;
	char *ptr = buf->buf + buf->pos;
	char *maxptr;

	// tab position already behind
	if (tab <= buf->lpos) {
		// we're not at the beginning of a line
		if (buf->lpos != 0) {
			maxptr = ptr + 1;
		// we're at the beginning of a line
		} else {
			return 0;
		}
	// tab position ahead
	} else {
		maxptr = ptr - buf->lpos + tab;
	}

	// want
	left = maxptr - ptr;
	// if greater than buf left
	if (left > (buf->len - buf->pos)) {
		left = buf->len - buf->pos;
	}

	// fill
	while (left) {
		*ptr++ = ' ';
		left--;
	}

	clen = ptr - buf->buf - buf->pos;
	buf->pos += clen;
	buf->lpos += clen;
	buf->buf[buf->pos] = '\0';

	return clen;
}

// -----------------------------------------------------------------------
int emdas_buf_tolower(struct emdas_buf *buf, int back)
{
	if (!buf) return 0;

	int clen = 0;

	while (clen < back) {
		buf->buf[buf->pos - (clen+1)] = tolower(buf->buf[buf->pos - (clen+1)]);
		clen++;
	}

	return clen;
}


// vim: tabstop=4 shiftwidth=4 autoindent
