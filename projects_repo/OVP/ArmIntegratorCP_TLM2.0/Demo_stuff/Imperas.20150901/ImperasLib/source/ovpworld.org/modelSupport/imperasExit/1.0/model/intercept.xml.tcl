#
# Copyright (c) 2005-2015 Imperas Software Ltd. All Rights Reserved.
#
# THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
# OF IMPERAS SOFTWARE LTD. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
# EXCEPT AS MAY BE PROVIDED FOR IN A WRITTEN AGREEMENT WITH IMPERAS SOFTWARE LTD.
#
# NAME : imperasExit

imodelnewsemihostlibrary  \
    -name imperasExit  \
    -vendor ovpworld.org  \
    -library modelSupport  \
    -version 1.0  \
    -releasestatus ovp \
    -visibility    visible

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Finish the simulation when symbol 'exit' is executed."

  imodeladdsupportedprocessor  \
                -name any 

