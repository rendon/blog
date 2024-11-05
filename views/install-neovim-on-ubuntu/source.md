---
tags:
    - productivity
    - vim
    - linux
    - post
created: 2024-11-05
updated: 2024-11-05
---

# Install Neovim on Ubuntu

In this short tutorial, I’ll show you how to install Neovim on Ubuntu in three different ways 1) from a precompiled binary, 2) using Ubuntu’s package manager and 3) from source code.

<iframe width="560" height="315" src="https://www.youtube.com/embed/XDlCIYJUgjU?si=VhLdtnI0Tr8W4oDJ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


## Download the binary
```sh
wget -c https://github.com/neovim/neovim/releases/latest/download/nvim-linux64.tar.gz
tar xvf nvim-linux64.tar.gz
sudo mv nvim-linux64 /usr/local/nvim
cd /usr/local/bin
sudo ln -svf ../nvim/bin/nvim nvim
```

Now, you should be able to run `nvim` on the command line.

## Use the package manager
Neovim has been in the Ubuntu's package archive for a while, so you can simply use the following command:

```sh
sudo apt install neovim
```

While this method is the easiest, it might not get you the latest version.

## Build from source code
By building from the source code, you can get the latest version available, but it requires installing a few dependencies and running a few commands.

```sh
sudo apt-get install ninja-build gettext cmake unzip curl
git clone https://github.com/neovim/neovim
cd neovim && git checkout stable
make CMAKE_BUILD_TYPE=RelWithDebInfo
sudo make install
```

There you are, if everything went well, you should have the latest (though stable) version of Neovim.

For other platforms, see the official documentation.
