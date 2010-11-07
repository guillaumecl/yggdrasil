TEMPLATE = subdirs

SUBDIRS += common game editor qtcore qtdrawgl

qtcore.depends = common
qtdraw.depends = common
game.depends = common
editor.depends = common game
