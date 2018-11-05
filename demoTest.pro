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
    $$PWD/componentsCreat/componentsCreat.pro \
    $$PWD/itemPositioner/itemPositioner.pro \
    $$PWD/musicList/musicList.pro \
    $$PWD/personinfo/personinfo.pro \
    $$PWD/scores/scores.pro \
    $$PWD/citytree/citytree.pro


CONFIG += orderde
