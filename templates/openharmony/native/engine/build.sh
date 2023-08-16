#!/bin/bash
buildMode="bc"

enginePath="E:\CocosDashboard_1.2.5\resources\.editors\Creator\2.4.11\CocosCreator.exe"

gamePath="E:\cocos\2.4.11Test"

tempPath="jsb-link"

if [[ "$(echo $buildMode | grep "a")" != "" ]]
then
    echo build $tempPath 
    $enginePath --path $gamePath --build "platform=android"
    echo start clean
    if [ -d "$tempPath" ]; then
    rm -r $tempPath
    fi
    echo start copy
    cp -r "$gamePath\build\\${tempPath}" "${tempPath}"
else
   echo no neeed to build Android jsb-link
fi

if [[ "$(echo $buildMode | grep "b")" != "" ]]
then
    echo build openharmony
    if [ -d "$tempPath" ]; 
    then
        if [ -d "node_modules" ]; 
        then
            echo already install gulp 
        else
            echo install gulp
            npm install
        fi
        gulp default --path $tempPath
    else
        echo pls check jsb_link or jsb_default
        pause
    fi
else
    echo no need to build openHarmony
fi

ver=0
version=$(java -version 2>&1 |awk 'NR==1{gsub(/"/,"");print $3}')
ver=${version%%.*}
v=11

if [[ "$(echo $buildMode | grep "c")" != "" ]]
then
    echo install lib
    if [ -f "./openharmony/entry/lib/cocos-lib-1.0.0.tgz" ];  
        then
        echo remove tgz
        rm "./openharmony/entry/lib/cocos-lib-1.0.0.tgz"
    fi
    cd "./openharmony/entry/lib"
    echo pack tgz
    npm pack
    cd ..
    if [ -d "oh_modules" ];
        then 
        rm -r "oh_modules"
    fi
    ohpm install
    cd ..
    echo build hap begin please waiting...
    sh hvigorw clean assembleHap --no-daemon debuggable=false
    if [ "$ver" -gt "$v" ] ; 
    then
    cd ..
    cp -r "./openharmony/entry/build/default/outputs/default/entry-default-unsigned.hap" "sign_tools"
    cd sign_tools
    java -jar hap-sign-tool.jar sign-profile -mode "localSign" -keyAlias "OpenHarmony Application Profile Release" -keyPwd "123456" -inFile "UnsgnedReleasedProfileTemplate.json" -outFile "myApplication_ohos_Provision.p7b" -keystoreFile "OpenHarmony.p12" -keystorePwd "123456"  -signAlg "SHA256withECDSA" -profileCertFile "OpenHarmonyProfileRelease.pem"
    java -jar hapsigntoolv2.jar sign -mode localjks -privatekey "OpenHarmony Application Release" -inputFile entry-default-unsigned.hap -outputFile entry-release-signed.hap -keystore "OpenHarmony.p12" -keystorepasswd 123456 -keyaliaspasswd 123456 -signAlg SHA256withECDSA -profile "myApplication_ohos_Provision.p7b" -certpath "OpenHarmonyApplication.pem"
    echo -e "\033[33m build success hap in ./sign_tools/entry-release-signed.hap \033[0m"
    echo build success Please click any key to continue...
    read -n 1
    else
    echo  -e "\033[33m Failed to sign. Upgrade the Java version to a version later than 11. \033[0m"
    echo sign fail Please click any key to continue... Upgrade the Java version
    read -n 1
    fi
else
    echo not build hap
fi