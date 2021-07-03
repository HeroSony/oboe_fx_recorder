# Android FXLab & Recording

## Credits to
- [Oboe FXLab](https://github.com/google/oboe/tree/master/apps/fxlab)
- [Oboe Recorder](https://github.com/sheraz-nadeem/oboe_recorder_sample)

## Pre-build
Link Oboe path directory in CmakeLists.txt
```
set (OBOE_DIR D:\\Android\\oboe)
```

Add [libsndfile](https://github.com/libsndfile/libsndfile) library
```
set(LIB_SND_FILE_DIR D:\\Android\\libsndfile)
add_subdirectory(${LIB_SND_FILE_DIR} ./sndfile)
include_directories(${LIB_SND_FILE_DIR}/src)
```

## Export directory file
Export file will be saved to Music directory.

## Preview
![photo_2021-07-03_18-38-12](https://user-images.githubusercontent.com/4160246/124352984-e6473f00-dc2d-11eb-910c-60900c4c90be.jpg)
