#!../../bin/linux-x86_64/mdrive_1IOC

#- SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change mdrive_1IOC to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/mdrive_1IOC.dbd"
mdrive_1IOC_registerRecordDeviceDriver pdbbase

epicsEnvSet ("STREAM_PROTOCOL_PATH", "${TOP}/db")
epicsEnvSet ("PORT_mdrive_x", "ip_x")
epicsEnvSet ("ip_address_x", "100.100.0.23:503")
#epicsEnvSet ("PORT_mdrive_y", "ip_y")
#epicsEnvSet ("PORT_mdrive_z", "ip_z")

#Z Axis
#drvAsynIPPortConfigure($(PORT_mdrive_z), "100.100.0.21:503")
#asynOctetSetInputEos($(PORT_mdrive_z),0,"\n\r")
#asynOctetSetOutputEos($(PORT_mdrive_z),0,"\n\r")
#
#asynSetTraceMask($(PORT_mdrive_z),-1,0x9);
#asynSetTraceIOMask($(PORT_mdrive_z),-1,0x2)
#
#Y Axis
#drvAsynIPPortConfigure($(PORT_mdrive_y), "100.100.0.22:503")
#asynOctetSetInputEos($(PORT_mdrive_y),0,"\n\r")
#asynOctetSetOutputEos($(PORT_mdrive_y),0,"\n\r")
#
#asynSetTraceMask($(PORT_mdrive_y),-1,0x9);
#asynSetTraceIOMask($(PORT_mdrive_y),-1,0x2)
#
#X Axis
#drvAsynIPPortConfigure($(PORT_mdrive_x), "100.100.0.23:503")
drvAsynIPPortConfigure($(PORT_mdrive_x), $(ip_address_x))
#asynOctetSetInputEos($(PORT_mdrive_x),0,"\r\n")
#asynOctetSetInputEos($(PORT_mdrive_x),0,"\n")
#asynOctetSetOutputEos($(PORT_mdrive_x),0,"\r\n")
#asynOctetSetOutputEos($(PORT_mdrive_x),0,"\n")

asynSetTraceMask($(PORT_mdrive_x),-1,0x9);
asynSetTraceIOMask($(PORT_mdrive_x),-1,0x2)

### Register all support components
#dbLoadDatabase "dbd/mdrive_1IOC.dbd"
#mdrive_1IOC_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/mdrive_1IOC.db","user=xlabsrv2")

dbLoadTemplate("db/mdrive_1IOC.val")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=xlabsrv2"
