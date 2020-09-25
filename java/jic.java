/**
    Copyright (C) powturbo 2013-2017
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
//   ic - "Integer Compression" Java Critical Native Interface Class
 
public class jic {
  // variable byte
  public native static int vbenc32(            int[] in, int n, byte[] out);
  public native static int vbdec32(           byte[] in, int n,  int[] out);

  public native static int vbdenc32(           int[] in, int n, byte[] out, int start);
  public native static int vbddec32(          byte[] in, int n,  int[] out, int start);
  
  public native static int vbd1enc32(          int[] in, int n, byte[] out, int start);
  public native static int vbd1dec32(         byte[] in, int n,  int[] out, int start);

  public native static int vbzenc32(           int[] in, int n, byte[] out, int start);
  public native static int vbzdec32(          byte[] in, int n,  int[] out, int start);
  
  // variable simple
  public native static int vsenc32(            int[] in, int n, byte[] out);
  public native static int vsdec32(           byte[] in, int n,  int[] out);

  //************ TurboPFor: PFor/PForDelta
  // High level API: n unlimited
  public native static int p4nenc32(           int[] in, int n, byte[] out);
  public native static int p4ndec32(          byte[] in, int n,  int[] out);
  public native static int p4nenc128v32(       int[] in, int n, byte[] out);
  public native static int p4ndec128v32(      byte[] in, int n,  int[] out);
  public native static int p4nenc256v32(       int[] in, int n, byte[] out);
  public native static int p4ndec256v32(      byte[] in, int n,  int[] out);

  public native static int p4ndenc32(          int[] in, int n, byte[] out); // delta 0: increasing integer list (sorted)
  public native static int p4nddec32(         byte[] in, int n,  int[] out);
  public native static int p4ndenc128v32(      int[] in, int n, byte[] out);
  public native static int p4nddec128v32(     byte[] in, int n,  int[] out);
  public native static int p4ndenc256v32(      int[] in, int n, byte[] out);
  public native static int p4nddec256v32(     byte[] in, int n,  int[] out);
 
  public native static int p4nd1enc32(         int[] in, int n, byte[] out); // delta 1: strictly increasing integer list (sorted)
  public native static int p4nd1dec32(        byte[] in, int n,  int[] out);
  public native static int p4nd1enc128v32(     int[] in, int n, byte[] out);
  public native static int p4nd1dec128v32(    byte[] in, int n,  int[] out);
  public native static int p4nd1enc256v32(     int[] in, int n, byte[] out);
  public native static int p4nd1dec256v32(    byte[] in, int n,  int[] out);

  public native static int p4nzenc32(          int[] in, int n, byte[] out); // zigzag: unsorted integer list
  public native static int p4nzdec32(         byte[] in, int n,  int[] out);
  public native static int p4nzenc128v32(      int[] in, int n, byte[] out);
  public native static int p4nzdec128v32(     byte[] in, int n,  int[] out);
  public native static int p4nzenc256v32(      int[] in, int n, byte[] out);
  public native static int p4nzdec256v32(     byte[] in, int n,  int[] out);
 
  // Single block: n limited to 128/256
  public native static int p4enc32(            int[] in, int n, byte[] out);
  public native static int p4dec32(           byte[] in, int n,  int[] out);

  public native static int p4enc128v32(        int[] in, int n, byte[] out);
  public native static int p4dec128v32(       byte[] in, int n,  int[] out);
  public native static int p4enc256v32(        int[] in, int n, byte[] out);
  public native static int p4dec256v32(       byte[] in, int n,  int[] out);

  public native static int p4ddec32(          byte[] in, int n,  int[] out, int start);
  public native static int p4ddec128v32(      byte[] in, int n,  int[] out, int start);
  public native static int p4ddec256v32(      byte[] in, int n,  int[] out, int start);

  public native static int p4d1dec32(         byte[] in, int n,  int[] out, int start);
  public native static int p4d1dec128v32(     byte[] in, int n,  int[] out, int start);
  public native static int p4d1dec256v32(     byte[] in, int n,  int[] out, int start);
  
  //********** bitpack scalar
  // High level API
  public native static int bitnpack32(         int[] in, int n, byte[] out);
  public native static int bitnunpack32(      byte[] in, int n,  int[] out);
  public native static int bitnpack128v32(     int[] in, int n, byte[] out);
  public native static int bitnunpack128v32(  byte[] in, int n,  int[] out);
  public native static int bitnpack256v32(     int[] in, int n, byte[] out);
  public native static int bitnunpack256v32(  byte[] in, int n,  int[] out);

  public native static int bitndpack32(        int[] in, int n, byte[] out);
  public native static int bitndunpack32(     byte[] in, int n,  int[] out);
  public native static int bitndpack128v32(    int[] in, int n, byte[] out);
  public native static int bitndunpack128v32( byte[] in, int n,  int[] out);
  public native static int bitndpack256v32(    int[] in, int n, byte[] out);
  public native static int bitndunpack256v32( byte[] in, int n,  int[] out);
  
  public native static int bitnd1pack32(       int[] in, int n, byte[] out);
  public native static int bitnd1unpack32(    byte[] in, int n,  int[] out);
  public native static int bitnd1pack128v32(   int[] in, int n, byte[] out);
  public native static int bitnd1unpack128v32(byte[] in, int n,  int[] out);
  public native static int bitnd1pack256v32(   int[] in, int n, byte[] out);
  public native static int bitnd1unpack256v32(byte[] in, int n,  int[] out);

  // Low level API - single block limited to 128/256 integers
  public native static int bitpack32(          int[] in, int n, byte[] out, int b);
  public native static int bitunpack32(       byte[] in, int n,  int[] out, int b);
  public native static int bitpack128v32(      int[] in, int n, byte[] out, int b);
  public native static int bitunpack128v32(   byte[] in, int n,  int[] out, int b);
  public native static int bitpack256v32(      int[] in, int n, byte[] out, int b);
  public native static int bitunpack256v32(   byte[] in, int n,  int[] out, int b);

  public native static int bitdpack32(         int[] in, int n, byte[] out, int start, int b);
  public native static int bitdunpack32(      byte[] in, int n,  int[] out, int start, int b);
  public native static int bitdpack128v32(     int[] in, int n, byte[] out, int start, int b);
  public native static int bitdunpack128v32(  byte[] in, int n,  int[] out, int start, int b);
  public native static int bitdpack256v32(     int[] in, int n, byte[] out, int start, int b);
  public native static int bitdunpack256v32(  byte[] in, int n,  int[] out, int start, int b);

  public native static int bitd1pack32(    	   int[] in, int n, byte[] out, int start, int b);
  public native static int bitd1unpack32( 	  byte[] in, int n,  int[] out, int start, int b);
  public native static int bitd1pack128v32(    int[] in, int n, byte[] out, int start, int b);
  public native static int bitd1unpack128v32( byte[] in, int n,  int[] out, int start, int b);
  public native static int bitd1pack256v32(    int[] in, int n, byte[] out, int start, int b);
  public native static int bitd1unpack256v32( byte[] in, int n,  int[] out, int start, int b);

  // bitutil
  public native static int bit32(              int[] in, int n);
  public native static int bitd32(             int[] in, int n, int start);
  public native static int bitd132(            int[] in, int n, int start);

  static {
    try {
      System.loadLibrary("ic");
      // System.load("/home/x/TurboPFor/libic.so");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("can't load Native TurboPFor from '" + System.getProperty("java.library.path") + "'" + e);
      System.exit(1);
    }
  }
}
