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
    icmCLParserAdd(parser, "uart0console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart0console, "enable console on UART0", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart1console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart1console, "enable console on UART1", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart2console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart2console, "enable console on UART2", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart3console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart3console, "enable console on UART3", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart4console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart4console, "enable console on UART4", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart5console", 0 , 0, 0                   , ICM_AT_BOOLVAL      , &options.uart5console, "enable console on UART5", 0x0, 0, 0);
}
