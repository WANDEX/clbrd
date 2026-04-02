[![CI/CD cmake-multi-platform][cicd_cmake_mp_bdg]][cicd_cmake_mp_url]

# wndx::clbrd

> [!IMPORTANT]
> WIP -- Expected feature set is not yet implemented!

The server is a GUI application that manages connected clients (devices) and displays their data in tables.\
The client is a console application that emulates a device, transmitting data of various types and lengths to the server (network metrics, device status, logs).

## Requirements
- git submodule: [wndx::sane](https://github.com/WANDEX/wndx_sane)
- lib Qt >= 6.5.2: comes with amazing IDE [qtcreator](https://github.com/qt-creator/qt-creator)
- tests require: [GoogleTest (gtest)](https://github.com/google/googletest) (CMake fetch content at configure time)

## Build
```sh
$ git clone --recurse-submodules git@github.com:WANDEX/clbrd.git && cd clbrd
$ cmake -E make_directory build
$ cmake -S . -B build
$ cmake --build build
```

<details><summary>
How to install specific Qt version using aqtinstall
</summary>

#### Instruction for systems origin from UNIX or Win OS w/ **MINGW64:git-bash** shell
Install pip with python from the official website or using platform default package manager\
https://www.python.org/downloads/

##### Install [aqtinstall](https://github.com/miurahr/aqtinstall)
```sh
$ pip install -U pip
$ pip install aqtinstall
```

##### See available architectures & aqt ref
local [./.aqt/settings.ini](./.aqt/settings.ini) &
local [./.aqt/set_aqt_env.sh](./.aqt/set_aqt_env.sh) &
online [settings.ini](https://aqtinstall.readthedocs.io/en/latest/configuration.html)

###### May be needed to add under group blocks: aqt, requests
`INSECURE_NOT_FOR_PRODUCTION_ignore_hash: True` [-> look into local settings.ini](./.aqt/settings.ini)

```sh
$ aqt -c ./.aqt/settings.ini list-qt windows desktop --arch 6.5.2
```
`>>> win64_mingw win64_msvc2019_64 win64_msvc2019_arm64 wasm_singlethread wasm_multithread`
##### cd into dir which will be new installation root of newly installed Qt and required modules
```sh
$ aqt -c ./.aqt/settings.ini install-qt windows desktop 6.5.2 win64_msvc2019_64 -m qtcharts
```
</details>

## Style
For the unified visual style between Qt & GTK applications you can use the default GTK theme, dark variant\
or something similar. `export QT_STYLE_OVERRIDE=Adwaita-Dark`
[[style]](https://wiki.archlinux.org/title/Dark_mode_switching)
[adwaita-qt](https://github.com/FedoraQt/adwaita-qt)

## License
[LGPL-3.0-or-later](https://choosealicense.com/licenses/lgpl-3.0/)

[cicd_cmake_mp_url]: https://github.com/WANDEX/clbrd/actions/workflows/cicd_cmake_multi_platform.yml
[cicd_cmake_mp_bdg]: https://github.com/WANDEX/clbrd/actions/workflows/cicd_cmake_multi_platform.yml/badge.svg?event=push
