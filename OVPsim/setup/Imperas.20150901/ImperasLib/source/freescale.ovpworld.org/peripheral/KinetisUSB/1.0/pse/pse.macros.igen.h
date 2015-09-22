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

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H
// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.
// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
    #error BPORT1 is undefined.It needs to be set to the port base address
#endif
#define BPORT1_AB_PERID    (BPORT1 + 0x0)

#define BPORT1_AB_PERID_ID   0x3f
#define BPORT1_AB_IDCOMP    (BPORT1 + 0x4)

#define BPORT1_AB_IDCOMP_NID   0x3f
#define BPORT1_AB_REV    (BPORT1 + 0x8)

#define BPORT1_AB_REV_REV   0xff
#define BPORT1_AB_ADDINFO    (BPORT1 + 0xc)

#define BPORT1_AB_ADDINFO_IEHOST   0x1
#define BPORT1_AB_ADDINFO_IRQNUM   (0x1f << 3)
#define BPORT1_AB_OTGISTAT    (BPORT1 + 0x10)

#define BPORT1_AB_OTGISTAT_AVBUSCHG   0x1
#define BPORT1_AB_OTGISTAT_B_SESS_CHG   (0x1 << 2)
#define BPORT1_AB_OTGISTAT_IDCHG   (0x1 << 7)
#define BPORT1_AB_OTGISTAT_LINE_STATE_CHG   (0x1 << 5)
#define BPORT1_AB_OTGISTAT_ONEMSEC   (0x1 << 6)
#define BPORT1_AB_OTGISTAT_SESSVLDCHG   (0x1 << 3)
#define BPORT1_AB_OTGICR    (BPORT1 + 0x14)

#define BPORT1_AB_OTGICR_AVBUSEN   0x1
#define BPORT1_AB_OTGICR_BSESSEN   (0x1 << 2)
#define BPORT1_AB_OTGICR_IDEN   (0x1 << 7)
#define BPORT1_AB_OTGICR_LINESTATEEN   (0x1 << 5)
#define BPORT1_AB_OTGICR_ONEMSECEN   (0x1 << 6)
#define BPORT1_AB_OTGICR_SESSVLDEN   (0x1 << 3)
#define BPORT1_AB_OTGSTAT    (BPORT1 + 0x18)

#define BPORT1_AB_OTGSTAT_AVBUSVLD   0x1
#define BPORT1_AB_OTGSTAT_BSESSEND   (0x1 << 2)
#define BPORT1_AB_OTGSTAT_ID   (0x1 << 7)
#define BPORT1_AB_OTGSTAT_LINESTATESTABLE   (0x1 << 5)
#define BPORT1_AB_OTGSTAT_ONEMSECEN   (0x1 << 6)
#define BPORT1_AB_OTGSTAT_SESS_VLD   (0x1 << 3)
#define BPORT1_AB_OTGCTL    (BPORT1 + 0x1c)

#define BPORT1_AB_OTGCTL_DMLOW   (0x1 << 4)
#define BPORT1_AB_OTGCTL_DPHIGH   (0x1 << 7)
#define BPORT1_AB_OTGCTL_DPLOW   (0x1 << 5)
#define BPORT1_AB_OTGCTL_OTGEN   (0x1 << 2)
#define BPORT1_AB_ISTAT    (BPORT1 + 0x80)

#define BPORT1_AB_ISTAT_ATTACH   (0x1 << 6)
#define BPORT1_AB_ISTAT_ERROR   (0x1 << 1)
#define BPORT1_AB_ISTAT_RESUME   (0x1 << 5)
#define BPORT1_AB_ISTAT_SLEEP   (0x1 << 4)
#define BPORT1_AB_ISTAT_SOFTOK   (0x1 << 2)
#define BPORT1_AB_ISTAT_STALL   (0x1 << 7)
#define BPORT1_AB_ISTAT_TOKDNE   (0x1 << 3)
#define BPORT1_AB_ISTAT_USBRST   0x1
#define BPORT1_AB_INTEN    (BPORT1 + 0x84)

