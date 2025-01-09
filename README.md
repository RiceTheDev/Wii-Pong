
# Wii Pong

WiiPong is a clone of [Pong](https://pt.wikipedia.org/wiki/Pong) for the [Nintendo Wii](https://pt.wikipedia.org/wiki/Wii).


You need 2 controllers to play!

## Demonstration
**Captured on a real Wii**

![](https://raw.githubusercontent.com/RiceTheDev/Wii-Pong/refs/heads/main/readme/Gameplay.gif)
## Running

You can use the [Homebrew Channel](https://github.com/fail0verflow/hbc) by FailedOverfl0w To run the game,
 You just need to create a folder called apps, create a directory for the game, and put the meta.xml and the logo.png with the boot.dol (rename the WiiPong to boot.dol).
  
Example: 
```
[USB:/ or SD:/]
└── apps
    └── pongwii
        ├── meta.xml (on the release page)
        ├── boot.dol (on the release page)
        └── logo.png (on the release page)

``` 



A compiled build of the game can be found in the [Releases](https://github.com/RiceTheDev/Wii-Pong/releases) page
    
## Building

Clone the repository

```bash
  git clone https://github.com/RiceTheDev/Wii-Pong/
```

Enter the directory

```bash
  cd Wii-Pong
```

Install the needed dependencies

```bash
  (dkp-)pacman --sync --needed --noconfirm libfat-ogc ppc-libpng ppc-freetype ppc-libjpeg-turbo zlib wii-dev
```

Build the game

```bash
  make
```


## FAQ

#### "I get X error when I compile!"

If you are getting errors when compiling, you can contact me on discord, my user is: [@raic.e](https://discord.com/users/570693486500773888), I will try to help.

#### How can I help in the project?

You can help by opening a pull request with updates in the game.
Any help is accepted.

#### The project is already done?

No, some features are missing, i'm doing this project in my free time, it's a very basic project, here are a list of things I'm planning to add:
* Update the sprites
* Add a solo mode (CPU)


## Credits

- [@RiceTheDev (Main Developer)](https://www.github.com/RiceTheDev)
- [@GRRLIB (For the Lib)](https://github.com/GRRLIB/GRRLIB/)
- [@PolyMars (For the Makefile)](https://github.com/PolyMarsDev/Terri-Fried/blob/master/wii/Makefile)

