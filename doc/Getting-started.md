# Getting started.
## Table of contents.
    * Installing simple-lang & it's enviroment.
    - Test your installation.
    * Getting help.
## Installing simple-lang & it's enviroment.
simple-lang can be installed on any operating system. Be it Windows, Linux or Unix OS* and even Mac. In this section, i'll discuss how we can install in all OS'es.
#### Unix / Linux Os.
To install **simple-lang** on a Unix / Linux OS, grab the latest release of the Linux package from [here](https://github.com/simple-lang/simple/releases). Choose the suitable OS type and download.
Upon downloading, you'll unzip and install. Open your terminal:
```sh
$ unzip simple-lang-release-version.zip & cd simple-lang-release-version
$ cd build & chmod +x Linux-build.sh 
$ sudo ./Linux-build.sh -c -i
# This check and configures your system (-c) and then install (-i)
```
Boom!. simple-lang has been installed and enviroments and modules have also been added.

#### Windows OS.
It's pretty simple-lang to install **simple-lang** on Windows OS. Grab the latest release for windows from [here](https://github.com/simple-lang/simple-lang/releases) and run the *.exe* file. In a few moments, you'll have simple-lang installed.

#### Mac OS.
The steps are pretty similar to the one of the Unix. Grab the latest release for **Mac** from [here](https://github.com/simple-lang/simple-lang/releases). Unzip and run the sh file. Open your console.
```sh
$ unzip simple-lang-release-version.zip & cd simple-lang-release-version
$ cd build & chmod +x simple-langOnlyBuild-mac.sh
$ sudo ./simple-langOnlyBuild-Mac.sh
```

## Testing your installation.
To test your installation, open your Konsole, Terminal or command prompt and test run the *simple-lang* command.
```sh
$ simple
```
You can also test the enviroments built with it, such as the repl ( read-evaluate-print-loop) with the command:
```sh
$ simplerepl
```

### Hello world - Testing the installation.
To see simple-lang in action, we'll write a basic *hello world* in simple-lang. Create a new file in your desired workspace, I'll name mine __hello.sim__. Write this in the file:
```
display "Hello World"
```
Run the file using the simple-lang compiler from your command prompt, terminal or konsole.
```sh
$ simple hello.sim
// Displays "Hello world"
```

## Getting help.
Stuck installing  simple-lang ? Do create a new issue **[here](https://github.com/simple-lang/simple/issues)**. We'll be glad to help.