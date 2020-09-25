/**
    Copyright (C) powturbo 2013-2019
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
//    ic - "Integer Compression" Java Critical Native Interface / JNI
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitutil.h"
#include "vint.h"
#include "vsimple.h"
#include "bitpack.h"
#include "vp4.h"

#include "jic.h"

#define JNIB jboolean _inlock, _outlock;\
  jint i  = (*env)->GetArrayLength(env, _in);  jbyte *in  = (jbyte *)(*env)->GetPrimitiveArrayCritical(env, _in, &_inlock);\
  jint o = (*env)->GetArrayLength(env, _out); jbyte *out = (jbyte *)(*env)->GetPrimitiveArrayCritical(env, _out,&_outlock)

#define JNIE\
 (*env)->ReleasePrimitiveArrayCritical(env, _in,   in, JNI_ABORT);\
 (*env)->ReleasePrimitiveArrayCritical(env, _out, out, JNI_ABORT)

#define JNIENC(__func, _in, n, _out        ) JNIB; jint l = __func ((unsigned      *)in, n,(unsigned char *)out      ) - (unsigned char *)out; JNIE; return l
#define JNIDEC(__func, _in, n, _out        ) JNIB; jint l = __func ((unsigned char *)in, n,(unsigned      *)out      ) - (unsigned char *)in;  JNIE; return l

#define JNIENCS(__func, _in, n, _out,  x   ) JNIB; jint l = __func ((unsigned      *)in, n,(unsigned char *)out, x   ) - (unsigned char *)out; JNIE; return l
#define JNIDECS(__func, _in, n, _out,  x   ) JNIB; jint l = __func ((unsigned char *)in, n,(unsigned      *)out, x   ) - (unsigned char *)in;  JNIE; return l

#define JNIENCSB(__func, _in, n, _out, x, b) JNIB; jint l = __func ((unsigned      *)in, n,(unsigned char *)out, x, b) - (unsigned char *)out; JNIE; return l
#define JNIDECSB(__func, _in, n, _out, x, b) JNIB; jint l = __func ((unsigned char *)in, n,(unsigned      *)out, x, b) - (unsigned char *)in;  JNIE; return l

#define JNINENC(__func, _in, n, _out        ) JNIB; jint l = __func ((unsigned      *)in, n,(unsigned char *)out      ); JNIE; return l
#define JNINDEC(__func, _in, n, _out        ) JNIB; jint l = __func ((unsigned char *)in, n,(unsigned      *)out      ); JNIE; return l

#define JNIBI jboolean _inlock; jint i = (*env)->GetArrayLength(env, _in); jbyte *in  = (jbyte *)(*env)->GetPrimitiveArrayCritical(env, _in, &_inlock);

#define JNIEI (*env)->ReleasePrimitiveArrayCritical(env, _in,   in, JNI_ABORT);

#define JNIBIT( __func, _in, n)    JNIBI; jint l = __func ((unsigned      *)in, n, 0   ); JNIEI; return l
#define JNIBITS(__func, _in, n, x) JNIBI; jint l = __func ((unsigned      *)in, n, 0, x); JNIEI; return l

//---------------------------------- variable byte ------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL Java_jic_vbenc32(           JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNIENC(vbenc32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbenc32(          jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return vbenc32(           (unsigned *)in, n, (unsigned char *)out          ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_vbdec32(           JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNIDEC(vbdec32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbdec32(          jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return vbdec32(      (unsigned char *)in, n,      (unsigned *)out          ) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_vbdenc32(          JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start        ) { JNIENCS(vbdenc32,            _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbdenc32(         jint i,  jint *in, jint n, jint o, jbyte *out, jint start         ) { return vbdenc32(          (unsigned *)in, n, (unsigned char *)out, start   ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_vbddec32(          JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start        ) { JNIDECS(vbddec32,            _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbddec32(         jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return vbddec32(     (unsigned char *)in, n,      (unsigned *)out, start   ) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_vbd1enc32(         JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start        ) { JNIENCS(vbd1enc32,           _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbd1enc32(        jint i,  jint *in, jint n, jint o, jbyte *out, jint start         ) { return vbd1enc32(         (unsigned *)in, n, (unsigned char *)out, start   ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_vbd1dec32(         JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start        ) { JNIDECS(vbd1dec32,           _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_vbd1dec32(        jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return vbd1dec32(    (unsigned char *)in, n,      (unsigned *)out, start   ) - (unsigned char *)in; }
//--------------------------------- variable simple ----------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL Java_jic_vsenc32(           JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNIENC(vsenc32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_vsenc32(          jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return vsenc32(           (unsigned *)in, n, (unsigned char *)out          ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_vsdec32(           JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNIDEC(vsdec32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_vsdec32(          jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return vsdec32(      (unsigned char *)in, n,      (unsigned *)out          ) - (unsigned char *)in; }
//--------------------------------- TurboPFor: PFor/PForDelta -----------------------------------------------------------------
// High level API - n = unlimited
JNIEXPORT jint JNICALL Java_jic_p4nenc32(          JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4nenc32,             _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nenc32(         jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4nenc32(          (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4ndec32(          JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4ndec32,             _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4ndec32(         jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4ndec32(     (unsigned char *)in, n,      (unsigned *)out          ); }

JNIEXPORT jint JNICALL Java_jic_p4nenc128v32(      JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4nenc128v32,         _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nenc128v32(     jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4nenc128v32(      (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4ndec128v32(      JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4ndec128v32,         _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4ndec128v32(     jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4ndec128v32( (unsigned char *)in, n,      (unsigned *)out          ); }

JNIEXPORT jint JNICALL Java_jic_p4nenc256v32(      JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4nenc256v32,         _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nenc256v32(     jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4nenc256v32(      (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4ndec256v32(      JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4ndec256v32,         _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4ndec256v32(     jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4ndec256v32( (unsigned char *)in, n,      (unsigned *)out          ); }
//--------
JNIEXPORT jint JNICALL Java_jic_p4ndenc32(         JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4ndenc32,            _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4ndenc32(        jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4ndenc32(         (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4nddec32(         JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4nddec32,           _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nddec32(        jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return p4nddec32(    (unsigned char *)in, n,      (unsigned *)out          ); }

JNIEXPORT jint JNICALL Java_jic_p4nd1enc32(        JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4nd1enc32,           _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nd1enc32(       jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4nd1enc32(        (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4nd1dec32(        JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4nd1dec32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nd1dec32(       jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return p4nd1dec32(   (unsigned char *)in, n,      (unsigned *)out          ); }

JNIEXPORT jint JNICALL Java_jic_p4nzenc32(         JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(p4nzenc32,            _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nzenc32(        jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4nzenc32(         (unsigned *)in, n, (unsigned char *)out          ); }
JNIEXPORT jint JNICALL Java_jic_p4nzdec32(         JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(p4nzdec32,           _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4nzdec32(        jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return p4nzdec32(    (unsigned char *)in, n,      (unsigned *)out          ); }

// Low level: Single block
JNIEXPORT jint JNICALL Java_jic_p4denc32(          JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNIENC(p4enc32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4enc32(          jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4enc32(           (unsigned *)in, n, (unsigned char *)out          ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_p4dec32(           JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNIDEC(p4dec32,              _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4dec32(          jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4dec32(      (unsigned char *)in, n,      (unsigned *)out          ) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_p4enc128v32(       JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNIENC(p4enc128v32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4enc128v32(      jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4enc128v32(        (unsigned *)in, n, (unsigned char *)out          ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_p4dec128v32(       JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNIDEC(p4dec128v32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4dec128v32(      jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4dec128v32(   (unsigned char *)in, n,      (unsigned *)out          ) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_p4enc256v32(       JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNIENC(p4enc256v32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4enc256v32(      jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return p4enc256v32(        (unsigned *)in, n, (unsigned char *)out          ) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_p4dec256v32(       JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNIDEC(p4dec256v32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4dec256v32(      jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return p4dec256v32(   (unsigned char *)in, n,      (unsigned *)out          ) - (unsigned char *)in; }

//--------
JNIEXPORT jint JNICALL Java_jic_p4ddec32(          JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start        ) { JNIDECS(p4ddec32,            _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4ddec32(         jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return p4ddec32(      (unsigned char *)in, n,      (unsigned *)out, start   ) - (unsigned char *)in; }
JNIEXPORT jint JNICALL Java_jic_p4d1dec32(         JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start        ) { JNIDECS(p4d1dec32,           _in, n, _out, start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_p4d1dec32(        jint i, jbyte *in, jint n, jint o,  jint *out, jint start         ) { return p4d1dec32(     (unsigned char *)in, n,      (unsigned *)out, start   ) - (unsigned char *)in; }
//--------------------------------- BitPack/BitUnpack ----------------------------------------------------------------------------
// High level API
JNIEXPORT jint JNICALL Java_jic_bitnpack32(        JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnpack32,          _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnpack32(       jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return bitnpack32(         (unsigned *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnunpack32(      JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnunpack32,        _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnunpack32(     jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return bitnunpack32(  (unsigned char *)in, n,      (unsigned *)out); }

JNIEXPORT jint JNICALL Java_jic_bitndpack32(       JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitndpack32,        _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndpack32(      jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return bitndpack32((        unsigned *)in, n, (unsigned char *)out);}
JNIEXPORT jint JNICALL Java_jic_bitndunpack32(     JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitndunpack32,      _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndunpack32(    jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return bitndunpack32((   unsigned char *)in, n, (unsigned *)out     ); }

JNIEXPORT jint JNICALL Java_jic_bitnd1pack32(      JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnd1pack32,       _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1pack32(     jint i,  jint *in, jint n, jint o, jbyte *out                     ) { return bitnd1pack32((        unsigned  *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnd1unpack32(    JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnd1unpack32,     _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1unpack32(   jint i, jbyte *in, jint n, jint o,  jint *out                     ) { return bitnd1unpack32( (unsigned char  *)in, n,      (unsigned *)out); }

// low level API
JNIEXPORT jint JNICALL Java_jic_bitpack32(         JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out,             jint b) { JNIENCS(bitpack32,           _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitpack32(        jint i,  jint *in, jint n, jint o, jbyte *out,             jint b ) { return bitpack32(            (unsigned *)in, n, (unsigned char *)out,        b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitunpack32(       JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out,             jint b) { JNIDECS(bitunpack32,         _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitunpack32(      jint i, jbyte *in, jint n, jint o,  jint *out,             jint b ) { return bitunpack32(     (unsigned char *)in, n,      (unsigned *)out,        b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitdpack32(        JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitdpack32,         _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdpack32(       jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b ) { return bitdpack32(            (unsigned *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out;}
JNIEXPORT jint JNICALL Java_jic_bitdunpack32(      JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitdunpack32,       _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdunpack32(     jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b ) { return bitdunpack32(     (unsigned char *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitd1pack32(       JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitd1pack32,        _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1pack32(      jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b ) { return bitd1pack32((          unsigned  *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitd1unpack32(     JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitd1unpack32,      _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1unpack32(    jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b ) { return bitd1unpack32(   (unsigned char  *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }

//--------------------------------- BitPack/BitUnpack SIMD -----------------------------------------------------------------------------------
// GHigh Level API: n unlimited
JNIEXPORT jint JNICALL Java_jic_bitnpack128v32(    JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnpack128v32,      _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnpack128v32(    jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitnpack128v32(    (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnunpack128v32(  JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnunpack128v32,    _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnunpack128v32(  jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitnunpack128v32(  (unsigned char *)in, n, (unsigned *)out     ); }

JNIEXPORT jint JNICALL Java_jic_bitndpack128v32(   JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitndpack128v32,    _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndpack128v32(   jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitndpack128v32(   (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitndunpack128v32( JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitndunpack128v32,  _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndunpack128v32( jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitndunpack128v32( (unsigned char *)in, n, (unsigned *)out     ); }

JNIEXPORT jint JNICALL Java_jic_bitnd1pack128v32(  JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnd1pack128v32,   _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1pack128v32(  jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitnd1pack128v32(  (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnd1unpack128v32(JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnd1unpack128v32, _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1unpack128v32(jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitnd1unpack128v32((unsigned char *)in, n, (unsigned *)out     ); }

// AVX2
JNIEXPORT jint JNICALL Java_jic_bitnpack256v32(    JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnpack256v32,      _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnpack256v32(    jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitnpack256v32(    (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnunpack256v32(  JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnunpack256v32,    _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnunpack256v32(  jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitnunpack256v32(  (unsigned char *)in, n, (unsigned *)out     ); }

JNIEXPORT jint JNICALL Java_jic_bitndpack256v32(   JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitndpack256v32,    _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndpack256v32(   jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitndpack256v32(   (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitndunpack256v32( JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitndunpack256v32,  _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitndunpack256v32( jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitndunpack256v32( (unsigned char *)in, n, (unsigned *)out     ); }

JNIEXPORT jint JNICALL Java_jic_bitnd1pack256v32(  JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out                    ) { JNINENC(bitnd1pack256v32,   _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1pack256v32(  jint i,  jint *in, jint n, jint o, jbyte *out                    ) { return bitnd1pack256v32(  (unsigned      *)in, n, (unsigned char *)out); }
JNIEXPORT jint JNICALL Java_jic_bitnd1unpack256v32(JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out                    ) { JNINDEC(bitnd1unpack256v32, _in, n, _out          ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitnd1unpack256v32(jint i, jbyte *in, jint n, jint o,  jint *out                    ) { return bitnd1unpack256v32((unsigned char *)in, n, (unsigned *)out     ); }

// Low level API
JNIEXPORT jint JNICALL Java_jic_bitpack128v32(     JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out,             jint b) { JNIENCS(bitpack128v32,       _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitpack128v32(     jint i,  jint *in, jint n, jint o, jbyte *out,             jint b) { return bitpack128v32(     (unsigned      *)in, n, (unsigned char *)out,        b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitunpack128v32(   JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out,             jint b) { JNIDECS(bitunpack128v32,     _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitunpack128v32(   jint i, jbyte *in, jint n, jint o,  jint *out,             jint b) { return bitunpack128v32(   (unsigned char *)in, n,      (unsigned *)out,        b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitdpack128v32(    JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitdpack128v32,     _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdpack128v32(    jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b) { return bitdpack128v32(    (unsigned      *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitdunpack128v32(  JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitdunpack128v32,   _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdunpack128v32(  jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b) { return bitdunpack128v32(  (unsigned char *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitd1pack128v32(   JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitd1pack128v32,    _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1pack128v32(   jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b) { return bitd1pack128v32(   (unsigned      *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitd1unpack128v32( JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitd1unpack128v32,  _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1unpack128v32( jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b) { return bitd1unpack128v32( (unsigned char *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }

// AVX2
JNIEXPORT jint JNICALL Java_jic_bitpack256v32(     JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out,             jint b) { JNIENCS(bitpack256v32,       _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitpack256v32(     jint i,  jint *in, jint n, jint o, jbyte *out,             jint b) { return bitpack256v32(     (unsigned      *)in, n, (unsigned char *)out,        b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitunpack256v32(   JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out,             jint b) { JNIDECS(bitunpack256v32,     _in, n, _out,        b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitunpack256v32(   jint i, jbyte *in, jint n, jint o,  jint *out,             jint b) { return bitunpack256v32(   (unsigned char *)in, n,      (unsigned *)out,        b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitdpack256v32(    JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitdpack256v32,     _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdpack256v32(    jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b) { return bitdpack256v32(    (unsigned      *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitdunpack256v32(  JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitdunpack256v32,   _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitdunpack256v32(  jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b) { return bitdunpack256v32(  (unsigned char *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }

JNIEXPORT jint JNICALL Java_jic_bitd1pack256v32(   JNIEnv *env, jclass cls,  jintArray _in, jint n, jbyteArray _out, jint start, jint b) { JNIENCSB(bitd1pack256v32,    _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1pack256v32(   jint i,  jint *in, jint n, jint o, jbyte *out, jint start, jint b) { return bitd1pack256v32(   (unsigned      *)in, n, (unsigned char *)out, start, b) - (unsigned char *)out; }
JNIEXPORT jint JNICALL Java_jic_bitd1unpack256v32( JNIEnv *env, jclass cls, jbyteArray _in, jint n,  jintArray _out, jint start, jint b) { JNIDECSB(bitd1unpack256v32,  _in, n, _out, start, b); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd1unpack256v32( jint i, jbyte *in, jint n, jint o,  jint *out, jint start, jint b) { return bitd1unpack256v32( (unsigned char *)in, n,      (unsigned *)out, start, b) - (unsigned char *)in; }
//--------------------------------- bitutil --------------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL Java_jic_bit32(             JNIEnv *env, jclass cls,  jintArray _in, jint n                                     ) { JNIBIT( bit32,               _in, n                ); } JNIEXPORT jint JNICALL JavaCritical_jic_bit32(             jint i,  jint *in, jint n                                        ) { return bit32(             (unsigned      *)in, n,                    0          ); }
JNIEXPORT jint JNICALL Java_jic_bitd32(            JNIEnv *env, jclass cls,  jintArray _in, jint n,                  jint start        ) { JNIBITS(bitd32,              _in, n,       start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd32(            jint i,  jint *in, jint n,                     jint start        ) { return bitd32(            (unsigned      *)in, n,                    0,   start ); }
JNIEXPORT jint JNICALL Java_jic_bitd132(           JNIEnv *env, jclass cls,  jintArray _in, jint n,                  jint start        ) { JNIBITS(bitd132,             _in, n,       start   ); } JNIEXPORT jint JNICALL JavaCritical_jic_bitd132(           jint i,  jint *in, jint n,                     jint start        ) { return bitd132(           (unsigned      *)in, n,                    0,   start ); }

