TEMPLATE = subdirs

SUBDIRS += \
    cli_app \
    hls_lib \
    ui_app

cli_app.depends = hls_lib
ui_app.depends = hls_lib
