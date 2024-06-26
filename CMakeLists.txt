cmake_minimum_required(VERSION 3.5)

project(game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Personnage.h
        Player.h
        Monstre.h
        Map.h

        Map.h Map.cpp
        Monstre.h Monstre.cpp
        Personnage.h Personnage.cpp
        Player.h Player.cpp
        Game.h Game.cpp
        res.qrc
        Objet.h
        OrbeXP.h
        OrbeXP.cpp
        ChoixNiveauUp.h
        ChoixNiveauUp.cpp
        upgrade.cpp
        upgrade.h




        hpbar.h hpbar.cpp
        xpbar.h xpbar.cpp
        hud.h hud.cpp
        damageindicator.h damageindicator.cpp
        upgrade.h upgrade.cpp
        chunk.h chunk.cpp

        Objet.h
        OrbeXP.h OrbeXP.cpp
        Vague.h Vague.cpp
        Projectile.h Projectile.cpp
        Ghost.h Ghost.cpp
        Sorcier.h Sorcier.cpp
        Cyclope.h Cyclope.cpp
        Boss.h Boss.cpp
        Menu.h Menu.cpp
        Wizard.h Wizard.cpp
        Tank.h Tank.cpp
        Runner.h Runner.cpp


        ObjectOnFloor.h
        ObjectOnFloor.cpp
        upgradeAttaque.h upgradeAttaque.cpp
        upgradeAttaqueDefault.h upgradeAttaqueDefault.cpp
        Fonctions.h Fonctions.cpp
        upgradeAttaqueShield.h upgradeAttaqueShield.cpp
        upgradePlayer.h upgradePlayer.cpp
        upgradePlayerSpeed.h upgradePlayerSpeed.cpp
        upgradeAttaqueSelfHeal.h upgradeAttaqueSelfHeal.cpp
        objectOnFloor.h objectOnFloor.cpp
        bombe.h bombe.cpp
        bouf.h bouf.cpp
        aimant.h aimant.cpp
        upgradeAttaqueArc.h upgradeAttaqueArc.cpp
        upgradeAttaqueHache.h upgradeAttaqueHache.cpp
        upgradePlayerArmor.h upgradePlayerArmor.cpp
        upgradePlayerHealth.h upgradePlayerHealth.cpp
        Fleche.h Fleche.cpp
        upgradeAttaqueBombes.h upgradeAttaqueBombes.cpp

















    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET game APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(game SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.game)
endif()
set_target_properties(game PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()
