#!/bin/bash
#
# Synopsis: Install Apple 2 cc65 Utilities
#
# Description:
#   - Add the Apple 2 cc65 utilities to the path,
#   - Write the cc65 environment variables to: cc65.sh
#   - Set bash to automatically set them via the profile config: ~/.bash_profile
#
# These command are then available:
#    src2dsk foo
#    dsk     foo
#    a2ls    foo.dsk
#
# Install via:
#
#    ./install.sh

BASH_CONFIG=~/.bash_profile
CC65_FILENAME=cc65.sh
CC65_CONFIG=$(pwd)/${CC65_FILENAME}


# Assume we are installing from cc65/apple2/
# We need the fully qualified path (current working directory)
# which will become the base root CC65_HOME
cd ..
CC65=$(pwd)

if [[ ! -e bin/ca65 ]]; then
    cd -
    echo "ERROR: Couldn't get root directory of cc65."
    echo "Please cd to the directory of this install script and re-run."
    exit 1
fi

if [[ -z "${CC65_HOME}" ]]; then
    echo "Saving cc65 environment variables to:"
    echo "--> ${CC65_CONFIG}"
    rm -f                                               ${CC65_CONFIG}
    echo "#!/bin/bash"                               >> ${CC65_CONFIG}
    echo "#"                                         >> ${CC65_CONFIG}
    echo "# Usage: source ${CC65_FILENAME}"          >> ${CC65_CONFIG}
    echo "#"                                         >> ${CC65_CONFIG}
    echo "# Apple 2 cc65 Toolchain"                  >> ${CC65_CONFIG}
    echo "    PATH=\${PATH}:${CC65}/apple2"          >> ${CC65_CONFIG}
    echo "    export PATH"                           >> ${CC65_CONFIG}
    echo "    CC65_HOME=${CC65}"                     >> ${CC65_CONFIG}
    echo "    export CC65_HOME"                      >> ${CC65_CONFIG}
    chmod u+x                                           ${CC65_CONFIG}
    echo ""

    echo "Installing Bash environment variables to profile:"
    echo "--> '${BASH_CONFIG}'"

    echo ""                                          >> ${BASH_CONFIG}
    echo "# Installed via ${CC65}/apple2/install.sh" >> ${BASH_CONFIG}
    echo "source ${CC65_CONFIG}"                     >> ${BASH_CONFIG}
    echo ""                                          >> ${BASH_CONFIG}

    echo "==> Done!"
    echo ""
    if [[ -z "${JACE_HOME}" ]]; then
        echo "NOTE: 'dsk' uses the JACE_HOME environment to locate the Jace emulator"
        echo "      You may wish to set that"
        echo ""
    fi

    echo "NOTE: You will need to either restart your shell,"
    echo "      or manually set the environment variables via:"
    echo ""
    echo "          source ${CC65_FILENAME}"
    echo ""
    echo "      The next time you login setting the cc65 env. vars."
    echo "      will be done automatically."

    # OSX - modify parent shell environment variables
    #Doesn't work on 10.11
    #gdb -nx -p $$ --batch -ex 'call setenv("CC65_HOME", "${CC65}")' >& /dev/null
else
    echo "Apple 2 cc65 utilties using 'CC65_HOME':"
    echo "--> ${CC65_HOME}"
fi

cd - >& /dev/null

