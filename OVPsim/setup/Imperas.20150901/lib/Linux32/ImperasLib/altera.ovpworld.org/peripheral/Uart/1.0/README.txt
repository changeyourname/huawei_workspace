Copyright (c) 2005-2015 Imperas Ltd. All Rights Reserved.

Name
----
    altera.ovpworld.org/peripheral/Uart/1.0


Bus interfaces
--------------
    Slave Port:        sp1

Net connections
---------------
    output: irq
    output: endofpacket
    output: dataavailable
    output: readyfordata
    input : RXD
    input : CTS
    output: TXD
    output: RTS

Formal attributes
-----------------
    integer      : baud
    integer      : dataBits
    integer      : fixedBaud
    enumeration  : parity
        Options: None, Even, Odd
    integer      : stopBits
    integer      : syncRegDepth
    integer      : useCtsRts
    integer      : useEopRegister


