/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * NB: This License is also known as the "BSD 2-Clause License".
 * 
 *
 * [SLIT] System Locality Information Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 */

[0004]                          Signature : "SLIT"
[0004]                       Table Length : 000001BC
[0001]                           Revision : 01
[0001]                           Checksum : 00
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110316

[0008]                         Localities : 0000000000000014
[0020]                       Locality   0 : 0A 10 16 17 18 19 1A 1B 1C 1D 1E 1F 20 21 22 23 \
                                            24 25 26 27
[0020]                       Locality   1 : 10 0A 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20 21 22 \
                                            23 24 25 26
[0020]                       Locality   2 : 16 15 0A 10 16 17 18 19 1A 1B 1C 1D 1E 1F 20 21 \
                                            22 23 24 25
[0020]                       Locality   3 : 17 16 10 0A 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20 \
                                            21 22 23 24
[0020]                       Locality   4 : 18 17 16 15 0A 10 16 17 18 19 1A 1B 1C 1D 1E 1F \
                                            20 21 22 23
[0020]                       Locality   5 : 19 18 17 16 10 0A 15 16 17 18 19 1A 1B 1C 1D 1E \
                                            1F 20 21 22
[0020]                       Locality   6 : 1A 19 18 17 16 15 0A 10 16 17 18 19 1A 1B 1C 1D \
                                            1E 1F 20 21
[0020]                       Locality   7 : 1B 1A 19 18 17 16 10 0A 15 16 17 18 19 1A 1B 1C \
                                            1D 1E 1F 20
[0020]                       Locality   8 : 1C 1B 1A 19 18 17 16 15 0A 10 16 17 18 19 1A 1B \
                                            1C 1D 1E 1F
[0020]                       Locality   9 : 1D 1C 1B 1A 19 18 17 16 10 0A 15 16 17 18 19 1A \
                                            1B 1C 1D 1E
[0020]                       Locality  10 : 1E 1D 1C 1B 1A 19 18 17 16 15 0A 10 16 17 18 19 \
                                            1A 1B 1C 1D
[0020]                       Locality  11 : 1F 1E 1D 1C 1B 1A 19 18 17 16 10 0A 15 16 17 18 \
                                            19 1A 1B 1C
[0020]                       Locality  12 : 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 0A 10 16 17 \
                                            18 19 1A 1B
[0020]                       Locality  13 : 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 10 0A 15 16 \
                                            17 18 19 1A
[0020]                       Locality  14 : 22 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 0A 10 \
                                            16 17 18 19
[0020]                       Locality  15 : 23 22 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 10 0A \
                                            15 16 17 18
[0020]                       Locality  16 : 24 23 22 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 \
                                            0A 10 16 17
[0020]                       Locality  17 : 25 24 23 22 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 \
                                            10 0A 15 16
[0020]                       Locality  18 : 26 25 24 23 22 21 20 1F 1E 1D 1C 1B 1A 19 18 17 \
                                            16 15 0A 10
[0020]                       Locality  19 : 27 26 25 24 23 22 21 20 1F 1E 1D 1C 1B 1A 19 18 \
                                            17 16 10 0A
