/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * Arm PrimeCell PL110 Color LCD Controller
 *
 * Copyright (c) 2005 CodeSourcery, LLC.
 * Written by Paul Brook
 *
 * This code is licenced under the GNU LGPL
 *
 */

#ifndef ORDER

#if BITS == 8
#    define COPY_PIXEL(to, from) *(to++) = from
#elif BITS == 15 || BITS == 16
#   define COPY_PIXEL(to, from)  *(Uns16 *)to = from; to += 2;
#elif BITS == 24
#    define COPY_PIXEL(to, from) *(to++) = from; *(to++) = (from) >> 8; *(to++) = (from) >> 16
#elif BITS == 32
#    define COPY_PIXEL(to, from) *(Uns32 *)to = from; to += 4;
#else
#    error unknown bit depth
#endif

#undef RGB
#define BORDER bgr
#define ORDER 0
#include "draw.h"
#define ORDER 1
#include "draw.h"
#define ORDER 2
#include "draw.h"
#undef BORDER
#define RGB
#define BORDER rgb
#define ORDER 0
#include "draw.h"
#define ORDER 1
#include "draw.h"
#define ORDER 2
#include "draw.h"
#undef BORDER

#define DRAWFN_MEMBERS      42
#define DRAWFN_RGB_OFFSET   (DRAWFN_MEMBERS/2)
#define DRAWFN_BEBO_OFFSET   7
#define DRAWFN_BEPO_OFFSET  14

static drawfn glue(pl110_draw_fn_,BITS)[DRAWFN_MEMBERS] =
{
    glue(pl110_draw_line1_lblp_bgr,BITS),
    glue(pl110_draw_line2_lblp_bgr,BITS),
    glue(pl110_draw_line4_lblp_bgr,BITS),
    glue(pl110_draw_line8_lblp_bgr,BITS),
    glue(pl110_draw_line16_lblp_bgr,BITS),
    glue(pl110_draw_line32_lblp_bgr,BITS),
    glue(pl110_draw_line24_lblp_bgr,BITS),

    glue(pl110_draw_line1_bbbp_bgr,BITS),
    glue(pl110_draw_line2_bbbp_bgr,BITS),
    glue(pl110_draw_line4_bbbp_bgr,BITS),
    glue(pl110_draw_line8_bbbp_bgr,BITS),
    glue(pl110_draw_line16_bbbp_bgr,BITS),
    glue(pl110_draw_line32_bbbp_bgr,BITS),
    glue(pl110_draw_line24_bbbp_bgr,BITS),

    glue(pl110_draw_line1_lbbp_bgr,BITS),
    glue(pl110_draw_line2_lbbp_bgr,BITS),
    glue(pl110_draw_line4_lbbp_bgr,BITS),
    glue(pl110_draw_line8_lbbp_bgr,BITS),
    glue(pl110_draw_line16_lbbp_bgr,BITS),
    glue(pl110_draw_line32_lbbp_bgr,BITS),
    glue(pl110_draw_line24_lbbp_bgr,BITS),

    glue(pl110_draw_line1_lblp_rgb,BITS),
    glue(pl110_draw_line2_lblp_rgb,BITS),
    glue(pl110_draw_line4_lblp_rgb,BITS),
    glue(pl110_draw_line8_lblp_rgb,BITS),
    glue(pl110_draw_line16_lblp_rgb,BITS),
    glue(pl110_draw_line32_lblp_rgb,BITS),
    glue(pl110_draw_line24_lblp_rgb,BITS),

    glue(pl110_draw_line1_bbbp_rgb,BITS),
    glue(pl110_draw_line2_bbbp_rgb,BITS),
    glue(pl110_draw_line4_bbbp_rgb,BITS),
    glue(pl110_draw_line8_bbbp_rgb,BITS),
    glue(pl110_draw_line16_bbbp_rgb,BITS),
    glue(pl110_draw_line32_bbbp_rgb,BITS),
    glue(pl110_draw_line24_bbbp_rgb,BITS),

    glue(pl110_draw_line1_lbbp_rgb,BITS),
    glue(pl110_draw_line2_lbbp_rgb,BITS),
    glue(pl110_draw_line4_lbbp_rgb,BITS),
    glue(pl110_draw_line8_lbbp_rgb,BITS),
    glue(pl110_draw_line16_lbbp_rgb,BITS),
    glue(pl110_draw_line32_lbbp_rgb,BITS),
    glue(pl110_draw_line24_lbbp_rgb,BITS),
};

#undef BITS
#undef COPY_PIXEL

#else /* ORDER */

#if ORDER == 0
#define NAME glue(glue(lblp_, BORDER), BITS)
#ifdef WORDS_BIGENDIAN
#define SWAP_WORDS 1
#endif
#elif ORDER == 1
#define NAME glue(glue(bbbp_, BORDER), BITS)
#ifndef WORDS_BIGENDIAN
#define SWAP_WORDS 1
#endif
#else
#define SWAP_PIXELS 1
#define NAME glue(glue(lbbp_, BORDER), BITS)
#ifdef WORDS_BIGENDIAN
#define SWAP_WORDS 1
#endif
#endif

#define FN_2(x, y) FN(x, y) FN(x+1, y)
#define FN_4(x, y) FN_2(x, y) FN_2(x+2, y)
#define FN_8(y) FN_4(0, y) FN_4(4, y)

static void glue(pl110_draw_line1_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    while (width > 0) {
        data = *(Uns32 *)src;
#ifdef SWAP_PIXELS
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> (y + 7 - (x))) & 1]);
#else
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> ((x) + y)) & 1]);
#endif
#ifdef SWAP_WORDS
        FN_8(24)
        FN_8(16)
        FN_8(8)
        FN_8(0)
#else
        FN_8(0)
        FN_8(8)
        FN_8(16)
        FN_8(24)
#endif
#undef FN
        width -= 32;
        src += 4;
    }
}

static void glue(pl110_draw_line2_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    while (width > 0) {
        data = *(Uns32 *)src;
#ifdef SWAP_PIXELS
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> (y + 6 - (x)*2)) & 3]);
#else
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> ((x)*2 + y)) & 3]);
#endif
#ifdef SWAP_WORDS
        FN_4(0, 24)
        FN_4(0, 16)
        FN_4(0, 8)
        FN_4(0, 0)
#else
        FN_4(0, 0)
        FN_4(0, 8)
        FN_4(0, 16)
        FN_4(0, 24)
#endif
#undef FN
        width -= 16;
        src += 4;
    }
}

static void glue(pl110_draw_line4_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    while (width > 0) {
        data = *(Uns32 *)src;
#ifdef SWAP_PIXELS
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> (y + 4 - (x)*4)) & 0xf]);
#else
#define FN(x, y) COPY_PIXEL(d, pallette[(data >> ((x)*4 + y)) & 0xf]);
#endif
#ifdef SWAP_WORDS
        FN_2(0, 24)
        FN_2(0, 16)
        FN_2(0, 8)
        FN_2(0, 0)
#else
        FN_2(0, 0)
        FN_2(0, 8)
        FN_2(0, 16)
        FN_2(0, 24)
#endif
#undef FN
        width -= 8;
        src += 4;
    }
}

static void glue(pl110_draw_line8_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    while (width > 0) {
        data = *(Uns32 *)src;
#define FN(x) COPY_PIXEL(d, pallette[(data >> (x)) & 0xff]);
#ifdef SWAP_WORDS
        FN(24)
        FN(16)
        FN(8)
        FN(0)
#else
        FN(0)
        FN(8)
        FN(16)
        FN(24)
#endif
#undef FN
        width -= 4;
        src += 4;
    }
}

static void glue(pl110_draw_line16_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    Uns32 r, g, b;
    while (width > 0) {
        data = *(Uns32 *)src;
#ifdef SWAP_WORDS
        data = bswap32(data);
#endif
#ifdef RGB
#define LSB r
#define MSB b
#else
#define LSB b
#define MSB r
#endif
#if 0
        LSB = data & 0x1f;
        data >>= 5;
        g = data & 0x3f;
        data >>= 6;
        MSB = data & 0x1f;
        data >>= 5;
#else
        LSB = (data & 0x1f) << 3;
        data >>= 5;
        g = (data & 0x3f) << 2;
        data >>= 6;
        MSB = (data & 0x1f) << 3;
        data >>= 5;
#endif
        COPY_PIXEL(d, glue(rgb_to_pixel,BITS)(r, g, b));
        LSB = (data & 0x1f) << 3;
        data >>= 5;
        g = (data & 0x3f) << 2;
        data >>= 6;
        MSB = (data & 0x1f) << 3;
        data >>= 5;
        COPY_PIXEL(d, glue(rgb_to_pixel,BITS)(r, g, b));
#undef MSB
#undef LSB
        width -= 2;
        src += 4;
    }
}

static void glue(pl110_draw_line32_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 data;
    Uns32 r, g, b;
    while (width > 0) {
        data = *(Uns32 *)src;
#ifdef RGB
#    define LSB r
#    define MSB b
#else
#    define LSB b
#    define MSB r
#endif

#ifdef SWAP_WORDS
        LSB = data & 0xff;
        g = (data >> 8) & 0xff;
        MSB = (data >> 16) & 0xff;
#else
        LSB = (data >> 24) & 0xff;
        g = (data >> 16) & 0xff;
        MSB = (data >> 8) & 0xff;
#endif
        COPY_PIXEL(d, glue(rgb_to_pixel,BITS)(r, g, b));
#undef MSB
#undef LSB
        width--;
        src += 4;
    }
}

static void glue(pl110_draw_line24_,NAME)(Uns32 *pallette, Uns8 *d, const Uns8 *src, Int32 width)
{
    Uns32 r, g, b;
    while (width > 0) {
#ifdef RGB
#    define LSB r
#    define MSB b
#else
#    define LSB b
#    define MSB r
#endif

#ifdef SWAP_WORDS
        LSB = *(Uns8 *)(src + 2);
        g   = *(Uns8 *)(src + 1);
        MSB = *(Uns8 *)(src + 0);
#else
        LSB = *(Uns8 *)(src + 0);
        g   = *(Uns8 *)(src + 1);
        MSB = *(Uns8 *)(src + 2);
#endif
        COPY_PIXEL(d, glue(rgb_to_pixel,BITS)(r, g, b));
#undef MSB
#undef LSB
        width--;
        src += 3;
    }
}

#undef SWAP_PIXELS
#undef NAME
#undef SWAP_WORDS
#undef ORDER

#endif
