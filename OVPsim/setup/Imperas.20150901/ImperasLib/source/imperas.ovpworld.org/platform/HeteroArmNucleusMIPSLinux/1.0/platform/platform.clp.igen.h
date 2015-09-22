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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////

static void cmdParserAddUserArgs(icmCLPP parser) {
    icmCLParserAdd(parser, "uartconsole", 0 , 0, "user platform config", ICM_AT_BOOLVAL      , &options.uartconsole, "open a console terminal on the ARM IntegratorCP UART", 0x0, 0, 0);
    icmCLParserAdd(parser, "uartport", 0 , 0, "user platform config", ICM_AT_UNS64VAL     , &options.uartport, "set the base port number to open on the ARM IntegratorCP UART", 0x0, 0, 0);
    icmCLParserAdd(parser, "nographics", 0 , 0, "user platform config", ICM_AT_BOOLVAL      , &options.nographics, "disable the MIPS Malta graphics window", 0x0, 0, 0);
}
