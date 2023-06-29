QT       += core gui
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ./code/sources \
                ./code/headers \
                ./test/sources \
                ./test/headers \
                ../../ \


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/sources/main.cpp \
    code/sources/des.cpp \
    code/sources/rsa.cpp \
    code/sources/ecc.cpp \
    code/sources/large.cpp \
    code/sources/bool_algeabra.cpp \
    code/sources/prime_arithmetic.cpp \
    code/sources/galois.cpp \
    code/sources/utils.cpp \
    code/sources/miller-rabin-gmp.cpp\
    test/sources/testsuite.cpp \
    test/sources/des_test.cpp \
    test/sources/rsa_test.cpp \
    test/sources/ecc_test.cpp \
    test/sources/large_test.cpp \
    test/sources/bool_algeabra_test.cpp \
    test/sources/prime_arithmetic_test.cpp \
    test/sources/galois_test.cpp \

HEADERS += \
    code/headers/des.h \
    code/headers/rsa.h \
    code/headers/ecc.h \
    code/headers/large.h \
    code/headers/bool_algeabra.h \
    code/headers/prime_arithmetic.h \
    code/headers/galois.h \
    code/headers/utils.h \
    code/headers/miller-rabin-gmp.h\
    test/headers/testsuite.hpp \
    test/headers/des_test.h \
    test/headers/rsa_test.h \
    test/headers/ecc_test.h \
    test/headers/large_test.h \
    test/headers/bool_algeabra_test.h \
    test/headers/prime_arithmetic_test.h \
    test/headers/galois_test.h \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