#define BPORT1_AB_INTEN_ATTACHEN   (0x1 << 6)
#define BPORT1_AB_INTEN_ERROREN   (0x1 << 1)
#define BPORT1_AB_INTEN_RESUMEEN   (0x1 << 5)
#define BPORT1_AB_INTEN_SLEEPEN   (0x1 << 4)
#define BPORT1_AB_INTEN_SOFTOKEN   (0x1 << 2)
#define BPORT1_AB_INTEN_STALLEN   (0x1 << 7)
#define BPORT1_AB_INTEN_TOKDNEEN   (0x1 << 3)
#define BPORT1_AB_INTEN_USBRSTEN   0x1
#define BPORT1_AB_ERRSTAT    (BPORT1 + 0x88)

#define BPORT1_AB_ERRSTAT_BTOERR   (0x1 << 4)
#define BPORT1_AB_ERRSTAT_BTSERR   (0x1 << 7)
#define BPORT1_AB_ERRSTAT_CRC16   (0x1 << 2)
#define BPORT1_AB_ERRSTAT_CRC5EOF   (0x1 << 1)
#define BPORT1_AB_ERRSTAT_DFN8   (0x1 << 3)
#define BPORT1_AB_ERRSTAT_DMAERR   (0x1 << 5)
#define BPORT1_AB_ERRSTAT_PIDERR   0x1
#define BPORT1_AB_ERREN    (BPORT1 + 0x8c)

#define BPORT1_AB_ERREN_BTOERREN   (0x1 << 4)
#define BPORT1_AB_ERREN_BTSERREN   (0x1 << 7)
#define BPORT1_AB_ERREN_CRC16EN   (0x1 << 2)
#define BPORT1_AB_ERREN_CRC5EOFEN   (0x1 << 1)
#define BPORT1_AB_ERREN_DFN8EN   (0x1 << 3)
#define BPORT1_AB_ERREN_DMAERREN   (0x1 << 5)
#define BPORT1_AB_ERREN_PIDERREN   0x1
#define BPORT1_AB_STAT    (BPORT1 + 0x90)

#define BPORT1_AB_STAT_ENDP   (0xf << 4)
#define BPORT1_AB_STAT_ODD   (0x1 << 2)
#define BPORT1_AB_STAT_TX   (0x1 << 3)
#define BPORT1_AB_CTL    (BPORT1 + 0x94)

#define BPORT1_AB_CTL_HOSTMODEEN   (0x1 << 3)
#define BPORT1_AB_CTL_JSTATE   (0x1 << 7)
#define BPORT1_AB_CTL_ODDRST   (0x1 << 1)
#define BPORT1_AB_CTL_RESET   (0x1 << 4)
#define BPORT1_AB_CTL_RESUME   (0x1 << 2)
#define BPORT1_AB_CTL_SE0   (0x1 << 6)
#define BPORT1_AB_CTL_TXSUSPENDTOKENBUSY   (0x1 << 5)
#define BPORT1_AB_CTL_USBENSOFEN   0x1
#define BPORT1_AB_ADDR    (BPORT1 + 0x98)

#define BPORT1_AB_ADDR_ADDR   0x7f
#define BPORT1_AB_ADDR_LSEN   (0x1 << 7)
#define BPORT1_AB_BDTPAGE1    (BPORT1 + 0x9c)

#define BPORT1_AB_BDTPAGE1_BDTBA   (0x7f << 1)
#define BPORT1_AB_FRMNUML    (BPORT1 + 0xa0)

#define BPORT1_AB_FRMNUML_FRM   0xff
#define BPORT1_AB_FRMNUMH    (BPORT1 + 0xa4)

#define BPORT1_AB_FRMNUMH_FRM   0x7
#define BPORT1_AB_TOKEN    (BPORT1 + 0xa8)

#define BPORT1_AB_TOKEN_TOKENENDPT   0xf
#define BPORT1_AB_TOKEN_TOKENPID   (0xf << 4)
#define BPORT1_AB_SOFTHLD    (BPORT1 + 0xac)

#define BPORT1_AB_SOFTHLD_CNT   0xff
#define BPORT1_AB_BDTPAGE2    (BPORT1 + 0xb0)

#define BPORT1_AB_BDTPAGE2_BDTBA   0xff
#define BPORT1_AB_BDTPAGE3    (BPORT1 + 0xb4)

