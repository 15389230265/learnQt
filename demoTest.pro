TEMPLATE = subdirs

#SUBDIRS += \
#    signalConnect \
#    mySignal \
#    handleKey \
#    handleMouse

SUBDIRS += \
    $$PWD/signalConnect/signalConnect.pro \
    $$PWD/mySignal/mySignal.pro \
    $$PWD/handleMouse/handleMouse.pro \
    $$PWD/handleKey/handleKey.pro \
    $$PWD/countDown/countDown.pro \
    $$PWD/componentsCreat/componentsCreat.pro


CONFIG += orderde
