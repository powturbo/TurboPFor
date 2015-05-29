/**
    Copyright (C) powturbo 2013-2015
    GPL v2 License
  
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - homepage : https://sites.google.com/site/powturbo/
    - github   : https://github.com/powturbo
    - twitter  : https://twitter.com/powturbo
    - email    : powturbo [_AT_] gmail [_DOT_] com
**/
//    vint.c - "Integer Compression" variable byte 
#include <stdio.h>   
     
#include "conf.h"
#include "vint.h"
#include "bitutil.h"
//-------------------------------------- variable byte : 32 bits ----------------------------------------------------------------
  #if defined(__AVX2__) && defined(__AVX2__VINT)
#include <immintrin.h>
#define M1         0xfeull //7
#define M2       0xfffcull //14
#define M3     0xfffff8ull //21
#define M4   0xfffffff0ull //28
#define M5 0xfffffffff0ull //36 

			                       //0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 					 
unsigned long long mtab[] = {    M1,  M2,  M1,  M3,  M1,  M2,  M1,  M4,  M1,  M2,  M1,  M3,  M1,  M2,  M1,  M5 };
  #endif
//------------------------------------------------------------------------------------------------------------------------
			                //0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 		
unsigned char vtab[] =      {    1,   2,   1,   3,   1,   2,   1,   4,   1,   2,   1,   3,   1,   2,   1,   5 };
// Length of uncompress value. Input __x is the compressed buffer start

// decompress buffer into an array of n unsigned values. Return value = end of decompressed buffer in
unsigned char *vbdec(unsigned char  *__restrict in, unsigned n, unsigned *__restrict out) { unsigned x,*op;
  for(op = out; op != out+(n&~(4-1)); ) {
    vbgeta(in, x, ;); *op++ = x;            
    vbgeta(in, x, ;); *op++ = x;
    vbgeta(in, x, ;); *op++ = x;
    vbgeta(in, x, ;); *op++ = x;
  }
  while(op != out+n) { vbgeta(in, x, ; ); *op++ = x; }
  return in;
}

// encode array with n unsigned (32 bits in[n]) values to the buffer out. Return value = end of compressed buffer out
unsigned char *vbenc(unsigned *__restrict in, unsigned n, unsigned char *__restrict out) { unsigned *ip;
  for(ip = in; ip != in+(n&~(4-1)); ) {
    vbput(out, *ip++);
    vbput(out, *ip++);
    vbput(out, *ip++);
    vbput(out, *ip++);  
  }
  while(ip <  in+n) vbput(out, *ip++);
  return out;
}
//---------------------------------- increasing integer lists ----------------------------------------------------------------------------------------------------
unsigned char *vbdenc(unsigned *__restrict in, unsigned n, unsigned char *__restrict out, unsigned start) { 
  unsigned *ip,v;
  for(ip = in; ip != in+(n&~(4-1)); ) {
    v = (*ip)-start; start=*ip++; vbputa(out, v, ;);
    v = (*ip)-start; start=*ip++; vbputa(out, v, ;);
    v = (*ip)-start; start=*ip++; vbputa(out, v, ;);
    v = (*ip)-start; start=*ip++; vbputa(out, v, ;);
  }
  while(ip <  in+n) { v = (*ip)-start; start = *ip++; vbput(out, v); }
  return out;
}  

unsigned char *vbddec(unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start) { 
  unsigned x,*op;
  for(op = out; op != out+(n&~(4-1)); ) { 
    vbgeta(in, x, ;); *op++ = (start += x);
    vbgeta(in, x, ;); *op++ = (start += x);
    vbgeta(in, x, ;); *op++ = (start += x);
    vbgeta(in, x, ;); *op++ = (start += x);
  }
  while(op < out+n) vbgeta(in, x, *op++ = (start += x));
  return in;
}

//----------------------------------strictly increasing (never remaining constant or decreasing) integer lists---------------------------------------------------------
unsigned char *vbd1enc(unsigned *__restrict in, unsigned n, unsigned char *__restrict out, unsigned start) { 
  unsigned *ip, v, b = 0; unsigned char *op = out; 
  v = ((*in) - start - 1)<<1; if(n == 1) v |= 1; 
  vbputa(op, v, ;); 
  if(!--n) return op; 
  start = *in++;
  
  for(ip = in; ip != in + (n&~(4-1)); ) {
    v = (*ip)-start-1; start = *ip++; vbputa(op, v, ;); b |= v;
    v = (*ip)-start-1; start = *ip++; vbputa(op, v, ;); b |= v;
    v = (*ip)-start-1; start = *ip++; vbputa(op, v, ;); b |= v;
    v = (*ip)-start-1; start = *ip++; vbputa(op, v, ;); b |= v;
  }
  while(ip < in+n) { v = (*ip)-start-1; start = *ip++; vbput(op, v); b |= v; } 
  if(!b) { 
    v = in[-1] << 1 | 1;
	vbputa(out, v, ;); 
	return out; 
  }
  return op;
}

#define BITUNBLKV32_0(ip, i, __op, __parm) {\
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
  _mm_storeu_si128(__op++, __parm); __parm = _mm_add_epi32(__parm, cv); \
}
#define BITUNPACK0(__parm) __parm = _mm_add_epi32(__parm, cv); cv = _mm_set1_epi32(4)

unsigned char *vbd1dec(unsigned char *__restrict in, unsigned n, unsigned *__restrict out, unsigned start) { unsigned x,*op;
  vbgeta(in, x, ;); *out = (start += (x>>1)+1);
  if(x & 1) { 
      #ifdef __SSE2__
	out++; --n; __m128i sv = _mm_set1_epi32(start), cv = _mm_set_epi32(4,3,2,1), *ov=(__m128i *)(out), *ove = (__m128i *)(out + n);
	BITUNPACK0(sv); do BITUNBLKV32_0( iv, 0, ov, sv) while(ov < ove);
	  #else 
    for(x = 1; x < n; x++) out[x] = start+x;
      #endif
	return in; 
  } 
  out++; --n;
  
  for(op = out; op != out+(n&~(4-1)); ) { 
    vbgeta(in, x, ;); *op++ = (start += x+1);
    vbgeta(in, x, ;); *op++ = (start += x+1);
    vbgeta(in, x, ;); *op++ = (start += x+1);
    vbgeta(in, x, ;); *op++ = (start += x+1);
  }
  while(op < out+n) { vbgeta(in, x, ;); *op++ = (start += x+1); }
  return in;
}

//--------------------------------------- variable byte : 15 bits -------------------------------------------------------------------
// like vbenc32 but for 16 bits values
unsigned char *vbenc16(unsigned short *__restrict in, unsigned n, unsigned char  *__restrict out) { unsigned short *in_  = in +n;   while(in  <  in_) vbput16(out, *in++);        return out;}
// like vbdec32 but for 16 bits values
unsigned char *vbdec16(unsigned char  *__restrict in, unsigned n, unsigned short *__restrict out) { unsigned short *out_ = out+n,x; while(out < out_) vbgeta16(in, x, *out++ = x); return in; }