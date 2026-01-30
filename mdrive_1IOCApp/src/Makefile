# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS

TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = mdrive_1IOC
# mdrive_1IOC.dbd will be created and installed
DBD += mdrive_1IOC.dbd

# mdrive_1IOC.dbd will be made up from these files:
mdrive_1IOC_DBD += base.dbd

# Include dbd files from all support applications:
#mdrive_1IOC_DBD += xxx.dbd
mdrive_1IOC_DBD += asyn.dbd
mdrive_1IOC_DBD += drvAsynIPPort.dbd
mdrive_1IOC_DBD += stream-base.dbd
mdrive_1IOC_DBD += calc.dbd

# Add all the support libraries needed by this IOC
#mdrive_1IOC_LIBS += xxx
mdrive_1IOC_LIBS += stream
mdrive_1IOC_LIBS += asyn
mdrive_1IOC_LIBS += calc

# mdrive_1IOC_registerRecordDeviceDriver.cpp derives from mdrive_1IOC.dbd
mdrive_1IOC_SRCS += mdrive_1IOC_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
mdrive_1IOC_SRCS_DEFAULT += mdrive_1IOCMain.cpp
mdrive_1IOC_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#mdrive_1IOC_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

ifdef EPICS_QSRV_MAJOR_VERSION
    mdrive_1IOC_LIBS += qsrv
    mdrive_1IOC_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    mdrive_1IOC_DBD += PVAServerRegister.dbd
    mdrive_1IOC_DBD += qsrv.dbd
endif

# Finally link to the EPICS Base libraries
mdrive_1IOC_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE


