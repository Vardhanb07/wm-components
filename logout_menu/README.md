# installation

```bash 
meson setup build 
meson configure build -Dbuildtype=release -Dprefix=~/.local
meson install -C build
```

This will install binary in `~/.local/bin`

# uninstallation

```bash
cd ~/.local/bin
rm vlogout
```

# how it looks

![logout-menu](logout-menu.png)

# deps
- gtkmm(gtk4)
- gtk4-layer-shell

# note
Installation requires deps
