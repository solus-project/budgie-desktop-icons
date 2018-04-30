# Build our main dummy executable

main_sources = [
    'desktop-manager.c',
    'desktop-view.c',
    'desktop-window.c',
    'main.c',
]

executable(
    'budgie-desktop-icons',
    sources: main_sources,
    dependencies: [
        dep_gtk3,
    ],
    install: true,
)
