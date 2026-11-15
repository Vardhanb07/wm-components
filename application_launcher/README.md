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
rm vapplauncher
```

# how it looks

![launcher](launcher.png)
