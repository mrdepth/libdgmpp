# libdgmpp 

This is a fork of [libdgmpp](https://github.com/mrdepth/libdgmpp) with additional support and modification for Java/Android.

For any C/C++ details, please refer to the above project.

-------------------------------------------------------------------------------

## Build

- You will need a relatively recent C++17 compiler and / or Android NDK.

- You will need [swig3+](https://swigt.org/) to generate Java classes from swig files.

After cloning this project, you should re-generate the java files using Swig:

```
cd ./swig
./build.sh
```

(You may have a look at the build.sh file before doing so)


### Android Gradle

Add the following to your gradle build file to have the NDK build the library with your application.

Assuming the libdgmpp library code is in './libdgmpp':

```
android {
    sourceSets {
        main {
            java {
                srcDirs += './libdgmpp/java-wrapper/src/'
            }
        }
    }

    externalNativeBuild {
        ndkBuild {
            path './libdgmpp/android/src/main/Android.mk'
        }
    }
}

```

You can also build the library independently, see the Android directory for details.

## References

[Dogma++](https://github.com/mrdepth/libdgmpp)

Thanks to [Artem Shimanski](https://github.com/mrdepth) for doing all the hard work.