#define BPORT1_AB_BDTPAGE3_BDTBA   0xff
#define BPORT1_AB_ENDPOINT0    (BPORT1 + 0xc0)

#define BPORT1_AB_ENDPOINT0_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT0_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT0_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT0_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT0_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT0_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT0_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT1    (BPORT1 + 0xc4)

#define BPORT1_AB_ENDPOINT1_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT1_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT1_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT1_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT1_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT1_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT1_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT2    (BPORT1 + 0xc8)

#define BPORT1_AB_ENDPOINT2_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT2_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT2_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT2_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT2_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT2_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT2_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT3    (BPORT1 + 0xcc)

#define BPORT1_AB_ENDPOINT3_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT3_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT3_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT3_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT3_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT3_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT3_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT4    (BPORT1 + 0xd0)

#define BPORT1_AB_ENDPOINT4_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT4_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT4_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT4_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT4_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT4_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT4_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT5    (BPORT1 + 0xd4)

#define BPORT1_AB_ENDPOINT5_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT5_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT5_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT5_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT5_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT5_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT5_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT6    (BPORT1 + 0xd8)

#define BPORT1_AB_ENDPOINT6_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT6_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT6_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT6_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT6_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT6_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT6_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT7    (BPORT1 + 0xdc)

#define BPORT1_AB_ENDPOINT7_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT7_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT7_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT7_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT7_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT7_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT7_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT8    (BPORT1 + 0xe0)

#define BPORT1_AB_ENDPOINT8_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT8_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT8_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT8_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT8_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT8_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT8_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT9    (BPORT1 + 0xe4)

#define BPORT1_AB_ENDPOINT9_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT9_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT9_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT9_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT9_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT9_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT9_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT10    (BPORT1 + 0xe8)

#define BPORT1_AB_ENDPOINT10_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT10_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT10_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT10_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT10_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT10_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT10_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT11    (BPORT1 + 0xec)

#define BPORT1_AB_ENDPOINT11_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT11_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT11_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT11_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT11_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT11_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT11_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT12    (BPORT1 + 0xf0)

#define BPORT1_AB_ENDPOINT12_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT12_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT12_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT12_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT12_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT12_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT12_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT13    (BPORT1 + 0xf4)

#define BPORT1_AB_ENDPOINT13_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT13_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT13_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT13_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT13_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT13_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT13_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT14    (BPORT1 + 0xf8)

#define BPORT1_AB_ENDPOINT14_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT14_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT14_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT14_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT14_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT14_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT14_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT15    (BPORT1 + 0xfc)

#define BPORT1_AB_ENDPOINT15_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT15_EPHSHK   0x1
#define BPORT1_AB_ENDPOINT15_EPRXEN   (0x1 << 3)
#define BPORT1_AB_ENDPOINT15_EPSTALL   (0x1 << 1)
#define BPORT1_AB_ENDPOINT15_EPTXEN   (0x1 << 2)
#define BPORT1_AB_ENDPOINT15_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT15_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_USBCTRL    (BPORT1 + 0x100)

#define BPORT1_AB_USBCTRL_PDE   (0x1 << 6)
#define BPORT1_AB_USBCTRL_SUSP   (0x1 << 7)
#define BPORT1_AB_OBSERVE    (BPORT1 + 0x104)

#define BPORT1_AB_OBSERVE_DMPD   (0x1 << 4)
#define BPORT1_AB_OBSERVE_DPPD   (0x1 << 6)
#define BPORT1_AB_OBSERVE_DPPU   (0x1 << 7)
#define BPORT1_AB_CONTROL    (BPORT1 + 0x108)

#define BPORT1_AB_CONTROL_DPPULLUPNONOTG   (0x1 << 4)
#define BPORT1_AB_USBTRC0    (BPORT1 + 0x10c)

#define BPORT1_AB_USBTRC0_SYNC_DET   (0x1 << 1)
#define BPORT1_AB_USBTRC0_USB_RESUME_INT   0x1
#define BPORT1_AB_USBTRC0_USBRESET   (0x1 << 7)
#define BPORT1_AB_USBTRC0_USBRESMEN   (0x1 << 5)
#define BPORT1_AB_USBFRMADJUST    (BPORT1 + 0x114)

#define BPORT1_AB_USBFRMADJUST_ADJ   0xff


#endif
